/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:17 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/04 00:44:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	loop_hook(t_game *g)
{
	double	delta_time;

	perf_update(&g->perf);
	delta_time = (g->perf.last_ms - g->perf.last_draw_ms) / 1000.0;
	update_door_animations(g, delta_time);
	rendering(g);
	mlx_put_image_to_window(g->mlx_init, g->win, g->screen->img, 0, 0);
	if (g->show_fps)
		draw_fps_overlay(g);
	return (0);
}

void	rendering(t_game *g)
{
	int		i;

	i = 0;
	ft_memset(g->screen->addr, 0, g->screen->line_len * g->height);
	update_player_position(g);
	update_player_rotation(g);
	while (i < g->width)
	{
		cast_one_ray(g, i);
		i++;
	}
	draw_minimap(g);
}


