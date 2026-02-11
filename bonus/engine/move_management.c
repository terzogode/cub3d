/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:02:27 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/11 21:42:04 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	try_move_x(t_game *g, double step)
{
	double	off;
	double	tx;
	int		ix;
	int		iy;
	char	tile;

	tile = '1';
	if (step == 0.0)
		return ;
	off = PLAYER_RADIUS;
	if (step < 0.0)
		off = -PLAYER_RADIUS;
	tx = POS_X + step;
	ix = (int)(tx + off);
	iy = (int)POS_Y;
	if (ix >= 0 && ix < WIDTH && iy >= 0 && iy < HEIGHT)
		tile = MAP_MATRIX[iy][ix];
	if (tile == '0' || (tile == 'D' && is_door_open(g, ix, iy)))
		POS_X = tx;
}

static void	try_move_y(t_game *g, double step)
{
	double	off;
	double	ty;
	int		ix;
	int		iy;
	char	tile;

	tile = '1';
	if (step == 0.0)
		return ;
	off = PLAYER_RADIUS;
	if (step < 0.0)
		off = -PLAYER_RADIUS;
	ty = POS_Y + step;
	ix = (int)POS_X;
	iy = (int)(ty + off);
	if (ix >= 0 && ix < WIDTH && iy >= 0 && iy < HEIGHT)
		tile = MAP_MATRIX[iy][ix];
	if (tile == '0' || (tile == 'D' && is_door_open(g, ix, iy)))
		POS_Y = ty;
}

void	move_forward(t_game *g)
{
	try_move_x(g, DIR_X * MOVE_SPEED);
	try_move_y(g, DIR_Y * MOVE_SPEED);
}

void	move_backward(t_game *g)
{
	try_move_x(g, -DIR_X * MOVE_SPEED);
	try_move_y(g, -DIR_Y * MOVE_SPEED);
}

void	lateral_move(t_game *g, int direction)
{
	double	d;

	d = (double)direction;
	try_move_x(g, PLANE_X * MOVE_SPEED * d);
	try_move_y(g, PLANE_Y * MOVE_SPEED * d);
}
