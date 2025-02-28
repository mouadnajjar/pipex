/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:29:47 by monajjar          #+#    #+#             */
/*   Updated: 2025/02/28 15:31:49 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void free_2d_array(char **arr)
{
    int i;

	i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}


char	*get_cmmand_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		i;
	int		j;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	j = 0;
	while (paths[j])
	{
		full_path = ft_strjoin(paths[j], "/");
		path = ft_strjoin(full_path, cmd);
		free(full_path);
		if (access(path, X_OK) == 0)
		{
			free_2d_array(paths);
			return (path);
		}
		free (path);
		j++;
	}
	return (NULL);
}

void	child_process(char *cmd, char	**envp, int input_fd, int output_fd)
{
	char	**args;
	char	*path;
	
	args = ft_split(cmd, ' ');
	path = get_cmmand_path(args[0], envp);
	if (!path)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\n", 2);
		exit (127);	
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 input_fd to STDIN_FILENO");
		exit (1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 output_fd to STDOUT_FILENO");
		exit (1);
	}
	close (input_fd);
	close (output_fd);
	if (execve(path, args, envp) == -1)
	{
		perror("execve error");
		exit (1);
	}
}

void	wait_child()
{
	wait(NULL);
	wait(NULL);
}

int	pipex(char **av, char **envp)
{
	int	fd[2];
	int	infile;
	int	outfile;

	open_files(&infile, &outfile, av);
	if (infile == -1 || outfile == -1)
		return (1);
	create_pipe(fd);
	fork_child(infile, fd[1], av[2], envp);
	fork_child(fd[0], outfile, av[3], envp);
	close_pipes(fd);
	close(infile);
	close(outfile);
	wait_child();
	return (0);
}
