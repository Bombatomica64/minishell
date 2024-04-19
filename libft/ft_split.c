/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli < lmicheli@student.42firenze.it>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/18 10:31:02 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*create_sub_str(int start, char const *s, char c)
{
	size_t		sub_str_len;
	size_t		i;
	char		*new_string;

	sub_str_len = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[start + sub_str_len] != c && s[start + sub_str_len] != '\0')
		sub_str_len++;
	new_string = (char *)malloc((sub_str_len + 1) * sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (i < sub_str_len)
	{
		new_string[i] = s[start + i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

static int	str_count(const char *s, char c)
{
	int		number_of_strings;
	int		start;

	start = 0;
	number_of_strings = 0;
	if (s == NULL)
		return (0);
	while (s[start])
	{
		if (s[start] != c)
		{
			number_of_strings++;
			while (s[start] != c && s[start])
				start++;
			start--;
		}
		if (s[start] == '\0')
			return (number_of_strings);
		start++;
	}
	return (number_of_strings);
}

char	**ft_split(char const *s, char c)
{
	int		number_of_str;
	int		pos_matrix;
	int		start;
	char	**matrix;

	number_of_str = str_count(s, c);
	pos_matrix = 0;
	start = 0;
	matrix = (char **)malloc((number_of_str + 1) * sizeof(char *));
	if (matrix == NULL)
		return (NULL);
	while (pos_matrix < number_of_str)
	{
		while (s[start] == c)
			start++;
		matrix[pos_matrix] = create_sub_str(start, s, c);
		if (matrix[pos_matrix] == NULL)
			return (NULL);
		while (s[start] != c && s[start] != '\0')
			start++;
		pos_matrix++;
	}
	matrix[pos_matrix] = NULL;
	return (matrix);
}

/*int main()
{
	char	*input = "   lorem\""
	char	**result = ft_split(input, 32);

	if (result)
	{
		for (int i = 0; result[i] != NULL; i++)
		{
			printf("Part %d: %s\n", i, result[i]);
		}
	}
	return (0);
}*/
