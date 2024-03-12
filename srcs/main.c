/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:05:49 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/12 12:47:40 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc > 1)
	{
		dup2(2, 1);
		ft_printf("minishell: too many arguments\n");
		exit (1);
	}
	(void)argv;
	data = ft_data_init(envp);
	signal(SIGINT, ft_action);
	signal(SIGQUIT, SIG_IGN);
	ft_tty_exec(&data);
	return (0);
}
