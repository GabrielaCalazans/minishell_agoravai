/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:55:22 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/12 06:52:10 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fd(t_data *data, int n_fd)
{
	int	i;

	i = 0;
	if (n_fd == 0)
		return ;
	while (i <= n_fd)
		close(data->fd[i++]);
}

void	execution(t_data *data)
{
	int		len;

	len = 0;
	data->pid = ft_calloc(data->n_cmd, sizeof(int));
	config_pipe(data);
	data->head_cmd = data->cmd;
	data->head_rdct = data->rdct;
	data->bkp_fd[1] = dup(1);
	data->bkp_fd[0] = dup(0);
	if (run_one_builtin(data))
		return ;
	run_only_redirects(data);
	len = run_process(data, &data->pid);
	run_waitpid(data, &data->pid, len);
}

void	execute_pid(t_data *data, int i, int ord)
{
	if (data->n_cmd - 1 != 0)
		dup_pipe(i, ord, data);
	run_redirect(data, i, 1);
	if (data->cmd->cmd && exec_builtin(data) == 0)
	{
		set_path_command(data);
		execve(data->cmd->cmd[0], data->cmd->cmd, data->env);
		dup2(data->bkp_fd[1], 1);
		close(1);
		close(0);
		perror(data->cmd->cmd[0]);
		data->exit_code = 127;
		clean_exit(data, 0);
	}
	else
		clean_exit(data, 0);
}

void	config_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->fd = ft_calloc(data->n_cmd * 2, sizeof(int));
	while (data->n_cmd != 1 && i < data->n_cmd * 2 - 1)
	{
		pipe(&data->fd[i]);
		i += 2;
	}
}

void	dup_pipe(int i, int ord, t_data *data)
{
	if (i == 0)
	{
		dup2(data->fd[1], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
		close(data->fd[1]);
	}
	else if (i == data->n_cmd - 1)
	{
		dup2(data->fd[ord - 2], 0);
		close_fd(data, (data->n_cmd - 1) * 2);
		close(data->fd[ord - 2]);
	}
	else
	{
		dup2(data->fd[ord - 2], 0);
		dup2(data->fd[ord + 1], 1);
		close_fd(data, (data->n_cmd - 1) * 2);
		close(data->fd[ord - 2]);
		close(data->fd[ord + 1]);
	}
}
