/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:46:50 by mcecchel          #+#    #+#             */
/*   Updated: 2026/02/11 16:43:07 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_position(t_game *game, int x, int y, char dir)
{
	if (y < 0 || y >= game->map->height || x < 0 || x >= game->map->width)
	{
		fd_printf(2, "Error: Player position out of bounds\n");
		return ;
	}
	game->player->pos_x = x + 0.5;
	game->player->pos_y = y + 0.5;
	set_player_direction(game->player, dir);
	game->map->grid[y][x] = '0';
}

static int	validate_char_and_check_player(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map->height || x < 0 || x >= game->map->width)
		return (-1);
	if (!is_valid_map_char(game->map->grid[y][x]))
	{
		fd_printf(2, "Error: Invalid character '%c' in map at position"
			"(%d, %d)\n", game->map->grid[y][x], x, y);
		return (-1);
	}
	if (is_player_char(game->map->grid[y][x]))
	{
		if (game->map->player_count > 0)
		{
			fd_printf(2, "Error: Multiple player found in map\n");
			return (-1);
		}
		game->map->player_count++;
	}
	return (0);
}

static int	scan_map_for_player(t_game *game, int *px, int *py, char *dir)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (validate_char_and_check_player(game, x, y) == -1)
				return (-1);
			if (is_player_char(game->map->grid[y][x]))
			{
				*px = x;
				*py = y;
				*dir = game->map->grid[y][x];
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_and_find_player(t_game *game)
{
	int		player_x;
	int		player_y;
	char	player_dir;

	player_x = 0;
	player_y = 0;
	player_dir = 'N';
	if (scan_map_for_player(game, &player_x, &player_y, &player_dir) == -1)
		return (-1);
	if (game->map->player_count != 1)
	{
		fd_printf(2, "Error: Invalid number of players in map"
			"(found %d, expected 1)\n", game->map->player_count);
		return (-1);
	}
	init_player_position(game, player_x, player_y, player_dir);
	fd_printf(1, "Player initialized at (%.2f, %.2f) facing '%c'\n",
		game->player->pos_x, game->player->pos_y, game->player->spawn_dir);
	return (0);
}
