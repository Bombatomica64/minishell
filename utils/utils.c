/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/28 10:33:40 by lmicheli         ###   ########.fr       */
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
	if (ft_strncmp(str, "cd ", 3) == 0
		|| ft_strncmp(str, "env ", 4) == 0
		|| ft_strncmp(str, "pwd ", 4) == 0
		|| ft_strncmp(str, "echo ", 5) == 0
		|| ft_strncmp(str, "exit ", 5) == 0
		|| ft_strncmp(str, "unset ", 6) == 0
		|| ft_strncmp(str, "export ", 7) == 0)
		return (TRUE);
	return (FALSE);
}
