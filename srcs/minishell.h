/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/27 17:58:20 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../pipex/pipex.h"
# include "../parser/parser.h"
# include "../built_in/built_in.h"
# include "../lexer/lexer.h"
//# pragma once

//input manage
void	ft_action(int sig);
void	malloc_input(char *str);
t_data	ft_data_init(char **envp);
void	ft_data_reinit(t_data *data);
void	ft_tty_exec(t_data *data);

void	fd_malloc(t_data *data);

int		ft_splut(char *str, t_input **input);
void	fd_for_pipex(t_data *data);
void	malloc_input_pipex(t_data *data, int i);

//fd_inout
int		open_type(char *str, t_type type, t_data *data);
void	close_fds(t_pipex *comm);
int		fd_io_check(int fd_io, int fd_to_check, int pipe_fd);
t_pipex	input_exec(t_data **data);

#endif
