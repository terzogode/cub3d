/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:53:49 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 21:25:57 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	shade_color(t_color col, double factor)
{
	col.red = (int)(col.red * factor);
	if (col.red > 255)
		col.red = 255;
	col.green = (int)(col.green * factor);
	if (col.green > 255)
		col.green = 255;
	col.blue = (int)(col.blue * factor);
	if (col.blue > 255)
		col.blue = 255;
	col.hex = col.red * 65536 + col.green * 256 + col.blue;
	return (col);
}

int	get_tex_x(t_ray *ray, t_game *g, t_image *texture,
		double wall_distance)
{
	double	wall_x;
	int		tex_x;

	if (!texture || !texture->img || texture->width == 0)
		return (0);
	if (ray->side == 0)
		wall_x = POS_Y + wall_distance * RAY_DIR_Y;
	else
		wall_x = POS_X + wall_distance * RAY_DIR_X;
	wall_x = wall_x - (int)wall_x;
	if (wall_x < 0.0)
		wall_x += 1.0;
	tex_x = (int)(wall_x * texture->width);
	if (ray->side == 0 && RAY_DIR_X > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && RAY_DIR_Y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

int	get_tex_y(int y, t_drawing *draw, t_image *tex)
{
	double	step;
	int		texture_y;

	step = (double)tex->height / (draw->draw_end - draw->draw_start + 1);
	texture_y = (int)((y - draw->draw_start) * step);
	return (texture_y);
}

t_color	get_texture_pixel(t_image *tex, int tex_x, int tex_y, t_game *g)
{
	char	*src;
	t_color	color;
	int		pixel_value;

	if (!tex || !tex->addr || tex->width == 0 || tex->height == 0)
		return (*g->wall);
	if (tex_x < 0 || tex_x >= tex->width)
		tex_x = 0;
	if (tex_y < 0 || tex_y >= tex->height)
		tex_y = 0;
	src = tex->addr + (tex_y * tex->line_len) + (tex_x * (tex->bpp / 8));
	pixel_value = *(unsigned int *)src;
	color.hex = pixel_value;
	color.red = (pixel_value / 65536) % 256;
	color.green = (pixel_value / 256) % 256;
	color.blue = pixel_value % 256;
	return (color);
}
