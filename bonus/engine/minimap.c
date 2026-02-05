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

#define MINIMAP_WIDTH 150
#define MINIMAP_HEIGHT 150
#define MINIMAP_PADDING 10
#define MINIMAP_SCALE 10

void	draw_minimap_grid(t_game *g)
{
	int	mx;
	int	my;
	int	px;
	int	py;
	int	center_x;
	int	center_y;

	center_x = (int)g->player->pos_x - (MINIMAP_WIDTH / MINIMAP_SCALE / 2);
	center_y = (int)g->player->pos_y - (MINIMAP_HEIGHT / MINIMAP_SCALE / 2);
	my = 0;
	while (my < MINIMAP_HEIGHT / MINIMAP_SCALE)
	{
		mx = 0;
		while (mx < MINIMAP_WIDTH / MINIMAP_SCALE)
		{
			px = MINIMAP_PADDING + (mx * MINIMAP_SCALE);
			py = MINIMAP_PADDING + (my * MINIMAP_SCALE);
			draw_minimap_square(g, px, py, center_x + mx, center_y + my);
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

	px = MINIMAP_PADDING + (MINIMAP_WIDTH / 2);
	py = MINIMAP_PADDING + (MINIMAP_HEIGHT / 2);
	size = 3;
	draw_player_pixel(g, px, py, size);
}

void	draw_minimap_border(t_game *g)
{
	int		x;
	int		y;
	t_color	border;

	border.hex = 0xFFFFFF;
	y = MINIMAP_PADDING;
	while (y <= MINIMAP_PADDING + MINIMAP_HEIGHT)
	{
		put_pixel(g->screen, MINIMAP_PADDING, y, border);
		put_pixel(g->screen, MINIMAP_PADDING + MINIMAP_WIDTH, y, border);
		y++;
	}
	x = MINIMAP_PADDING;
	while (x <= MINIMAP_PADDING + MINIMAP_WIDTH)
	{
		put_pixel(g->screen, x, MINIMAP_PADDING, border);
		put_pixel(g->screen, x, MINIMAP_PADDING + MINIMAP_HEIGHT, border);
		x++;
	}
}

void	draw_minimap(t_game *g)
{
	draw_minimap_grid(g);
	draw_minimap_border(g);
	draw_player_indicator(g);
}
