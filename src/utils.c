/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:14:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/02/28 15:31:43 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void	open_files(int *infile, int *outfile, char **av)
{
	*infile = open(av[1], O_RDONLY);
	if (*infile == -1)
	{
		perror("infile open Error");
		exit (1);
	}
	*outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
	{
		perror("outfile open error");
		close (*infile);
		exit (1)
	}
}

void	create_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit (1);
	}
}

void	fork_child(int input_fd, int output_fd, char *cmd, char **envp)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
	{
		perror("Fork error");
		exit (1);
	}
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(input_fd);
		close(output_fd);
		child_process(cmd, envp, input_fd, output_fd);
	}
}
void	close_pipes(int *fd)
{
	close (fd[0]);
	close (fd[1]);
}