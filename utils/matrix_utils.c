/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:27:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/22 18:39:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	find_in_env(char **envp, char *to_find)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(to_find);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], to_find, len) == 0)
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
	value = ft_strdup(envp[i] + ft_strlen(to_find));
	return (value);
}
