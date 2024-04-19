/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_type(char *str, t_type type, t_data *data)
{
	int	fd;

	if (check_access(str, type, data) != 0)
		return (-1);
	fd = -1;
	if (type == TRUNC)
		fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (type == INPUT)
	{
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
