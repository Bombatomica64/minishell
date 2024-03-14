/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:36 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/14 18:14:16 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../parser/parser.h"
# include "../bonus/bonus.h"
# pragma once

t_bool	open_quote_check(char *line, char *new_quote);
void	uselss_quotes(char **buff, char *quote);
char	*read_quotes(char *c);

void	quote_check(char **line);
t_bool	lexer(char **line, t_data *data);
t_bool	lexer_error(char *error, t_data *data, char c);
int		pipe_count(char *line, t_data *data);
t_bool	pipe_check(char *line);
t_bool	check_middle(char *line, t_quote *squote);
t_bool	check_start_end(char *line, t_quote *squote);

#endif

// Path: lexer/lexer.c