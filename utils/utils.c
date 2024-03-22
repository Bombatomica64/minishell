/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:10:41 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/22 15:25:21 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_iscmd(t_input *input, t_data *data)
{
	(void)data;
	if (!input)
		return (ERROR);
	if (input->type == BUILT_IN || input->type == COMMAND)
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
