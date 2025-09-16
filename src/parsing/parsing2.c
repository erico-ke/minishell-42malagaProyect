/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/06/04 17:37:05 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_counterwords(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (is_op(s[i]))
		{
			words++;
			if ((s[i] == '>' || s[i] == '<') && s[i] == s[i + 1])
				i += 2;
			else
				i++;
		}
		else
		{
			words++;
			while (s[i] && s[i] != c && !is_op(s[i]))
				i++;
		}
	}
	return (words);
}

void	ft_prompt_preexecutor(t_data *data, int pipe_num, int i)
{
	char	*c_input;
	char	*tmp;

	if (!check_input(data->input))
		return ;
	pipe_num = ft_count_pipes(data);
	c_input = ft_strtrim(data->input, " ");
	data->tokens = tokenize_command(tokenizer(c_input, &i), &i, 0, 0);
	i = -1;
	while (data->tokens[++i] && data->tokens[i]->cmd)
	{
		tmp = data->tokens[i]->cmd;
		data->tokens[i]->cmd = ft_strtrim(data->tokens[i]->cmd, "\"");
		free(tmp);
		if (data->tokens[i] && data->tokens[i]->cargs
			&& data->tokens[i]->cargs[i])
		{
			tmp = data->tokens[i]->cargs[i];
			data->tokens[i]->cargs[i] = ft_strtrim(data->tokens[i]->cargs[i],
					"\"");
			free(tmp);
		}
	}
	free(c_input);
	ft_executor_controler(data, pipe_num);
}

int	ft_is_all_space(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ')
			return (FALSE);
		i++;
	}
	data->status = 127;
	return (TRUE);
}

int	ft_count_pipes(t_data *data)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (data->input[i])
	{
		if (data->input[i] == '|')
			pipes++;
		i++;
	}
	return (pipes);
}
