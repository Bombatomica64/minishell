/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/04/15 11:52:21 by gduranti         ###   ########.fr       */
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

//fd_inout
int		open_type(char *str, t_type type, t_data *data);
int		fd_io_check(int fd_io, int fd_to_check, int pipe_fd);
t_pipex	input_exec(t_data **data);

/**
 * @brief Function that returns the number of arguments in a command string
 * @param str string to be checked
 * @param i index of the string
 * @param nbr_args number of arguments
 * @return the number of arguments in the string
*/
int		ft_arg_count(char *str, int i, int nbr_args);

/**
 * @brief Function that allocates a new string with the argument
 * @param str string to be checked
 * @param c character used as a check for quotes
 * @param i index of the new string
 * @param j index of the old string
 * @return a new string with the length of the argument
*/
char	*ft_rowfill(char *str, int *j, int i);

/**
 * @brief Function that creates the matrix of a command and arguments
 * @param str string to be splitted
 * @return the matrix with command and arguments
*/
char	**ft_splitarg(char *str);

/**
 * @brief adds the heredoc functionality to the program
 * @param limiter string that will be used as a limiter
 * @param data data envp to be passed to the function
 * @param pid pid to be passed to the function
 * @return fd with the file descriptor of the pipe fd[0]
*/
int		heredoc_creat(char *limiter, t_data *data, pid_t pid, t_pipex *comm);

#endif
