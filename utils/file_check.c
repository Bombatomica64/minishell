/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/29 17:07:55 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	file_exist(char *file)
{
	if (access(file, F_OK) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	file_readable(char *file)
{
	if (access(file, R_OK) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	file_writable(char *file)
{
	if (access(file, W_OK) == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	file_executable(char *file)
{
	if (access(file, X_OK) == 0)
		return (TRUE);
	return (FALSE);
}

int	check_access(char *file, t_type type, t_data *data)
{
	if (type == INPUT)
	{
		if (file_exist(file) == TRUE && file_readable(file) == TRUE)
			return (0);
		else if (file_exist(file) == FALSE)
			return (ft_error(file, NO_EST_NOFREE, 1, data));
		else if (file_readable(file) == FALSE)
			return (ft_error(file, ACCESS_NOFREE, 1, data));
	}
	else
	{
		if (file_exist(file) == TRUE && file_writable(file) == TRUE)
			return (0);
		else if (file_exist(file) == TRUE && file_writable(file) == FALSE)
			return (ft_error(file, WRITE, 1, data));
		return (0);
	}
	return (-1);
}
