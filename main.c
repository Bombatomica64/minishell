/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/09 12:29:36 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_action(int sig)
{
	printf("\nyou can't kill me\n");
	(void)sig;
}

int	main(int argc, char **argv, char **envp)
{
	char	**input;
	int		error;
	char	*read;
	int		i;

	int original_stdin = dup(STDIN_FILENO);
    int original_stdout = dup(STDOUT_FILENO);
	i = 0;
	signal(SIGINT, ft_action);
	while ( i < 5 )
	{
		if (isatty(STDIN_FILENO))
		{
			printf("stdin is a terminal\n");
		}
		else 
		{
			dup2(original_stdin, STDIN_FILENO);
    		dup2(original_stdout, STDOUT_FILENO);
			printf("stdin has been redirected\n");
		}
		
		read = readline("minishell> ");
		add_history(read);
		if (read == NULL)
		{
			printf("EOF received, exiting\n");
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
		i++;
	}
	(void)argc;
	(void)argv;
	return (0);
}
