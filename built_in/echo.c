/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:24:10 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/23 10:42:03 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

t_bool	ft_echo(char **mtx)
{
	int i;

	if (!mtx || ft_strcmp(mtx[0], "echo") != 0)
		return (FALSE);
	i = 1;
	if (ft_strcmp(mtx[i], "-n") == TRUE)
		i++;
	ft_printmtx(&mtx[i]);
	if (ft_strcmp(mtx[i], "-n") == TRUE)
		ft_printf("\n");
	return (TRUE);
}
