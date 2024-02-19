/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splut.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:47:08 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 10:10:32 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_spaces(char **str)
{
	while (**str == ' ' && **str != '\0')
		(*str)++;
}

void	get_file_name(char **str, int x, t_input *input)
{
	int i;

	i = 0;
	while ((*str)[i] != '|' && (*str)[i] != '>'
		&& (*str)[i] != '<' && (*str)[i] != '\0')
		i++;
	input[x].file.name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (**str != '|' && **str != '>'
		&& **str != '<' && **str != '\0')
	{
		input[x].file.name[i] = **str;
		(*str)++;
		i++;
	}
	input[x].file.name[i] = '\0';
	while (input[x].file.name[i - 1] == ' ' && i > 0)
	{
		input[x].file.name[i - 1] = '\0';
		i--;
	}
}

void	get_cmd_name(char **str, int x, t_input *input)
{
	int i;

	i = 0;
	while ((*str)[i] != '|' && (*str)[i] != '>'
		&& (*str)[i] != '<' && (*str)[i] != '\0')
		i++;
	input[x].cmd.name = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (**str != '|' && **str != '>'
		&& **str != '<' && **str != '\0')
	{
		input[x].cmd.name[i] = **str;
		(*str)++;
		i++;
	}
	input[x].cmd.name[i] = '\0';
	while (input[x].cmd.name[i - 1] == ' ' && i > 0)
	{
		input[x].cmd.name[i - 1] = '\0';
		i--;
	}
}

int	check_file_tipe(char **str, int x, t_input *input)
{
	if (**str == '<')
	{
		(*str)++;
		if (**str == '<')
		{
			input[x].file.type = HEREDOC;
			(*str)++;
		}
		else
			input[x].file.type = INPUT;
		return (TRUE);
	}
	else if (**str == '>')
	{
		(*str)++;
		if (**str == '>')
		{
			input[x].file.type = APPEND;
			(*str)++;
		}
		else
			input[x].file.type = TRUNC;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_splut(char *str, t_input **input)
{
	int x;

	x = 0;
	while (*str != '\0')
	{
		skip_spaces(&str);
		if (check_file_tipe(&str, x, *input) == TRUE)
		{
			(*input)[x].is_a_file = TRUE;
			skip_spaces(&str);
			get_file_name(&str, x, *input);
			if ((*input)[x].file.type == INPUT)
				(*input)[x].file.fd = open((*input)[x].file.name, O_RDONLY , 0777);
			else if ((*input)[x].file.type == TRUNC || (*input)[x].file.type == APPEND)
				(*input)[x].file.fd = open((*input)[x].file.name, O_WRONLY | O_CREAT | (*input)[x].file.type, 0777);
			//else if ((*input)[x].file.type == HEREDOC) -_-
			(*input)[x].cmd.name = NULL;
		}
		else
		{
			(*input)[x].is_a_file = FALSE;
			get_cmd_name(&str, x, *input);
			(*input)[x].file.name = NULL;
			(*input)[x].file.type = -1;
			(*input)[x].file.fd = -1;
		}
		if (*str == '|')
			str++;
		x++;
	}
	return (x);
}
