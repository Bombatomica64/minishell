/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/26 12:30:08 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	heredoc_creat(char *limiter, t_data *data)
{
	char	*str;
	char	*name;
	int		fd;

	str = NULL;
	name = ft_strjoin(data->home, "/.heredoc.txt");
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
		ft_error("heredoc_creat", OPEN, 101, NULL);
	while (ft_strcmp((const char *)str, (const char *)limiter) != 0)
	{
		str = readline("heredoc> ");
		if (ft_strcmp((const char *)str, (const char *)limiter) != 0)
			ft_putendl_fd(str, fd);
		free(str);
	}
	close(fd);
	return (open(name, O_RDONLY));
}
