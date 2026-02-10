/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:00:54 by mcecchel          #+#    #+#             */
/*   Updated: 2026/02/09 16:43:16 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'D' && line[i] != 'B'
			&& line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

static int	check_content_after_map(t_game *game, int start_line,
	int *content_line, int *is_map_content)
{
	int	i;

	i = start_line;
	while (i < game->parse->line_count)
	{
		if (!is_line_empty(game->parse->file_lines[i]))
		{
			*content_line = i + 1;
			*is_map_content = is_map_line(game->parse->file_lines[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	handle_empty_line(t_game *game, int found, char **grid, int row,
	int line_idx)
{
	int	content_line;
	int	is_map_content;

	if (found > 0)
	{
		if (check_content_after_map(game, line_idx + 1, &content_line,
				&is_map_content))
		{
			if (is_map_content)
				fd_printf(2, "Error: Empty line inside map at line %d\n",
					line_idx + 1);
			else
				fd_printf(2, "Error: Content found after map at line %d\n",
					content_line);
			free_map_rows(grid, row);
			return (-1);
		}
	}
	return (0);
}

static int	process_map_line(char *line, char **grid, int row, int width)
{
	grid[row] = pad_map_line(line, width);
	if (!grid[row])
	{
		free_map_rows(grid, row);
		fd_printf(2, "Error: Memory allocation failed for map row\n");
		return (-1);
	}
	return (0);
}

static int	fill_map_grid(t_game *game, char **map_grid, int map_width)
{
	int	i;
	int	map_row;
	int	found_map_line;

	i = game->parse->map_start;
	map_row = 0;
	found_map_line = 0;
	while (i < game->parse->line_count)
	{
		if (is_line_empty(game->parse->file_lines[i]))
		{
			if (handle_empty_line(game, found_map_line, map_grid, map_row,
					i) == -1)
				return (-1);
			i++;
			continue ;
		}
		found_map_line = 1;
		if (process_map_line(game->parse->file_lines[i], map_grid,
				map_row, map_width) == -1)
			return (-1);
		map_row++;
		i++;
	}
	return (0);
}

int	extract_map(t_game *game)
{
	int		map_height;
	int		map_width;
	char	**map_grid;

	map_height = get_map_height(game);
	map_width = get_map_width(game);
	if (map_height == 0 || map_width == 0)
	{
		fd_printf(2, "Error: Map is empty\n");
		return (-1);
	}
	// Alloco la griglia 2D
	map_grid = alloc_map_grid(map_height);
	if (!map_grid)
		return (-1);
	if (fill_map_grid(game, map_grid, map_width) == -1)
		return (-1);
	// Assegno la griglia alla struttura di gioco
	game->map->grid = map_grid;
	game->map->width = map_width;
	game->map->height = map_height;
	fd_printf(1, "Map parsed successfully: width=%d, height=%d\n",
		map_width, map_height);
	return (0);
}
