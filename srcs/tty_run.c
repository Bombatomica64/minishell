/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/29 11:14:52 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	*comm;
	int		i;

	parser(terminal_input, data, 0, (t_parser){NULL, NULL, 69});
	comm = ft_calloc(nbr_cmds(data) + 1, sizeof(t_pipex));
	i = 0;
	while (data->input && data->input->type != FINISH)
		comm[i++] = input_exec(&data, &comm);
	if (comm[0].cmd)
	{
		data->error_codes = pipex(comm, data);
		while (i--)
			free_matrix(&comm[i].cmd);
	}
	else
	{
		close_fds(&comm[0]);
		data->counter++;
	}
}

void	ft_action2(int sig)
{
	fprintf(stderr, "\n");
	if (sig == SIGINT)
	{
		g_duranti = 130;
	}
	if (sig == SIGQUIT)
	{
		g_duranti = 131;
	}
}

void	process_input(t_data *data)
{
	char	*terminal_input;

	terminal_input = readline("\033[0;95;1mミニシェル\033[0;96m> \033[0m");
	if (g_duranti == 130)
		data->error_codes = 130;
	g_duranti = 0;
	if (terminal_input == NULL)
	{
		free(terminal_input);
		rl_clear_history();
		free_close(&data, 0);
	}
	else if (terminal_input[skip_spaces2(terminal_input)] == '\0')
		return (free(terminal_input));
	add_history(terminal_input);
	terminal_input = expand_name(terminal_input, data);
	if (lexer(&terminal_input, data) == FALSE)
		return (free(terminal_input));
	fd_malloc(data);
	if (*terminal_input == '\0')
		return ;
	signal(SIGINT, ft_action2);
	signal(SIGQUIT, ft_action2);
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
		signal(SIGINT, ft_action);
		signal(SIGQUIT, SIG_IGN);
		process_input(data);
	}
}
//ciao :)
