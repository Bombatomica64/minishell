/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:47:54 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/26 15:27:56 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_input	*ft_inputfirst(t_input **lst)
{
	t_input	*tmp;

	tmp = *lst;
	if (!tmp)
		return (NULL);
	while (tmp->prev)
		tmp = tmp->prev;
	return (tmp);
}

int	input_size(t_input *input)
{
	int	i;

	i = 0;
	while (input)
	{
		i++;
		input = input->next;
	}
	return (i);
}

int	input_nbr_of_cmd(t_input *input)
{
	int	i;

	i = 0;
	while (input)
	{
		if (input->type == COMMAND || input->type == BUILT_IN)
			i++;
		input = input->next;
	}
	return (i);
}

void	print_list(t_input *input)
{
	while (input)
	{
		printf("type: %d\n", input->type);
		printf("path: %s\n", input->path);
		printf("node: %s\n", input->node);
		printf("--------------------\n");
		input = input->next;
	}
}
