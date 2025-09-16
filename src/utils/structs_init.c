/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:09:20 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/26 16:15:49 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*ft_init_data(int argc, char **env)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->input = NULL;
	data->child = 42;
	data->argv = NULL;
	data->tokens = NULL;
	data->lvl = 0;
	data->env = ft_fill_map(env);
	data->exp = ft_fill_map(env);
	data->argc = argc;
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
	data->expand = NULL;
	return (data);
}

void	ft_map_init(t_map *map)
{
	if (!map)
		return ;
	map->size = 0;
	map->capacity = 20;
	map->keys = (t_key **)ft_calloc(sizeof(t_key *), map->capacity);
	if (!map->keys)
		perror(MALLOC_ERR);
}

t_token	*get_next_token(t_token **token, int reset)
{
	static int	position = 0;
	int			array_size;
	t_token		*invalid_token;

	array_size = ft_toklen(token);
	if (reset == TRUE)
		position = 0;
	if (position >= array_size)
	{
		position = 0;
		invalid_token = malloc(sizeof(t_token));
		if (!invalid_token)
			return (NULL);
		invalid_token->cmd = NULL;
		invalid_token->cargs = NULL;
		return (invalid_token);
	}
	return (token[position++]);
}

static void	token_check(t_data *data)
{
	if (!data->tokens)
	{
		perror("No tokens found\n");
		return ;
	}
}

void	ft_load_args(t_data *data, t_token *token)
{
	int	i;
	int	args_size;

	token_check(data);
	if (token->cargs)
	{
		args_size = ft_matrix_size(token->cargs);
		data->argc = args_size + 1;
	}
	else
		args_size = 0;
	data->argv = ft_calloc(sizeof(char *), args_size + 2);
	if (!data->argv)
	{
		perror("Memory allocation for argv failed\n");
		return ;
	}
	i = 0;
	data->argv[i] = ft_strdup(token->cmd);
	while (token->cargs[i])
	{
		data->argv[i + 1] = ft_strdup(token->cargs[i]);
		i++;
	}
	data->argv[i + 1] = NULL;
}
