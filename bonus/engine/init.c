/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:06:37 by marvin            #+#    #+#             */
/*   Updated: 2026/02/02 21:06:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_minimap(t_game *g)
{
	g->minimap.width = 150;
	g->minimap.height = 150;
	g->minimap.padding = 10;
	g->minimap.scale = 10;
}

void	init_game(t_game *g)
{
	int	i;

	i = 0;
	init_color(g);
	g->player->columns_distance = malloc(sizeof(double) * g->width);
	if (!g->player->columns_distance)
	{
		fd_printf(2, "Error: Failed to allocate columns_distance\n");
		clean_up(g);
	}
	while (i < g->width)
	{
		g->player->columns_distance[i] = 0;
		i++;
	}
	init_minimap(g);
	g->drawing = ft_calloc(1, sizeof(t_drawing));
	if (!g->drawing)
	{
		fd_printf(2, "Error: Failed to allocate drawing\n");
		clean_up(g);
	}
}

void	init_mlx(t_game *g)
{
	g->mlx_init = mlx_init();
	if (!g->mlx_init)
	{
		fd_printf(2, "Error: MLX initialization failed\n");
		cleanup_game_fields(g);
		exit(1);
	}
	g->win = mlx_new_window(g->mlx_init, g->width, g->height, "cub3D");
	mlx_mouse_hide(g->mlx_init, g->win);
	g->screen = malloc(sizeof(t_image));
	if (!g->screen)
		clean_up(g);
	g->screen->img = mlx_new_image(g->mlx_init, g->width, g->height);
	if (!g->screen->img)
	{
		free(g->screen);
		clean_up(g);
	}
	g->screen->width = g->width;
	g->screen->height = g->height;
	g->screen->addr = mlx_get_data_addr(g->screen->img,
			&g->screen->bpp, &g->screen->line_len, &g->screen->endian);
	if (!g->screen->addr)
		clean_up(g);
	g->pix = (t_color *)g->screen->addr;
}
