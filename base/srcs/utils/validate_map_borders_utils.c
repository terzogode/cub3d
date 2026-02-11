/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_borders_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 19:05:00 by mcecchel          #+#    #+#             */
/*   Updated: 2026/02/11 18:18:43 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		i;

	map_copy = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < game->map->height)
	{
		map_copy[i] = ft_strdup(game->map->grid[i]);
		if (!map_copy[i])
		{
			while (i > 0)
			{
				free(map_copy[i - 1]);
				i--;
			}
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	return (map_copy);
}

bool	is_valid_position(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return (false);
	if (y >= game->map->height)
		return (false);
	if (x >= game->map->width)
		return (false);
	return (true);
}

int	check_top_bottom_borders(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		if (y == 0 || y == game->map->height - 1)
		{
			x = 0;
			while (x < game->map->width && game->map->grid[y][x])
			{
				if (game->map->grid[y][x] != '1'
					&& game->map->grid[y][x] != ' ')
				{
					fd_printf(2, "Error: Map border not closed at (%d, %d)"
						" - found '%c'\n", x, y, game->map->grid[y][x]);
					return (-1);
				}
				x++;
			}
		}
		y++;
	}
	return (0);
}

static int	check_column(t_game *game, int x, int y)
{
	if (x >= 0 && x < (int)ft_strlen(game->map->grid[y]))
	{
		if (game->map->grid[y][x] != '1' && game->map->grid[y][x] != ' ')
		{
			fd_printf(2, "Error: Map border not closed at (%d, %d)"
				" - found '%c'\n", x, y, game->map->grid[y][x]);
			return (-1);
		}
	}
	return (0);
}

int	check_left_right_borders(t_game *game)
{
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		if (check_column(game, 0, y) == -1)
			return (-1);
		if (check_column(game, game->map->width - 1, y) == -1)
			return (-1);
		y++;
	}
	return (0);
}
