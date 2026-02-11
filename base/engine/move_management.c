/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 20:02:27 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/11 21:20:10 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	try_move_x(t_game *g, double step)
{
	if (step == 0.0)
		return ;
	POS_X += step;
}

static void	try_move_y(t_game *g, double step)
{
	if (step == 0.0)
		return ;
	POS_Y += step;
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
