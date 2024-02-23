/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:18:56 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/23 10:48:07 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/minishell.h"

/*
	if (ft_strncmp(terminal_input, "cd", 2) == 0)
	{
		ft_cd(terminal_input, data);
		exit(0);
	}



	mettere in tty_run.c
*/

void	print_pwd(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if ((ft_strncmp(envp[i], "PWD=", 4) == 0)
			|| (ft_strncmp(envp[i], "OLDPWD=", 7) == 0))
			printf("%s\n", envp[i]);
		i++;
	}
}

void	ft_cd(char *str, t_data *data)
{
	(void)str;
	print_pwd(data->envp);
	str += 2;
	skip_spaces(&str);
	if (*str == '\0')
	{
		if (chdir(data->home) == -1)
			perror("cd"); //TODO: change value in envp PWD e OLDPWD
	}
	printf("%s\n", str);
}
