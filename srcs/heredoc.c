/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by lmicheli          #+#    #+#             */
/*   Updated: 2024/04/30 12:40:44 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_close_resources(t_pipex *comm, t_pipex **origin, t_data **data)
{
	int		i;

	i = 0;
	while ((*data)->cmd_nbr >= i)
	{
		free_matrix(&(*origin)[i].cmd);
		i++;
	}
	free(*origin);
	free_matrix(&(comm)->cmd);
	ft_inputclear(&(*data)->input);
	free_array_matrix((*data)->fd, (*data)->pipe_nbr);
	close((*data)->original_stdin);
	close((*data)->original_stdout);
	free_matrix(&(*data)->envp);
	free((*data)->home);
	free((*data)->pwd);
}

void	heredoc_child(char *lim, t_data *data, t_pipex *comm, t_pipex **origin)
{
	char	*str;
	int		file;

	free_and_close_resources(comm, origin, &data);
	signal(SIGINT, ft_hereaction);
	file = open("temp/.heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	while (TRUE)
	{
		str = readline(YELLOW BOLD"サ巳尺巳りロと"BRIGHT_CYAN"> "END);
		if (ft_strcmp(str, lim) == 0 || str == NULL)
		{
			if (str == NULL)
				printf("\n");
			free(str);
			break ;
		}
		ft_putendl_fd_free(str, file);
	}
	close_n_fd((int []){file, 1, 0}, 3);
	free(lim);
}

int	fork_heredoc(char *lim, t_data *data, t_pipex *comm, t_pipex **origin)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		heredoc_child(lim, data, comm, origin);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

void	ft_expand_heredoc(t_data *data, int fd)
{
	char	*line;
	int		temp;

	temp = open("temp/.heredoc", O_RDONLY);
	line = get_next_line(temp);
	while (line)
	{
		line = expand_name(line, data);
		ft_putendl_fd_free(line, fd);
		line = get_next_line(temp);
	}
	free(line);
	close(fd);
	close(temp);
}

int	heredoc_creat(char *lim, t_data *data, t_pipex *comm, t_pipex **origin)
{
	int		fd[2];
	int		status;

	status = 0;
	lim = ft_strncpy_noquote(lim, 0, ft_strlen(lim), (t_quote){0, 0});
	status = fork_heredoc(lim, data, comm, origin);
	pipe(fd);
	if (WIFSIGNALED(status) || WEXITSTATUS(status) != 0 || g_duranti == 130)
		return (close(fd[1]), free(lim), ERROR);
	ft_expand_heredoc(data, fd[1]);
	return (close(fd[1]), free(lim), fd[0]);
}
