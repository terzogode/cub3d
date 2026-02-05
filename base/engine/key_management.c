/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:48:21 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/03 01:17:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_movement_keys(int keycode, t_game *g)
{
	if (keycode == 'w')
		g->player->move_forward = 1;
	if (keycode == 's')
		g->player->move_backward = 1;
	if (keycode == 'a')
		g->player->move_left = 1;
	if (keycode == 'd')
		g->player->move_right = 1;
}

void	handle_rotation_keys(int keycode, t_game *g)
{
	if (keycode == 'e' || keycode == 65363)
		g->player->rotate_left = 1;
	if (keycode == 'q' || keycode == 65361)
		g->player->rotate_right = 1;
}

int	key_press(int keycode, t_game *g)
{
	if (keycode == 65307)
		clean_up(g);
	handle_movement_keys(keycode, g);
	handle_rotation_keys(keycode, g);
	handle_toggle_keys(keycode, g);
	if (keycode == 'm')
	{
		if (g->player->m_key_down)
			return (0);
		g->player->m_key_down = 1;
		g->player->mouse_enabled = !g->player->mouse_enabled;
		g->player->last_mouse_x = g->width / 2;
		if (g->player->mouse_enabled)
			mlx_mouse_hide(g->mlx_init, g->win);
		else
			mlx_mouse_show(g->mlx_init, g->win);
	}
	return (0);
}
