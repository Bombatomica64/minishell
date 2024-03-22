/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/22 17:35:51 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define BRIGHT_BLACK "\033[0;90m"
# define BRIGHT_RED "\033[0;91m"
# define BRIGHT_GREEN "\033[0;92m"
# define BRIGHT_YELLOW "\033[0;93m"
# define BRIGHT_BLUE "\033[0;94m"
# define BRIGHT_MAGENTA "\033[0;95m"
# define BRIGHT_CYAN "\033[0;96m"
# define BRIGHT_WHITE "\033[0;97m"
# define END "\033[0m"
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"
# define BG_BRIGHT_BLACK "\033[100m"
# define BG_BRIGHT_RED "\033[101m"
# define BG_BRIGHT_GREEN "\033[102m"
# define BG_BRIGHT_YELLOW "\033[103m"
# define BG_BRIGHT_BLUE "\033[104m"
# define BG_BRIGHT_MAGENTA "\033[105m"
# define BG_BRIGHT_CYAN "\033[106m"
# define BG_BRIGHT_WHITE "\033[107m"
# define BG_END "\033[49m"
//printf(RED "Questo testo sarà rosso" END "\n");

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
// int		fd_in(t_data data);
// int		fd_out(t_data data);

t_pipex	input_exec(t_data **data);

#endif
