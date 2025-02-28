/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 16:01:55 by monajjar          #+#    #+#             */
/*   Updated: 2025/02/28 15:24:23 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

//-------------------Includes-----------//
# include <fcntl.h>
# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <sys/wait.h>
//--------------------------------------//

//-----------------errors&closes------------//
void	ft_error(void);
//--------------------------------------//

//----------------execution-------------//
int		pipex(char **av, char **envp);
void	open_files(int *infile, int *outfile, char **av);
void	fork_child(int input_fd, int output_fd, char *cmd, char **envp);
void	close_pipes(int *fd);
//--------------------------------------//
#endif