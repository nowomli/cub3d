/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:22:23 by ccompote          #+#    #+#             */
/*   Updated: 2022/03/25 12:35:01 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ldst;
	size_t	lsrc;

	if (!src && !dst)
		return (0);
	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (dstsize < ldst)
		return (dstsize + lsrc);
	else
	{
		dst += ldst;
		ft_strlcpy(dst, src, (dstsize - ldst));
		return (ldst + lsrc);
	}
}
