/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 18:02:58 by ccompote          #+#    #+#             */
/*   Updated: 2022/04/05 15:06:54 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = (unsigned int)ft_strlen(s);
	if (start > i)
		len = 0;
	if (len > i - start)
		len = i - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (sub);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
