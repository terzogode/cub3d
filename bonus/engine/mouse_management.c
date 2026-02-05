/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:39:07 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/01/30 23:49:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mouse_move(int x, int y, t_game *g)
{
	int	delta_x;
	int	center_x;
	int	center_y;

	if (g->player->ignore_next_mouse)
	{
		g->player->ignore_next_mouse = 0;
		return (0);
	}
	(void)y;
	if (!g->player->mouse_enabled)
		return (0);
	center_x = g->width / 2;
	center_y = g->height / 2;
	delta_x = x - center_x;
	if (delta_x != 0)
		apply_rotation(g, delta_x * MOUSE_SENSITIVITY);
	mlx_mouse_move(g->mlx_init, g->win, center_x, center_y);
	g->player->ignore_next_mouse = 1;
	return (0);
}



