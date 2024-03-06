/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/06 11:30:01 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	comm;

	if (parser(terminal_input, data) == FALSE)
		return ;
	while (data->input && data->input->next)
	{
		comm = input_exec(&data);
		if (comm.cmd)
		{
			data->error_codes += pipex(&comm, data);
			free_matrix(&comm.cmd);
		}
	}
	if (data->input
		&& (data->input->type == COMMAND || data->input->type == BUILT_IN))
	{
		comm = input_exec(&data);
		if (comm.cmd)
		{
			data->error_codes += pipex(&comm, data);
			free_matrix(&comm.cmd);
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
	lexer(&terminal_input, data);
	fd_malloc(data);
	printf("data->pipe_nbr: %d\n", data->pipe_nbr);
	if (terminal_input == NULL)
	{
		ft_printf("EOF received, exiting\n");
		free(terminal_input);
		rl_clear_history();
		free_close(&data, 0);
	}
	add_history(terminal_input);
	if (*terminal_input == '\0')
		return ;
	ft_do_it(data, terminal_input);
	(void)free_return(&data, 0);
}

void	fd_malloc(t_data *data)
{
	int		i;

	i = 0;
	if (data->pipe_nbr == 0)
		return ;
	data->fd = malloc((sizeof(int *)) * data->pipe_nbr);
	while (i < data->pipe_nbr)
	{
		data->fd[i] = malloc((sizeof(int)) * 2);
		i++;
	}
}

void	ft_tty_exec(t_data *data)
{
	while (TRUE)
	{
		process_input(data);
	}
}
