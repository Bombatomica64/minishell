/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/21 09:52:58 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_open_write(char *str)
{
	int		fd;
	char	*line;

	fd = open("heredoc.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (NULL);
	}
	while (read(fd, line, 1024) != 0);
	ft_putendl_fd(str, fd);
	close(fd);
}

void	heredoc_creat(char *limiter)
{
	char	*str;

	str = NULL;
	while (ft_strncmp((const char *)str, (const char *)limiter, ft_strlen(str) != 0))
	{
		str = readline("heredoc> ");
		if (ft_strncmp((const char *)str, (const char *)limiter, ft_strlen(str) != 0))
			heredoc_open_write(str);
	}
}
