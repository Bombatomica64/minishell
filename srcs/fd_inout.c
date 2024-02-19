/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_inout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:07 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 16:35:08 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fd_in(t_data data) //se file in consecutivi, prendo l'ultimo
{
	while (data.nb_total > 0)
	{
		data.nb_total--;
		if (data.input[data.nb_total].file.type == INPUT
			|| data.input[data.nb_total].file.type == HEREDOC)
			return (data.input[data.nb_total].file.fd);
	}
	return (STDIN_FILENO);
}

int	ft_fd_out(t_data data) //se file in consecutivi, prendo l'ultimo
{
	while (data.nb_total > 0)
	{
		data.nb_total--;
		if (data.input[data.nb_total].file.type == TRUNC
			|| data.input[data.nb_total].file.type == APPEND)
			return (data.input[data.nb_total].file.fd);
	}
	return (STDOUT_FILENO);
}
