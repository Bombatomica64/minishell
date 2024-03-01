/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:36 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/01 10:49:50 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../utils/utils.h"
//# pragma once

char	*strjoin_n_free1(char *line, char *buff, int index);
t_bool	check_for_open_quote(char *line);
void	uselss_quotes(char **buff, char *quote);
int		find_first(char *str, char c);
char	*read_quotes(char *c);

void	quote_check(char **line);
t_bool	lexer(char **line, t_data *data);

#endif