/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/26 15:42:37 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


/*int	heredoc_creat(char *limiter, t_data *data)
  void	heredoc_creat(char *limiter)
{
	char	*str;
	char	*name;
	int		fd;

	str = NULL;
	name = ft_strjoin(data->home, "/.heredoc.txt");
	fd = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
		ft_error("heredoc_creat", OPEN, 101, NULL);
	while (ft_strcmp((const char *)str, (const char *)limiter) != 0)
	{
		str = readline("heredoc> ");
		if (ft_strcmp((const char *)str, (const char *)limiter) != 0)
			ft_putendl_fd(str, fd);
		free(str);
	}
	close(fd);

} */

int	heredoc_creat(char *limiter)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_error("heredoc_creat", PIPE, 132, NULL);
	str = readline("heredoc> ");
	while (ft_strcmp((const char *)str, (const char *)limiter) != 0)
	{
		ft_putendl_fd(str, fd[1]);
		free(str);
		str = readline("heredoc> ");
	}
	close(fd[1]);
	return (fd[0]);
}
