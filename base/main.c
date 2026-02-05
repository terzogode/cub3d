/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:33:54 by mcecchel          #+#    #+#             */
/*   Updated: 2026/02/04 04:53:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	g = {0};

	if (validate_input(ac, av) == -1)
		return (1);
	if (struct_init(&g))
		return (cleanup_game_fields(&g), 1);
	if (parse_file(&g, av[1]) == -1)	
		return (cleanup_game_fields(&g), 1);
	if (validate_map(&g) == -1)
		return (cleanup_game_fields(&g), 1);
	init_game(&g);
	init_mlx(&g);
	init_textures(&g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_hook(g.win, 17, 0, clean_up, &g);
	mlx_loop_hook(g.mlx_init, loop_hook, &g);
	mlx_loop(g.mlx_init);
	cleanup_game_fields(&g);
	return (0);
}
