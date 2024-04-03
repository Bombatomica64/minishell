/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:27:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/03 18:47:20 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**matrix_dup(char **matrix)
{
	char	**new_matrix;
	int		i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
		i++;
	new_matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
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
