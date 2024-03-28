/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:07 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/28 11:00:20 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_type(char *str, t_type type, t_data *data)
{
	int	fd;

	fd = -1;
	if (type == TRUNC)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (type == INPUT)
	{
		if (check_access(str, type, data) != 0)
			return (-1);
		fd = open(str, O_RDONLY);
	}
	if (fd < 0)
		ft_error(str, OPEN, 101, data);
	return (fd);
}

int	fd_io_check(int fd_io, int fd_to_check, int pipe_fd)
{
	if (fd_io == fd_to_check)
		return (pipe_fd);
	close(pipe_fd);
	return (fd_io);
}
