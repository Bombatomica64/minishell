/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/08 17:51:56 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

static void	ft_action(int sig)
{
	printf("\nyou can't kill me\n");
}

int main(int argc, char **argv, char **envp)
{
	char	*arg[] = {"ls", NULL};
	char	*arg2[] = {"echo", "ciao", NULL};
	char	*inpt;
	int		i = 0;

	signal(SIGINT, ft_action);
	while ( i < 10 )
	{
		inpt = readline("MINISHELL: ");
		add_history(inpt);
		if ((strcmp(inpt, "ls")) == 0)
		{
			execve("/usr/bin/ls", arg, NULL);
		}
		if ((strcmp(inpt, "echo")) == 0)
			execve("/usr/bin/echo", arg2, NULL);
		++i;
	}
}
