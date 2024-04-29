/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:06 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_duranti = -1;

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
	{
		dup2(2, 1);
		ft_printf("minishell: too many arguments\n");
		exit (1);
	}
	(void)argv;
	data = ft_data_init(envp);
	ft_tty_exec(&data);
	return (0);
}
