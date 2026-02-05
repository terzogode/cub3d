/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:17:09 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/01/30 23:49:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	release_rotation_keys(int keycode, t_game *g)
{
	if (keycode == 'e' || keycode == 65363)
		g->player->rotate_left = 0;
	if (keycode == 'q' || keycode == 65361)
		g->player->rotate_right = 0;
}

int	key_release(int keycode, t_game *g)
{
	release_movement_keys(keycode, g);
	release_rotation_keys(keycode, g);
	if (keycode == 'm')
		g->player->m_key_down = 0;
	return (0);
}

void	handle_toggle_keys(int keycode, t_game *g)
{
	if (keycode == 'i')
	{
		g->show_fps = !g->show_fps;
		fd_printf(1,"FPS toggle: ");
		if (g->show_fps)
			fd_printf(1, "ON");
		else
			fd_printf(1, "OFF");
	}
}

void	release_movement_keys(int keycode, t_game *g)
{
	if (keycode == 'w')
		g->player->move_forward = 0;
	if (keycode == 's')
		g->player->move_backward = 0;
	if (keycode == 'a')
		g->player->move_left = 0;
	if (keycode == 'd')
		g->player->move_right = 0;
}
