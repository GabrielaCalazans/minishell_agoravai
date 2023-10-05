/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:59:35 by gacalaza          #+#    #+#             */
/*   Updated: 2023/10/03 16:15:56 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_dollar(char c)
{
	if (c == '$')
		return (7);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\"')
		return (8);
	if (c == '\'')
		return (9);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ')
		return (11);
	return (0);
}

int	is_heredoc(char *str, int check)
{
	if (check == 1)
	{
		if (str[0] == str[1])
			return (12);
	}
	if (check == 2)
	{
		if (str[0] == str[1])
			return (13);
	}
	return (check);
}

int	find_type(char *str)
{
	if (0 < is_redirect(*str))
		return (is_heredoc(str, is_redirect(*str)));
	if (0 < is_pipe(*str))
		return (is_pipe(*str));
	if (0 < is_flag(*str))
		return (is_flag(*str));
	if (0 < is_dollar(*str))
		return (is_dollar(*str));
	if (0 < is_slash(*str))
		return (is_slash(*str));
	if (0 < is_questionmark(*str))
		return (is_questionmark(*str));
	if (0 < is_quote(*str))
		return (is_quote(*str));
	if (0 < is_space(*str))
		return (is_space(*str));
	else
		return (10);
}
