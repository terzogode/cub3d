/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 21:54:41 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 22:11:52 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENGINE_H
# define ENGINE_H

# include <math.h>

typedef struct	s_ray t_ray; 
typedef struct	s_perf t_perf;
typedef struct	s_game t_game;
typedef struct	s_color t_color;
typedef struct	s_image t_image; 
typedef struct	s_texture t_texture;

# define MOVE_SPEED 0.08
# define ROT_SPEED  0.07
# define PLAYER_RADIUS 0.20
# define MAX_RAY_DISTANCE 50.0
# define MOUSE_SENSITIVITY 0.003
# define MAX_DOORS 20
# define ARMS_FRAME_TIME 0.06
# define ARMS_TRANSPARENT 0xFF00FF


# define HEIGHT					g->map->height
# define WIDTH					g->map->width
# define DIR_X					g->player->dir_x
# define DIR_Y					g->player->dir_y
# define PLANE_X				g->player->plane_x
# define PLANE_Y				g->player->plane_y
# define POS_X					g->player->pos_x
# define POS_Y					g->player->pos_y
# define MAP_MATRIX				g->map->grid
# define WALL_DISTANCE_ARRAY	g->player->columns_distance
# define WALL					g->wall


typedef struct s_ray
{
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
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
	double	wall_distance;
	int		line_height;
}			t_drawing;

typedef struct s_door
{
	int			x;
	int			y;
	char		orientation;
	bool		is_open;
	t_texture	*frames[1];
	int			frame_count;
	float		animation;
}			t_door;

typedef struct s_arms
{
	t_texture	*frames[4];
	int			frame_count;
	int			frame_idx;
	int			anim_dir;
	int			anim_active;
	int			key_down;
	double		anim_time;
}			t_arms;

# define SIDE_DIST_X	ray->sideDistX
# define SIDE_DIST_Y	ray->sideDistY
# define RAY_DIR_X		ray->rayDirX
# define RAY_DIR_Y		ray->rayDirY
# define MAP_X			ray->mapX
# define MAP_Y			ray->mapY
# define STEP_X			ray->stepX
# define STEP_Y			ray->stepY
# define DELTA_DIST_X	ray->deltaDistX
# define DELTA_DIST_Y	ray->deltaDistY

//arms.c
void	trigger_arms_animation(t_game *g);
void	update_arms_animation(t_game *g, double dt);
void	draw_arms_overlay(t_game *g);
void	free_arms_frames(t_game *g, t_texture **frames);
void	init_arms(t_game *g);

//clean_up.c
void		destroy_mlx_image(t_game *g);
void		destroy_doors(t_game *g);
void		free_struct(t_game *g);
void		free_wall_image(t_game *g);
int			clean_up(t_game *g);
void		free_door_frames(t_game *g, t_texture **frames);
void		free_arms_frames(t_game *g, t_texture **frames);

// colours_management.c
t_color		shade_color(t_color col, double factor);
int		get_tex_x(t_ray *ray, t_game *g, t_image *texture,
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

// texture_select.c
t_texture	*select_tex_face(t_drawing *draw, t_game *g);

// texture_draw.c
void		draw_solid_column(t_game *g, int x, t_drawing *draw, double factor);

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
void		init_doors(t_game *g, t_texture **door_frames);
void		init_single_door(t_door *door, int x, int y,
				t_texture **door_frames);

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

// mouse_management.c
int			mouse_move(int x, int y, t_game *g);
void		recenter_mouse_if_needed(t_game *g, int x);

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
void		check_and_toggle_door(t_game *g);
t_texture	**allocate_door_frames(void);

// arms.c
void		update_arms_animation(t_game *g, double delta_time);
void		draw_arms_overlay(t_game *g);
void		trigger_arms_animation(t_game *g);

//doors.c
bool		is_door_open(t_game *g, int x, int y);
float		get_door_animation(t_game *g, int x, int y);
void		update_door_animations(t_game *g, double delta_time);
t_texture	*get_door_frame_texture(t_game *g, int x, int y);

// minimap.c
void		draw_minimap(t_game *g);

// minimap_utils.c
t_color		get_minimap_color(t_game *g, int mx, int my);
void		draw_minimap_square(t_game *g, int mx, int my);
void		draw_player_pixel(t_game *g, int px, int py, int size);

bool		struct_init(t_game *g);
void		init_game(t_game *g);
void		init_mlx(t_game *g);

#endif
