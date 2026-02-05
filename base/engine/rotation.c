/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mattebrighi <mattebrighi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:41:21 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/01/28 22:59:42 by mattebrighi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_rotation(t_game *g)
{
	if (g->player->rotate_left)
		apply_rotation(g, ROT_SPEED);
	if (g->player->rotate_right)
		apply_rotation(g, -ROT_SPEED);
}

void	apply_rotation(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = DIR_X;
	DIR_X = DIR_X * cos(angle) - DIR_Y * sin(angle);
	DIR_Y = old_dir_x * sin(angle) + DIR_Y * cos(angle);
	old_plane_x = PLANE_X;
	PLANE_X = PLANE_X * cos(angle) - PLANE_Y * sin(angle);
	PLANE_Y = old_plane_x * sin(angle) + PLANE_Y * cos(angle);
}


