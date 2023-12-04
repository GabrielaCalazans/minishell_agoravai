/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckunimur <ckunimur@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:39:53 by ckunimur          #+#    #+#             */
/*   Updated: 2023/12/04 17:20:45 by ckunimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_env(t_data **data, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		link_end(&(*data)->env_node, create_list(envp[i]));
		i++;
	}
}

t_env	*create_list(char *str)
{
	t_env	*aux;
	char	**split;

	aux = malloc(sizeof(t_env));
	split = ft_split(str, '=');
	aux->var = ft_strdup(split[0]);
	aux->value = ft_strdup(split[1]);
	aux->next = NULL;
	freearray(split);
	return (aux);
}

t_env	*node_last(t_env *list)
{
	t_env	*last;

	last = list;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

t_env	*linkar(t_data *data)
{
	t_env	*new_node;
	char	**split;

	new_node = ft_calloc(sizeof(t_env), 1);
	split = ft_split(data->cmd->cmd[1], '=');
	new_node->var = split[0];
	if (split[1])
		new_node->value = split[1];
	else
		new_node->value = NULL;
	free(split);
	new_node->next = NULL;
	return (new_node);
}

void	link_end(t_env **list, t_env *current)
{
	t_env	*aux;

	if (list == NULL)
		return ;
	if (*list == NULL)
	{
		*list = current;
		return ;
	}
	aux = node_last(*list);
	aux->next = current;
}
