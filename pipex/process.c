/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:08:34 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/08 18:40:36 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(t_pipex *pipex)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("1", PIPE);
	pid = fork();
	if (pid == -1)
		ft_error("1", FORK);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error("1", DUP);
		if (execve(pipex->path1, pipex->cmd1, NULL) < 0)
			ft_error("1", EXECVE);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("1", DUP);
		waitpid(pid, NULL, 0);
	}
}

void	parent(t_pipex *pipex)
{
	if (execve(pipex->path2, pipex->cmd2, NULL) < 0)
		ft_error ("parent", EXECVE);
	if (pipex->fd_in > 2)
		close(pipex->fd_in);
	if (pipex->fd_out > 2)
		close(pipex->fd_out);
}

int	checkfile_fd(t_pipex *pipex)
{
	if (access(pipex->filein, F_OK | R_OK) == -1)
		ft_error("1", ACCESS);
	if (access(pipex->fileout, F_OK | W_OK) == -1)
		ft_error("1", ACCESS);	
	if (pipex->fd_in < 0 || pipex->fd_out < 0)
		ft_error("2", OPEN);
	return (0);
}

void	ft_execute(t_pipex *pipex)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		ft_error("2", DUP);
	child(pipex);
	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		ft_error("2", DUP);
	parent(pipex);
}
