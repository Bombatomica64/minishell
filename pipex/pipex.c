/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/28 11:39:59 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_execve(char *command, char **envp)
{
	int		i;
	char	*tmp_path;
	char	*possible_path;
	char	**all_paths;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i] != NULL)
	{
		tmp_path = ft_strjoin("/", command);
		possible_path = ft_strjoin(all_paths[i], tmp_path);
		free(tmp_path);
		if (access(possible_path, F_OK) == 0)
			return (free_matrix(&all_paths), possible_path);
		else
			free(possible_path);
		i++;
	}
	free_matrix(&all_paths);
	return (NULL);
}

void	child(t_pipex *pipex, t_data *data)
{
	if (pipex->fd_in != STDIN_FILENO)
	{
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			ft_error("child", DUP, 13, data);
	}
	if (pipex->fd_out != STDOUT_FILENO)
	{
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			ft_error("child", DUP, 13, data);
	}
	if (ft_isbuiltin(ft_strjoin(pipex->cmd[0], " ")) == TRUE)
	{
		ft_printf("qui we\n");
		do_builtin(pipex->cmd, data);
	}
	else if (execve(pipex->path, pipex->cmd, data->envp) < 0)
		ft_error(pipex->cmd[0], EXECVE, 126, data);
}

int	pipex(t_pipex *pipex, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		ft_error("executor", FORK, 124, NULL);
	if (pid == 0)
		child(pipex, data);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
