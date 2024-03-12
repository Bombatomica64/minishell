/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:47:34 by lmicheli          #+#    #+#             */
/*   Updated: 2023/12/06 13:06:27 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <stddef.h>
# include <stdlib.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*ft_read(char *old_str, int fd);
char	*ft_newstrjoin(char *old_str, char *buf);
char	*ft_correctline(char *old_str);
char	*ft_resto(char *old_str);

#endif