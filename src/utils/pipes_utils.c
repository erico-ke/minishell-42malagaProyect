/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 20:28:15 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:29:17 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cld_cntrl_ext(t_data *data, t_token *curr, int fd[2], t_token *next)
{
	int	aux;

	if (ft_nonenv_builtin(curr->cmd) || (ft_is_env_builtin(curr->cmd) && !next))
	{
		aux = data->fdout;
		if (data->pipe_num != data->aux)
			data->fdout = fd[1];
		ft_exec_built(data, curr->cmd);
		data->fdout = aux;
	}
	else
	{
		if (ft_nonenv_builtin(curr->cmd) == FALSE
			&& (ft_is_env_builtin(curr->cmd) == FALSE)
			&& access(data->argv[0], F_OK) != 0)
		{
			ft_execpath(data);
			ft_child_proccess(data, curr, fd, data->pipe_num);
		}
	}
}

void	ft_control_child(t_data *data, t_token *curr, t_token *next, int fd[2])
{
	data->child = fork();
	if (data->child < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (perror(FORK_ERR));
	}
	if (data->child == 0)
	{
		cld_cntrl_ext(data, curr, fd, next);
		close(fd[0]);
		close(fd[1]);
		ft_special_exit(data);
	}
	else
	{
		close(fd[1]);
		if (data->pipe_num > 0)
			close(data->fdin);
		data->fdin = fd[0];
	}
}

void	ft_redir_check(t_token *token, t_data *data, int fd[2])
{
	if (token && (has_redirection(token) || has_redir_cmd(data)))
	{
		ft_start_redi(data, token);
		ft_redir_cmd(data, token);
		close(fd[1]);
		fd[1] = data->fdout;
	}
}
