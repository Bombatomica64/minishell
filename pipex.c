/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruggier <mruggier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:07:15 by mruggier          #+#    #+#             */
/*   Updated: 2024/02/08 17:32:22 by mruggier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_cmd_path(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->argc - 3)
	{
		j = 0;
		while (data->cmd[i][j])
		{
			free(data->cmd[i][j]);
			j++;
		}
		free(data->cmd[i]);
		i++;
	}
	free(data->cmd);
	i = 0;
	while (i < data->argc - 3)
	{
		free(data->path[i]);
		i++;
	}
	free(data->path);
}

void	path_execve(char *command, char **envp)
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
			return(possible_path);
		else
			free(possible_path);
		i++;
	}
	return (NULL);
}

void	child(t_pipex *pipex)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("1", PIPE);
	pid = fork();
	if (pid == -1)
		ft_error("1", FORK);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error("1", DUP);
		if (execve(pipex->path1, pipex->cmd1, NULL) < 0)
			ft_error("1", EXECVE);
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("1", DUP);
		waitpid(pid, NULL, 0);
	}
}

void	parent(t_pipex *pipex)
{
	if (execve(pipex->path2, pipex->cmd2, NULL) < 0)
		ft_error ("1", EXECVE);
	if (pipex->filein != -1)
		close(pipex->filein);
	if (pipex->fileout != -1)
		close(pipex->fileout);
}

int	checkfile_fd(t_pipex *pipex)
{
	if (access(pipex->filein, F_OK | R_OK) == -1)
		ft_error("1", ACCESS_IN); 
	if (access(pipex->fileout, F_OK | W_OK) == -1)
		ft_error("1", ACCESS_OUT);
	pipex->fd_in = open(pipex->filein, O_RDONLY, 0644);
	pipex->fd_out = open(pipex->fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_in < 0 || pipex->fd_out < 0)
		ft_error("2", OPEN);
	
	return (0);
}

void	ft_execute(t_pipex *pipex)
{
	if (dup2(pipex->fd_in, STDIN_FILENO) == -1)
		ft_error("2", DUP);
	child(&pipex);

	if (dup2(pipex->fd_out, STDOUT_FILENO) == -1)
		ft_error("2", DUP);
	parent(&pipex);
}

//pipex(ft_split(commands, '|'), fd, envp)

int pipex(char **input, int fd[2], char **envp)
{
	t_pipex	pipex;
	char	**temp;

	pipex.input = fd[0];
	pipex.output = fd[1];
	pipex.cmd1 = ft_split(input[0], ' ');
	pipex.cmd2 = ft_split(input[1], ' ');
	
	pipex.path1 = path_execve(pipex.cmd1[0], envp);
	if (pipex.path1 == NULL)
		ft_error("1", NO_PATH);
	pipex.path2 = path_execve(pipex.cmd2[0], envp);
	if (pipex.path2 == NULL)
		ft_error("2", NO_PATH);

	checkfile_fd(&pipex);

	ft_execute(&pipex);
	
	free_cmd_path(&data);
}

