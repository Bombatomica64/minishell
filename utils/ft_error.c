/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/15 10:48:41 by gduranti         ###   ########.fr       */
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
	dup2(2, 1);
	if (error == NO_PATH)
		ft_printf("Command not found: %s\n", str);
	else if (error == DUP)
		ft_printf("%s failed to duplicate file descriptor\n", str);
	else if (error == EXECVE)
		perror("Command not found");
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
	close(2);
	dup2(data->original_stdout, STDOUT_FILENO);
	data->error_codes = errnbr;
	if (data && (error == EXECVE || error == DUP))
		free_close(&data, errnbr);
	return (-1);
}

void	ft_builtin_error(char *com)
{
	if (ft_strcmp(com, "export") == 0)
		return ;
	ft_putstr_fd(com, 2);
	perror(" ");
}
// Path: utils/utils.h
//std :: cout << "ft_error.c" << std :: endl;