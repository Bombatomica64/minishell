/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:12 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/23 15:49:46 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	ft_env(char **envp)
{
	print_matrix(envp);
}

void	remove_envp_entry(char ***envp, char *entry)
{
	int		j;
	char	**new_envp;

	j = 0;
	while ((*envp)[j])
	{
		if (ft_strncmp(entry, (*envp)[j], ft_strlen(entry)) == 0)
		{
			new_envp = ft_calloc(ft_matrix_len(*envp), sizeof(char *));
			if (!new_envp)
				return ;
			ft_memcpy(new_envp, *envp, j * sizeof(char *));
			ft_memcpy(new_envp + j, *envp + j + 1,
				(ft_matrix_len(*envp) - j) * sizeof(char *));
			free(*envp);
			*envp = new_envp;
			break ;
		}
		j++;
	}
}

t_bool	ft_unset(char **mtx, char ***envp)
{
	int		i;
	char	**new_envp;

	if (!mtx || ft_strcmp(mtx[0], "unset") != 0)
		return (FALSE);
	i = 1;
	while (mtx[i])
	{
		remove_envp_entry(envp, mtx[i]);
		i++;
	}
	return (TRUE);
}

t_bool	export(char ***envp, char *str)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (!str)
		return (FALSE);
	if (find_in_env(*envp, str) != -1)
	{
		while ((*envp)[i])
			i++;
		new_envp = ft_calloc(i + 2, sizeof(char *));
		if (!new_envp)
			return (FALSE);
		ft_memcpy(new_envp, *envp, i * sizeof(char *));
		new_envp[i] = ft_strdup(str);
		if (!new_envp[i])
			return (FALSE);
		free(*envp);
		*envp = new_envp;
	}
	else
	{
		i = find_in_env(*envp, str);
		free((*envp)[i]);
		(*envp)[i] = ft_strdup(str);
		if (!(*envp)[i])
			return (FALSE);
	}
	return (TRUE);
}
