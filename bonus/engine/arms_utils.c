/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arms_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 18:06:50 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/10 18:10:29 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_arms(t_game *g)
{
	if (!g || g->arms.frame_count > 0)
		return ;
	g->arms.frames[0] = initialize_texture();
	g->arms.frames[1] = initialize_texture();
	g->arms.frames[2] = initialize_texture();
	g->arms.frames[3] = initialize_texture();
	load_single_texture(g, g->arms.frames[0], "./textures/arms_0.xpm");
	load_single_texture(g, g->arms.frames[1], "./textures/arms_1.xpm");
	load_single_texture(g, g->arms.frames[2], "./textures/arms_2.xpm");
	load_single_texture(g, g->arms.frames[3], "./textures/arms_3.xpm");
	g->arms.frame_count = 4;
	g->arms.frame_idx = 0;
	g->arms.anim_dir = 1;
	g->arms.anim_active = 0;
	g->arms.key_down = 0;
	g->arms.anim_time = 0.0;
}

void	trigger_arms_animation(t_game *g)
{
	if (!g)
		return ;
	init_arms(g);
	if (g->arms.anim_active)
		return ;
	g->arms.anim_active = 1;
	g->arms.anim_dir = 1;
	g->arms.frame_idx = 0;
	g->arms.anim_time = 0.0;
}

void	update_arms_animation(t_game *g, double dt)
{
	if (!g)
		return ;
	init_arms(g);
	if (!g->arms.anim_active)
		return ;
	g->arms.anim_time += dt;
	while (g->arms.anim_time >= ARMS_FRAME_TIME)
	{
		g->arms.anim_time -= ARMS_FRAME_TIME;
		g->arms.frame_idx += g->arms.anim_dir;
		if (g->arms.frame_idx >= g->arms.frame_count - 1)
			g->arms.anim_dir = -1;
		if (g->arms.frame_idx <= 0)
		{
			g->arms.frame_idx = 0;
			g->arms.anim_dir = 1;
			g->arms.anim_active = 0;
		}
	}
}

void	free_arms_frames(t_game *g, t_texture **frames)
{
	int	i;

	if (!frames)
		return ;
	i = 0;
	while (i < 4)
	{
		if (frames[i])
		{
			if (frames[i]->img && frames[i]->img->img && g->mlx_init)
				mlx_destroy_image(g->mlx_init, frames[i]->img->img);
			if (frames[i]->img)
				free(frames[i]->img);
			free(frames[i]);
		}
		i++;
	}
}
