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

static void	draw_textured_column(t_game *g, int x, t_texture *tex_face,
		double factor)
{
	int			y;
	int			tx_x;
	double		tex_pos;
	double		step;
	t_image		*img;

	img = tex_face->img;
	tx_x = get_tex_x(g->drawing->ray, g, img, g->drawing->wall_distance);
	step = (double)img->height / (double)g->drawing->line_height;
	tex_pos = (g->drawing->draw_start - g->height / 2
			+ g->drawing->line_height / 2) * step;
	y = g->drawing->draw_start;
	while (y <= g->drawing->draw_end)
	{
		put_pixel(g->screen, x, y,
			shade_color(get_texture_pixel(img, tx_x, (int)tex_pos, g),
				factor));
		tex_pos += step;
		y++;
	}
}

void	draw_wall_part(t_game *g, int x, t_drawing *draw, double factor)
{
	t_texture	*tex_face;

	tex_face = select_tex_face(draw, g);
	if (!tex_face || !tex_face->img || draw->line_height <= 0)
		return ;
	draw_textured_column(g, x, tex_face, factor);
}

int	allocate_and_load_xpm(t_game *g, t_texture *tex, const char *path)
{
	tex->img = malloc(sizeof(t_image));
	if (!tex->img)
		return (0);
	tex->img->img = mlx_xpm_file_to_image(g->mlx_init, (char *)path,
			&tex->img->width, &tex->img->height);
	if (!tex->img->img)
	{
		fd_printf(2, "Error: Could not load texture: ");
		fd_printf(2, (char *)path);
		fd_printf(2, "\n");
		free(tex->img);
		tex->img = NULL;
		return (0);
	}
	return (1);
}
