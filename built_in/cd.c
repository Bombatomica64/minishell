/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:18:56 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/23 16:16:13 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/*
	if (ft_strncmp(terminal_input, "cd", 2) == 0)
	{
		ft_cd(terminal_input, data);
		exit(0);
	}

	env | grep -E '^(HOME|PWD|OLDPWD)='

	mettere in tty_run.c
*/

void	print_pwds(char **envp)
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

char *

void	ft_cd(char *str, t_data *data) //TODO: change value in envp PWD e OLDPWD
{
	int	i;
	
	(void)str;
	print_pwd(data->envp);
	str += 2;
	skip_spaces(&str);
	if (*str == '\0')
	{
		if (chdir(data->home) == -1)
			perror("cd"); 
		i = find_in_env(data->envp, "PWD");
		free(data->envp[i]);
		data->envp[i] = ft_strjoin("PWD=", data->home);
		//print_pwd(data->envp);
		return ;
	}
	//if (cd - spazio fino a \0 vai OLDPWD)
	
	if (*str == '~')
	{
		str++;
		str = ft_strjoin(data->home, str);
	}
	else if (*str != '/')
	{
		str = ft_strjoin("/", str);
		str = ft_strjoin(get_env_value(data->envp, "PWD="), str);
	}
	
	i = 0;
	while (str[i] != '\0')
	{
		if (strncmp(str + i, "./", 2) == 0)
		{
			ft_remove_chars(str, "./", 2);
		}
		else if (strncmp(str + i, "../", 3) == 0)
		{
			str = ft_strjoin(str, str + i + 3);
		}
		i++;
	}
	








	
	printf("%s\n", str);
}

/*
se inizia con / path assoluto
se inizia con ~ cambiare con data->home e fare strjoin con il resto
se inizia con il resto, path relativo. strjoin di PWD e il resto



se ./ cancellare (le cose con se inizia vanno fatte solo all'inizio 1 volta)
se ../ cancellare insieme alla directory se c'e':  

*/