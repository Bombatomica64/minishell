/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hicat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:05:27 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/20 16:34:20 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_reparsing(char *str, int i, t_data *data)
{
	t_quote	squote;
	char	*tmp;
	char	*dst;
	int		j;
	int		k;

	squote = (t_quote){FALSE, 0};
	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!dst)
		return(free(str), ft_inputclear(&data->input), NULL);
	k = i;
	j = -1;
	while (k > 0 && (ft_islimiter(str[k]) == FALSE || squote.open == TRUE))
		quote_start(&squote.open, str[k--], &squote.type);
	if (ft_islimiter(str[k - 1]) == TRUE)
		k--;
	while(str[++j] && j < k)
		dst[j] = str[j];
	tmp = ft_strncpy(str, k, i);
	while(str[i] && (ft_islimiter(str[i]) == FALSE || squote.open == TRUE))
	{
		quote_start(&squote.open, str[i], &squote.type);
		dst[j++] = str[i++];
	}
	k = 0;
	while (tmp && tmp[k])
		dst[j++] = tmp[k++];
	while (str[i])
		dst[j++] = str[i++];
	return (free(tmp), free(str), ft_inputclear(&data->input), dst);
}
//echo ciao > "file1 |" pippo 'amico|' ls