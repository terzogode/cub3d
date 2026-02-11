/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:41:21 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/11 22:57:37 by mbrighi          ###   ########.fr       */
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

	old_dir_x = g->player->dir_x;
	g->player->dir_x = g->player->dir_x * cos(angle)
		- g->player->dir_y * sin(angle);
	g->player->dir_y = old_dir_x * sin(angle) + g->player->dir_y * cos(angle);
	old_plane_x = g->player->plane_x;
	g->player->plane_x = g->player->plane_x * cos(angle)
		- g->player->plane_y * sin(angle);
	g->player->plane_y = old_plane_x * sin(angle)
		+ g->player->plane_y * cos(angle);
}
