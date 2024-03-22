/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgarigli <sgarigli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/03/22 11:27:22 by sgarigli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"

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
static void	ft_putendl_fd_free(char **s, int fd)
{
	if (fd < 0)
		return ;
	write(fd, *s, ft_strlen(*s));
	write(fd, "\n", 1);
	free(*s);
}

int	heredoc_creat(char *limiter, t_data *data, pid_t pid)
{
	char	*str;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_error("heredoc_creat", PIPE, 132, NULL);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		while (TRUE)
		{
			str = readline("heredoc> ");
			if (ft_strcmp(str, limiter) == 0)
				break ;
			str = expand_name(str, data);
			ft_putendl_fd_free(&str, fd[1]);
		}
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
	}
	return (fd[0]);
}
