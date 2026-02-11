/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:07:54 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/11 22:54:29 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceiling_part(t_game *g, int x, int draw_start)
{
	int		y;
	double	factor;

	y = 0;
	while (y < draw_start)
	{
		factor = 1.0 - ((g->height / 2.0 - y) / (g->height / 2.0)) * 0.6;
		if (factor < 0.3)
			factor = 0.3;
		put_pixel(g->screen, x, y++, shade_color(*g->ceiling, factor));
	}
}

void	draw_wall_part(t_game *g, int x, t_drawing *draw, double factor)
{
	int			y;
	int			tex_x;
	int			tex_y;
	t_texture	*tex_face;

	tex_face = select_tex_face(draw, g);
	if (!tex_face || !tex_face->img || draw->line_height <= 0)
		return ;
	tex_x = get_tex_x(draw->ray, g, tex_face->img, draw->wall_distance);
	y = draw->draw_start;
	while (y <= draw->draw_end)
	{
		tex_y = get_tex_y(y, draw, tex_face->img);
		put_pixel(g->screen, x, y,
			shade_color(get_texture_pixel(tex_face->img, tex_x, tex_y, g),
				factor));
		y++;
	}
}

void	draw_floor_part(t_game *g, int x, int draw_end)
{
	int		y;
	double	factor;

	y = draw_end + 1;
	while (y < g->height)
	{
		factor = 1.0 - ((y - g->height / 2.0) / (g->height / 2.0)) * 0.6;
		if (factor < 0.3)
			factor = 0.3;
		put_pixel(g->screen, x, y++, shade_color(*g->floor, factor));
	}
}

void	draw_columns(t_game *g, int x, t_drawing *draw)
{
	double	factor;
	double	distance;

	if (!draw || !draw->ray)
		return ;
	distance = g->player->columns_distance[x];
	factor = 1.0 / (1.0 + 0.05 * distance);
	if (draw->ray->side == 1)
		factor = factor * 0.7;
	draw_ceiling_part(g, x, draw->draw_start);
	draw_wall_part(g, x, draw, factor);
	draw_floor_part(g, x, draw->draw_end);
}
