/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/15 17:19:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_action(int sig)
{
	if (sig == SIGINT)
		printf("\nminishell> ");
}


// TODO:

// [grep e] {< file} | [wc -l] {>> file2} | [cat -e] {>> file3}  NON ESISTE, NON FUNZIONA

// [grep e] {<< file} | [wc -l]          heredoc   posso fare che in input non ci sia nulla e nel mentre leggo da terminale finche non trovo il limiter. quando trovato mando EOF

// [grep e] | [wc -l] {> file}

// [grep e] {< file1} {< file2}         multiple input files      NON ESISTE, NON FUNZIONA  l'unico input sarà file2

// [grep e] {> file1} {> file2}         multiple output files   NON ESISTE, NON FUNZIONA  l'unico output sarà file2

/* **imput = {"grep e", "wc -l", "cat -e", NULL};
struttura per gli fd*/

// grep a < file1 | uniq | wc -l > file2   grep a < file1 | uniq > file2 > file3 IN QUESTO CASO L'UNICO FILE OUTPUT é file3

//#include <fcntl.h>


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		error;
	char	*terminal_input;
	int		i;
	
	int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
	signal(SIGINT, ft_action);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 0)
		{
			dup2(original_stdin, STDIN_FILENO);
    		dup2(original_stdout, STDOUT_FILENO);
		}
		terminal_input = readline("minishell> ");
		add_history(terminal_input);
		if (terminal_input == NULL)
		{
			printf("EOF received, exiting\n");
			return (EXIT_SUCCESS);
		}
		
		data.input = malloc(sizeof(t_input) * 8); // calc number of commands and files
		
		data.nb_total = ft_splut(terminal_input, &data.input);

		i = 0;
		while (i < data.nb_total)
		{
			if (data.input[i].is_a_file == TRUE)
				printf("file[%d]: %s\n", i, data.input[i].file.name);
			else
				printf("cmd[%d]: %s\n", i, data.input[i].cmd.name);
			i++;
		}


		data.fd_in = ft_fd_in(data);
		ft_fd_out(&data);

		printf("fd_in: %d\n", data.fd_in);
		i = 0;
		while (data.fd_out[i] != -1)
		{
			printf("fd_out[%d]: %d\n", i, data.fd_out[i]);
			i++;
		}

		



		
		error = pipex((char *[]){data.input[0].cmd.name, data.input[1].cmd.name, NULL}, (char *[]){NULL, data.input[2].file.name}, (int []){data.fd_in, data.fd_out[0]}, envp);

       


	}
	(void)argc;
	(void)argv;
	(void)envp;
	(void)i;
	(void)error;

	free(data.input);
	free(data.fd_out);
	free(terminal_input);
	

	
	return (0);

}
