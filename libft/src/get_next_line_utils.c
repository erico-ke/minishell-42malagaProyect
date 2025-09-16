/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:22:00 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:28:16 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	while (i < (count * size))
		((unsigned char *)ptr)[i++] = '\0';
	return (ptr);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*combinedstring;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	j = 0;
	i = 0;
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	if (!s1 && !s2)
		return (NULL);
	combinedstring = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!combinedstring)
		return (NULL);
	while (i < len_s1)
	{
		combinedstring[i] = s1[i];
		i++;
	}
	while (j < len_s2)
		combinedstring[i++] = s2[j++];
	combinedstring[i] = '\0';
	free(s1);
	return (combinedstring);
}

void	ft_strlcpy_gnl(char const *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strchr_gnl(const char *str, int c)
{
	while (*str != '\0' && *str != (char)c)
		str++;
	if ((char)c == *str)
		return ((char *)str);
	return (0);
}
