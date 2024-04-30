/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 12:39:34 by mruggier          #+#    #+#             */
/*   Updated: 2024/04/30 12:44:17 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putendl_fd_free(char *s, int fd)
{
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	free(s);
}

void	ft_hereaction(int sig)
{
	if (sig == SIGINT)
	{
		g_duranti = 130;
		close (0);
	}
}

void	close_n_fd(int *fd, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(fd[i]);
		i++;
	}
}
