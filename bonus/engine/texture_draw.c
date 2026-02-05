/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:10:00 by marvin           #+#    #+#             */
/*   Updated: 2026/02/04 01:10:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
