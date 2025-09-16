/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:50:15 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/26 11:57:49 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strchr_mn(char *str, int c)
{
	if (!str)
		return (FALSE);
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

int	ft_is_expandable(char *var)
{
	if (var[0] != '\'' && ft_strchr_mn(var, '$'))
		return (TRUE);
	else
		return (FALSE);
}
