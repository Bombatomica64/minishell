/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/20 18:11:19 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_open_write(void)
{
	int		fd;

	fd = open("heredoc.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		printf("Error opening file\n");
		return (NULL);
	}
}

void	heredoc_creat(char *limiter, t_data *data)
{
	char	*str;
	int		fd;

	fd = open("heredoctemp", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	str = readline("heredoc> " );
	heredoc_open_write(str);
	while (ft_strcmp(str, limiter) != NULL)
	{
		write(fd, str, ft_strlen(str));
		free(str);
		str = readline("heredoc> " );
	}
	free(str);
	close(fd);
	printf("sesso pazzo\n");
}
