/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:52:32 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/09 12:48:08 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../utils/utils.h"

typedef struct s_pipex
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
	char	*filein;
	char	*fileout;
	int		fd_in;
	int		fd_out;
}				t_pipex;

char	*path_execve(char *command, char **envp);
void	child(t_pipex *pipex);
void	parent(t_pipex *pipex);
int		checkfile_fd(t_pipex *pipex);
void	ft_execute(t_pipex *pipex);

/**
 * @brief This function will execute 2 commands between a SINGLE pipe
 * @example pipex(ft_split(commands, '|'), fd, , envp);
 * @param input The commands to execute divided by the pipe
 * @param fd The file descriptors to use
 * @param envp The environment variables to use
 * @return 0 if the commands are executed correctly;
 * -1 if an error occurred
*/
int		pipex(char **input, int fd[2], char **envp);

#endif
