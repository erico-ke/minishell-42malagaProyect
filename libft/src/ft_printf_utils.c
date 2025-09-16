/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 18:30:06 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/29 16:58:24 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
		ft_putstrc("-2147483648", count);
	else
	{
		if (n < 0)
		{
			ft_putchar('-', count);
			n = n * -1;
		}
		if (n > 9)
			ft_putnbr(n / 10, count);
		ft_putchar((n % 10) + '0', count);
	}
}

void	ft_putstrc(char *str, int *count)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(1, "(null)", 6);
		(*count) += 6;
	}
	else
	{
		while (str[i])
			ft_putchar(str[i++], count);
	}
}

void	ft_putunsignednbr(unsigned int nbr, int *count)
{
	if (nbr > 9)
		ft_putunsignednbr(nbr / 10, count);
	ft_putchar((nbr % 10) + '0', count);
}

void	ft_printhexa(unsigned long long nbr, char h, int *count)
{
	int		i;
	char	*base;
	char	str[25];

	i = 0;
	if (h == 'x')
		base = "0123456789abcdef";
	if (h == 'X')
		base = "0123456789ABCDEF";
	if (nbr == 0)
		return (ft_putchar('0', count));
	while (nbr > 0)
	{
		str[i] = base[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i--)
		ft_putchar(str[i], count);
}

void	ft_printptr(void *ptr, int *count)
{
	if (!ptr)
		ft_putstrc("0x0", count);
	else
	{
		ft_putstrc("0x", count);
		ft_printhexa((unsigned long long)ptr, 'x', count);
	}
}
