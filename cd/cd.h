/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:52:01 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/22 17:53:12 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CD_H
# define CD_H

#include "../utils/utils.h"

void	print_pwd(char ** envp);
void	ft_cd(char *str, t_data *data);

#endif