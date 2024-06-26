/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/30 16:48:27 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_bool	file_check(char *tmp, t_data *data)
{
	struct stat	st;
	char		*line;
	int			i;

	i = 0;
	if (!tmp)
		return (FALSE);
	while (tmp[i] && ft_isspace(tmp[i]) == FALSE)
		i++;
	line = ft_strncpy(tmp, 0, i);
	if (!line)
		return (ERROR);
	if (ft_strncmp(line, "./", 2) == 0 || ft_strncmp(line, "/", 1) == 0)
	{
		if (stat(line, &st) == -1)
			return (ft_error(line, NO_EXST, 127, data), ERROR);
		else if (S_ISDIR(st.st_mode))
			return (ft_error(line, DIR, 126, data), ERROR);
		else if (access(line, X_OK) == -1)
			return (ft_error(line, ACCESS, 126, data), ERROR);
	}
	return (free(line), TRUE);
}

t_pipex	comm_error(t_data **data)
{
	(*data)->input = (*data)->input->next;
	return ((t_pipex){NULL, NULL, NULL, NULL, -1, -1});
}
