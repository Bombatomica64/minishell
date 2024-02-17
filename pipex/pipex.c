/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/17 02:05:32 by marvin           ###   ########.fr       */
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

int	pipex(char **cmds, char **files, int fd[2], char **envp)
{
	t_pipex	pipex;
	int		i;
	int		len;

	pipex.filein = files[0];
	pipex.fileout = files[1];
	pipex.fd_in = fd[0];
	pipex.fd_out = fd[1];
	len = ft_matrixlen(cmds);
	pipex.cmd = malloc(sizeof(char **) * (len + 1));
	pipex.path = malloc(sizeof(char *) * (len + 1));
	i = 0;
	while (cmds[i] != NULL)
	{
		pipex.cmd[i] = ft_split(cmds[i], ' ');
		pipex.path[i] = path_execve(pipex.cmd[i][0], envp);
		if (pipex.path[i] == NULL)
			ft_error("1", NO_PATH);
		i++;
	}
	pipex.cmd[i] = NULL;
	pipex.path[i] = NULL;
	checkfile_fd(&pipex);
	ft_execute(&pipex);
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
