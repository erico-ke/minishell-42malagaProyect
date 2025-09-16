/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:48:21 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:59:27 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_mini_split(char *str, char c)
{
	size_t	i;
	size_t	j;
	char	**splitedstr;

	i = 0;
	j = 0;
	splitedstr = (char **)malloc (sizeof(char *) * 3);
	if (!splitedstr)
		return (free(splitedstr), NULL);
	while (str[i] && str[i] != c)
		i++;
	splitedstr[0] = ft_substr(str, 0, i);
	j = i + 1;
	while (str[i])
		i++;
	splitedstr[1] = ft_substr(str, j, i);
	splitedstr[2] = NULL;
	return (splitedstr);
}
