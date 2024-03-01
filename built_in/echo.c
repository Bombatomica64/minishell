/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:24:10 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/01 11:30:50 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

t_bool	ft_echo(char **mtx)
{
	int		i;

	if (!mtx || ft_strcmp(mtx[0], "echo") != 0)
		return (FALSE);
	i = 1;
	if (ft_strcmp(mtx[i], "-n") == 0)
		i++;
	while (mtx[i])
		ft_printf("%s", mtx[i++]);
	if (ft_strcmp(mtx[1], "-n") != 0)
		ft_printf("\n");
	return (TRUE);
}

void	ft_env(char **envp)
{
	print_matrix(envp);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}
