/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:05:13 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/15 11:55:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	skip_spaces2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && ft_isspace(str[i]) == TRUE)
		i++;
	return (i);
}

void	skip_spaces(char **str)
{
	if (!*str || !**str)
		return ;
	while (**str && ft_isspace(**str) == TRUE)
		(**str)++;
}

t_bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

t_bool	print_matrix(char **mtx)
{
	int	i;

	i = -1;
	if (!mtx)
		return (FALSE);
	while (mtx[++i])
		printf("%s\n", mtx[i]);
	return (TRUE);
}
