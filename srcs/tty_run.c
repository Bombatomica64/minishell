/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/13 11:39:41 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	comm;

	if (parser(terminal_input, data) == FALSE)
		return ;
	while (data->input && data->input->type != FINISH)
	{
		comm = input_exec(&data);
		if (comm.cmd)
		{
			data->error_codes = pipex(&comm, data);
			free_matrix(&comm.cmd);
		}
		if (data->error_codes > 0)
			break ;
	}
}

void	process_input(t_data *data)
{
	char	*terminal_input;

	terminal_input = readline("\033[0;95;1mミニシェル\033[0;96m> \033[0m");
	if (lexer(&terminal_input, data) == FALSE)
	{
		free(terminal_input);
		return ;
	}
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
	/*while (data->bonus)
	{
		ft_do_it(data, data->bonus->str);
		free_return(&data, 0);
		if (data->error_codes > 0)
			break ;
	}*/
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
