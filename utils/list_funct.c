/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:27:22 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/22 12:00:59 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_input	*ft_inputnew(t_parser prs)
{
	t_input	*my_list;

	my_list = (t_input *)malloc(sizeof(t_input));
	if (!my_list)
		return (NULL);
	my_list->node = ft_strdup(prs.tmp);
	my_list->type = prs.tmp_type;
	my_list->path = ft_strdup(prs.tmp_path);
	my_list->next = NULL;
	my_list->prev = NULL;
	return (my_list);
}

void	ft_inputclear(t_input **lst)
{
	t_input	*tofree_lst;

	if (!lst || !*lst)
		return ;
	*lst = ft_inputfirst(lst);
	while (*lst)
	{
		free((*lst)->node);
		free((*lst)->path);
		tofree_lst = *lst;
		*lst = (*lst)->next;
		free(tofree_lst);
	}
	lst = NULL;
}

void	ft_inputadd_back(t_input **lst, t_input *news)
{
	t_input	*tmp_lst;

	if (!news || !lst)
		return ;
	if (!*lst)
		*lst = news;
	else
	{
		tmp_lst = ft_inputlast(lst);
		tmp_lst->next = news;
		news->prev = tmp_lst;
	}
}

void	ft_inputadd_front(t_input **lst, t_input *news)
{
	t_input	*tmp;

	if (!news || !lst)
		return ;
	if (*lst)
	{
		tmp = (*lst);
		tmp->prev = news;
		news->next = tmp;
		news->prev = NULL;
		*lst = news;
	}
	else
	{
		*lst = news;
		(*lst)->next = NULL;
		(*lst)->prev = NULL;
	}
}

t_input	*ft_inputlast(t_input **lst)
{
	t_input	*tmp;

	if (!lst || !*lst)
		return (NULL);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
