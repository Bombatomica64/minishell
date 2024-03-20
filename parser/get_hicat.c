/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hicat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 10:05:27 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/20 13:03:05 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*ft_reparsing(char *str, int i, t_data *data)
{
	t_quote	quote;
	char	*tmp;
	char	*dst;
	int		j;
	int		k;

	quote = (t_quote){FALSE, 0};
	dst = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!str)
		return(free(str), ft_inputclear(&data->input), NULL);
	k = i;
	j = -1;
	while (k >= 0 && ft_islimiter(str[k--]) == FALSE);
	while(str[++j] && j < k)
		dst[j] = str[j];
	printf("dst1: %s\n", dst);
	tmp = ft_strncpy(str, k, i);
	printf("tmp: %s\n", tmp);
	while(str[i] && (ft_islimiter(str[i]) == FALSE || quote.open == TRUE))
	{
		quote_start(&quote.open, str[i], &quote.type);
		dst[j++] = str[i++];
	}
	k = 0;
	printf("dst2: %s\n", dst);
	while (tmp[k])
		dst[j++] = tmp[k++];
	printf("dst3: %s\n", dst);
	while (str[i])
		dst[j++] = str[i++];
	printf("dstFINAL: %s\n", dst);
	return (free(str), ft_inputclear(&data->input), dst);
}
//echo ciao > "file1 |" pippo 'amico|' ls