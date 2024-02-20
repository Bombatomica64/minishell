/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/20 16:42:41 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_open_write(char *str)
{
	int		fd;

	fd = open("heredoc.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (NULL);
	}
	ft_putendl_fd(str, fd);
	close(fd);
}

void	heredoc_creat(char *limiter, t_data *data)
{
	char	*str;

	while (ft_strcmp());
}
