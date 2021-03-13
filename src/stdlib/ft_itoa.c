/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urbilya@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 10:38:31 by nalysann          #+#    #+#             */
/*   Updated: 2020/08/27 10:38:52 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

#include <stddef.h>
#include <stdlib.h>

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	sign;
	char	*str;

	len = ft_intlen(n);
	sign = n < 0;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len > sign)
	{
		str[--len] = (char)('0' + ft_abs(n % 10));
		n /= 10;
	}
	if (sign != 0)
		str[--len] = '-';
	return (str);
}
