/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:08:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/19 10:25:19 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	ft_isthesameas(char *s1, char *s2)
{
	if (ft_strcmp(s1, s2) == 0)
		return (TRUE);
	return (FALSE);
}

int	do_builtin(t_pipex *comm, t_data *data)
{
	int	ret;

	ret = 0;
	if (ft_strcmp(comm->cmd[0], "echo") == 0)
		ret = ft_echo(comm->cmd);
	else if (ft_strcmp(comm->cmd[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(comm->cmd[0], "export") == 0)
		ret = ft_export(&data->envp, comm->cmd);
	else if (ft_strcmp(comm->cmd[0], "unset") == 0)
		ret = ft_unset(comm->cmd, &data->envp);
	else if (ft_strcmp(comm->cmd[0], "env") == 0)
		ret = ft_env(data->envp, &comm->cmd[1]);
	else if (ft_strcmp(comm->cmd[0], "exit") == 0)
		ret = ft_exit(comm->cmd, data);
	else if (ft_strcmp(comm->cmd[0], "cd") == 0)
		ret = ft_cd(comm->cmd, data);
	non_pipe_close(data, comm);
	if (data->in_pipe == TRUE && data->cmd_nbr <= data->pipe_nbr)
		close(data->fd[data->cmd_nbr][1]);
	return (free_matrix(&comm->cmd), ret);
}

void	non_pipe_close(t_data *data, t_pipex *comm)
{
	if (data->in_pipe == FALSE)
	{
		if (comm->fd_in >= 0 && comm->fd_in != STDIN_FILENO)
			close(comm->fd_in);
		if (comm->fd_out >= 0 && comm->fd_out != STDOUT_FILENO)
			close(comm->fd_out);
	}
}

void	io_redir(t_pipex *comm, t_data *data)
{
	if (comm->fd_in != STDIN_FILENO)
	{
		if (dup2(comm->fd_in, STDIN_FILENO) == -1)
			ft_error("child_stdin", DUP, 13, data);
	}
	if (comm->fd_out != STDOUT_FILENO)
	{
		if (dup2(comm->fd_out, STDOUT_FILENO) == -1)
			ft_error("child", DUP, 13, data);
	}
}

/* void	child(t_data *data, int i)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("child", PIPE, 132, data);
	pid = fork();
	if (pid == -1)
		ft_error("child", FORK, 124, data);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error("child", DUP, 13, data);
		if (execve(data->pipex.path[i], data->pipex.cmd[i], NULL) < 0)
			ft_error(data->pipex.path[i], EXECVE, 126, data);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("stdin to fd[0]", DUP, 13, data);
		waitpid(pid, NULL, 0);
	}
}

void	parent(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("parent", FORK, 124, data);
	if (pid == 0)
	{
		if (execve(data->pipex.path[i], data->pipex.cmd[i], NULL) == -1)
			ft_error ("parent", EXECVE, 126, data);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (data->pipex.fd_in > 2)
			close(data->pipex.fd_in);
		if (data->pipex.fd_out > 2)
			close(data->pipex.fd_out);
	}
}

int	checkfile_fd(t_data *data)
{
	if (data->pipex.fd_in < 0 || data->pipex.fd_out < 0)
		ft_error("open", OPEN, 101, data);
	if (data->pipex.fd_in > 2)
		if (access(data->pipex.filein, F_OK | R_OK) == -1)
			ft_error("input file", ACCESS, 133, data);
	if (data->pipex.fd_out > 2)
		if (access(data->pipex.fileout, F_OK | W_OK) == -1)
			ft_error("output file", ACCESS, 133, data);
	return (0);
}

void	ft_execute(t_data *data)
{
	int		i;

	i = 0;
	if (dup2(data->pipex.fd_in, STDIN_FILENO) == -1)
		ft_error("stdin to filein", DUP, 13, data);
	while (data->pipex.path[i + 1] != NULL)
	{
		child(data, i);
		i++;
	}
	if (dup2(data->pipex.fd_out, STDOUT_FILENO) == -1)
		ft_error("stdout to fileout", DUP, 13, data);
	parent(data, i);
}
 */