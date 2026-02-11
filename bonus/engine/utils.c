/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:42:39 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 23:32:18 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_image *img, int x, int y, t_color color)
{
	char	*dst;

	if (!img || x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	if (img->bpp == 32)
		*(unsigned int *)dst = (unsigned int)color.hex;
	else
		*(unsigned long *)dst = (unsigned long)color.hex;
}

static void	try_toggle_door(t_game *g, int i)
{
	int	door_x;
	int	door_y;

	door_x = g->doors[i].x;
	door_y = g->doors[i].y;
	if (fabs(g->player->pos_x - door_x) < 2.0
		&& fabs(g->player->pos_y - door_y) < 2.0)
	{
		if (g->doors[i].is_open)
		{
			if ((int)g->player->pos_x == door_x
				&& (int)g->player->pos_y == door_y)
				return ;
		}
		g->doors[i].is_open = !g->doors[i].is_open;
	}
}

void	check_and_toggle_door(t_game *g)
{
	int	i;

	i = 0;
	if (!g || !g->doors || g->door_count == 0)
		return ;
	while (i < g->door_count)
	{
		try_toggle_door(g, i);
		i++;
	}
}

t_texture	**allocate_door_frames(void)
{
	t_texture	**frames;
	int			i;

	frames = malloc(sizeof(t_texture *) * 1);
	if (!frames)
		return (NULL);
	i = 0;
	while (i < 1)
	{
		frames[i] = malloc(sizeof(t_texture));
		if (!frames[i])
		{
			while (--i >= 0)
				free(frames[i]);
			free(frames);
			return (NULL);
		}
		frames[i]->img = NULL;
		i++;
	}
	return (frames);
}

void	update_player_position(t_game *g)
{
	if (g->player->move_forward)
		move_forward(g);
	if (g->player->move_backward)
		move_backward(g);
	if (g->player->move_left)
		lateral_move(g, -1);
	if (g->player->move_right)
		lateral_move(g, 1);
}
