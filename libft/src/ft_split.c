/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:05:28 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:57:07 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counterwords(const char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			words++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (words);
}

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		found;
	char	**splitedstr;

	i = 0;
	j = 0;
	found = 0;
	splitedstr = (char **)malloc(sizeof(char *) * (ft_counterwords(s, c) + 1));
	if (!splitedstr)
		return (free(splitedstr), NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (i > 0 && s[i - 1] != c)
			splitedstr[found++] = ft_substr(s, j, (i - j));
	}
	splitedstr[found] = NULL;
	return (splitedstr);
}
