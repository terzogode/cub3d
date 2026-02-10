/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arms.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 15:53:03 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/10 18:23:17 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_img_pixel(t_image *img, int x, int y)
{
	return (*(unsigned int *)(img->addr
			+ y * img->line_len + x * (img->bpp / 8)));
}

static void			set_screen_pixel(t_game *g, int x, int y, unsigned int px)
{
	*(unsigned int *)(g->screen->addr
			+ y * g->screen->line_len + x * (g->screen->bpp / 8)) = px;
}

static int			is_chroma_green(unsigned int px)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (px >> 16) & 0xFF;
	g = (px >> 8) & 0xFF;
	b = px & 0xFF;
	return (g >= 150 && r <= 120 && b <= 120);
}

static void			draw_arms_pixels(t_game *g, t_image *img)
{
	unsigned int	px;
	int				x;
	int				y;
	int				start_x;
	int				start_y;

	start_x = (g->width - img->width) / 2;
	start_y = g->height - img->height;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			px = get_img_pixel(img, x, y);
			if (is_chroma_green(px))
			{
				x++;
				continue ;
			}
			set_screen_pixel(g, start_x + x, start_y + y, px);
			x++;
		}
		y++;
	}
}

void	draw_arms_overlay(t_game *g)
{
	t_image			*img;

	if (!g)
		return ;
	init_arms(g);
	if (!g->arms.frames[0])
		return ;
	img = g->arms.frames[g->arms.frame_idx]->img;
	if (!img || !img->addr)
		return ;
	draw_arms_pixels(g, img);
}
