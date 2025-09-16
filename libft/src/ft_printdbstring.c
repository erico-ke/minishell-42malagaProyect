/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdbstring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 13:10:29 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:58:51 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_printdbstring(char **db)
{
	int	i;

	i = 0;
	while (db[i])
	{
		ft_putstr(db[i++]);
		write(1, "\n", 1);
	}
}
