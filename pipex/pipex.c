/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/09 17:51:53 by mruggier         ###   ########.fr       */
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

int	pipex(char **input, int *fd[2], char **envp)
{
	t_pipex	pipex;

	pipex.fd_in = fd[0];
	pipex.fd_out = fd[1];
	pipex.cmd1 = ft_split(input[0], ' ');
	pipex.cmd2 = ft_split(input[1], ' ');
	pipex.path1 = path_execve(pipex.cmd1[0], envp);
	if (pipex.path1 == NULL)
		ft_error("1", NO_PATH);
	pipex.path2 = path_execve(pipex.cmd2[0], envp);
	if (pipex.path2 == NULL)
		ft_error("2", NO_PATH);
	checkfile_fd(&pipex);
	ft_execute(&pipex);
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
