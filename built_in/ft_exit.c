/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:23:22 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/14 15:27:34 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

t_bool	is_exit(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_exit(char **cmd, t_data *data)
{
	int		arg2;
	char	*str;

	arg2 = 0;
	str = NULL;
	if (cmd[1] && ft_atoibool(cmd[1], &arg2) == FALSE)
	{
		str = ft_strjoin("exit\nminishell: exit: ", cmd[1]);
		str = ft_newstrjoin(str, ": numeric argument required\n");
		ft_putstr_fd(str, 2);
		free(str);
		arg2 = 2;
	}
	else if (cmd[1] && cmd[2])
	{
		write(2, "exit\nminishell: exit: too many arguments\n", 42);
		return (127);
	}
	free_matrix(&cmd);
	free_close(&data, arg2);
	return (0);
}
