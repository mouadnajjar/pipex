/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:29:47 by monajjar          #+#    #+#             */
/*   Updated: 2025/03/13 16:05:22 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*get_cmmand_path(char *cmd, char **envp)
{
	t_cmd	c;

	if (ft_strchr(cmd, '/') && (access(cmd, X_OK) == 0))
		return (ft_strdup(cmd));
	if (ft_strchr(cmd, '/') && !(access(cmd, X_OK) == 0))
		return (NULL);
	c.paths = split_paths(envp);
	if (!c.paths)
		return (NULL);
	c.j = 0;
	while (c.paths[c.j])
	{
		c.full_path = ft_strjoin(c.paths[c.j], "/");
		c.path = ft_strjoin(c.full_path, cmd);
		free(c.full_path);
		if (access(c.path, X_OK) == 0)
		{
			free_2d_array(c.paths);
			return (c.path);
		}
		free (c.path);
		c.j++;
	}
	free_2d_array(c.paths);
	return (NULL);
}

void	setup_redirections(t_pipex *px, int *input_fd, int *output_fd,
	t_cmd_data *cmd_data)
{
	if (*output_fd == -1)
		open_files(px, input_fd, output_fd, cmd_data);
	if (dup2(*output_fd, STDOUT_FILENO) == -1)
	{
		write(2, "dup2 output_fd to STDOUT_FILENO\n", 31);
		exit (errno);
	}
	if (*input_fd == -1)
		open_files(px, input_fd, output_fd, cmd_data);
	if (dup2(*input_fd, STDIN_FILENO) == -1)
	{
		write(2, "dup2 input_fd to STDIN_FILENO\n", 31);
		exit (errno);
	}
	close (*input_fd);
	close (*output_fd);
}

void	child_process(char *cmd, t_pipex *px, int input_fd, int output_fd)
{
	t_cmd_data	cmd_data;

	cmd_data.args = ft_split(cmd, ' ');
	if (!cmd_data.args || !cmd_data.args[0] || cmd_data.args[0][0] == '\0')
	{
		close_fds(px, cmd_data.args, NULL);
		if (input_fd != -1)
			close(input_fd);
		if (output_fd != -1)
			close (output_fd);
		exit (1);
	}
	cmd_data.path = get_cmmand_path(cmd_data.args[0], px->envp);
	if (!cmd_data.path)
		error_command(cmd, cmd_data.args, cmd_data.path, px);
	setup_redirections(px, &input_fd, &output_fd, &cmd_data);
	if (execve(cmd_data.path, cmd_data.args, px->envp) == -1)
	{
		perror("execve error");
		exit (errno);
	}
}

int	wait_child(pid_t pid1, pid_t pid2)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(pid1, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
	}
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	return (exit_code);
}
