/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by mruggier          #+#    #+#             */
/*   Updated: 2024/04/16 12:28:29 by lmicheli         ###   ########.fr       */
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

int	heredoc_creat(char *lim, t_data *data, pid_t pid, t_pipex *comm)
{
	char	*str;
	int		fd[2];

	lim = ft_strncpy_noquote(lim, 0, ft_strlen(lim), (t_quote){0, 0});
	if (pipe(fd) < 0)
		ft_error("heredoc_creat", PIPE, 132, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (TRUE)
		{
			str = readline(YELLOW BOLD"サ巳尺巳りロと"BRIGHT_CYAN"> "END);
			if (ft_strcmp(str, lim) == 0 || str == NULL)
				break ;
			ft_putendl_fd_free(expand_name(str, data), fd[1]);
		}
		close(fd[1]);
		free_matrix(&comm->cmd);
		free(lim);
		free_close(&data, 0);
	}
	else
		waitpid(pid, NULL, 0);
	return (close(fd[1]), free(lim), fd[0]);
}
