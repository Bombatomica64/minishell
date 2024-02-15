/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/13 19:59:13 by marvin           ###   ########.fr       */
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