/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:09:04 by monajjar          #+#    #+#             */
/*   Updated: 2025/03/16 16:06:20 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(char **av, char **envp)
{
	t_pipex	px;
	int		status;
	int		fd_in;
	int		fd_out;

	fd_in = -1;
	fd_out = -1;
	px.input_file = av[1];
	px.output_file = av[4];
	px.envp = envp;
	create_pipe(&px);
	px.pid1 = fork_child(&px, fd_in, px.pipe_fd[1], av[2]);
	close(px.pipe_fd[1]);
	px.pid2 = fork_child(&px, px.pipe_fd[0], fd_out, av[3]);
	close(px.pipe_fd[0]);
	status = wait_child(px.pid1, px.pid2);
	return (status);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 5)
	{
		write(2, "Error\n", 7);
		return (1);
	}
	return (pipex(av, envp));
}
