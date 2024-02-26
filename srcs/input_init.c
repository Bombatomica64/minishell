/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:28:06 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/26 16:29:45 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_action(int sig)
{
	if (sig == SIGINT)
	{
		printf("\033[0;94m\nminishell> \033[0m");
	}
}

void	malloc_input(char *str, t_data *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			nb++;
		i++;
	}
	data->nb_total = nb;
}

t_data	ft_data_init(char **envp)
{
	t_data	data;

	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	data.nb_total = 0;
	data.nb_cmds = 0;
	data.nb_files = 0;
	data.input_found = FALSE;
	data.fd_in = 0;
	data.fd_out = 0;
	data.input = NULL;
	data.fd[1] = STDOUT_FILENO;
	data.fd[0] = STDIN_FILENO;
	data.envp = matrix_dup(envp);
	data.home = get_env_value(data.envp, "HOME=");
	return (data);
}

void	ft_data_reinit(t_data *data)
{
	if (!data)
		return ;
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
	data->nb_total = 0;
	data->nb_cmds = 0;
	data->nb_files = 0;
	data->input_found = FALSE;
	data->fd_in = 0;
	data->fd_out = 0;
	data->input = NULL;
	data->fd[1] = STDOUT_FILENO;
	data->fd[0] = STDIN_FILENO;
}
