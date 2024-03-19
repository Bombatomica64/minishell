/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:29:56 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/19 10:46:40 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../pipex/pipex.h"
# pragma once

//parser
t_type	ft_file_type(char *str, int *offset);
t_bool	parser(char *str, t_data *data, int offset);
int		count_limiter(char *str, t_quote squote);
t_bool	is_double_operator(char *str, int i, t_quote squote);
t_bool	quote_error(char *tmp, t_bool *quote);

//expand_variables_utils
char	*expand_name(char *str, t_data *data, t_bool open, char type, int *off);
char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data, int *off);

//quotes
void	quote_start(t_bool *quote, char c, char *quote_type);
void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type);
void	quote_display(char *quote_type);
t_bool	check_quote(char *tmp, char quote_type, t_type type, int index);

#endif