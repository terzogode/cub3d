/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_implementation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:00 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/09 16:43:16 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_ray(t_ray *ray)
{
	if (SIDE_DIST_X < SIDE_DIST_Y)
	{
		SIDE_DIST_X += DELTA_DIST_X;
		MAP_X += STEP_X;
		ray->side = 0;
	}
	else
	{
		SIDE_DIST_Y += DELTA_DIST_Y;
		MAP_Y += STEP_Y;
		ray->side = 1;
	}
}

void	check_collision(t_ray *ray, t_game *g)
{
	int	i;

	if (MAP_X < 0 || MAP_X >= g->map->width
		|| MAP_Y < 0 || MAP_Y >= g->map->height)
		return ;
	if (MAP_MATRIX[MAP_Y][MAP_X] == '1'
		|| MAP_MATRIX[MAP_Y][MAP_X] == 'B')
	{
		ray->hit = 1;
	}
	else if (MAP_MATRIX[MAP_Y][MAP_X] == 'D')
	{
		i = 0;
		while (i < g->door_count)
		{
			if (g->doors[i].x == MAP_X && g->doors[i].y == MAP_Y)
			{
				if (!g->doors[i].is_open)
					ray->hit = 1;
				break ;
			}
			i++;
		}
	}
}

void	perform_dda(t_ray *ray, t_game *g)
{
	int	steps;

	ray->hit = 0;
	ray->out_of_bounds = 0;
	steps = 0;
	while (!ray->hit && steps < 100)
	{
		step_ray(ray);
		steps++;
		check_collision(ray, g);
	}
}

double	compute_wall_distance(t_ray *ray, t_game *g)
{
	if (ray->side == 0)
		return (fabs((MAP_X - POS_X + (1 - STEP_X) / 2) / RAY_DIR_X));
	else
		return (fabs((MAP_Y - POS_Y + (1 - STEP_Y) / 2) / RAY_DIR_Y));
}
