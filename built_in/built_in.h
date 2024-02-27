/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:03:32 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/27 11:42:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../utils/utils.h"

//built-in functions
t_bool	ft_echo(char **mtx);
void	ft_cd(char **str, t_data *data);
void	ft_env(char **envp);
void	ft_pwd(void);
t_bool	ft_export(char ***envp, char *str);
t_bool	ft_unset(char **mtx, char ***envp);

// unset helper functions
void	remove_envp_entry(char ***envp, char *entry);

// export  helper functions
t_bool	add_to_env(char ***envp, char *str);
t_bool	update_env(char ***envp, char *str);

// debug functions
void	print_pwd(char **envp);
void	print_pwds(char **envp);

#endif