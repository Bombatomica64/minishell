/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 12:24:26 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_iscmd(t_input *input, t_data *data)
{
	//struct stat st;

	(void)data;
	if (!input)
		return (ERROR);
	if (input->type == BUILT_IN)
		return (TRUE);
	/*if (stat(input->path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))		
		{
			ft_putstr_fd(input->path, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			data->error_codes = 126;
			return (ERROR);
		}
		else if (check_access(input->path, input->type, data) != 0)
		{
			ft_putstr_fd(input->path, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			data->error_codes = 126;
			return (ERROR);
		}
	}
	else
	{
		ft_putstr_fd(input->node, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->error_codes = 127;
	}*/
	if (input->type == COMMAND)
		return (TRUE);
	return (FALSE);
}

t_bool	ft_islimiter(char c)
{
	if (c == '<' || c == '>' || c == '\0' || c == '|')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isquote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	return (FALSE);
}

t_bool	ft_isbuiltin(char *cmd)
{
	char	*str;
	int		i;

	i = 0;
	if (!cmd)
		return (ERROR);
	while (cmd[i] && ft_isspace(cmd[i]) == FALSE)
		i++;
	str = ft_strndup(cmd, i);
	if (ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "pwd") == 0
		|| ft_strcmp(str, "echo") == 0
		|| ft_strcmp(str, "exit") == 0
		|| ft_strcmp(str, "unset") == 0
		|| ft_strcmp(str, "export") == 0)
		return (free(str), TRUE);
	free(str);
	return (FALSE);
}
