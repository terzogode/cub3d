/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:35:00 by marvin           #+#    #+#             */
/*   Updated: 2026/02/04 01:35:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	get_minimap_color(t_game *g, int mx, int my)
{
	t_color	c;

	if (mx < 0 || my < 0 || mx >= g->map->width || my >= g->map->height)
	{
		c.hex = 0x000000;
		return (c);
	}
	if (g->map->grid[my][mx] == '1')
	{
		c.hex = 0x444444;
		return (c);
	}
	else if (g->map->grid[my][mx] == 'D')
	{
		c.hex = 0xFF8800;
		return (c);
	}
	else
	{
		c.hex = 0x222222;
		return (c);
	}
}

void	draw_minimap_square(t_game *g, int mx, int my)
{
	t_minimap	*m;
	int			x;
	int			y;
	t_color		c;

	m = &g->minimap;
	c = get_minimap_color(g,
			(int)g->player->pos_x - ((m->width / m->scale) / 2) + mx,
			(int)g->player->pos_y - ((m->height / m->scale) / 2) + my);
	y = 0;
	while (y < m->scale)
	{
		x = 0;
		while (x < m->scale)
		{
			if (m->padding + (mx * m->scale) + x < m->padding + m->width
				&& m->padding + (my * m->scale) + y < m->padding + m->height)
				put_pixel(g->screen,
					m->padding + (mx * m->scale) + x,
					m->padding + (my * m->scale) + y, c);
			x++;
		}
		y++;
	}
}

void	draw_player_pixel(t_game *g, int px, int py, int size)
{
	int		x;
	int		y;
	t_color	player_color;

	player_color.hex = 0xFF0000;
	y = -size;
	while (y <= size)
	{
		x = -size;
		while (x <= size)
		{
			if (px + x >= g->minimap.padding
				&& px + x < g->minimap.padding + g->minimap.width
				&& py + y >= g->minimap.padding
				&& py + y < g->minimap.padding + g->minimap.height)
				put_pixel(g->screen, px + x, py + y, player_color);
			x++;
		}
		y++;
	}
}
