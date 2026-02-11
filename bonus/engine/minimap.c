/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by marvin           #+#    #+#             */
/*   Updated: 2026/02/04 01:35:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_grid(t_game *g)
{
	t_minimap	*m;
	int			mx;
	int			my;

	m = &g->minimap;
	my = 0;
	while (my < (m->height / m->scale))
	{
		mx = 0;
		while (mx < (m->width / m->scale))
		{
			draw_minimap_square(g, mx, my);
			mx++;
		}
		my++;
	}
}

void	draw_player_indicator(t_game *g)
{
	int		px;
	int		py;
	int		size;

	px = g->minimap.padding + (g->minimap.width / 2);
	py = g->minimap.padding + (g->minimap.height / 2);
	size = 3;
	draw_player_pixel(g, px, py, size);
}

void	draw_minimap_border(t_game *g)
{
	int		x;
	int		y;
	t_color	border;

	border.hex = 0xFFFFFF;
	y = g->minimap.padding;
	while (y <= g->minimap.padding + g->minimap.height)
	{
		put_pixel(g->screen, g->minimap.padding, y, border);
		put_pixel(g->screen, g->minimap.padding + g->minimap.width,
			y, border);
		y++;
	}
	x = g->minimap.padding;
	while (x <= g->minimap.padding + g->minimap.width)
	{
		put_pixel(g->screen, x, g->minimap.padding, border);
		put_pixel(g->screen, x,
			g->minimap.padding + g->minimap.height, border);
		x++;
	}
}

void	draw_minimap(t_game *g)
{
	draw_minimap_grid(g);
	draw_minimap_border(g);
	draw_player_indicator(g);
}
