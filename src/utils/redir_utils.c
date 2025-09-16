/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 15:43:09 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/04 19:12:38 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_clean_redirections(char **tokens)
{
	char	**cleaned;
	int		i;
	int		j;
	int		type;

	i = 0;
	j = 0;
	cleaned = ft_calloc(sizeof(char *), (ft_matrix_size(tokens) + 1));
	if (!cleaned)
		return (NULL);
	while (tokens[i])
	{
		type = ft_redir_type(tokens[i]);
		if ((type == S_OUT || type == D_OUT || type == S_IN || type == D_IN)
			&& tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		cleaned[j++] = ft_strdup(tokens[i++]);
	}
	return (cleaned);
}

void	ft_clean_and_replace_args(t_data *data)
{
	char	**cleaned;

	cleaned = ft_clean_redirections(data->argv);
	ft_free_matrix(data->argv);
	data->argv = cleaned;
}

int	ft_redi_ok(const char *input)
{
	int	i;
	int	dquote;
	int	squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !squote)
			dquote = !dquote;
		else if (input[i] == '\'' && !dquote)
			squote = !squote;
		else if (!dquote && !squote && (input[i] == '>' || input[i] == '<'))
		{
			if ((input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<'))
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	has_redirection(t_token *token)
{
	int	j;

	j = 0;
	while (token->cargs && token->cargs[j])
	{
		if (ft_redir_type(token->cargs[j]) != -1)
			return (1);
		j++;
	}
	return (0);
}

void	ft_redir_cmd(t_data *data, t_token *token)
{
	int	type;
	int	i;

	i = 0;
	while (token && data->tokens[i] && data->tokens[i]->cmd)
	{
		type = ft_redir_type(data->tokens[i]->cmd);
		if (type == S_OUT || type == D_OUT)
		{
			if (token->cargs)
				ft_redirout(data, token->cargs[0], type);
			i++;
		}
		else if (type == S_IN || type == D_IN)
		{
			if (token->cargs)
				ft_redirin(data, token->cargs[0], type);
			i++;
		}
		i++;
	}
}
