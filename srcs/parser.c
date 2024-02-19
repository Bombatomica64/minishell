/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:50:51 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/19 18:07:27 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **str)
{
	while (**str == ' ' && **str != '\0')
		(*str)++;
}

ft_file_type(char **str)
{
	if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			return (HEREDOC);
			(*str)++;
		}
		else
			return (INPUT);
	}
	else if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			return (APPEND);
			(*str)++;
		}
		else
			return (TRUNC);
	}
	return (COMMAND); check se e' un built in
}

void	get_name(char *str, int tmp_type)

void	ft_parser(char *str, t_data *data)
{
	char	*tmp;
	t_type	tmp_type;
	int		i;

	i = 0;
	skip_spaces(&str);
	tmp_type = ft_file_type(&str);
	tmp = get_name(&str, tmp_type);
	 
	ft_inputadd_back(&(*data).input, ft_inputnew(tmp, tmp_type));
}