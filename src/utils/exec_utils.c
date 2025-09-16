/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:10:38 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 17:19:02 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_full_path(char *dir, char *cmd)
{
	char	*pre;
	char	*full_path;

	pre = ft_strjoin(dir, "/");
	full_path = ft_strjoin(pre, cmd);
	free(pre);
	return (full_path);
}

static int	ft_path_replace(char **argv, char **paths)
{
	int		i;
	char	*replacement;

	i = 0;
	if (!argv[0])
		return (0);
	while (paths[i])
	{
		replacement = ft_full_path(paths[i], argv[0]);
		if (access(replacement, F_OK) == 0)
		{
			free(argv[0]);
			argv[0] = ft_strdup(replacement);
			free(replacement);
			return (1);
		}
		free(replacement);
		i++;
	}
	return (0);
}

void	ft_execpath(t_data *data)
{
	t_key	*path_key;
	char	**path_dirs;
	char	*path_aux;

	path_key = ft_get_keymap(data->env, "PATH");
	if (!path_key || !path_key->value)
	{
		perror("PATH not found in environment");
		return ;
	}
	path_aux = ft_strdup(path_key->value);
	path_dirs = ft_split(path_aux, ':');
	free(path_aux);
	if (!ft_path_replace(data->argv, path_dirs))
	{
		perror("Command not found in PATH");
	}
	ft_free_matrix(path_dirs);
}

static void	ft_executor(t_data *data, char **env, int fdin, int fdout)
{
	if (execve(data->argv[0], data->argv, env) == -1)
	{
		perror("execve error");
		ft_free_resources(data);
		ft_free_matrix(env);
		exit(EXIT_FAILURE);
	}
	if (data->status == 131)
	{
		ft_free_resources(data);
		ft_free_matrix(env);
		dup2(fdin, STDIN_FILENO);
		dup2(fdout, STDOUT_FILENO);
		close(fdin);
		close(fdout);
		exit(0);
	}
}

void	ft_runexec(t_data *data, char **env, int fdin, int fdout)
{
	env = ft_revert_env(data->env);
	if (fdin != STDIN_FILENO)
	{
		if (dup2(fdin, STDIN_FILENO) == -1)
		{
			perror("dup2 error for fdin");
			exit(EXIT_FAILURE);
		}
		close(fdin);
	}
	if (fdout != STDOUT_FILENO)
	{
		if (dup2(fdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 error for fdout");
			exit(EXIT_FAILURE);
		}
		close(fdout);
	}
	ft_executor(data, env, fdin, fdout);
}
