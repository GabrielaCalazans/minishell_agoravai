/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:05:26 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/04 17:30:15 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_data *data)
{
	long	err;

	err = 1;
	if (!data->cmd->cmd[1])
	{
		ft_clear_data(data);
		ft_printf("exit\n");
		exit(err);
	}
	else if (data->cmd->cmd[2])
		printf("exit: too many argments\n");
	else if (data->cmd->cmd[1])
	{
		if (ft_atoi(data->cmd->cmd[1]) == 0 && (data->cmd->cmd[1][0] != '0'))
		{
			err = 2;
			ft_printf("numeric argument is required\n");
		}
		else if (ft_strlen(data->cmd->cmd[1]) < 19)
			err = ft_atoi(data->cmd->cmd[1]);
		ft_clear_data(data);
		ft_clear_env(data->env_node);
		ft_printf("exit\n");
		exit(err);
	}
}
