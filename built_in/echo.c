/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

int	ft_echo(char **mtx)
{
	int		i;

	if (!mtx || ft_strcmp(mtx[0], "echo") != 0)
		return (1);
	i = 1;
	if (ft_strcmp(mtx[i], "-n") == 0)
		i++;
	while (mtx[i])
	{
		ft_printf("%s", mtx[i++]);
		if (mtx[i])
			ft_printf(" ");
	}
	if (ft_strcmp(mtx[1], "-n") != 0 || mtx[1] == NULL)
		ft_printf("\n");
	return (0);
}

int	ft_env(char **envp, char **mtx)
{
	if (*mtx)
	{
		while (*mtx)
		{
			ft_putstr_fd("minishell: env: `", 2);
			ft_putstr_fd(*mtx, 2);
			ft_putstr_fd("': No such file or directory\n", 2);
			mtx++;
		}
		return (1);
	}
	print_matrix(envp);
	return (0);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}

int	print_export(char **envp)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char *), (ft_matrix_len(envp) + 1));
	while (envp[i])
	{
		tmp[j] = ft_strdup(envp[i]);
		tmp[j] = ft_strjoin_2("declare -x ", tmp[j]);
		j++;
		i++;
	}
	sort_matrix(&tmp);
	print_matrix(tmp);
	free_matrix(&tmp);
	return (0);
}
