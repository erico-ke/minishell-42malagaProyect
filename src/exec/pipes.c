/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:14:16 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 17:35:47 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(t_data *data)
{
	if (data->fdin != STDIN_FILENO)
		close(data->fdin);
	if (data->fdout != STDOUT_FILENO)
		close(data->fdout);
	data->fdin = STDIN_FILENO;
	data->fdout = STDOUT_FILENO;
}

void ft_executor_controler(t_data *data, int pipe_num)
{
	t_token *curr_token;
	t_token *next_token;
	t_token *token;

	if (pipe_num == 0)
	{
		curr_token = data->tokens[0];
		next_token = data->tokens[1];
		if (!curr_token || !curr_token->cmd)
		{
			perror("Command token not found\n");
			return;
		}
		ft_load_args(data, curr_token);
		ft_clean_and_replace_args(data);
		token = data->tokens[0];
		if (token && (has_redirection(token) || has_redir_cmd(data)))
		{
			ft_start_redi(data, token);
			ft_redir_cmd(data, token);
		}
		if (ft_nonenv_builtin(curr_token->cmd) || (ft_is_env_builtin(curr_token->cmd) && !next_token))
			ft_exec_built(data, curr_token->cmd);
		else
		{
			data->child = fork();
			if (data->child < 0)
				perror(FORK_ERR);
			if (data->child == 0)
				ft_exec(data, (int[]){data->fdin, data->fdout});
		}
	}
	else
		ft_pipe_processing(data, pipe_num);
	ft_ign_signals();
	waitpid(data->child, &data->status, 0);
	ft_setup_parent_signals();
	ft_close_fds(data);
}

void ft_pipe_processing(t_data *data, int pipe_num)
{
	int		fd[2];
	int 	i;
	t_token *curr_token;
	t_token *next_token;
	t_token *token;

	i = 0;
	while (i <= pipe_num)
	{
		if (pipe(fd) == -1)
		{
			perror(PIPE_ERR);
			return;
		}
		curr_token = data->tokens[i];
		next_token = data->tokens[i + 1];
		if (!curr_token || !curr_token->cmd)
		{
			perror("Command token not found\n");
			return;
		}
		ft_load_args(data, curr_token);
		ft_clean_and_replace_args(data);
		token = data->tokens[0];
		if (token && (has_redirection(token) || has_redir_cmd(data)))
		{
			ft_start_redi(data, token);
			ft_redir_cmd(data, token);
			close(fd[1]);
			fd[1] = data->fdout;
		}
		if (ft_nonenv_builtin(curr_token->cmd) 
			|| (ft_is_env_builtin(curr_token->cmd) && !next_token))
			ft_exec_built(data, curr_token->cmd);
		else
		{
			if (ft_nonenv_builtin(curr_token->cmd) == FALSE && (ft_is_env_builtin(curr_token->cmd) == FALSE) && access(data->argv[0], F_OK) != 0)
				ft_execpath(data);
			data->child = fork();
			if (data->child < 0)
			{
				close(fd[0]);
				close(fd[1]);
				perror(FORK_ERR);
				return;
			}
			if (data->child == 0)
			{
				if (i > 0)
				{
					if (dup2(data->fdin, STDIN_FILENO) == -1)
					{
						perror("dup2 error for fdin");
						exit(EXIT_FAILURE);
					}
					close(data->fdin);
				}
				if (i < pipe_num)
				{
					if (dup2(fd[1], STDOUT_FILENO) == -1)
					{
						perror("dup2 error for fdout");
						exit(EXIT_FAILURE);
					}
					close(fd[1]);
				}
				close(fd[0]);
				if (ft_nonenv_builtin(curr_token->cmd) == FALSE && (ft_is_env_builtin(curr_token->cmd) == FALSE))
					ft_runexec(data, NULL, STDIN_FILENO, STDOUT_FILENO);
				exit(EXIT_SUCCESS);
			}
			else
			{
				close(fd[1]);
				if (i > 0)
					close(data->fdin);
				data->fdin = fd[0];
			}
		}
		i++;
	}
	while(waitpid(-1, NULL, 0)  > 0)
	;
}
