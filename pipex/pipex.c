/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/19 16:01:11 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_execve(char *command, char **envp)
{
	int		i;
	char	*tmp_path;
	char	*possible_path;
	char	**all_paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i] != NULL)
	{
		tmp_path = ft_strjoin("/", command);
		possible_path = ft_strjoin(all_paths[i], tmp_path);
		free(tmp_path);
		if (access(possible_path, F_OK) == 0)
			return (free_matrix(all_paths), possible_path);
		else
			free(possible_path);
		i++;
	}
	return (NULL);
}

int	ft_matrixlen(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

int	pipex(t_data *data, int fd[2], char **envp)
{
	int		i;
	int		len;

	data->pipex.fd_in = fd[0];
	data->pipex.fd_out = fd[1];
	len = ft_matrixlen(data->in_p.cmds);
	data->pipex.cmd = malloc(sizeof(char **) * (len + 1));
	data->pipex.path = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (data->in_p.cmds[i] != NULL)
	{
		data->pipex.cmd[i] = ft_split(data->in_p.cmds[i], ' ');
		data->pipex.path[i] = path_execve(data->pipex.cmd[i][0], envp);
		if (data->pipex.path[i] == NULL)
			ft_error("missing in the path", NO_PATH, 127);
		i++;
	}
	data->pipex.cmd[i] = NULL;
	data->pipex.path[i] = NULL;
	checkfile_fd(data);
	ft_execute(data);
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
