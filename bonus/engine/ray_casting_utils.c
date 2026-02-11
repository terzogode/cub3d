/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 21:32:17 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 23:23:27 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_direction(t_ray *ray, t_game *g, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)g->width - 1.0;
	ray->ray_dir_x = g->player->dir_x + g->player->plane_x * camera_x;
	ray->ray_dir_y = g->player->dir_y + g->player->plane_y * camera_x;
}

void	init_ray_map(t_ray *ray, t_game *g)
{
	ray->map_x = (int)g->player->pos_x;
	ray->map_y = (int)g->player->pos_y;
}

void	init_delta_distance(t_ray *ray)
{
	if (fabs(ray->ray_dir_x) < 1e-12)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (fabs(ray->ray_dir_y) < 1e-12)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_step_side_distance(t_ray *ray, t_game *g)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->player->pos_y)
			* ray->delta_dist_y;
	}
}
