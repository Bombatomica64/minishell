/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:18:56 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/13 15:33:37 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"
/*void	print_pwds(char **envp)
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
}*/

char	*ft_tilde(char *str, t_data *data)
{
	char	*user;
	char	*tmp;

	user = get_env_value(data->envp, "USER");
	if (str[1] == '\0' || str[1] == '/')
		tmp = ft_strjoin(data->home, str + 1);
	else if (str[1] == '+' && (str[2] == '\0' || str[2] == '/'))
	{
		tmp = ft_strdup(data->pwd);
		if (str[2] == '/')
			tmp = ft_newstrjoin(tmp, str + 2);
	}
	else if (str[1] == '-' && (str[2] == '\0' || str[2] == '/'))
	{
		tmp = get_env_value(data->envp, "OLDPWD");
		if (str[2] == '/')
			tmp = ft_newstrjoin(tmp, str + 2);
	}
	else if (ft_strnstr(str, user, ft_strlen(str)) != NULL)
		tmp = ft_strjoin(data->home, str + ft_strlen(user) + 1);
	else
		tmp = ft_strjoin("/nfs/homes/", str + 1);
	free(str);
	free(user);
	return (tmp);
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
	if (ft_strcmp(to_remove, "../") == 0 || (ft_strcmp(to_remove, "..") == 0))
	{
		char_path = 2;
		while (str[j - char_path] != '/')
			char_path++;
		tmp[j - char_path + 1] = '\0';
	}
	tmp = ft_newstrjoin(tmp, str + i + ft_strlen(to_remove));
	free(str);
	return (tmp);
}

char	*refactor_path(char *tmp, t_data *data, int i)
{
	char	*str;

	str = ft_strdup(tmp);
	if (*str == '~')
		str = ft_tilde(str, data);
	else if (*str != '/')
		str = ft_strjoin_2(data->pwd, ft_strjoin_2("/", str));
	while (str[i] != '\0')
	{
		if (strncmp(str + i, "./", 2) == 0 || strncmp(str + i, "../", 3) == 0
			|| strncmp(str + i, "..", 2) == 0)
		{
			if (strncmp(str + i, "./", 2) == 0)
				str = ft_remove_chars(str, "./", i);
			else if (strncmp(str + i, "../", 3) == 0)
				str = ft_remove_chars(str, "../", i);
			else if (strncmp(str + i, "..", 2) == 0)
				str = ft_remove_chars(str, "..", i);
			i = 0;
		}
		i++;
	}
	while (str[ft_strlen(str) - 1] == '/' || str[ft_strlen(str) - 1] == '.')
		str[ft_strlen(str) - 1] = '\0';
	return (str);
}

t_bool	ft_change_env(char **str, char *oldpwd, t_data *data)
{
	int	i;

	i = find_in_env(data->envp, "PWD");
	free(data->envp[i]);
	data->envp[i] = ft_strjoin("PWD=", *str);
	free(data->pwd);
	data->pwd = ft_strdup(data->envp[i] + 4);
	i = find_in_env(data->envp, "OLDPWD");
	free(data->envp[i]);
	data->envp[i] = oldpwd;
	free(*str);
	return (TRUE);
}

//TODO: cd "~/ecc" o < "~", tra virgolette è un path relativo e ~ è il nome

t_bool	ft_cd(char **mtx, t_data *data)
{
	char	*change_oldpwd;
	char	*str;

	if (mtx[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (FALSE);
	}
	change_oldpwd = ft_strjoin_2("OLDPWD=", getcwd(NULL, 0));
	if (mtx[1] == NULL)
		str = ft_strdup(data->home);
	else if (ft_strcmp(mtx[1], "-") == 0)
		str = get_env_value(data->envp, "OLDPWD");
	else
		str = refactor_path(ft_strdup(mtx[1]), data, 0);
	if (chdir(str) == -1)
	{
		perror("cd");
		free(change_oldpwd);
		free(str);
		return (FALSE);
	}
	ft_change_env(&str, change_oldpwd, data);
	return (TRUE);
}
