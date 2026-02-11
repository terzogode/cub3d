/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 14:42:39 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 21:42:08 by mbrighi          ###   ########.fr       */
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

void	init_color(t_game *g)
{
	g->floor->red = 100;
	g->floor->green = 100;
	g->floor->blue = 100;
	g->floor->hex = g->floor->red * 65536
		+ g->floor->green * 256 + g->floor->blue;
	g->ceiling->red = 200;
	g->ceiling->green = 200;
	g->ceiling->blue = 200;
	g->ceiling->hex = g->ceiling->red * 65536
		+ g->ceiling->green * 256 + g->ceiling->blue;
	g->wall->red = 255;
	g->wall->green = 0;
	g->wall->blue = 0;
	g->wall->hex = g->wall->red * 65536
		+ g->wall->green * 256 + g->wall->blue;
}

void	check_and_toggle_door(t_game *g)
{
	int	i;
	int	door_x;
	int	door_y;

	i = 0;
	if (!g || !g->doors || g->door_count == 0)
		return ;
	while (i < g->door_count)
	{
		door_x = g->doors[i].x;
		door_y = g->doors[i].y;
		if (fabs(POS_X - door_x) < 2.0 && fabs(POS_Y - door_y) < 2.0)
		{
			if (g->doors[i].is_open)
			{
				if ((int)POS_X == door_x && (int)POS_Y == door_y)
				{
					i++;
					continue ;
				}
			}
			g->doors[i].is_open = !g->doors[i].is_open;
		}
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
