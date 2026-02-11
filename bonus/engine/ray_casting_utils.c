/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:32:17 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 21:32:32 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_direction(t_ray *ray, t_game *g, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)g->width - 1.0;
	RAY_DIR_X = DIR_X + PLANE_X * camera_x;
	RAY_DIR_Y = DIR_Y + PLANE_Y * camera_x;
}

void	init_ray_map(t_ray *ray, t_game *g)
{
	MAP_X = (int)POS_X;
	MAP_Y = (int)POS_Y;
}

void	init_delta_distance(t_ray *ray)
{
	if (fabs(RAY_DIR_X) < 1e-12)
		DELTA_DIST_X = 1e30;
	else
		DELTA_DIST_X = fabs(1 / RAY_DIR_X);
	if (fabs(RAY_DIR_Y) < 1e-12)
		DELTA_DIST_Y = 1e30;
	else
		DELTA_DIST_Y = fabs(1 / RAY_DIR_Y);
}

void	init_step_side_distance(t_ray *ray, t_game *g)
{
	if (RAY_DIR_X < 0)
	{
		STEP_X = -1;
		SIDE_DIST_X = (POS_X - MAP_X) * DELTA_DIST_X;
	}
	else
	{
		STEP_X = 1;
		SIDE_DIST_X = (MAP_X + 1.0 - POS_X) * DELTA_DIST_X;
	}
	if (RAY_DIR_Y < 0)
	{
		STEP_Y = -1;
		SIDE_DIST_Y = (POS_Y - MAP_Y) * DELTA_DIST_Y;
	}
	else
	{
		STEP_Y = 1;
		SIDE_DIST_Y = (MAP_Y + 1.0 - POS_Y) * DELTA_DIST_Y;
	}
}
