/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:16:42 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:16:57 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_redir_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i] && data->tokens[i]->cmd)
	{
		if (ft_redir_type(data->tokens[i]->cmd) != -1)
		{
			printf("que hay aqui2:%s\n", data->tokens[i]->cmd);
			return (1);
		}
		i++;
	}
	return (0);
}
