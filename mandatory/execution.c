/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carolinekunimura <carolinekunimura@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/13 11:32:49 by carolinekun      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	exec_cmd(t_data *ptr)
// {
// 	char	*path;
// 	char	**cmd_args;
// 	char	*env_var;
// 	pid_t	child_pid;

// 	path = find_path(ptr->cmd);
// 	cmd_args = find_args(ptr->cmd_args);
// }

void	exec_check(t_data *data)
{
 	if (is_builtins(data->prompt_in))
 		return (call_builtins(data->prompt_in));
 	else
 		printf("Se foda.");
}
