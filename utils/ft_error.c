/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:14:28 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/28 18:08:01 by mruggier         ###   ########.fr       */
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
		ft_printf("%s: command not found\n", str);
	else if (error == DUP)
		ft_printf("%s failed to duplicate file descriptor\n", str);
	else if (error == ACCESS)
		ft_printf("minishell: %s: Permission denied\n", str);
	else if (error == OPEN)
		ft_printf("minishell: %s: No such file or directory\n", str);
	else if (error == NO_EXST)
		ft_printf("minishell: %s: No such file or directory\n", str);
	else if (error == WRITE)
		ft_printf("minishell: %s: Permission denied\n", str);
	else if (error == DIR)
		ft_printf("minishell: %s: Is a directory\n", str);
	else
		perror("unknown error");
	if (error == NO_EXST || error == ACCESS || error == DIR)
		free(str);
	close(1);
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