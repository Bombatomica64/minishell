/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/09 16:27:55 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_action(int sig)
{
	if (sig == SIGINT)
		printf("\nminishell> ");
}

int	main(int argc, char **argv, char **envp)
{
	char	**input;
	int		error;
	char	*read;

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
		read = readline("minishell> ");
		add_history(read);
		if (read == NULL)
		{
			printf("EOF received, exiting\n");
			return (EXIT_SUCCESS);
		}
		else if((strcmp(read, "a")) == 0)
		{
			input = malloc(sizeof(char *) * 3);
			input[2] = NULL;
			input[0] = "ls -l";
			input[1] = "grep -n .c";
			error = pipex(input, (int []){0, 1}, envp);
			printf("error: %d\n", error);
		}
	}
	(void)argc;
	(void)argv;
	return (0);
}
