/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:23:22 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/05 11:35:08 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

t_bool	is_exit(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_exit(char **cmd, t_data *data)
{
	free_matrix(&cmd);
	free_close(&data, EXIT_SUCCESS);
	return (0);
}
