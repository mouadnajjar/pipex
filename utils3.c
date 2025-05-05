/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monajjar <monajjar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:52:56 by monajjar          #+#    #+#             */
/*   Updated: 2025/03/16 17:08:50 by monajjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_sign(char *s)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			sign = 1;
		else if (sign && s[i] == ' ')
			s[i] = -32;
		i++;
	}
	return (s);
}

void	reset_space(t_cmd_data *cmd_data)
{
	int	i;
	int	j;

	j = 0;
	while (cmd_data->args[j])
	{
		i = 0;
		while (cmd_data->args[j][i])
		{
			if (cmd_data->args[j][i] == -32)
				cmd_data->args[j][i] = ' ';
			i++;
		}
		j++;
	}
}

char	*remove_quotes(char *cmd)
{
	int		i;
	int		j;
	char	*new_cmd;

	i = 0;
	j = 0;
	new_cmd = malloc(ft_strlen(cmd) + 1);
	while (cmd[i])
	{
		if (cmd[i] != '\'' && cmd[i] != '"')
			new_cmd[j++] = cmd[i];
		i++;
	}
	new_cmd[j] = '\0';
	return (new_cmd);
}
