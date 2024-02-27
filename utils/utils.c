/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/27 11:12:23 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_islimiter(char c)
{
	if (c == '<' || c == '>' || c == '\0' || c == '|')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	return (FALSE);
}

void	skip_spaces(char **str)
{
	if (!str || !*str)
		return ;
	while (**str && ft_isspace(**str) == TRUE)
		(*str)++;
}

t_bool	ft_isbuiltin(char *str)
{
	if (!str)
		return (ERROR);
	if (ft_strcmp(str, "echo") || ft_strcmp(str, "cd") || ft_strcmp(str, "pwd")
		|| ft_strcmp(str, "export") || ft_strcmp(str, "unset")
		|| ft_strcmp(str, "env") || ft_strcmp(str, "exit"))
		return (TRUE);
	return (FALSE);
}
