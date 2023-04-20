/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:50:51 by ccompote          #+#    #+#             */
/*   Updated: 2022/05/25 19:44:27 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] && haystack[i + j]
			&& needle[j] == haystack[i + j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		if (!haystack[i + j] || j + i == len)
			return (NULL);
		i++;
	}
	return (NULL);
}
