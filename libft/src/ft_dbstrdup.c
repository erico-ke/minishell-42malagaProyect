/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:04:57 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 17:01:42 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_dbp_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_dbstrdup(char **s1)
{
	char	**s2;
	int		i;

	i = 0;
	s2 = ft_calloc(ft_dbp_size(s1) + 1, sizeof(char *));
	while (s1[i])
	{
		s2[i] = ft_strdup(s1[i]);
		i++;
	}
	s2[i] = NULL;
	return (s2);
}
