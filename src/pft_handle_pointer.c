/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_handle_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urb-ilya@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:47:41 by nalysann          #+#    #+#             */
/*   Updated: 2020/08/25 18:47:42 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"
#include "pft_handle_placeholder.h"
#include "pft_utils.h"

#include <stdarg.h>
#include <stddef.h>

char	*handle_pointer(t_fields *fields, va_list ap)
{
	char *result;
	char str[42];

	itoa_base_unsigned((unsigned long)va_arg(ap, void *), HEXL_DIGITS, str);
	if (!(result = ft_strnew(ft_strlen(str) + 2)))
		return (NULL);
	result[0] = '0';
	result[1] = 'x';
	ft_strcpy(result + 2, str);
	(void)fields;
	return (result);
}