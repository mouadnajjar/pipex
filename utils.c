/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:14:02 by monajjar          #+#    #+#             */
/*   Updated: 2025/03/15 21:17:46 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(t_pipex *px, int *input_fd, int *output_fd, t_cmd_data *data)
{
	if (*input_fd == -1)
	{
		close(px->pipe_fd[0]);
		*input_fd = open(px->input_file, O_RDONLY);
		if (*input_fd == -1)
		{
			perror(px->input_file);
			close_fds(px, data->args, data->path);
			exit(1);
		}
	}
	if (*output_fd == -1)
	{
		close(px->pipe_fd[1]);
		*output_fd = open(px->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*output_fd == -1)
		{
			perror(px->output_file);
			if (*input_fd != -1)
				close (*input_fd);
			close_fds(px, data->args, data->path);
			exit(1);
		}
	}
}

void	create_pipe(t_pipex *px)
{
	if (pipe(px->pipe_fd) == -1)
	{
		write(2, "pipe error", 11);
		exit (1);
	}
}

pid_t	fork_child(t_pipex *px, int input_fd, int output_fd, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_pipes(px);
		perror("Fork error");
		exit (errno);
	}
	if (pid == 0)
		child_process(cmd, px, input_fd, output_fd);
	return (pid);
}

void	close_pipes(t_pipex *px)
{
	close (px->pipe_fd[0]);
	close (px->pipe_fd[1]);
}
