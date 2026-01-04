/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:54:14 by fracurul          #+#    #+#             */
/*   Updated: 2026/01/04 11:07:49 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quoted_section(const char *s, int *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
}

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
		if (s[i] == '\'' || s[i] == '"')
		{
			words++;
			skip_quoted_section(s, &i);
		}
		else if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			words++;
			if ((s[i] == '>' || s[i] == '<') && s[i] == s[i + 1])
				i += 2;
			else
				i++;
		}
		else if (s[i])
		{
			words++;
			while (s[i] && s[i] != c && s[i] != '>' && s[i] != '<'
				&& s[i] != '|' && s[i] != '\'' && s[i] != '"')
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
	int		i;
	int		pipes;
	int		in_quote;
	int		in_dquote;

	i = 0;
	pipes = 0;
	in_quote = 0;
	in_dquote = 0;
	while (data->input[i])
	{
		if (data->input[i] == '\'' && !in_dquote)
			in_quote = !in_quote;
		else if (data->input[i] == '"' && !in_quote)
			in_dquote = !in_dquote;
		else if (data->input[i] == '|' && !in_quote && !in_dquote)
			pipes++;
		i++;
	}
	return (pipes);
}
