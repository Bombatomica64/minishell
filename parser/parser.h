/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:29:56 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/03 16:20:55 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../pipex/pipex.h"
# pragma once

typedef struct s_curs
{
	int		k;
	int		j;
}	t_curs;

//parser
t_type	ft_file_type(char *str, int *offset);
t_bool	get_command(int *off, char *str, t_parser *prs, t_data *data);
t_bool	get_inout(int *off, char *str, t_parser *prs, t_data *data);
int		i_skip_pippe(char *str, int i);
char	*cut_pars_str(char *str, char *node);
t_bool	parser(char *str, t_data *data, int offset, t_parser prs);
int		count_limiter(char *str, t_quote squote);
t_bool	is_double_operator(char *str, int i, t_quote squote);
t_bool	quote_error(char *tmp, t_bool *quote);
char	*ft_reparsing(char *str, int i, t_data *data, t_quote squote);
int		get_cmd_name(char *str, int *offset, t_quote squote);
char	*remove_quotes(char *str, int *offset);

//expand_variables_utils
char	*expand_name(char *str, t_data *data);
char	*expand_dollar(char *str, char *tmp, size_t *i, t_data *data);
void	expand_list(t_data *data);

//quotes
// void	quote_start(t_bool *quote, char c, char *quote_type);
// void	quote_waiting(char **tmp, t_bool *quote, char *quote_type, t_type type);
// void	quote_display(char *quote_type);
// t_bool	check_quote(char *tmp, char quote_type, t_type type, int index);

#endif