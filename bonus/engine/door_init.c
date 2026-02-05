/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:30:00 by marvin           #+#    #+#             */
/*   Updated: 2026/02/04 01:30:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	detect_door_orientation(t_game *g, int x, int y)
{
	int	has_north_wall;
	int	has_south_wall;
	int	has_east_wall;
	int	has_west_wall;

	has_north_wall = (y > 0 && MAP_MATRIX[y - 1][x] == '1');
	has_south_wall = (y < HEIGHT - 1 && MAP_MATRIX[y + 1][x] == '1');
	has_east_wall = (x < WIDTH - 1 && MAP_MATRIX[y][x + 1] == '1');
	has_west_wall = (x > 0 && MAP_MATRIX[y][x - 1] == '1');
	if ((has_north_wall || has_south_wall) && !has_east_wall && !has_west_wall)
		return ('H');
	else if ((has_east_wall || has_west_wall) && !has_north_wall && !has_south_wall)
		return ('V');
	else if ((has_north_wall || has_south_wall) && (has_east_wall || has_west_wall))
		return ('H');
	return ('V');
}

void	init_single_door(t_door *door, int x, int y, t_texture **door_frames, t_game *g)
{
	door->x = x;
	door->y = y;
	door->orientation = detect_door_orientation(g, x, y);
	door->is_open = 0;
	door->animation = 0.0;
	door->frame_count = 4;
	door->frames[0] = door_frames[0];
	door->frames[1] = door_frames[1];
	door->frames[2] = door_frames[2];
	door->frames[3] = door_frames[3];
}

void	init_doors(t_game *g, t_texture **door_frames)
{
	int	x;
	int	y;

	g->door_count = 0;
	g->doors = malloc(sizeof(t_door) * MAX_DOORS);
	if (!g->doors)
		clean_up(g);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (MAP_MATRIX[y][x] == 'D')
			{
				if (g->door_count >= MAX_DOORS)
					clean_up(g);
				init_single_door(&g->doors[g->door_count++], x, y, door_frames, g);
			}
		x++;
		}
		y++;
	}
}
