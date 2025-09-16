/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erico-ke <erico-ke@42malaga.student.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:49:07 by erico-ke          #+#    #+#             */
/*   Updated: 2025/05/26 11:57:49 by erico-ke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_printf(const char *string, ...);
void	ft_putchar(int c, int *count);
void	ft_putstrc(char *str, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putunsignednbr(unsigned int nbr, int *count);
void	ft_printhexa(unsigned long long nbr, char h, int *count);
void	ft_printptr(void *ptr, int *count);

#endif
