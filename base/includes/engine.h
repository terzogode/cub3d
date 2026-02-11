/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:41 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 23:09:50 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>

typedef struct s_ray		t_ray;
typedef struct s_perf		t_perf;
typedef struct s_game		t_game;
typedef struct s_color		t_color;
typedef struct s_image		t_image;
typedef struct s_texture	t_texture;

# define MOVE_SPEED 0.08
# define ROT_SPEED  0.07
# define PLAYER_RADIUS 0.20
# define MAX_RAY_DISTANCE 50.0

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		distance_exceeded;
	int		out_of_bounds;
}				t_ray;

typedef struct s_drawing
{
	t_ray	*ray;
	int		draw_start;
	int		draw_end;
	int		wall_top;
	double	wall_distance;
	int		line_height;
}			t_drawing;

//clean_up.c
void		destroy_mlx_image(t_game *g);
void		free_struct(t_game *g);
void		free_wall_image(t_game *g);
int			clean_up(t_game *g);

// colours_management.c
t_color		shade_color(t_color col, double factor);
int			get_tex_x(t_ray *ray, t_game *g, t_image *texture,
				double wall_distance);
int			get_tex_y(int y, t_drawing *draw, t_image *tex);
t_color		get_texture_pixel(t_image *tex, int tex_x, int tex_y, t_game *g);

// dda_implementation.c
void		step_ray(t_ray *ray);
void		check_collision(t_ray *ray, t_game *g);
void		perform_dda(t_ray *ray, t_game *g);
double		compute_wall_distance(t_ray *ray, t_game *g);

// draw.c
void		draw_ceiling_part(t_game *g, int x, int draw_start);
void		draw_wall_part(t_game *g, int x, t_drawing *draw, double factor);
void		draw_floor_part(t_game *g, int x, int draw_end);
void		draw_columns(t_game *g, int x, t_drawing *draw);

// fps.c
double		clamp_positive(double value);
void		update_buffered_fps(t_game *g, double *buff_fps,
				double *last_update);
double		now_ms(void	);
void		perf_update(t_perf *p);
void		draw_fps_overlay(t_game *g);

//init.c
void		init_game(t_game *g);
void		init_mlx(t_game *g);

// key_management.c
void		handle_movement_keys(int keycode, t_game *g);
void		handle_rotation_keys(int keycode, t_game *g);
int			key_press(int keycode, t_game *g);
int			close_window(t_game *g);

// key_utils.c
void		release_rotation_keys(int keycode, t_game *g);
int			key_release(int keycode, t_game *g);
void		handle_toggle_keys(int keycode, t_game *g);
void		release_movement_keys(int keycode, t_game *g);

// main_rendering.c
int			loop_hook(t_game *g);
void		rendering(t_game *g);

// move_management.c
void		move_forward(t_game *g);
void		move_backward(t_game *g);
void		lateral_move(t_game *g, int direction);
void		update_player_position(t_game *g);

// ray_casting.c
void		compute_wall_drawing(t_drawing *draw, t_ray *ray, t_game *g);
void		cast_one_ray(t_game *g, int x);
void		init_ray_direction(t_ray *ray, t_game *g, int x);
void		init_ray_map(t_ray *ray, t_game *g);
void		init_delta_distance(t_ray *ray);
void		init_step_side_distance(t_ray *ray, t_game *g);

// rotation.c
void		update_player_rotation(t_game *g);
void		apply_rotation(t_game *g, double angle);

// texture.c
int			allocate_and_load_xpm(t_game *g, t_texture *tex, const char *path);
int			setup_texture_address(t_game *g, t_texture *tex);
int			load_single_texture(t_game *g, t_texture *tex, const char *path);
void		init_textures(t_game *g);

// utils.c
void		put_pixel(t_image *img, int x, int y, t_color color);
void		init_color(t_game *g);
t_texture	*select_tex_face(t_drawing *draw, t_game *g);

bool		struct_init(t_game *g);
void		init_game(t_game *g);
void		init_mlx(t_game *g);

#endif
