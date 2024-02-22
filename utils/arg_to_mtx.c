/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_mtx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:42:04 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/22 15:23:08 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_isspace(char c)
{
	if ((c >= 9 && c<= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	return (FALSE);
}

int	ft_arg_count(char *str)
{
	int		nbr_args;
	int		i;
	char	c;

	i = 0;
	c = 42;
	nbr_args = 0;
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

char	*ft_rowfill(char **str)
{
	char	*row;
	int		i;
	char	c;

	i = 0;
	skip_spaces(str);
	if (ft_isquote((*str)[i]) == TRUE)
	{
		c = (*str)[i];
		while ((*str)[i] && (*str)[i] != c)
			i++;
	}
	else
		while ((*str)[i] && ft_isspace((*str)[i]) == FALSE)
			i++;
	row = ft_calloc((i + 1), sizeof(char));
	ft_malloc_err((void *)row, "ft_rowfill");
	i = 0;
	if (ft_isquote(**str) == TRUE)
	{
		c = **str;
		(*str)++;
		while (**str && **str != c)
		{
			row[i++] == **str;
			(*str)++;
		}
		(*str)++;
	}
	else
	{
		while (**str && ft_isspace(**str) == FALSE)
		{
			row[i++] == **str;
			(*str)++;
		}
	}
	return (row);
}

char	**ft_splitarg(char *str)
{
	char	**mtx;
	int		args;
	int		i;

	i = 0;
	args = ft_arg_count(str);
	mtx = malloc(args * sizeof(char *));
	ft_malloc_err((void *)mtx, "ft_splitarg");
	while (i < args)
	{
		mtx[i] = ft_rowfill(&str);
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
