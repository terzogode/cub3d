/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:49:50 by mattebrighi       #+#    #+#             */
/*   Updated: 2026/02/05 16:09:17 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	allocate_and_load_xpm(t_game *g, t_texture *tex, const char *path)
{
	tex->img = malloc(sizeof(t_image));
	if (!tex->img)
		return (0);
	tex->img->img = mlx_xpm_file_to_image(g->mlx_init, (char *)path,
			&tex->img->width, &tex->img->height);
	if (!tex->img->img)
	{
		fd_printf(2, "Error: Could not load texture: ");
		fd_printf(2, (char *)path);
		fd_printf(2, "\n");
		free(tex->img);
		tex->img = NULL;
		return (0);
	}
	return (1);
}

int	setup_texture_address(t_game *g, t_texture *tex)
{
	tex->img->addr = mlx_get_data_addr(tex->img->img,
			&tex->img->bpp, &tex->img->line_len, &tex->img->endian);
	if (!tex->img->addr)
	{
		fd_printf(2, "Error: Could not get texture data address\n", 2);
		mlx_destroy_image(g->mlx_init, tex->img->img);
		free(tex->img);
		tex->img = NULL;
		return (0);
	}
	return (1);
}

int	load_single_texture(t_game *g, t_texture *tex, const char *path)
{
	if (!allocate_and_load_xpm(g, tex, path))
		return (0);
	if (!setup_texture_address(g, tex))
		return (0);
	return (1);
}

static bool	init_walls(t_game *g)
{
	if (!load_single_texture(g, g->tex_north, g->tex_north->path))
		return (0);
	if (!load_single_texture(g, g->tex_south, g->tex_south->path))
		return (0);
	if (!load_single_texture(g, g->tex_west, g->tex_west->path))
		return (0);
	if (!load_single_texture(g, g->tex_east, g->tex_east->path))
		return (0);
	return (1);
}

static bool	init_doors_text(t_game *g, t_texture **frames)
{
	if (!load_single_texture(g, frames[0], "../textures/door_closed.xpm"))
		return (0);
	if (!load_single_texture(g, frames[1], "../textures/door_opening1.xpm"))
		return (0);
	if (!load_single_texture(g, frames[2], "../textures/door_opening2.xpm"))
		return (0);
	if (!load_single_texture(g, frames[3], "../textures/door_open.xpm"))
		return (0);
	return (1);
}

void	init_textures(t_game *g)
{
	t_texture	**door_frames;

	if (!init_walls(g))
	{
		cleanup_game_fields(g);
		exit(1);
	}
	door_frames = allocate_door_frames();
	if (!door_frames)
	{
		fd_printf(2, "Warning: Could not allocate door frames\n");
		return ;
	}
	if (!init_doors_text(g, door_frames))
	{
		fd_printf(2, "Warning: Failed to load door textures\n");
		free_door_frames(g, door_frames);
		return ;
	}
	g->door_frames = door_frames;
	init_doors(g, door_frames);
}
