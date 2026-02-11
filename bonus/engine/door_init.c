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

void	init_single_door(t_door *door, int x, int y, t_texture **door_frames)
{
	door->x = x;
	door->y = y;
	door->is_open = 0;
	door->animation = 0.0;
	door->frame_count = 1;
	door->frames[0] = door_frames[0];
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
	while (y < g->map->height)
	{
		x = 0;
		while (x < g->map->width)
		{
			if (g->map->grid[y][x] == 'D')
			{
				if (g->door_count >= MAX_DOORS)
					clean_up(g);
				init_single_door(&g->doors[g->door_count++], x, y, door_frames);
			}
			x++;
		}
		y++;
	}
}
