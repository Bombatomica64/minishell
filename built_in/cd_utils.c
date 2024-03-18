/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/18 16:21:44 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_errors_cd(char **mtx)
{
	char	*tmp;

	if (ft_matrix_len(mtx) > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("cd");
		return (1);
	}
	free(tmp);
	return (0);
}

t_bool	ft_change_env(char **str, char *oldpwd, t_data *data)
{
	int	i;

	i = find_in_env(data->envp, "PWD");
	free(data->envp[i]);
	data->envp[i] = ft_strjoin("PWD=", *str);
	free(data->pwd);
	data->pwd = ft_strdup(data->envp[i] + 4);
	i = find_in_env(data->envp, "OLDPWD");
	free(data->envp[i]);
	data->envp[i] = oldpwd;
	free(*str);
	return (TRUE);
}
