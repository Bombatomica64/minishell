/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gduranti <gduranti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:46:13 by lmicheli          #+#    #+#             */
/*   Updated: 2024/03/12 12:21:51 by gduranti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		s_len;
	int		i;
	char	*new_string;

	s_len = ft_strlen(s);
	i = 0;
	new_string = malloc((s_len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (s_len > i)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
