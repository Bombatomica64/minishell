/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:18:56 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/23 18:46:45 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/*
ciao
	char *command[] = {"cd", terminal_input, NULL};
	ft_cd(command, data);
	exit(0);


	env | grep -E '^(HOME|PWD|OLDPWD)='

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

char *ft_remove_chars(char **str, char *to_remove, int i)
{
	int	j;
	int char_path;
	char *tmp;

	j = 0;
	tmp = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		tmp[j] = (*str)[j];
		j++;
	}
	tmp[j] = '\0';
	if (ft_strcmp(to_remove, "../") == 0)
	{
		char_path = 2;
		while ((*str)[j - char_path] != '/')
			char_path++;
		tmp[j - char_path + 1] = '\0';
	}
	tmp = ft_strjoin(tmp, *str + i + ft_strlen(to_remove));
	free(*str);
	return (tmp);
}


void	ft_cd(char **mtx, t_data *data) //TODO: change  OLDPWD
{
	int		i;
	char	*str;
	
	str = NULL;
	if (mtx[1] == NULL)
	{
		if (chdir(data->home) == -1)
			perror("cd"); 
		i = find_in_env(data->envp, "PWD");
		free(data->envp[i]);
		data->envp[i] = ft_strjoin("PWD=", data->home);
		//print_pwd(data->envp);
		return ;
	}
	str = ft_strdup(mtx[1]);
	//print_pwd(data->envp);
	//TODO: if (cd - spazio fino a \0 vai OLDPWD)
	
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
			str = ft_remove_chars(&str, "./", i);
			i = 0;
		}
		else if (strncmp(str + i, "../", 3) == 0)
		{
			str = ft_remove_chars(&str, "../", i);
			i = 0;
		}
		i++;
	}

	if (chdir(str) == -1)
			perror("cd"); 
	i = find_in_env(data->envp, "PWD");
	free(data->envp[i]);
	data->envp[i] = ft_strjoin("PWD=", str);
	








	
	printf("%s\n", str);
}