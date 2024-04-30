/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/30 14:59:17 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	input_exec_pre(t_data **data, t_pipex **comm, int *i)
{
	(*comm)[(*i)] = input_exec(data, comm);
	if ((*comm)[(*i)++].cmd != NULL)
		return (TRUE);
	return (ERROR);
}

void	ft_do_it(t_data *data, char *terminal_input)
{
	t_pipex	*comm;
	int		i;
	int		check;

	parser(terminal_input, data, 0, (t_parser){NULL, NULL, 69});
	comm = ft_calloc(nbr_cmds(data) + 1, sizeof(t_pipex));
	i = 0;
	while (data->input && data->input->type != FINISH)
	{
		check = input_exec_pre(&data, &comm, &i);
		if (check == ERROR)
			break ;
	}
	if (check == TRUE)
		data->error_codes = pipex(comm, data);
	else
	{
		close_fds(&comm[0]);
		data->counter++;
	}
	while (i--)
		free_matrix(&comm[i].cmd);
	free(comm);
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
