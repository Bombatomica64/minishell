/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accounting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 11:40:17 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	nbr_cmds(t_data *data)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = data->input;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == COMMAND || tmp->type == BUILT_IN)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	nbr_cmds_notb(t_data *data)
{
	t_input	*tmp;
	int		i;

	i = 0;
	tmp = data->input;
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
