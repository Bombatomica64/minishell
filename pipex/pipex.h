/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:52:32 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/19 16:36:15 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../utils/utils.h"

char	*path_execve(char *command, char **envp);
void	child(t_pipex *pipex, int i);
void	parent(t_pipex *pipex, int i);
int		checkfile_fd(t_pipex *pipex);
void	ft_execute(t_pipex *pipex);

/**
 * @brief This function will execute 2 commands between a SINGLE pipe
 * @example pipex(ft_split(commands, '|'), fd, , envp);
 * @param input The commands to execute divided by the pipe
 * @param fd The file descriptors to use and the fd to connect multiple pipes
 * @param envp The environment variables to use
 * @return 0 if the commands are executed correctly;
 * -1 if an error occurred
*/
int		pipex(t_data *data, int fd[2], char **envp);

#endif
