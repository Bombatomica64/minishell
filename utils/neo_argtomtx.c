/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neo_argtomtx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 11:58:00 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/15 15:36:01 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

char	*ft_neorowfill(char *str, int *j, int i)
{
	char	*row;
	t_quote	quote;

	quote.open = FALSE;
	quote.type = 0;
	*j += skip_spaces2(&str[*j]);
	row = ft_rowgen(&str[*j]);
	if (!row)
		return (NULL);
	while (str[*j])
	{
		if (ft_isquote(str[*j]))
			quote_start(&quote.open, str[*j], &quote.type);
		if (!str[*j] || (ft_isspace(str[*j]) == TRUE && quote.open == FALSE))
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
