/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/19 15:42:55 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tty_exec(t_data *data, char **envp)
{
	int		error;
	char	*terminal_input;

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
			exit (EXIT_SUCCESS);
		}
		if (terminal_input[0] == '\0')
			continue ;
		malloc_input(terminal_input, data);
		data->nb_total = ft_splut(terminal_input, &(data->input));
		data->fd_in = ft_fd_in(*data);
		data->fd_out = ft_fd_out(*data);
		input_for_pipex(data, 0);
		error = pipex(data->in_p.cmds, data->in_p.files, data->in_p.fds, envp);
	}
	(void) error;
	free(terminal_input);
}