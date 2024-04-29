/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:50:05 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/29 12:41:49 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	builtin_child(t_pipex *comm, t_data *data)
{
	io_redir(comm, data);
	return (do_builtin(comm, data));
}

char	*path_execve(char *command, char **envp, t_data *data)
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
	(void)data;
	free(command);
	free_matrix(&all_paths);
	return (NULL);
}

void	free_childsrcs(t_data *data, t_pipex **origin, pid_t **pid, int flag)
{
	int	i;

	i = data->pipe_nbr;
	while (i >= 0)
		free_matrix(&(*origin)[i--].cmd);
	free(*origin);
	free(*pid);
	free_close(&data, flag);
}

void	child(t_pipex *comm, t_data *data, t_pipex **origin, pid_t **pid)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (data->in_pipe == TRUE && data->cmd_nbr == 0)
		close(data->fd[0][0]);
	else if (data->in_pipe == TRUE
		&& data->cmd_nbr > 0 && data->cmd_nbr < data->pipe_nbr)
		close(data->fd[data->cmd_nbr][0]);
	io_redir(comm, data);
	if (comm->fd_in < 0 || comm->fd_out < 0)
		return (free_childsrcs(data, origin, pid, 1));
	execve(comm->path, comm->cmd, data->envp);
	free_childsrcs(data, origin, pid, 127);
}

// t_type	find_prev_cmd_type(t_input *input)
// {
// 	t_input	*tmp;

// 	tmp = input->prev;
// 	if (tmp == NULL)
// 		return (FINISH);
// 	while (tmp && tmp->type != COMMAND && tmp->type != BUILT_IN)
// 		tmp = tmp->prev;
// 	return (tmp->type);
// }c

void	wait_pids(pid_t *pid, int nbr_cmds, int *status)
{
	int	i;

	i = nbr_cmds - 1;
	while (i >= 0)
	{
		waitpid(pid[i], status, 0);
		i--;
	}
}

int	pipex(t_pipex *comm, t_data *data)
{
	pid_t	*pid;
	int		status;
	t_curs	curs;

	curs = (t_curs){-1, 0, 0};
	status = 0;
	curs.k = nbr_cmds(data);
	pid = malloc(sizeof(pid_t) * nbr_cmds_notb(data));
	while (++(curs.i) < curs.k)
	{
		if (ft_isbuiltin(comm[curs.i].cmd[0]) == TRUE)
		{
			status = builtin_child(&comm[curs.i], data);
			dup2(data->original_stdin, STDIN_FILENO);
			dup2(data->original_stdout, STDOUT_FILENO);
			continue ;
		}
		pid[curs.j] = fork();
		if (pid[curs.j] == -1)
			ft_error("fork", FORK, 124, NULL);
		if (pid[curs.j] == 0)
			child(&comm[curs.i], data, &comm, &pid);
		close_fds(&comm[curs.i]);
		curs.j++;
	}
	wait_pids(pid, curs.j, &status);
	free (pid);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
