/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_np.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:40:45 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:54:38 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strchr_np(char *str, int c)
{
	if (!str)
	{
		ft_putstr("str NULL\n");
		return (0);
	}
	if (*str == c)
		return (1);
	else
		return (0);
}
