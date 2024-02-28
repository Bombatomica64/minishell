/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/02/28 15:47:15 by lmicheli         ###   ########.fr       */
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

int	ft_error(const char *str, t_error error, int errnbr, t_data *data)
{
	if (error == NO_PATH)
		perror("Command not found in available paths");
	else if (error == DUP)
		ft_printf("%s failed to duplicate file descriptor\n", str);
	else if (error == EXECVE)
		perror("Error execve");
	else if (error == PIPE)
		perror("pipex: pipe error");
	else if (error == FORK)
		perror("pipex: fork error");
	else if (error == ACCESS)
		perror("pipex: access error");
	else if (error == OPEN)
		ft_printf("Open error in %s\n", str);
	else
		perror("unknown error");
	if (data && (error == EXECVE || error == DUP))
		free_close(&data, errnbr);
	else
		return (free_return(&data, errnbr));
}
// Path: utils/utils.h
//std :: cout << "ft_error.c" << std :: endl;