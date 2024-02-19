/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/19 12:15:36 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	ft_malloc_err(void *ptr, char *str)
{
	if (!ptr)
	{
		dup2(2, 1);
		ft_printf("Error: Unexpected malloc behaviour at %s\n", str);
		return (TRUE);
	}
	return (FALSE);
}

void	ft_error(const char *str, t_error error)
{
	dup2(2, 1);
	if (error == NO_PATH)
	{
		ft_printf("pipex: command not found: %s\n", str);
		exit(127);
	}
	else if (error == DUP)
		perror("pipex: dup error");
	else if (error == EXECVE)
		perror("pipex: execve error");
	else if (error == PIPE)
		perror("pipex: pipe error");
	else if (error == FORK)
		perror("pipex: fork error");
	else if (error == ACCESS)
		perror("pipex: access error");
	else if (error == OPEN)
		perror("pipex: open error");
	else
		perror("pipex: unknown error");
}
// Path: utils/utils.h