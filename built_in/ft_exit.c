/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/30 11:28:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

t_bool	is_exit(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

void	free_exitsrcs(t_data *data, t_pipex **origin, pid_t **pid)
{
	int	i;

	i = 0;
	while (data->cmd_nbr >= i)
	{
		free_matrix(&(*origin)[i].cmd);
		i++;
	}
	free(*origin);
	free(*pid);
}

// t_bool	ft_atoll(char *str)
// {
// 	long long int	num;
// 	t_bool			neg;
// 	int				i;
// //	int				digit;

// 	num = 0;
// 	neg = FALSE;
// 	i = 0;
// 	if (*str == '-')
// 	{
// 		neg = TRUE;
// 		str++;
// 	}
// 	else if (*str == '+')
// 		str++;
// 	while (str[i] && ft_isdigit(str[i]))
// 	{
// 		num = num * 10 + (str[i] - '0');
// 		i++;
// 	}
// }

int	ft_exit(char **cmd, t_data *data, t_pipex **origin, pid_t **pid)
{
	unsigned int		arg2;

	arg2 = 0;
	if (cmd[1] && ft_atoibool(cmd[1], &arg2, 0, 1) == FALSE)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		arg2 = 2;
	}
	else if (cmd[1] && cmd[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	free_exitsrcs(data, origin, pid);
	free_close(&data, arg2);
	return (0);
}
