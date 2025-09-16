/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 13:14:16 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:23:29 by erico-ke         ###   ########.fr       */
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

static void	ft_exec_no_pipes(t_data *data, t_token *curr, t_token *next)
{
	t_token	*token;

	token = data->tokens[0];
	if (token && (has_redirection(token) || has_redir_cmd(data)))
	{
		ft_start_redi(data, token);
		ft_redir_cmd(data, token);
	}
	if (ft_nonenv_builtin(curr->cmd)
		|| (ft_is_env_builtin(curr->cmd) && !next))
		ft_exec_built(data, curr->cmd);
	else if (access(data->input, F_OK) == -1 && (data->input[0] == '<'
			|| data->input[0] == '>'))
		return ;
	else
	{
		data->child = fork();
		if (data->child < 0)
			perror(FORK_ERR);
		if (data->child == 0)
			ft_exec(data, (int []){data->fdin, data->fdout});
	}
}

void	ft_executor_controler(t_data *data, int pipe_num)
{
	t_token	*curr_token;
	t_token	*next_token;

	g_block = 1;
	ft_setup_parent_signals();
	if (pipe_num == 0)
	{
		curr_token = data->tokens[0];
		if (!curr_token)
			return ;
		next_token = data->tokens[1];
		if (!curr_token || !curr_token->cmd)
			return (perror("Command token not found\n"));
		ft_load_args(data, curr_token);
		ft_clean_and_replace_args(data);
		ft_exec_no_pipes(data, curr_token, next_token);
	}
	else
		ft_pipe_processing(data, pipe_num, NULL, NULL);
	waitpid(data->child, &data->status, 0);
	g_block = 0;
	ft_ign_signals();
	ft_setup_parent_signals();
	ft_close_fds(data);
}

void	ft_child_proccess(t_data *data, t_token *curr, int fd[2], int i)
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
	if (i < data->aux)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 error for fdout");
			exit(EXIT_FAILURE);
		}
		close(fd[1]);
	}
	close(fd[0]);
	if (ft_nonenv_builtin(curr->cmd) == FALSE
		&& (ft_is_env_builtin(curr->cmd) == FALSE))
		ft_runexec(data, NULL, STDIN_FILENO, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	ft_pipe_processing(t_data *data, int pin, t_token *curr, t_token *next)
{
	int		fd[2];
	int		i;
	t_token	*token;

	i = -1;
	while (++i <= pin)
	{
		data->pipe_num = pin;
		if (pipe(fd) == -1)
			return (perror(PIPE_ERR));
		curr = data->tokens[i];
		next = data->tokens[i + 1];
		if (!curr || !curr->cmd)
			return (perror("Command token not found\n"));
		ft_load_args(data, curr);
		ft_clean_and_replace_args(data);
		token = data->tokens[0];
		ft_redir_check(token, data, fd);
		data->aux = data->pipe_num;
		data->pipe_num = i;
		ft_control_child(data, curr, next, fd);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	ft_close_fds(data);
}
