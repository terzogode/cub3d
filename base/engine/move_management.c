/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:02:27 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/11 22:54:03 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	try_move_x(t_game *g, double step)
{
	if (step == 0.0)
		return ;
	g->player->pos_x += step;
}

static void	try_move_y(t_game *g, double step)
{
	if (step == 0.0)
		return ;
	g->player->pos_y += step;
}

void	move_forward(t_game *g)
{
	try_move_x(g, g->player->dir_x * MOVE_SPEED);
	try_move_y(g, g->player->dir_y * MOVE_SPEED);
}

void	move_backward(t_game *g)
{
	try_move_x(g, -g->player->dir_x * MOVE_SPEED);
	try_move_y(g, -g->player->dir_y * MOVE_SPEED);
}

void	lateral_move(t_game *g, int direction)
{
	double	d;

	d = (double)direction;
	try_move_x(g, g->player->plane_x * MOVE_SPEED * d);
	try_move_y(g, g->player->plane_y * MOVE_SPEED * d);
}
