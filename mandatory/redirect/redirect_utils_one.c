/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils_one.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:10:45 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/06 21:29:46 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*jump_white_spaces(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	if (tmp == NULL)
		return (NULL);
	while (tmp && (tmp->type == C_SPACE || tmp->type == H_TAB))
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*word_case(t_token *tokens)
{
	t_token	*tmp;
	char	*result;

	tmp = tokens;
	result = ft_strdup(tmp->token);
	if (tmp->next)
		tmp = tmp->next;
	else
		return (result);
	while (tmp)
	{
		if (tmp->type != SLASH && tmp->type != WORD
			&& is_special_case(tmp->type, 3))
			break ;
		result = ft_strjoin(result, tmp->token);
		tmp = tmp->next;
	}
	return (result);
}

// PRECISO AJUSTAR A expansão de variavel em caso de exit status
char	*find_file_name(t_token *tokens)
{
	t_token	*temp;

	temp = tokens;
	if (check_file_name(tokens))
		return_error();
	while (temp)
	{
		if (temp->type == C_SPACE || temp->type == H_TAB)
		{
			while (temp->type == C_SPACE || temp->type == H_TAB)
				temp = temp->next;
		}
		if (temp->type == QUOTED_WORD)
			return (take_q_name(temp));
		if (temp->type == EXIT_STATUS)
			return (ft_strdup("0"));
		if (temp->type == WORD || is_slashcase(temp->type)
			|| is_special_case(temp->type, 2))
			return (word_case(temp));
		temp = temp->next;
	}
	ft_error_redirect(4);
	return (NULL);
}

// Handle the error appropriately
t_params	*inicialize_rd_params(void)
{
	t_params	*params;

	params = (t_params *)malloc(sizeof(t_params));
	if (!params)
	{
		printf("Error malloc: initialize_rd_params");
		exit(1);
	}
	params->i = 0;
	params->index = 0;
	params->len = 0;
	params->inside_pipe = 0;
	params->files = NULL;
	params->redirects = NULL;
	return (params);
}
