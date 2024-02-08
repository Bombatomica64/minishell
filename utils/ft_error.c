/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/08 18:43:22 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_error(const char *str, t_error error)
{
	if (error == NO_PATH)
	{
		printf("pipex: command not found: %s\n", str);
		exit(127);
	}
	else if (error == DUP)
		printf("pipex: dup error\n");
	else if (error == EXECVE)
		printf("pipex: execve error\n");
	else if (error == PIPE)
		printf("pipex: pipe error\n");
	else if (error == FORK)
		printf("pipex: fork error\n");
	else if (error == ACCESS)
		printf("pipex: access error\n");
	else if (error == OPEN)
		printf("pipex: open error\n");
	else
		printf("pipex: unknown error\n");
}
// Path: utils/utils.h