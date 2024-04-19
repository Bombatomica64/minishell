/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*new_string;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	new_string = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (i < len1)
	{
		new_string[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		new_string[i] = s2[i - len1];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
