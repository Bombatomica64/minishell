/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:47:13 by gduranti          #+#    #+#             */
/*   Updated: 2024/04/15 11:55:57 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "../lexer/lexer.h"
# pragma once

t_bool	bonus_checker(char *line, t_data *data);
t_bool	check_if_last(char c, char *str, t_data *data);
t_bool	redir_check(char *line, t_data *data);

#endif
// Path: built_in/export.c
