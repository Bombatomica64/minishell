/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:03:32 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/23 18:20:20 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../utils/utils.h"

//built-in functions
t_bool	ft_echo(char **mtx);
void	print_pwd(char **envp);
void	ft_cd(char **str, t_data *data);
void	ft_env(char **envp);

// unset & helper functions
t_bool	ft_unset(char **mtx, char ***envp);
void	remove_envp_entry(char ***envp, char *entry);

// export & helper functions

t_bool	ft_export(char ***envp, char *str);
t_bool	add_to_env(char ***envp, char *str);
t_bool	update_env(char ***envp, char *str);

// debug functions
void	print_pwds(char **envp);

#endif