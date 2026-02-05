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

#define MINIMAP_WIDTH 150
#define MINIMAP_HEIGHT 150
#define MINIMAP_PADDING 10
#define MINIMAP_SCALE 10

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

void	draw_minimap_square(t_game *g, int px, int py, int mx, int my)
{
	int		x;
	int		y;
	t_color	c;

	c = get_minimap_color(g, mx, my);
	y = 0;
	while (y < MINIMAP_SCALE)
	{
		x = 0;
		while (x < MINIMAP_SCALE)
		{
			if (px + x < MINIMAP_PADDING + MINIMAP_WIDTH
				&& py + y < MINIMAP_PADDING + MINIMAP_HEIGHT)
				put_pixel(g->screen, px + x, py + y, c);
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
			if (px + x >= MINIMAP_PADDING && px + x < MINIMAP_PADDING + MINIMAP_WIDTH
				&& py + y >= MINIMAP_PADDING && py + y < MINIMAP_PADDING + MINIMAP_HEIGHT)
				put_pixel(g->screen, px + x, py + y, player_color);
			x++;
		}
		y++;
	}
}
