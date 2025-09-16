/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:52:21 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/04 20:57:08 by fracurul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_data *data, int fd[2])
{
	g_block = 1;
	if (data->env->keys[0] != NULL && access(data->argv[0], F_OK) != 0)
		ft_execpath(data);
	ft_runexec(data, NULL, fd[0], fd[1]);
	g_block = 0;
}
