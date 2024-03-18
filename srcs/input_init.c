/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:28:06 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/14 16:08:45 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_action(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n\033[0;95;1mミニシェル\033[0;96m> \033[0m");
	}
}

void	malloc_input(char *str)
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
}

t_data	ft_data_init(char **envp)
{
	t_data	data;

	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	data.error_codes = 0;
	data.last_pipe = 0;
	data.input = NULL;
	data.in_pipe = FALSE;
	data.fd = NULL;
	data.cmd_nbr = 0;
	data.pipe_nbr = 0;
	data.envp = matrix_dup(envp);
	data.home = get_env_value(data.envp, "HOME");
	data.pwd = get_env_value(data.envp, "PWD");
	return (data);
}

void	ft_data_reinit(t_data *data)
{
	if (!data)
		return ;
	data->cmd_nbr = 0;
	data->last_pipe = 0;
	data->pipe_nbr = 0;
	data->in_pipe = FALSE;
	data->input = NULL;
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
}
