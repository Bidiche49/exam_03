/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntardy <ntardy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:54:35 by ntardy            #+#    #+#             */
/*   Updated: 2023/10/03 01:39:09 by ntardy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_putstr(char *str)
{
	int lenght = 0;

	if (!str)
		return (ft_putstr("(null)"));
	while (*str)
		lenght += write(1, str++, 1);
	return (lenght);
}

int	put_digit(long long int nb, int len_base)
{
	char *hexa = "0123456789abcdef";
	int lenght = 0;

	if (nb < 0)
	{
		lenght += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > len_base)
		lenght += put_digit(nb/len_base, len_base);
	lenght += write (1, &hexa[nb % len_base], 1);
	return (lenght);
}

int	ft_printf(char *format, ...)
{
	int lenght = 0;

	va_list	pointer;
	va_start(pointer, format);

	while (*format)
	{
		if ((*format == '%') && ((*(format + 1) == 's') || (*(format + 1) == 'd') || (*(format + 1) == 'x')))
		{
			format++;
			if (*format == 's')
				lenght += ft_putstr(va_arg(pointer, char *));
			else if (*format == 'd')
				lenght += put_digit((long long int)va_arg(pointer, int), 10);
			else if (*format == 'x')
				lenght += put_digit((long long int)va_arg(pointer, unsigned int), 16);
		}
		else
			lenght += write(1, format, 1);
		format++;
	}
	return (va_end(pointer), lenght);
}

int main(void)
{
	char *str = NULL;
	ft_printf("salut %s, j'ai %x age\n", str, 2224);
	printf("salut %s, j'ai %x age\n", str, 2224);
	printf("%d\n", ft_printf("salut %s, j'ai %d age\n", str, -2624));
	printf("%d\n", printf("salut %s, j'ai %d age\n", str, -2624));
	printf("salut %s\n", str);
	printf("%d\n", ft_printf("salut %s", str));
	printf("%d\n", printf("salut %s", str));
}
