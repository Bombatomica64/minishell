/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/19 12:04:36 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_action(int sig)
{
	if (sig == SIGINT)
		printf("\nminishell> ");
}

// TODO:

// {< file} [grep e] | [wc -l] {>> file2} | [cat -e] {>> file3}  NON ESISTE, NON FUNZIONA

// [grep e] {<< file} | [wc -l]          heredoc   posso fare che in input non ci sia nulla e nel mentre leggo da terminale finche non trovo il limiter. quando trovato mando EOF

// [grep e] | [wc -l] {> file}

// [grep e] {< file1} {< file2}         multiple input files      NON ESISTE, NON FUNZIONA  l'unico input sarà file2

// [grep e] {> file1} {> file2}         multiple output files   NON ESISTE, NON FUNZIONA  l'unico output sarà file2

/* **imput = {"grep e", "wc -l", "cat -e", NULL};
struttura per gli fd*/

// grep a < file1 | uniq | wc -l > file2   grep a < file1 | uniq > file2 > file3 IN QUESTO CASO L'UNICO FILE OUTPUT é file3

//#include <fcntl.h>


void	malloc_input(char *str, t_data *data)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			nb++;
		i++;
	}
	data->input = malloc(sizeof(t_input) * (nb + 1));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		error;
	char	*terminal_input;
	int		i;

	(void) argc;
	(void) argv;
	(void) i;
	(void) error;
	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	signal(SIGINT, ft_action);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(data.original_stdin, STDIN_FILENO);
			dup2(data.original_stdout, STDOUT_FILENO);
		}
		terminal_input = readline("minishell> ");
		add_history(terminal_input);
		if (terminal_input == NULL)
		{
			printf("EOF received, exiting\n");
			return (EXIT_SUCCESS);
		}
		malloc_input(terminal_input, &data);
		data.nb_total = ft_splut(terminal_input, &data.input);
		data.fd_in = ft_fd_in(data);
		data.fd_out = ft_fd_out(data);
		input_for_pipex(&data, 0);
		error = pipex(data.in_p.cmds, data.in_p.files, data.in_p.fds, envp);
	}
	free(data.input);
	free(terminal_input);
	return (0);
}
