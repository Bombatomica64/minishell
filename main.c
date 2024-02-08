/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/08 18:31:09 by lmicheli         ###   ########.fr       */
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

	signal(SIGINT, ft_action);
	input = malloc(sizeof(char *) * 3);
	input[2] = NULL;
	input[0] = "ls -l";
	input[1] = "grep -e .c";
	error = pipex(input, (int []){0, 1}, envp);
	printf("error: %d\n", error);
	(void)argc;
	(void)argv;
	return (0);
}
