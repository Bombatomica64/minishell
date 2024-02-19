/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:47:58 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/19 13:08:34 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../data.h"

void	ft_freenclose(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_total)
	{
		if (data->input[i].is_a_file == TRUE)
			free(data->input[i].file.name);
		else
			free(data->input[i].cmd.name);
	}
	i = -1;
	while (++i < data->nb_cmds)
		free(data->in_p.cmds[i]);
	i = -1;
	while (++i < data->nb_files)
		free(data->in_p.files[i]);
	free(data->in_p.cmds);
	free(data->in_p.files);
	free(data->input);
}
