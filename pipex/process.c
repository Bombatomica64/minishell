/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:08:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/27 15:53:11 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(char **cmd, t_data *data)
{
	(void)cmd;
	(void)data;
	ft_printf("ciaone\n");
}

void	do_builtin(char **cmd, t_data *data)
{
	t_bool	ret;

	ret = TRUE;
	if (ft_strcmp(cmd[0], "echo") == TRUE)
		ret = ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "cd") == TRUE)
		ret = ft_cd(cmd, data);
	else if (ft_strcmp(cmd[0], "pwd") == TRUE)
		ft_pwd();
	else if (ft_strcmp(cmd[0], "export") == TRUE)
		ret = ft_export(&data->envp, cmd);
	else if (ft_strcmp(cmd[0], "unset") == TRUE)
		ret = ft_unset(cmd, &data->envp);
	else if (ft_strcmp(cmd[0], "env") == TRUE)
		ft_env(data->envp);
	else if (ft_strcmp(cmd[0], "exit") == TRUE)
		ft_exit(cmd, data);
	if (ret == FALSE)
		ft_error(cmd[0], BUILTIN, 1, data);
	else
		free_close(data, 0);
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