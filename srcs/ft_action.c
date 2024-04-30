/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:58:12 by mruggier          #+#    #+#             */
/*   Updated: 2024/04/30 15:00:51 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_action2(int sig)
{
	fprintf(stderr, "\n");
	if (sig == SIGINT)
	{
		g_duranti = 130;
	}
	if (sig == SIGQUIT)
	{
		g_duranti = 131;
	}
}

void	ft_action(int sig)
{
	if (sig == SIGINT)
	{
		g_duranti = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
