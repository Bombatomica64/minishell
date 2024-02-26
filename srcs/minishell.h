/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/26 15:29:44 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../pipex/pipex.h"
# include "../parser/parser.h"
# include "../built_in/built_in.h"

//input manage
void	ft_action(int sig);
void	malloc_input(char *str, t_data *data);
t_data	ft_data_init(char **envp);
void	ft_tty_exec(t_data *data, char **envp);

int		ft_splut(char *str, t_input **input);
void	fd_for_pipex(t_data *data);
void	malloc_input_pipex(t_data *data, int i);
void	input_for_pipex(t_data *data);

//fd_inout
int		open_type(char *str, t_type type);
int		fd_in(t_data data);
int		fd_out(t_data data);

t_pipex	input_exec(t_data *data);

#endif
