/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:24:10 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/22 15:24:16 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_echo(char *str, t_data *data)
{
	int	i;

	str += 4;
	i = 0;
	while (*str)
	{
		while (*str == ' ' || *str == '\t')
			str++;
	}
}
