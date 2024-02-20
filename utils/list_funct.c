/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:27:22 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/20 15:56:52 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_input	*ft_inputnew(char *node, char *path, t_type type)
{
	t_input	*my_list;

	my_list = (t_input *)malloc(sizeof(t_input));
	if (!my_list)
		return (NULL);
	my_list->node = node;
	my_list->type = type;
	my_list->path = path;
	my_list->next = NULL;
	my_list->prev = NULL;
	return (my_list);
}

void	ft_inputclear(t_input **lst)
{
	t_input	*tofree_lst;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tofree_lst = *lst;
		*lst = (*lst)->next;
		free(tofree_lst);
	}
	lst = NULL;
}

void	ft_inputadd_back(t_input **lst, t_input *new)
{
	t_input	*tmp_lst;

	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp_lst = ft_inputlast(lst);
		tmp_lst->next = new;
		new->prev = tmp_lst;
	}
}

void	ft_inputadd_front(t_input **lst, t_input *new)
{
	t_input	*tmp;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		tmp = (*lst);
		tmp->prev = new;
		new->next = tmp;
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		*lst = new;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
	}
}

t_input	*ft_inputlast(t_input **stack)
{
	t_input	*lst;

	lst = *stack;
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
