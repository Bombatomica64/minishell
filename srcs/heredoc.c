/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/29 12:11:54 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_putendl_fd_free(char *s, int fd)
{
	if (fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
	free(s);
}

static void	ft_hereaction(int sig)
{
	if (sig == SIGINT)
	{
		g_duranti = 130;
		exit(130);
	}
}

void	free_and_close_resources(t_pipex **comm, char **lim,
	t_pipex **origin, t_data **data)
{
	free_matrix(&(*comm)->cmd);
	free(*lim);
	free(*origin);
	free_close(data, 0);
}

int	heredoc_creat(char *lim, t_data *data, t_pipex *comm, t_pipex **origin)
{
	char	*str;
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	lim = ft_strncpy_noquote(lim, 0, ft_strlen(lim), (t_quote){0, 0});
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		signal(SIGINT, ft_hereaction);
		while (TRUE)
		{
			str = readline(YELLOW BOLD"サ巳尺巳りロと"BRIGHT_CYAN"> "END);
			if (ft_strcmp(str, lim) == 0 || str == NULL)
			{
				if (str == NULL)
					printf("\n");
				break ;
			}
			ft_putendl_fd_free(expand_name(str, data), fd[1]);
		}
		close(fd[1]);
		free_and_close_resources(&comm, &lim, origin, &data);
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (close(fd[1]), free(lim), ERROR);
	return (close(fd[1]), free(lim), fd[0]);
}
