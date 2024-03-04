/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:28:06 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/04 10:44:50 by lmicheli         ###   ########.fr       */
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
	data.last_pipe = 0;
	data.input = NULL;
	data.in_pipe = FALSE;
	data.envp = matrix_dup(envp);
	data.home = get_env_value(data.envp, "HOME");
	data.pwd = get_env_value(data.envp, "PWD");
	return (data);
}

void	ft_data_reinit(t_data *data)
{
	if (!data)
		return ;
	data->last_pipe = 0;
	data->input = NULL;
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
}
