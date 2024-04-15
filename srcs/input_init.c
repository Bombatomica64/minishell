/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:28:06 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/15 11:31:14 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**matrix_dup(char **matrix)
{
	char	**new_matrix;
	int		i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
		i++;
	new_matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new_matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
	{
		new_matrix[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

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

void	malloc_input(char *str)
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
}

t_data	ft_data_init(char **envp)
{
	t_data	data;

	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	data.error_codes = 0;
	data.counter = 0;
	data.input = NULL;
	data.in_pipe = FALSE;
	data.fd = NULL;
	data.cmd_nbr = 0;
	data.pipe_nbr = 0;
	data.envp = matrix_dup(envp);
	data.home = get_env_value(data.envp, "HOME");
	data.pwd = get_env_value(data.envp, "PWD");
	return (data);
}

void	ft_data_reinit(t_data *data)
{
	if (!data)
		return ;
	data->cmd_nbr = 0;
	data->counter = 0;
	data->pipe_nbr = 0;
	data->in_pipe = FALSE;
	data->input = NULL;
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
}
