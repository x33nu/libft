/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalysann <urbilya@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 10:51:21 by nalysann          #+#    #+#             */
/*   Updated: 2020/08/27 10:51:22 by nalysann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"
#include "ft_string.h"

#include <stddef.h>
#include <stdlib.h>

char	**ft_strsplit(const char *s, char sep)
{
	char	**split;
	char	*p;
	size_t	n;
	size_t	i;

	n = ft_strcnt(s, sep);
	split = (char **)malloc((n + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p = ft_strjmp(&s, sep);
		split[i] = ft_strndup(p, s - p);
		if (split[i] == NULL)
		{
			free_split(split, 0);
			return (NULL);
		}
		++i;
	}
	split[n] = NULL;
	return (split);
}
