/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmicheli <lmicheli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/03/01 18:22:51 by lmicheli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	is_cd(char *command)
{
	if (ft_strcmp(command, "cd") == 0)
		return (TRUE);
	return (FALSE);
}


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
			return (free_matrix(&all_paths), free(command), possible_path);
		else
			free(possible_path);
		i++;
	}
	free(command);
	free_matrix(&all_paths);
	return (NULL);
}

void	child(t_pipex *pipex, t_data *data)
{
	if (data->in_pipe == TRUE)
		close(data->fd[data->last_pipe - 1][0]);
	if (pipex->fd_in != STDIN_FILENO)
	{
		if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
			ft_error("chsild", DUP, 13, data);
	}
	if (pipex->fd_out != STDOUT_FILENO)
	{
		if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
			ft_error("child", DUP, 13, data);
	}
	if (ft_isbuiltin(pipex->cmd[0]) == TRUE)
		do_builtin(pipex->cmd, data);
	else if (execve(pipex->path, pipex->cmd, data->envp) < 0)
		ft_error(pipex->cmd[0], EXECVE, 126, data);
}

int	pipex(t_pipex *pipex, t_data *data)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (is_cd(pipex->cmd[0]) == TRUE)
		return (ft_cd(pipex->cmd, data));
	pid = fork();
	if (pid == -1)
		ft_error("executor", FORK, 124, NULL);
	if (pid == 0)
		child(pipex, data);
	else
	{
		waitpid(pid, &status, 0);
		if (data->in_pipe == TRUE)
			close(data->fd[data->last_pipe - 1][1]);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

//fd [1][0] = -2

//int *fd[2];
//fd[0] = {0 , 1}; 
//pipe(fd[1]);
