/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/28 22:00:57 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static void	ft_signal_handler(t_data *data, int stat)
{
	if (WIFEXITED(stat))
		data->status = WEXITSTATUS(stat);
	else if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == SIGQUIT)
		{
			write(2, "Quit (core dumped)\n", 18);
			write(1, "\n", 1);
		}
		data->status = 128 + WTERMSIG(stat);
	}
}
*/
void	ft_exec(t_data *data, int fd[2])
{
	g_block = 1;
	if (data->env->keys[0] != NULL && access(data->argv[0], F_OK) != 0)
		ft_execpath(data);
	ft_runexec(data, NULL, fd[0], fd[1]);
	g_block = 0;
}
