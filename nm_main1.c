/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inovomli <inovomli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:46:22 by inovomli          #+#    #+#             */
/*   Updated: 2023/05/01 11:49:13 by inovomli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_arg(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			printf("%s", args[i]);
			printf("\n");
			i++;
		}
	}
	else
		printf("args: (null)\n");
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	gtcl(mlx_texture_t *texture, int x_coord, int y_coord)
{
	int			byte;
	uint32_t	color;

	byte = (y_coord * texture->width * 4) + (x_coord * 4);
	color = ft_pixel(texture->pixels[byte], texture->pixels[byte + 1],
			texture->pixels[byte + 2], texture->pixels[byte + 3]);
	return (color);
}

int	min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
