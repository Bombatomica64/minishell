/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/11 12:46:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	is_cd(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (TRUE);
	return (FALSE);
}

char	*path_execve(char *command, char **envp)
{
	int		i;
	char	*tmp_path;
	char	*possible_path;
	char	**all_paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
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

void	child(t_pipex *pipex, t_data *data)
{
	fprintf(stderr, "pipex->fd_in: %d\n", pipex->fd_in);
	fprintf(stderr, "pipex->fd_out: %d\n", pipex->fd_out);
	if (data->in_pipe == TRUE && data->cmd_nbr == 0)
		close(data->fd[0][0]);
	else if (data->in_pipe == TRUE
		&& data->cmd_nbr > 0 && data->cmd_nbr < data->pipe_nbr - 1)
		close(data->fd[data->cmd_nbr][0]);
	if (pipex->fd_out != STDOUT_FILENO)
	{
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			ft_error("child", DUP, 13, data);
	}
	if (pipex->fd_in != STDIN_FILENO)
	{
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			ft_error("child_stdin", DUP, 13, data);
	}
	if (ft_isbuiltin(pipex->cmd[0]) == TRUE)
		do_builtin(pipex->cmd, data);
	execve(pipex->path, pipex->cmd, data->envp);
	free_array_matrix(data->fd, data->pipe_nbr);
	free_matrix(&pipex->cmd);
	ft_error("pipex->cmd[0]", EXECVE, 126, data);
}

int	pipex(t_pipex *pipex, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (is_cd(pipex->cmd[0]) == TRUE)
		return (ft_cd(pipex->cmd, data));
	if (is_exit(pipex->cmd[0]) == TRUE)
		return (ft_exit(pipex->cmd, data));
	pid = fork();
	if (pid == -1)
		ft_error("executor", FORK, 124, NULL);
	if (pid == 0)
		child(pipex, data);
	else
	{
		wait(&status);
		printf("status: %d\n", status);
		if (data->in_pipe == TRUE && data->cmd_nbr < data->pipe_nbr)
			close(data->fd[ft_max(data->cmd_nbr - 1, 0)][1]);
		// if (data->cmd_nbr < data->pipe_nbr)
		// 	if (dup2(data->fd[ft_max(data->cmd_nbr - 1, 0)][0], STDIN_FILENO) == -1)
		// 		perror("sesso dup2");
		// if (data->cmd_nbr == data->pipe_nbr && data->pipe_nbr > 1)
		// 	close(data->fd[data->pipe_nbr - 1][0]);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
