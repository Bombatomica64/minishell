/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:30:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/25 18:35:34 by mruggier         ###   ########.fr       */
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
	char	*mtx[3];
	int		i;

	mtx[0] = ft_strdup("export");
	mtx[1] = ft_strjoin("PWD=", *str);
	mtx[2] = NULL;
	ft_export(&data->envp, mtx);
	free(mtx[0]);
	free(mtx[1]);

	mtx[0] = ft_strdup("export");
	mtx[1] = ft_strdup(oldpwd);
	mtx[2] = NULL;
	ft_export(&data->envp, mtx);
	free(mtx[0]);
	free(mtx[1]);
	free(oldpwd);
	free(*str);

	//data->pwd = get_env_value(data->envp, "PWD");
	
	i = find_in_env(data->envp, "PWD");
	// free(data->envp[i]);
	// data->envp[i] = ft_strjoin("PWD=", *str);
	free(data->pwd);
	data->pwd = ft_strdup(data->envp[i] + 4);
	// i = find_in_env(data->envp, "OLDPWD");
	// free(data->envp[i]);
	// data->envp[i] = oldpwd;
	// free(*str);
	return (TRUE);
}
