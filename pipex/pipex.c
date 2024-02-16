/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/16 22:28:01 by marvin           ###   ########.fr       */
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

int	pipex(char **cmds, char **files, int fd[2], char **envp)
{
	t_pipex	pipex;

	printf("cmds[0] = %s\n", cmds[0]);
	printf("cmds[1] = %s\n", cmds[1]);
	pipex.filein = files[0];
	pipex.fileout = files[1];
	printf("filein = %s\n", pipex.filein);
	printf("fileout = %s\n", pipex.fileout);
	pipex.fd_in = fd[0];
	printf("fd[0] = %d\n", pipex.fd_in);
	pipex.fd_out = fd[1];
	printf("fd[1] = %d\n", pipex.fd_out);
	pipex.cmd1 = ft_split(cmds[0], ' ');
	pipex.cmd2 = ft_split(cmds[1], ' ');
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
