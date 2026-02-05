/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:06:37 by marvin            #+#    #+#             */
/*   Updated: 2026/02/02 21:06:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	initialize_mlx_fields(t_game *g)
{
	g->mlx_init = NULL;
	g->win = NULL;
	g->screen = NULL;
	g->width = 1920;
	g->height = 1080;
	g->perf.last_ms = 0.0;
	g->perf.fps = 0.0;
	g->perf.fps_raw = 0.0;
	g->perf.last_draw_ms = 0.0;
	g->show_fps = false;
}

bool	struct_init(t_game *g)
{
	g->map = initialize_map();
	g->player = initialize_player();
	g->floor = initialize_color();
	g->wall = initialize_color();
	g->ceiling = initialize_color();
	g->tex_north = initialize_texture();
	g->tex_south = initialize_texture();
	g->tex_west = initialize_texture();
	g->tex_east = initialize_texture();
	g->parse = initialize_parse();
	if (!g->map || !g->player || !g->floor || !g->wall || !g->ceiling
		|| !g->tex_north || !g->tex_south || !g->tex_west 
		|| !g->tex_east || !g->parse)
		return (1);
	initialize_mlx_fields(g);
	return (0);
}
