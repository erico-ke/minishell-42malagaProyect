/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/28 18:44:26 by erico-ke         ###   ########.fr       */
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

void	ft_prompt_preexecutor(t_data *data)
{
	int		pipe_num;
	char	*c_input;
	int		i;

	i = 0;
	if (!check_input(data->input))
		return ;
	pipe_num = ft_count_pipes(data);
	c_input = ft_strtrim(data->input, " ");
	data->tokens = tokenize_command(tokenizer(c_input, &i), &i, 0, 0);
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
