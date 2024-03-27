/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:47:54 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/27 18:00:50 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_input2str(t_input **input)
{
	t_input	*tmp;
	char	*str;

	if (!input || !*input)
		return (NULL);
	tmp = *input;
	str = NULL;
	while (tmp)
	{
		str = ft_newstrjoin(str, tmp->node);
		str = join_char(str, ' ');
		tmp = tmp->next;
	}
	return (str);
}

t_input	*ft_inputfirst(t_input **lst)
{
	t_input	*tmp;

	if (!lst || !*lst)
		return (NULL);
	tmp = *lst;
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
	static char	*colors[] = {RED, BRIGHT_RED, YELLOW, BRIGHT_YELLOW,
		GREEN, BRIGHT_GREEN, CYAN, BRIGHT_CYAN, BLUE, BRIGHT_BLUE,
		MAGENTA, BRIGHT_MAGENTA, RED, BRIGHT_RED, YELLOW, BRIGHT_YELLOW,
		GREEN, BRIGHT_GREEN, CYAN, BRIGHT_CYAN, BLUE, BRIGHT_BLUE, END};
	int			i;

	while (input)
	{
		i = 0;
		while (i < 22)
			printf("%s-"END, colors[i++]);
		printf("\n");
		printf("type: %d\n", input->type);
		printf("path: %s\n", input->path);
		printf("node: |%s|\n", input->node);
		input = input->next;
	}
	i = 0;
	while (i < 22)
		printf("%s-"END, colors[i++]);
	printf("\n");
}
