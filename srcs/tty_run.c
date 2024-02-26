/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/26 17:14:57 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input, int error)
{
	t_pipex	comm;

	if (parser(terminal_input, data) == FALSE)
		return ;
	while (data->input)
	{
		comm = input_exec(data);
		if (comm.cmd)
			data->error_codes += pipex(&comm, data);
	}
}

void	process_input(t_data *data, int error)
{
	char	*terminal_input;

	if (isatty(STDIN_FILENO) == 0)
	{
		dup2(data->original_stdin, STDIN_FILENO);
		dup2(data->original_stdout, STDOUT_FILENO);
	}
	terminal_input = readline("\033[0;94mminishell> \033[0m");
	add_history(terminal_input);
	if (terminal_input == NULL)
	{
		ft_printf("EOF received, exiting\n");
		free(terminal_input);
		if (terminal_input)
			freenclose(data);
		exit (1024);
	}
	if (terminal_input[0] == '\0')
		return ;
	ft_do_it(data, terminal_input, error);
	free(terminal_input);
}

void	ft_tty_exec(t_data *data, char **envp)
{
	int		error;
	int		status;
	int		fd[2];
	pid_t	pid;

	(void)envp;
	error = 0;
	while (TRUE)
	{
		process_input(data, error);
	}
}
