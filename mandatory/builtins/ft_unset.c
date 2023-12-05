/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:06:15 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/05 16:53:25 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(t_data *data)
{
	t_env	*env_node;
	t_env	*temp_node;

	temp_node = ft_calloc(sizeof(t_env), 1);
	env_node = data->env_node;
	if (data->cmd->cmd[1])
	{
		temp_node = have_var(data, data->cmd->cmd[1]);
		if (temp_node == NULL)
			return ;
		while (env_node->next != temp_node)
				env_node = env_node->next;
			env_node->next = temp_node->next;
		ft_clear_env(temp_node);
	}
}
