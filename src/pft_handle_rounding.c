/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pft_handle_rounding.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urb-ilya@yandex.ru>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 18:47:58 by nalysann          #+#    #+#             */
/*   Updated: 2020/08/25 18:47:59 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "pft_bigint.h"
#include "pft_handle_bigfloat.h"
#include "pft_handle_placeholder.h"
#include "pft_utils.h"

#include <stddef.h>

static void		digit_plus_plus(t_string *string, unsigned len, int *more)
{
	*more = 0;
	if (string->str[len - 1] == '9')
	{
		string->str[len - 1] = '0';
		*more = 1;
	}
	else
		++(string->str[len - 1]);
}

static void		round_decimal(t_string *decimal, char digit, int *more)
{
	unsigned	len;

	len = decimal->len;
	if (digit - '0' > 5)
	{
		digit_plus_plus(decimal, len, more);
		--len;
	}
	else if (digit - '0' == 5 && (decimal->str[len - 1] - '0') % 2 != 0)
		digit_plus_plus(decimal, len, more);
	while (len > 0 && *more)
	{
		--len;
		digit_plus_plus(decimal, len + 1, more);
	}
	if (*more)
	{
		ft_memmove(decimal->str + 1, decimal->str, decimal->len);
		++(decimal->len);
		decimal->str[0] = '1';
	}
}

int				round_fractional(t_string *decimal, t_string *fractional,
						t_fields *fields)
{
	unsigned	len;
	int			more;
	char		digit;

	len = fractional->len - 1;
	more = 0;
	if (fractional->str[len] - '0' >= 5 && fractional->str[len - 1] != '.')
		digit_plus_plus(fractional, len, &more);
	--len;
	while (fractional->str[len - 1] != '.' && more)
	{
		--len;
		digit_plus_plus(fractional, len + 1, &more);
	}
	digit = fractional->str[1];
	fractional->str[(fractional->len)-- - 1] = '\0';
	if (more || fields->precision == 1)
		round_decimal(decimal, digit, &more);
	return (more);
}

int				count_leading_zeros(t_bigfloat *bf)
{
	int		len;

	if (bf->fractional.size == 0)
		return (0);
	len =
		get_length_unsigned(bf->fractional.blocks[bf->fractional.size - 1], 10);
	return (63 - bf->exponent -
			BIGINT_BLOCK_SIZE * (bf->fractional.size - 1) - len);
}