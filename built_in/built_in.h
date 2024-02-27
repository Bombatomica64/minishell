/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:03:32 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/27 17:20:03 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../utils/utils.h"

//built-in functions
t_bool	ft_echo(char **mtx);
t_bool	ft_cd(char **str, t_data *data);
void	ft_env(char **envp);
void	ft_pwd(void);
t_bool	ft_export(char ***envp, char **cmd);
t_bool	ft_unset(char **mtx, char ***envp);

// unset helper functions
void	remove_envp_entry(char ***envp, char *entry);

// export  helper functions
t_bool	add_to_env(char ***envp, char *str);
t_bool	update_env(char ***envp, char *str);

// debug functions
void	print_pwd(char **envp);
void	print_pwds(char **envp);

// take a file and output absolute path
char	*refactor_path(char *str, t_data *data, int i);
char	*ft_remove_chars(char *str, char *to_remove, int i);

#endif