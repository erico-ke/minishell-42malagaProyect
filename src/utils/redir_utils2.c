/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fracurul <fracurul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:16:42 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/04 21:46:08 by fracurul         ###   ########.fr       */
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
			return (1);
		}
		i++;
	}
	return (0);
}
