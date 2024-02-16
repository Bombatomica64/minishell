/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/16 23:07:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "data.h"
# include "pipex/pipex.h"

// typedef enum e_error
// {
// 	NO_PATH,
// 	DUP,
// 	EXECVE,
// 	PIPE,
// 	FORK,
// 	ACCESS,
// 	OPEN
// }	t_error;



int		ft_splut(char *str, t_input **input);
int		ft_fd_out(t_data data);
int		ft_fd_in(t_data data);
void	fd_for_pipex(t_data *data);
void	malloc_input_pipex(t_data *data, int i);
void	input_for_pipex(t_data *data, int i);

#endif
