/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:24:10 by mruggier          #+#    #+#             */
/*   Updated: 2024/04/03 18:43:50 by mruggier         ###   ########.fr       */
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
	while (envp[i])
	{
		j = 0;
		tmp = ft_split(envp[i], '=');
		ft_printf("declare -x %s", tmp[j]);
		if (tmp[++j])
			ft_printf("=\"%s\"", tmp[j]);
		ft_printf("\n");
		free_matrix(&tmp);
		i++;
	}
	return (0);
}
