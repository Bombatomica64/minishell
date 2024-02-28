/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:32:21 by gduranti          #+#    #+#             */
/*   Updated: 2024/02/28 11:51:55 by lmicheli         ###   ########.fr       */
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
static void	ft_putendl_fd_free(char **s, int fd)
{
	if (fd < 0)
		return ;
	write(fd, *s, ft_strlen(*s));
	write(fd, "\n", 1);
	free(*s);
}

int	heredoc_creat(char *limiter)
{
	char	*str;
	int		fd[2];
	pid_t	pid;

	printf("limiter: |%s|\n", limiter);
	if (pipe(fd) < 0)
		ft_error("heredoc_creat", PIPE, 132, NULL);
	pid = fork();
	if (pid == 0)
	{
		str = readline("heredoc> ");
		while (ft_strcmp(str, limiter) != 0)
		{
			write(2, str, ft_strlen(str));
			ft_putendl_fd_free(&str, fd[1]);
			str = readline("heredoc> ");
		}
		close(fd[1]);
		write(2, "ciao", 4);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
	}
	return (0);
}
