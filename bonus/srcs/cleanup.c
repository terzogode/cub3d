/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:30:59 by mcecchel          #+#    #+#             */
/*   Updated: 2026/02/10 18:53:04 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_doors(t_game *g)
{
	if (!g)
		return ;
	if (g->door_frames)
		free_door_frames(g, g->door_frames);
	if (g->doors)
		free(g->doors);
}

// Cleanup parsing structures (textures, colors, map, player, parse data)
void	cleanup_parsing_fields(t_game *game)
{
	if (!game)
		return ;
	free_texture(game, game->tex_north);
	free_texture(game, game->tex_south);
	free_texture(game, game->tex_west);
	free_texture(game, game->tex_east);
	free_texture(game, game->tex_box);
	free_arms_frames(game, game->arms.frames);
	destroy_doors(game);
	if (game->floor)
		free(game->floor);
	if (game->wall)
		free(game->wall);
	if (game->ceiling)
		free(game->ceiling);
	free_map(game->map);
	if (game->player)
	{
		if (game->player->columns_distance)
			free(game->player->columns_distance);
		free(game->player);
	}
	free_parse(game->parse);
}

void	cleanup_mlx_resources(t_game *game)
{
	if (!game)
		return ;
	free_screen(game);
	if (game->win && game->mlx_init)
		mlx_destroy_window(game->mlx_init, game->win);
	if (game->mlx_init)
	{
		mlx_destroy_display(game->mlx_init);
		free(game->mlx_init);
	}
	if (game->drawing)
		free(game->drawing);
}

void	cleanup_game_fields(t_game *game)
{
	if (!game)
		return ;
	cleanup_parsing_fields(game);
	cleanup_mlx_resources(game);
}

int	clean_up(t_game *g)
{
	if (!g)
		exit(0);
	cleanup_game_fields(g);
	exit(0);
}
