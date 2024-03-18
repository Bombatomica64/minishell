/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:39:27 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/18 16:08:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	check_for_non_valid_export(char **cmd)
{
	int		i;
	int		j;

	j = 0;
	while (cmd[++j])
	{
		i = 0;
		while (cmd[j][i] && cmd[j][i] != '=')
		{
			if (i == 0 && !ft_isalpha(cmd[j][i]) && cmd[j][i] != '_')
				return (export_error(cmd[j]));
			if (!ft_isalnum(cmd[j][i]) && cmd[j][i] != '_')
				return (export_error(cmd[j]));
			i++;
		}
		if (ft_strcmp(cmd[j], "=") == 0)
			return (export_error(cmd[j]));
	}
	return (0);
}

int	ft_export(char ***envp, char **cmd)
{
	char	*tmp;
	int		i;
	int		j;
	int		error;

	if (!cmd)
		return (FALSE);
	j = 0;
	error = 0;
	if (check_for_non_valid_export(cmd) == 1)
		return (1);
	while (cmd[++j])
	{
		i = 0;
		while (cmd[j][i] && cmd[j][i] != '=')
			i++;
		tmp = ft_strndup(cmd[j], i);
		error += add_or_update(envp, tmp, cmd, j);
		free(tmp);
	}
	return (error);
}

int	add_or_update(char ***envp, char *tmp, char **cmd, int j)
{
	if (find_in_env(*envp, tmp) == -1)
		return (add_to_env(envp, cmd[j]));
	else
		return (update_env(envp, cmd[j], tmp));
}

int	add_to_env(char ***envp, char *str)
{
	int		i;
	char	**new_envp;

	new_envp = malloc((ft_matrix_len(*envp) + 2) * sizeof(char *));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < ft_matrix_len(*envp))
	{
		new_envp[i] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[i] = ft_strdup(str);
	new_envp[i + 1] = NULL;
	if (!new_envp[i])
		return (1);
	free_matrix(envp);
	*envp = new_envp;
	return (0);
}

int	update_env(char ***envp, char *str, char *tmp)
{
	int		i;

	i = find_in_env(*envp, tmp);
	free((*envp)[i]);
	(*envp)[i] = ft_strdup(str);
	if (!(*envp)[i])
		return (1);
	return (0);
}
