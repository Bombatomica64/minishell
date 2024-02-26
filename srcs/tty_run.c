/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:41:01 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/26 16:15:23 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_do_it(t_data *data, char *terminal_input, int error)
{
	if (parser(terminal_input, data) == FALSE)
		return ;
	data->pipex.fd_in = fd_in(*data);
	data->pipex.fd_out = fd_out(*data);
	// input_for_pipex(data, 0);
	int fds[2] = {data->fd_in, data->fd_out};
	error = pipex(data, fds);
	(void)error;
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
		if (pipe(fd) == -1)
			ft_error("pipe", PIPE, 132, data);
		pid = fork();
		if (pid == -1)
			ft_error("fork", FORK, 124, data);
		if (pid == 0)
			process_input(data, error);
		else
		{
			close(fd[1]);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				data->error_codes = WEXITSTATUS(status);
			if (data->error_codes == 0)
				exit (EXIT_SUCCESS);
			close(fd[0]);
		}
	}
}
