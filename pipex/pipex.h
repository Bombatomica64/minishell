/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:52:32 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/26 15:31:10 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../utils/utils.h"

char	*path_execve(char *command, char **envp);
void	child(t_pipex *pipex, t_data *data, int fd[2]);
void	parent(t_data *data, int i);
int		checkfile_fd(t_data *data);
void	ft_execute(t_data *data);

/**
 * @brief This function will execute 2 commands between a SINGLE pipe
 * @example pipex(ft_split(commands, '|'), fd, , envp);
 * @param data the data containing all the information of a command line 
 * @param fd The file descriptors to use
 * @return 0 if the commands are executed correctly;
 * -1 if an error occurred
*/
int		pipex(t_pipex *pipex, int fd[2], t_data *data);

#endif
