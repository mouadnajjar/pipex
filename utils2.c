/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 15:17:31 by monajjar          #+#    #+#             */
/*   Updated: 2025/03/13 16:04:11 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_command(char	*cmd, char **args, char *path, t_pipex *px)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	if (args)
		free_2d_array(args);
	if (path)
		free(path);
	exit (CMD_NOT_FOUND);
}

char	**split_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

void	check_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
	{
		ft_putstr_fd("Error\nPATH variable is not set.\n", 2);
		exit(CMD_NOT_FOUND);
	}
}

void	print_error(const char *cmd)
{
	write(2, "pipex: ", 7);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, ": ", 2);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
}

void	close_fds(t_pipex *px, char **args, char *path)
{
	close(px->pipe_fd[0]);
	close(px->pipe_fd[1]);
	if (args)
		free_2d_array(args);
	if (path)
		free(path);
}
