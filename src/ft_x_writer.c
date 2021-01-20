/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atweek <atweek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 20:33:05 by atweek            #+#    #+#             */
/*   Updated: 2021/01/20 20:42:26 by atweek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "../libft/libft.h"

int hex_intlen(int num)
{
	
	if (num <= 0)
		return (0);
	else
		return(1 + hex_intlen(num / 16));
}

int hex_convert(unsigned int hex,int len,t_pars *st_pars)
{
	int count;
	int mod;
	char str[len + 1];
	int 		i;
	
	if (hex == 0)
		return (write(1,"0",1));
	i = 0;
	count = 0;
	while (hex > 0)
	{
		mod = hex % 16;
		hex = hex / 16;
		str[i++] = (st_pars->type == 'X') ? "0123456789ABCDEF"[mod] :
										"0123456789abcdef"[mod];
	}
	str[i--] = '\0';
	while (i >= 0)
		count += write(1,&str[i--],1);
	return (count);
}

int x_processing_minus(t_pars *st_pars,int len, int hex)
{
	int count;
	int i;
	// len = hex_intlen(hex);
	// len = (len == 0) ? 1 : len;
	count = 0;
	i = 0;
	while (i++ < st_pars->prec - len)
		count +=write(1,"0",1);
	count += hex_convert(hex,len,st_pars);
	// i += len;
	i = 0;
	while (i < st_pars->width - len && (i < st_pars->width - st_pars->prec))
	{
		if (st_pars->zero == 1)
			count += write(1,"0",1);
		else
			count +=write(1," ",1);
		i++;
	}
	return (count);
}

int x_processing(t_pars *st_pars, va_list argptr)
{
	int				i;
	unsigned int	hex;
	int count;
	int len;
	
	i = 0;
	count = 0;
	hex = va_arg(argptr, unsigned int);
	len = hex_intlen(hex);
	if ((st_pars->prec == 0 || (st_pars->prec == -1  && st_pars->dot == 1)))
	{
		while (i++ < st_pars->width)
			count += write(1," ", 1);
		return (count);
	}
	if (st_pars->prec != -1 && st_pars->zero == 1)
		st_pars->zero = -1;
	if (st_pars->prec == -1)
		st_pars->prec = 0;
	if (st_pars->width == -1)
		st_pars->width = 0;
	len = (len == 0) ? 1 : len;
	st_pars->prec = (st_pars->prec < len) ? st_pars->prec = 0 : st_pars->prec;
	if (st_pars->minus == 1)
	{
		return (x_processing_minus(st_pars,len,hex));
	}
	// if (hex == 0)
	// 	return (x_processing_zero(st_pars))
	while (i < st_pars->width - len && (i < st_pars->width - st_pars->prec))
	{
		if (st_pars->zero == 1)
			count += write(1,"0",1);
		else
			count +=write(1," ",1);
		i++;
	}
	i = 0;
	while (i++ < st_pars->prec - len)
		count += write(1,"0",1);
	count += hex_convert(hex,len,st_pars);
	return (count);
}
