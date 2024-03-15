/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_mtx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:42:04 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/15 12:05:28 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

int	ft_arg_count(char *str, int i, int nbr_args)
{
	t_quote	quote;

	quote.open = FALSE;
	quote.type = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == FALSE)
			nbr_args++;
		if (ft_isquote(str[i]))
		{
			quote_start(&quote.open, str[i], &quote.type);
			i++;
		}
		while (str[i] && (quote.open == TRUE || ft_isspace(str[i]) == FALSE))
		{
			quote_start(&quote.open, str[i], &quote.type);
			i++;
		}
		if (str[i])
			i++;
	}
	return (nbr_args);
}

char	*ft_rowgen(char *str)
{
	char	*row;
	t_quote	quote;
	int		i;

	i = 0;
	quote.open = FALSE;
	quote.type = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]))
		{
			quote_start(&quote.open, str[i], &quote.type);
			if (str[i] == quote.type || !quote.type)
				i++;
		}
		if (!str[i] || (ft_isspace(str[i]) == TRUE && quote.open == FALSE))
			break ;
		i++;
	}
	row = ft_calloc((i + 1), sizeof(char));
	if (!row)
		return (NULL);
	return (row);
}

char	*ft_rowfill(char *str, int *j, int i)
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
		{
			quote_start(&quote.open, str[*j], &quote.type);
			while (ft_isquote(str[*j])
				&& ((quote.open && str[*j] == quote.type) || !quote.open))
				quote_start(&quote.open, str[++(*j)], &quote.type);
		}
		if (!str[*j] || (ft_isspace(str[*j]) == TRUE && quote.open == FALSE))
			break ;
		row[i++] = str[(*j)++];
	}
	return (row);
}

char	**ft_splitarg(char *str)
{
	char	**mtx;
	int		args;
	int		i;
	int		j;

	j = 0;
	i = 0;
	args = ft_arg_count(str, 0, 0);
	mtx = malloc((args + 1) * sizeof(char *));
	ft_malloc_err((void *)mtx, "ft_splitarg");
	while (i < args)
	{
		mtx[i] = ft_rowfill(str, &j, 0);
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
