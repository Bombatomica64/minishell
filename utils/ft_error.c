/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/20 11:49:29 by mruggier         ###   ########.fr       */
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

int	ft_error(char *str, t_error error, int errnbr, t_data *data)
{
	dup2(2, 1);
	if (error == NO_PATH)
		{ft_putstr_fd(str, 2);
		ft_printf(": command not found\n");}
	else if (error == DUP)
		{ft_putstr_fd(str, 2);
		ft_printf(": failed to duplicate file descriptor\n");}
	else if (error == ACCESS)
		{ft_putstr_fd(str, 2);
		ft_printf(": Permission denied\n");}
	else if (error == OPEN)
		ft_printf(" No such file or directory\n");
	else if (error == NO_EXST)
		ft_printf(" No such file or directory\n");
	else if (error == WRITE)
		{ft_putstr_fd(str, 2);
		ft_printf(": Permission denied\n");}
	else
		perror("unknown error");
	close(1);
	dup2(data->original_stdout, STDOUT_FILENO);
	if (data && (error == EXECVE || error == DUP))
		return (free_return(&data, errnbr));
	data->error_codes = errnbr;
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