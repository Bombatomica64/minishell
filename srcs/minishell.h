/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:20 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/20 16:15:07 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../pipex/pipex.h"

//input manage
void	ft_action(int sig);
void	malloc_input(char *str, t_data *data);
t_data	ft_data_init(char **envp);
void	ft_tty_exec(t_data *data, char **envp);

int		ft_splut(char *str, t_input **input);
int		ft_fd_out(t_data data);
int		ft_fd_in(t_data data);
void	fd_for_pipex(t_data *data);
void	malloc_input_pipex(t_data *data, int i);
void	input_for_pipex(t_data *data, int i);
//parser
t_type	ft_file_type(char **str);
void	parser(char *str, t_data *data);
char	*join_char(char *str, char c);

//quotes
void	quote_start(t_bool *quote, char c, char *quote_type);
void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type);
void	quote_display(char *quote_type);
t_bool	check_quote(char *tmp, char quote_type);
#endif
