/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urb-ilya@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 18:26:33 by nalysann          #+#    #+#             */
/*   Updated: 2020/07/13 18:26:35 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

static int	count_with_longwords(const char *s, const char *char_ptr,
								const char *end_ptr)
{
	const unsigned long		*long_ptr;
	unsigned long			longword;
	size_t					i;

	long_ptr = (unsigned long *)char_ptr;
	while (long_ptr < (unsigned long *)end_ptr)
	{
		longword = *long_ptr++;
		if (((longword - 0x0101010101010101) & 0x8080808080808080))
		{
			char_ptr = (const char *)(long_ptr - 1);
			i = -1;
			while (++i < sizeof(unsigned long))
				if (char_ptr[i] == '\0')
					break ;
			if (i < 8 && (char_ptr += i))
				break;
		}
		char_ptr = end_ptr;
	}
	if (char_ptr > end_ptr)
		char_ptr = end_ptr;
	return (char_ptr - s);
}

size_t		ft_strnlen(const char *s, size_t maxlen)
{
	const char	*char_ptr;
	const char	*end_ptr;

	if (maxlen == 0)
		return (0);
	char_ptr = (const char *)s;
	end_ptr = s + maxlen;
	while (((size_t)char_ptr & (sizeof(unsigned long) - 1)) != 0)
	{
		if (*char_ptr == '\0')
		{
			if (char_ptr > end_ptr)
				char_ptr = end_ptr;
			return (char_ptr - s);
		}
		++char_ptr;
	}
	return (count_with_longwords(s, char_ptr, end_ptr));
}