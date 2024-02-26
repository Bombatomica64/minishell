/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:08:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/26 12:23:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
