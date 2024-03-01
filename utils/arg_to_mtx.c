/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_mtx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:42:04 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/01 11:30:12 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_arg_count(char *str, char c, int i, int nbr_args)
{
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (ft_isquote(str[i]) == TRUE)
			c = str[i];
		if (ft_isspace(str[i]) == FALSE && ft_isquote(c) == FALSE)
		{
			nbr_args++;
			while (str[i] && ft_isspace(str[i]) == FALSE)
				i++;
			i--;
		}
		else if (ft_isquote(c) == TRUE)
		{
			i++;
			if (str[i] != c)
				nbr_args++;
			while (str[i] && str[i] != c)
				i++;
			c = 42;
		}
		i++;
	}
	return (nbr_args);
}

static char	*ft_rowgen(char *str)
{
	char	*row;
	char	c;
	int		i;

	i = 0;
	c = 42;
	if (ft_isquote(str[i]) == TRUE)
	{
		c = str[i];
		i++;
		while (str[i] && str[i] != c)
			i++;
	}
	else
		while (str[i] && ft_isspace(str[i]) == FALSE)
			i++;
	row = ft_calloc((i + 1), sizeof(char));
	if (ft_malloc_err((void *)row, "ft_rowfill") == TRUE)
		return (NULL);
	return (row);
}

char	*ft_rowfill(char *str, char c, int i, int *j)
{
	char	*row;

	*j += skip_spaces2(str);
	row = ft_rowgen(&str[*j]);
	if (!row)
		return (NULL);
	if (ft_isquote(str[*j]) == TRUE)
	{
		c = str[*j];
		(*j)++;
		while (str[*j] && str[*j] != c)
			row[i++] = str[(*j)++];
	}
	else
	{
		while (str[*j] && ft_isspace(str[*j]) == FALSE)
			row[i++] = str[(*j)++];
	}
	(*j)++;
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
	args = ft_arg_count(str, 42, 0, 0);
	mtx = malloc((args + 1) * sizeof(char *));
	ft_malloc_err((void *)mtx, "ft_splitarg");
	while (i < args)
	{
		mtx[i] = ft_rowfill(str, 42, 0, &j);
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
