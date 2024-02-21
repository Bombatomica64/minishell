/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/21 12:22:25 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_creat(char *limiter)
{
	char	*str;
	int		fd;

	str = NULL;
	fd = open(".heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return ;
	}
	while (ft_strcmp((const char *)str, (const char *)limiter) != 0)
	{
		str = readline("heredoc> ");
		if (ft_strcmp((const char *)str, (const char *)limiter) != 0)
			ft_putendl_fd(str, fd);
		free(str);
	}
	close(fd);
}
