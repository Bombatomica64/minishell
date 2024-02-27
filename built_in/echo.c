/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:24:10 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/27 12:05:48 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static t_bool	print_matrix_echo(char **mtx)
{
	int	i;

	i = -1;
	if (!mtx)
		return (FALSE);
	while (mtx[++i])
		ft_printf("%s", mtx[i]);
	return (TRUE);
}

t_bool	ft_echo(char **mtx)
{
	int		i;

	if (!mtx || ft_strcmp(mtx[0], "echo") != 0)
		return (FALSE);
	i = 1;
	if (ft_strcmp(mtx[i], "-n") == TRUE)
		i++;
	print_matrix_echo(&mtx[i]);
	if (ft_strcmp(mtx[1], "-n") == TRUE)
		ft_printf("\n");
	return (TRUE);
}

void	ft_env(char **envp)
{
	print_matrix(envp);
}

void	ft_pwd(void)
{
	ft_printf("%s\n", getcwd(NULL, 0));
}
