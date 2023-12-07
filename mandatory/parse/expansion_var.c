/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:42:48 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/07 05:04:16 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// PENSAR COMO RETIRAR AS ASPAS DUPLAS EM CASO DE VARIAVEL EXPANSÃO
int	can_expand(t_data *data, char *var)
{
	t_env	*tmp;

	tmp = data->env_node;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, var, ft_strlen(tmp->var) + 1))
			tmp = tmp->next;
		else
			return (1);
	}
	return (0);
}

int	has_variable(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (can_expand(data, &str[++i]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*get_var_value(t_data *data, char *var, int *i)
{
	t_env	*tmp;

	tmp = data->env_node;
	while (tmp)
	{
		if ((ft_strncmp(tmp->var, var, ft_strlen(tmp->var) + 1)) == 0)
		{
			(*i) += ft_strlen(tmp->var);
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_str_expand_process(char *str, char *var, char *value, int i)
{
	int		j;
	int		k;
	int		len;
	char	*new_str;

	k = 0;
	j = 0;
	len = ((ft_strlen(str) - ft_strlen(var)) + ft_strlen(value));
	new_str = malloc(sizeof(char) * len + 1);
	while (j++ < i && str[j] != '$')
		new_str[j] = str[j];
	if (ft_strncmp(&str[i], var, ft_strlen(var) + 1) == 0)
	{
		while (value[k] != '\0')
			new_str[j++] = value[k++];
	}
	i += ft_strlen(var);
	while (str[i] && str[i] != '\0')
		new_str[j++] = str[i++];
	return (new_str);
}

char	*get_str_expand(t_data *data, char *str)
{
	int		i;
	char	*value;
	char	*new_str;

	value = NULL;
	new_str = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			if (can_expand(data, &str[++i]))
			{
				printf("VALUE i: %i\n", i);
				new_str = ft_substr(str, 0, i - 1);
				value = get_var_value(data, &str[i], &i);
				new_str = ft_strjoin(new_str, value);
				str = ft_strjoin(new_str, &str[i]);
				i = 0;
				// i += ft_strlen(value);
				// str = get_str_expand_process(str, &str[i], value, i);
			}
		}
		i++;
	}
	return (str);
}

char	**process_vars(t_data *data, char **words)
{
	int		i;
	char	*aux;

	i = 0;
	while (words[i] != NULL)
	{
		if (has_variable(data, words[i]))
		{
			aux = words[i];
			words[i] = get_str_expand(data, aux);
			free(aux);
		}
		i++;
	}
	return (words);
}

int	check_vars(t_data *data, char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (has_variable(data, words[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

// char	*revise_str(t_data *data, char *word)
// {

// }
