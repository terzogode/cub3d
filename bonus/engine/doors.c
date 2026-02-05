/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 00:00:00 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/04 00:00:00 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_door_open(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	if (!g || !g->doors || g->door_count == 0)
		return (false);
	while (i < g->door_count)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (g->doors[i].is_open);
		i++;
	}
	return (false);
}

float	get_door_animation(t_game *g, int x, int y)
{
	int	i;

	i = 0;
	while (i < g->door_count)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
			return (g->doors[i].animation);
		i++;
	}
	return (0.0f);
}

void	update_door_animations(t_game *g, double delta_time)
{
	int		i;
	float	speed;

	if (!g || !g->doors || g->door_count == 0)
		return ;
	speed = 2.0f;
	i = 0;
	while (i < g->door_count)
	{
		if (g->doors[i].is_open && g->doors[i].animation < 1.0f)
		{
			g->doors[i].animation += speed * (float)delta_time;
			if (g->doors[i].animation > 1.0f)
				g->doors[i].animation = 1.0f;
		}
		else if (!g->doors[i].is_open && g->doors[i].animation > 0.0f)
		{
			g->doors[i].animation -= speed * (float)delta_time;
			if (g->doors[i].animation < 0.0f)
				g->doors[i].animation = 0.0f;
		}
		i++;
	}
}

t_texture	*get_door_frame_texture(t_game *g, int x, int y)
{
	int		i;
	int		frame_idx;
	float	animation;
	t_texture	*result;

	i = 0;
	while (i < g->door_count)
	{
		if (g->doors[i].x == x && g->doors[i].y == y)
		{
			animation = g->doors[i].animation;
			frame_idx = (int)(animation * g->doors[i].frame_count);
			if (frame_idx >= g->doors[i].frame_count)
				frame_idx = g->doors[i].frame_count - 1;
			result = g->doors[i].frames[frame_idx];
			return (result);
		}
		i++;
	}
	return (NULL);
}
