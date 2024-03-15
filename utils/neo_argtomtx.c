/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_argtomtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:58:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/15 12:06:15 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

static char	*ft_neorowfill(char *str, int *j, int i)
{
	char	*row;

	*j += skip_spaces2(&str[*j]);
	row = ft_rowgen(&str[*j]);
	if (!row)
		return (NULL);
	while (str[*j])
	{
		if (!str[*j] || ft_isspace(str[*j]) == TRUE)
			break ;
		row[i++] = str[(*j)++];
	}
	return (row);
}

char	**ft_neosplitarg(char *str)
{
	char	**mtx;
	int		args;
	int		i;
	int		j;

	j = 0;
	i = 0;
	args = ft_arg_count(str, 0, 0);
	mtx = malloc((args + 1) * sizeof(char *));
	ft_malloc_err((void *)mtx, "ft_neosplitarg");
	while (i < args)
	{
		mtx[i] = ft_neorowfill(str, &j, 0);
		if (!mtx[i])
		{
			free_matrix(&mtx);
			return (NULL);
		}
		i++;
	}
	mtx[i] = NULL;
	return (mtx);
}