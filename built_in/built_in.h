/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:03:32 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/23 10:51:27 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../utils/utils.h"

t_bool	ft_echo(char **mtx);
void	print_pwd(char **envp);
void	ft_cd(char *str, t_data *data);
void	ft_env(char **envp);

#endif