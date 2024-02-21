/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/21 16:25:23 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char **envp, char *terminal_input, int error)
{
	parser(terminal_input, data);
	data->fd_in = fd_in(*data);
	data->fd_out = fd_out(*data);
	// input_for_pipex(data, 0);
	error = pipex(data, (int *){data->fd_in, data->fd_out});
	(void) envp;
	(void) error;
	(void) data;
	(void) terminal_input;
}

void	ft_tty_exec(t_data *data, char **envp)
{
	int		error;
	char	*terminal_input;

	error = 0;
	// (void) envp;
	while (1)
	{
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(data->original_stdin, STDIN_FILENO);
			dup2(data->original_stdout, STDOUT_FILENO);
		}
		terminal_input = readline("minishell> ");
		add_history(terminal_input);
		if (terminal_input == NULL)
		{
			printf("EOF received, exiting\n");
			if (terminal_input)
				free(terminal_input);
			return ;
		}
		if (terminal_input[0] == '\0')
			continue ;
		ft_do_it(data, envp, terminal_input, error);
	}
	free(terminal_input);
}
