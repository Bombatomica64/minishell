/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:33:17 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/26 11:34:19 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_for_pipex(t_data *data)
{
	int		i;

	i = 0;
	data->pipex.cmd = malloc(sizeof(char **)
			* (input_nbr_of_cmd(data->input) + 1));
	ft_malloc_err(data->pipex.cmd, "data->pipex.cmd");
	data->pipex.path = malloc(sizeof(char *)
			* (input_size(data->input) + 1));
	ft_malloc_err(data->pipex.path, "data->pipex.path");
	while (data->input)
	{
		if (data->input->type == COMMAND || data->input->type == BUILT_IN)
		{
			data->pipex.cmd[i] = ft_splitarg(data->input->node);
			data->pipex.path[i] = data->input->path;
		}
		else if (data->input->type == INPUT)
			data->pipex.filein = ft_strdup(data->input->node);
		else if (data->input->type == TRUNC || data->input->type == APPEND)
			data->pipex.fileout = ft_strdup(data->input->node);
		else if (data->input->type == HEREDOC)
			data->pipex.filein = ft_strdup(".heredoc.txt");
		i++;
	}
	data->pipex.cmd[i] = NULL;
	data->pipex.path[i] = NULL;
}
//execve("/bin/ls", ["/bin/ls", NULL], envp);