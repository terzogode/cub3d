/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_select.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:10:00 by marvin           #+#    #+#             */
/*   Updated: 2026/02/04 01:10:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	get_side_type(int side)
{
	if (side == 0)
		return ('V');
	return ('H');
}

static t_texture	*get_match_door(t_game *g, int x, int y, char side_type)
{
	int	i;

	i = 0;
	(void)side_type;
	while (i < g->door_count)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (get_door_frame_texture(g, x, y));
		i++;
	}
	return (NULL);
}

static t_texture	*select_door_texture(t_drawing *draw, t_game *g)
{
	int		door_x;
	int		door_y;

	door_x = draw->ray->mapX;
	door_y = draw->ray->mapY;
	if (door_x < 0 || door_x >= WIDTH || door_y < 0 || door_y >= HEIGHT)
		return (NULL);
	if (MAP_MATRIX[door_y][door_x] != 'D')
		return (NULL);
	return (get_match_door(g, door_x, door_y, get_side_type(draw->ray->side)));
}

t_texture	*select_tex_face(t_drawing *draw, t_game *g)
{
	t_texture	*door_tex;
	int			x;
	int			y;

	door_tex = select_door_texture(draw, g);
	if (door_tex)
		return (door_tex);
	x = draw->ray->mapX;
	y = draw->ray->mapY;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		if (MAP_MATRIX[y][x] == 'B')
			return (g->tex_box);
	}
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
