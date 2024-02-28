/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/28 11:53:27 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	*comm;

	if (parser(terminal_input, data) == FALSE)
		return ;
	while (data->input)
	{
		comm = input_exec(&data);
		if (comm->cmd)
		{
			data->error_codes += pipex(comm, data);
			free_matrix(&comm->cmd);
			free(comm);
		}
	}
}

void	process_input(t_data *data)
{
	char	*terminal_input;

	if (isatty(STDIN_FILENO) == 0)
	{
		dup2(data->original_stdin, STDIN_FILENO);
		dup2(data->original_stdout, STDOUT_FILENO);
	}
	terminal_input = readline("\033[0;94mminishell> \033[0m");
	if (terminal_input == NULL || ft_strcmp(terminal_input, "exit") == 0)
	{
		ft_printf("EOF received, exiting\n");
		free(terminal_input);
		rl_clear_history();
		free_close(data, 0);
	}
	add_history(terminal_input);
	if (*terminal_input == '\0')
		return ;
	ft_do_it(data, terminal_input);
	(void)free_return(data, 0);
}

void	ft_tty_exec(t_data *data)
{
	while (TRUE)
	{
		process_input(data);
	}
}
