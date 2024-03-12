/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freesubstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:38:35 by sgarigli          #+#    #+#             */
/*   Updated: 2024/02/29 10:44:24 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_freesubstr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	len_src;
	char	*new_string;

	i = 0;
	if (!s || len == 0 || start >= ft_strlen(s) || ft_strlen(s) == 0)
		return (NULL);
	len_src = ft_strlen(s);
	if (start + len > len_src && start < len_src)
		len = len_src - start;
	else if (start >= len_src)
		len = 0;
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (i < len)
	{
		new_string[i] = s[i + start];
		i++;
	}
	new_string[len] = '\0';
	free(s);
	return (new_string);
}
