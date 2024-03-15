/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:14:12 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/15 18:13:49 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

void	remove_envp_entry(char ***envp, int index)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_envp = (char **)malloc(sizeof(char *) * i);
	if (!new_envp)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		if (i != index)
		{
			new_envp[j] = ft_strdup((*envp)[i]);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_matrix(envp);
	*envp = new_envp;
}

int	ft_unset(char **mtx, char ***envp)
{
	int		i;

	if (!mtx || ft_strcmp(mtx[0], "unset") != 0)
		return (1);
	i = 1;
	if (find_in_env(*envp, mtx[i]) == -1)
		return (0);
	while (mtx[i])
	{
		remove_envp_entry(envp, find_in_env(*envp, mtx[i]));
		i++;
	}
	return (0);
}

int	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
