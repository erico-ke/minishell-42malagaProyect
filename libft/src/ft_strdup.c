/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:18:06 by erico-ke          #+#    #+#             */
/*   Updated: 2025/06/05 17:28:16 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns a pointer to a new string which is a duplicate of the string s1.
char	*ft_strdup(const char *s1)
{
	char	*cpy;

	if (!s1)
		return (NULL);
	cpy = (char *)malloc(ft_strlen(s1) + 1);
	if (!cpy)
		return (0);
	ft_memcpy(cpy, s1, ft_strlen(s1) + 1);
	return (cpy);
}
