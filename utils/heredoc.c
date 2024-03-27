/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/27 18:21:09 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

static void	ft_putendl_fd_free(char **s, int fd)
{
	if (fd < 0)
		return ;
	write(fd, *s, ft_strlen(*s));
	write(fd, "\n", 1);
	free(*s);
}

int	heredoc_creat(char *limiter, t_data *data, pid_t pid, t_pipex *comm)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_error("heredoc_creat", PIPE, 132, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (TRUE)
		{
			str = readline("Heredoc> ");
			if (ft_strcmp(str, limiter) == 0 || str == NULL)
				break ;
			str = expand_name(str, data);
			ft_putendl_fd_free(&str, fd[1]);
		}
		close(fd[1]);
		free_matrix(&comm->cmd);
		free_close(&data, 0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
	}
	return (fd[0]);
}
