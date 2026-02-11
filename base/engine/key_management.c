/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 20:48:21 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 21:18:04 by mbrighi          ###   ########.fr       */
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
	return (0);
}
