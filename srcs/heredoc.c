/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/02 15:34:15 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putendl_fd_free(char *s, int fd)
{
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	free(s);
}

int	heredoc_creat(char *limiter, t_data *data, pid_t pid, t_pipex *comm)
{
	char	*str;
	int		fd[2];

	limiter = ft_strncpy_noquote(limiter, 0, ft_strlen(limiter),
			(t_quote){0, 0});
	if (pipe(fd) < 0)
		ft_error("heredoc_creat", PIPE, 132, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (TRUE)
		{
			str = readline(YELLOW BOLD"サ巳尺巳りロと"BRIGHT_CYAN"> "END);
			if (ft_strcmp(str, limiter) == 0 || str == NULL)
				break ;
			ft_putendl_fd_free(expand_name(str, data), fd[1]);
		}
		close(fd[1]);
		free_matrix(&comm->cmd);
		free_close(&data, 0);
	}
	else
		waitpid(pid, NULL, 0);
	return (close(fd[1]), fd[0]);
}
