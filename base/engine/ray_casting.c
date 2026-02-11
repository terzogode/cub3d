/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:28 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 23:04:26 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_wall_drawing(t_drawing *draw, t_ray *ray, t_game *g)
{
	if (!ray->hit)
	{
		draw->wall_distance = 1000.0;
		draw->line_height = 0;
		draw->wall_top = g->height / 2;
		draw->draw_start = g->height / 2;
		draw->draw_end = g->height / 2 - 1;
	}
	else
	{
		draw->wall_distance = compute_wall_distance(ray, g);
		if (draw->wall_distance <= 0.0)
			draw->wall_distance = 0.01;
		draw->line_height = g->height / draw->wall_distance;
		draw->wall_top = -draw->line_height / 2 + g->height / 2;
		draw->draw_start = draw->wall_top;
		if (draw->draw_start < 0)
			draw->draw_start = 0;
		draw->draw_end = draw->line_height / 2 + g->height / 2;
		if (draw->draw_end >= g->height)
			draw->draw_end = g->height - 1;
	}
}

void	cast_one_ray(t_game *g, int x)
{
	t_ray		ray;

	init_ray_direction(&ray, g, x);
	init_ray_map(&ray, g);
	init_delta_distance(&ray);
	init_step_side_distance(&ray, g);
	perform_dda(&ray, g);
	compute_wall_drawing(g->drawing, &ray, g);
	g->player->columns_distance[x] = g->drawing->wall_distance;
	g->drawing->ray = &ray;
	draw_columns(g, x, g->drawing);
}
