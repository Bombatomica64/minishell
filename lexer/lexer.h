/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:52:36 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/29 18:28:51 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../utils/utils.h"

char	*strjoin_n_free1(char *line, char *buff, int index);
t_bool	check_for_open_quote(char *line, char *quote);
void	uselss_quotes(char **buff, char *quote);
int		find_first(char *str, char c);
char	*read_quotes(char *c);

void	quote_check(char *line);

#endif