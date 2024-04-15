/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:29:22 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/15 11:55:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_islimiter(char c)
{
	if (c == '<' || c == '>' || c == '\0' || c == '|')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	return (FALSE);
}
