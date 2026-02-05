/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:07:54 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/03 01:16:59 by marvin           ###   ########.fr       */
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

t_texture	*select_tex_face(t_drawing *draw, t_game *g)
{
	if (draw->ray->side == 0)
	{
		if (draw->ray->rayDirX > 0)
			return (g->tex_east);
		return (g->tex_west);
	}
	if (draw->ray->rayDirY > 0)
		return (g->tex_south);
	return (g->tex_north);
}

void	draw_textured_column(t_game *g, int x, t_drawing *draw,
		t_texture *tex_face, double factor)
{
	int			y;
	int			tex_x;
	double		tex_pos;
	double		step;
	t_image		*img;

	img = tex_face->img;
	if (draw->line_height <= 0)
		return ;
	tex_x = get_tex_x(draw->ray, g, draw->ray->side, img, draw->wall_distance);
	step = (double)img->height / (double)draw->line_height;
	tex_pos = (draw->draw_start - g->height / 2 + draw->line_height / 2) * step;
	y = draw->draw_start;
	while (y <= draw->draw_end)
	{
		put_pixel(g->screen, x, y,
			shade_color(get_texture_pixel(img, tex_x, (int)tex_pos, g),
			factor));
		tex_pos += step;
		y++;
	}
}

void	draw_solid_column(t_game *g, int x, t_drawing *draw, double factor)
{
	int		y;
	t_color	pixel;

	y = draw->draw_start;
	while (y <= draw->draw_end)
	{
		pixel = shade_color(*g->wall, factor);
		put_pixel(g->screen, x, y, pixel);
		y++;
	}
}

void		draw_wall_part(t_game *g, int x, t_drawing *draw, double factor)
{
	t_texture	*tex_face;

	tex_face = select_tex_face(draw, g);
	if (tex_face && tex_face->img)
		draw_textured_column(g, x, draw, tex_face, factor);
	else
		draw_solid_column(g, x, draw, factor);
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
	distance = WALL_DISTANCE_ARRAY[x];
	factor = 1.0 / (1.0 + 0.05 * distance);
	if (draw->ray->side == 1)
		factor = factor * 0.7;
	draw_ceiling_part(g, x, draw->draw_start);
	draw_wall_part(g, x, draw, factor);
	draw_floor_part(g, x, draw->draw_end);
}
