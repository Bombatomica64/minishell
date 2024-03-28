/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:38:58 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/28 15:37:09 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

# define RED "\033[0;31m"
# define BRIGHT_RED "\033[0;91m"
# define YELLOW "\033[0;33m"
# define BRIGHT_YELLOW "\033[0;93m"
# define GREEN "\033[0;32m"
# define BRIGHT_GREEN "\033[0;92m"
# define CYAN "\033[0;36m"
# define BRIGHT_CYAN "\033[0;96m"
# define BLUE "\033[0;34m"
# define BRIGHT_BLUE "\033[0;94m"
# define MAGENTA "\033[0;35m"
# define PURPLE MAGENTA
# define BRIGHT_MAGENTA "\033[0;95m"
# define BLACK "\033[0;30m"
# define BRIGHT_BLACK "\033[0;90m"
# define WHITE "\033[0;37m"
# define BRIGHT_WHITE "\033[0;97m"
# define END "\033[0m"

# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define REVERSED "\033[7m"

# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"
# define BG_BRIGHT_BLACK "\033[100m"
# define BG_BRIGHT_RED "\033[101m"
# define BG_BRIGHT_GREEN "\033[102m"
# define BG_BRIGHT_YELLOW "\033[103m"
# define BG_BRIGHT_BLUE "\033[104m"
# define BG_BRIGHT_MAGENTA "\033[105m"
# define BG_BRIGHT_CYAN "\033[106m"
# define BG_BRIGHT_WHITE "\033[107m"
# define BG_END "\033[49m"
//printf(RED "Questo testo sarà rosso" END "\n");

#endif