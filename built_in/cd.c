/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:18:56 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/27 17:30:01 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

/*
	char **mtx;
	
	mtx = ft_split(terminal_input, ' ');

	char *command[] = {mtx[0], mtx[1], NULL};
	ft_cd(command, data);
	return ;

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

char	*ft_remove_chars(char *str, char *to_remove, int i)
{
	int		j;
	int		char_path;
	char	*tmp;

	j = 0;
	tmp = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		tmp[j] = str[j];
		j++;
	}
	tmp[j] = '\0';
	if (ft_strcmp(to_remove, "../") == 0)
	{
		char_path = 2;
		while (str[j - char_path] != '/')
			char_path++;
		tmp[j - char_path + 1] = '\0';
	}
	tmp = ft_strjoin(tmp, str + i + ft_strlen(to_remove));
	free(str);
	return (tmp);
}

char	*refactor_path(char *str, t_data *data, int i) //TODO: cd "~/ecc" o < "~", tra virgolette è un path relativo e ~ è il nome
{
	if (*str == '~')
		str = ft_strjoin(data->home, ++(str));
	else if (*str != '/')
	{
		str = ft_strjoin("/", str);
		str = ft_strjoin(get_env_value(data->envp, "PWD="), str);
	}
	while ((str)[i] != '\0')
	{
		if (strncmp(str + i, "./", 2) == 0)
		{
			str = ft_remove_chars(str, "./", i);
			i = 0;
		}
		else if (strncmp(str + i, "../", 3) == 0
			|| strncmp(str + i, "..", 2) == 0)
		{
			str = ft_remove_chars(str, "../", i);
			i = 0;
		}
		i++;
	}
	if (str[ft_strlen(str) - 1] == '/')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

t_bool	ft_change_env(char **str, char *oldpwd, t_data *data)
{
	int	i;

	i = find_in_env(data->envp, "PWD");
	free(data->envp[i]);
	data->envp[i] = ft_strjoin("PWD=", *str);
	i = find_in_env(data->envp, "OLDPWD");
	free(data->envp[i]);
	data->envp[i] = oldpwd;
	free(*str);
	return (TRUE);
}

t_bool	ft_cd(char **mtx, t_data *data)
{
	char	*change_oldpwd;
	char	*str;

	change_oldpwd = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
	if (mtx[1] == NULL)
		str = ft_strdup(data->home);
	else if (ft_strcmp(mtx[1], "-") == 0)
	{
		str = get_env_value(data->envp, "OLDPWD=");
		ft_printf("%s\n", str);
	}
	else
	{
		str = ft_strdup(mtx[1]);
		str = refactor_path(str, data, 0);
	}
	if (chdir(str) == -1)
	{
		perror("cd");
		free(change_oldpwd);
		free(str);
		return (FALSE);
	}
	return (ft_change_env(&str, change_oldpwd, data));
}
