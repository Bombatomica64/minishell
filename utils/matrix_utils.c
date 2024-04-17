/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:27:41 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/15 11:55:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	sort_matrix(char ***mtx)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while ((*mtx)[i])
	{
		j = i + 1;
		if (j > ft_matrix_len((*mtx)) - 1)
			break ;
		while ((*mtx)[j])
		{
			if (ft_strcmp((*mtx)[i], (*mtx)[j]) > 0)
			{
				tmp = (*mtx)[i];
				(*mtx)[i] = (*mtx)[j];
				(*mtx)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_bool	name_is_thesame(char *envp, char *to_find)
{
	int	i;

	i = 0;
	while (envp[i] != '=' && to_find[i] != '\0')
	{
		if (envp[i] != to_find[i])
			return (FALSE);
		i++;
	}
	if (envp[i] == '=' && to_find[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	find_in_env(char **envp, char *to_find)
{
	int	i;

	i = 0;
	if (ft_strlen(to_find) == 0)
		return (-1);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], to_find, ft_strlen(to_find)) == 0
			|| name_is_thesame(envp[i], to_find) == TRUE)
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_value(char **envp, char *to_find)
{
	int		i;
	char	*value;

	i = find_in_env(envp, to_find);
	if (i == -1)
		return (NULL);
	if (envp[i][ft_strlen(to_find)] == '=')
		value = ft_strdup(envp[i] + ft_strlen(to_find) + 1);
	else
		value = ft_strdup(envp[i] + ft_strlen(to_find));
	return (value);
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}
