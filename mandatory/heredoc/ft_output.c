/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 19:17:28 by ckunimur          #+#    #+#             */
/*   Updated: 2023/11/30 08:47:56 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_output(t_data *data)
{
	int	fd;

	if (access(data->cmd->cmd[1], F_OK) == 0)
	{
		if (access(data->cmd->cmd[1], W_OK) == 0)
			fd = open(data->cmd->cmd[1], O_WRONLY | O_TRUNC);
		else
		{
			printf("error1\n");
			return ;
		}
	}
	else
		fd = (open(data->cmd->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644));
	if (fd == -1)
	{
		printf("error!2\n");
		return ;
	}
	dup2(fd, 1);
}