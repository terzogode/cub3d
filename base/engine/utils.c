/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:42:39 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/03 01:17:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_image *img, int x, int y, t_color color)
{
	char	*dst;

	if (!img || x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	if (img->bpp == 32)
		*(unsigned int *)dst = (unsigned int)color.hex;
	else
		*(unsigned long *)dst = (unsigned long)color.hex;
}

void	init_color(t_game *g)
{
	g->floor->red = 100;
	g->floor->green = 100;
	g->floor->blue = 100;
	g->floor->hex = g->floor->red * 65536
		+ g->floor->green * 256 + g->floor->blue;
	g->ceiling->red = 200;
	g->ceiling->green = 200;
	g->ceiling->blue = 200;
	g->ceiling->hex = g->ceiling->red * 65536
		+ g->ceiling->green * 256 + g->ceiling->blue;
	g->wall->red = 255;
	g->wall->green = 0;
	g->wall->blue = 0;
	g->wall->hex = g->wall->red * 65536
		+ g->wall->green * 256 + g->wall->blue;
}


