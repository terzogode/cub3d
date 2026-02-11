/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_implementation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:00 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 23:00:51 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	step_ray(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

void	check_collision(t_ray *ray, t_game *g)
{
	if (ray->map_x < 0 || ray->map_x >= g->map->width
		|| ray->map_y < 0 || ray->map_y >= g->map->height)
		return ;
	if (g->map->grid[ray->map_y][ray->map_x] == '1')
		ray->hit = 1;
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
		return (fabs((ray->map_x - g->player->pos_x
					+ (1 - ray->step_x) / 2) / ray->ray_dir_x));
	else
		return (fabs((ray->map_y - g->player->pos_y
					+ (1 - ray->step_y) / 2) / ray->ray_dir_y));
}
