/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:30:19 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/02 12:50:10 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strncpy_noquote(char *str, int start, int end)
{
	char	*dst;
	int		i;
	t_quote	squote;

	squote = (t_quote){FALSE, 0};
	if (!str)
		return (NULL);
	dst = malloc(sizeof(char) * (end - start + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (str[start])
	{
		if (ft_isquote(str[start]))
		{
			quote_start(&squote.open, str[start], &squote.type);
			while (ft_isquote(str[start])
				&& ((squote.open && str[start] == squote.type) || !squote.open))
				quote_start(&squote.open, str[++(start)], &squote.type);
		}
		if (!str[start] || (ft_isspace(str[start]) == TRUE && squote.open == FALSE))
			break ;
		dst[i++] = str[(start)++];
	}
	// while (start < end)
	// {
	// 	quote_start(&squote.open, str[start], &squote.type);
	// 	dst[i] = str[start];
	// 	i++;
	// 	start++;
	// }
	dst[i] = '\0';
	return (dst);
}

t_bool	is_double_operator(char *str, int i, t_quote squote)
{
	return (((str[i] == '<' && str[i + 1] == '<')
			|| (str[i] == '>' && str[i + 1] == '>'))
		&& squote.type == FALSE);
}

t_bool	ft_iscmd(t_input *input, t_data *data)
{
	if (!input)
		return (ERROR);
	if (input->type == BUILT_IN || input->type == COMMAND)
		return (file_check(input->node, data));
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

void	close_fds(t_pipex *comm)
{
	if (comm->fd_in != STDIN_FILENO && comm->fd_in != -1)
		close(comm->fd_in);
	if (comm->fd_out != STDOUT_FILENO && comm->fd_out != -1)
		close(comm->fd_out);
}
