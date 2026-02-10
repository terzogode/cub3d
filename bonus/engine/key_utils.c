/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:17:09 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/10 17:54:38 by mbrighi          ###   ########.fr       */
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
	if (keycode == 'f')
		g->arms.key_down = 0;
	return (0);
}

void	handle_toggle_keys(int keycode, t_game *g)
{
	if (keycode == 'i')
		g->show_fps = !g->show_fps;
	if (keycode == 'f')
	{
		if (g->arms.key_down)
			return ;
		g->arms.key_down = 1;
		trigger_arms_animation(g);
		check_and_toggle_door(g);
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
