/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/02 10:18:00 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	comm;

	parser(expand_name(terminal_input, data),
		data, 0, (t_parser){NULL, NULL, 69});
	while (data->input && data->input->type != FINISH)
	{
		comm = input_exec(&data);
		if (comm.cmd)
		{
			data->error_codes = pipex(&comm, data);
			free_matrix(&comm.cmd);
		}
		else
		{
			close_fds(&comm);
			data->counter++;
		}
		if (data->in_pipe == FALSE)
			close_fds(&comm);
	}
}

void	process_input(t_data *data)
{
	char	*terminal_input;

	terminal_input = readline("\033[0;95;1mミニシェル\033[0;96m> \033[0m");
	if (terminal_input == NULL)
	{
		free(terminal_input);
		rl_clear_history();
		free_close(&data, 0);
	}
	else if (terminal_input[skip_spaces2(terminal_input)] == '\0')
		return (free(terminal_input));
	if (lexer(&terminal_input, data) == FALSE)
		return (free(terminal_input));
	fd_malloc(data);
	add_history(terminal_input);
	if (*terminal_input == '\0')
		return ;
	ft_do_it(data, terminal_input);
	free_return(&data, 0);
	ft_data_reinit(data);
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
//ciao :)