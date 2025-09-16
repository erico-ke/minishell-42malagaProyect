/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:48:19 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:58:36 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_format(va_list args, const char format, int *count)
{
	if (format == 'c')
		ft_putchar(va_arg(args, int), count);
	if (format == 's')
		ft_putstrc(va_arg(args, char *), count);
	if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(args, int), count);
	if (format == 'u')
		ft_putunsignednbr(va_arg(args, unsigned int), count);
	if (format == 'x' || format == 'X')
		ft_printhexa(va_arg(args, unsigned int), format, count);
	if (format == 'p')
		ft_printptr(va_arg(args, void *), count);
	if (format == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, string);
	while (string[i])
	{
		if (string[i] == '%')
		{
			ft_format(args, string[++i], &count);
			i ++;
		}
		else
			ft_putchar(string[i++], &count);
	}
	va_end(args);
	return (count);
}
