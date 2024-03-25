/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/25 10:15:23 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	builtin_child(t_pipex *comm, t_data *data)
{
	io_redir(comm, data);
	return (do_builtin(comm, data));
}

char	*path_execve(char *command, char **envp)
{
	int		i;
	char	*tmp_path;
	char	*possible_path;
	char	**all_paths;

	i = find_in_env(envp, "PATH=");
	if (i == -1)
		return (free(command), NULL);
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i] != NULL)
	{
		tmp_path = ft_strjoin("/", command);
		possible_path = ft_strjoin(all_paths[i], tmp_path);
		free(tmp_path);
		if (access(possible_path, F_OK) == 0)
			return (free_matrix(&all_paths), free(command), possible_path);
		else
			free(possible_path);
		i++;
	}
	free(command);
	free_matrix(&all_paths);
	return (NULL);
}

void	child(t_pipex *comm, t_data *data)
{
	if (data->in_pipe == TRUE && data->cmd_nbr == 0)
		close(data->fd[0][0]);
	else if (data->in_pipe == TRUE
		&& data->cmd_nbr > 0 && data->cmd_nbr < data->pipe_nbr)
		close(data->fd[data->cmd_nbr][0]);
	io_redir(comm, data);
	if (ft_isbuiltin(comm->cmd[0]) == TRUE)
		builtin_child(comm, data);
	execve(comm->path, comm->cmd, data->envp);
	free_matrix(&comm->cmd);
	free_close(&data, 127);
}

t_type	find_prev_cmd_type(t_input *input)
{
	t_input	*tmp;

	tmp = input->prev;
	if (tmp == NULL)
		return (FINISH);
	while (tmp && tmp->type != COMMAND && tmp->type != BUILT_IN)
		tmp = tmp->prev;
	return (tmp->type);
}

int	pipex(t_pipex *comm, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (ft_isbuiltin(comm->cmd[0]) == TRUE)
		return (builtin_child(comm, data));
	pid = fork();
	if (pid == -1)
		ft_error("fork", FORK, 124, NULL);
	if (pid == 0)
		child(comm, data);
	else
	{
		waitpid(pid, &status, 0);
		if (data->in_pipe == TRUE && data->cmd_nbr <= data->pipe_nbr)
			close(data->fd[data->cmd_nbr][1]);
		if (data->cmd_nbr > 0 && data->cmd_nbr <= data->pipe_nbr)
			close(data->fd[data->cmd_nbr - 1][0]);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
