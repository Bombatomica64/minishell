/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:28:06 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/20 11:38:31 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_action(int sig)
{
	if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

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
	data->nb_total = nb;
}

t_data	ft_data_init(char **envp)
{
	t_data	data;

	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	data.nb_total = 0;
	data.nb_cmds = 0;
	data.nb_files = 0;
	data.input_found = FALSE;
	data.in_p.cmds = NULL;
	data.in_p.files = NULL;
	data.in_p.fds[0] = 0;
	data.in_p.fds[1] = 0;
	data.fd_in = 0;
	data.fd_out = 0;
	data.input = NULL;
	data.envp = matrix_dup(envp);
	data.directory = getcwd(NULL, 0);
	return (data);
}
