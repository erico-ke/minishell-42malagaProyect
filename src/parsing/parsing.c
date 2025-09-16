/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:59:23 by fracurul          #+#    #+#             */
/*   Updated: 2025/05/29 18:43:55 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *line)
{
	int	quote;
	int	dquote;

	quote = 0;
	dquote = 0;
	while (*line)
	{
		if (*line == '\'' && (dquote % 2 == 0))
			quote++;
		if (*line == '\"' && (quote % 2 == 0))
			dquote++;
		line++;
	}
	if ((quote % 2 == 0) && (dquote % 2 == 0))
		return (TRUE);
	return (FALSE);
}

int	is_in_quotes(char *line, int index)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (i < index)
	{
		if (line[i] == '\'' && dquote == 0)
			quote = !quote;
		if (line[i] == '\"' && quote == 0)
			dquote = !dquote;
		i++;
	}
	return (quote || dquote);
}

int	check_line(char *line)
{
	int	len;
	int	i;

	i = -1;
	len = (int)ft_strlen(line);
	if (!check_quotes(line))
		return (FALSE);
	if (len == 1 && line[0] == '\n' && line[1] == '\0')
		return (FALSE);
	if (line[0] == '|')
		return (FALSE);
	if (len != 0 && (line[len - 1] == '|' || line[len - 1] == '>'
			|| line[len - 1] == '<'))
		return (FALSE);
	while (line[++i])
	{
		if ((line[i] == '|' && (line[i + 1] == '>' || line[i + 1] == '<'
					|| line[i + 1] == '|')) || (line[i] == '|'
				&& ((line[i + 2] == '>'
						|| line[i + 2] == '<' || line[i + 2] == '|'))))
			return (FALSE);
		if ((line[i] == '&' || line[i] == ';') && !is_in_quotes(line, i))
			return (FALSE);
	}
	return (TRUE);
}

int	check_input(char *line)
{
	if (line)
	{
		if (!check_line(line) || !validate_metachar(line, 0))
			return (FALSE);
		else
			return (TRUE);
	}
	return (FALSE);
}
