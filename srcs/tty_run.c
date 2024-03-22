/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/22 12:51:27 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	comm;

	if (parser(terminal_input, data, 0, (t_parser){NULL, NULL, 69}) == FALSE)
		return ;
	while (data->input && data->input->type != FINISH)
	{
		comm = input_exec(&data);
		if (comm.cmd)
		{
			data->error_codes = pipex(&comm, data);
			free_matrix(&comm.cmd);
		}
		else
			break ;
		if (data->in_pipe == FALSE)
		{
			if (comm.fd_in >= 0 && comm.fd_in != STDIN_FILENO)
				close(comm.fd_in);
			if (comm.fd_out >= 0 && comm.fd_out != STDOUT_FILENO)
				close(comm.fd_out);
		}
		if (data->error_codes > 0)
			break ;
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
