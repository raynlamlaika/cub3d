 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:10:29 by abouabba          #+#    #+#             */
/*   Updated: 2024/11/22 12:32:24 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"  

static int	ft_overflow(int sing)
{
	if (sing == 1)
		return (-1);   
	return (0);
}

int	ft_atoi(const char	*str)
{
	int				i;
	unsigned long	n;
	int				a;

	i = 0;
	n = 0;
	a = 1;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (n > (9223372036854775807UL - (str[i] - 48)) / 10)
			return (ft_overflow(a));
		n = n * 10 + (str[i] - 48);
		i++;
	}
	return (n * a);
}
