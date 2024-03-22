/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:23:22 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/22 17:58:38 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

t_bool	is_exit(char *command)
{
	if (ft_strcmp(command, "exit") == 0)
		return (TRUE);
	return (FALSE);
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

int	ft_exit(char **cmd, t_data *data)
{
	int		arg2;
	//char	*str
	//exit\n va stampato in stdin, il resto l'ho cambiato perche sono stupido;

	arg2 = 0;
	//str = NULL;
	if (cmd[1] && ft_atoibool(cmd[1], &arg2) == FALSE)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		/*str = ft_strjoin("exit\nminishell: exit: ", cmd[1]);
		str = ft_newstrjoin(str, ": numeric argument required\n");
		ft_putstr_fd(str, 2);
		free(str);*/
		arg2 = 2;
	}
	else if (cmd[1] && cmd[2])
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		//write(2, "exit\nminishell: exit: too many arguments\n", 42);
		return (1);
	}
	free_matrix(&cmd);
	free_close(&data, arg2);
	return (0);
}
