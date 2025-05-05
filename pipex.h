/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:01:55 by monajjar          #+#    #+#             */
/*   Updated: 2025/03/16 15:39:05 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# define CMD_NOT_FOUND 127
//-------------------Includes-----------//
# include <fcntl.h>
# include "libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
//--------------------------------------//

//----------------structers--------------//
typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fd[2];
	int		status;
	char	**envp;
	char	*cmd;
	char	*input_file;
	char	*output_file;
}			t_pipex;

typedef struct s_cmd
{
	char	**paths;
	char	*path;
	char	*full_path;
	int		j;
}			t_cmd;

typedef struct s_cmd_data
{
	char	**args;
	char	*path;
}			t_cmd_data;
//---------------------------------------//

//-----------------errors&closes------------//
void	close_pipes(t_pipex *px);
void	error_command(char	*cmd, char **args, char *path, t_pipex *px);
void	free_2d_array(char **arr);
void	print_error(const char *cmd);
void	close_fds(t_pipex *px, char **args, char *path);
//--------------------------------------//

//----------------execution-------------//
int		pipex(char **av, char **envp);
void	open_files(t_pipex *px, int *input_fd, int *output_fd,
			t_cmd_data *data);
pid_t	fork_child(t_pipex *px, int input_fd, int output_fd, char *cmd);
void	child_process(char *cmd, t_pipex *px, int input_fd, int output_fd);
void	create_pipe(t_pipex *px);
int		wait_child(pid_t pid1, pid_t pid2);
//--------------------------------------//

//--------------PATH_PARSING------------//
char	**split_paths(char **envp);
void	check_path(char **envp);
char	*check_sign(char *s);
void	reset_space(t_cmd_data *cmd_data);
char	*remove_quotes(char *cmd);
//--------------------------------------//
#endif