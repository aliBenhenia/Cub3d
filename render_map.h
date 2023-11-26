# ifndef RENDER_MAP_H
# define RENDER_MAP_H

# include <stdlib.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>

# define PI2 6.28318530718
# define PI 3.141592653589
# define WIDTH 1080
# define HEIGHT 720
# define TILE_SIZE 30
# define FOV ((60.0 * M_PI) / 180.0)
# define WALL_STRIPE 1
# define NUM_RAYS  WIDTH
# define MINI_MAP_SCALE 0.5
# define MOVE_SPEED 10
// direction
#define NORTH "N"
#define SOUTH "S"
#define WEST  "W"
#define EAST  "E"

typedef struct player
{
	int		square_size;
	double	x;
	double	y;
	int		turn_direction;
	int		walk_direction;
	int		is_lr;
	double	rotation_angle;
	int		move_speed;
	double	rotation_speed;
}t_player;

typedef struct help
{
	int		found_horz_wall_hit;
	double	wall_hit_x;
	double	wall_hit_y;
	int		found_vertical_wall_hit;
	double	vert_wall_hit_x;
	double	vert_wall_hit_y;
	double	y_intercept;
	double	x_intercept;
	double	y_step;
}t_help;

typedef struct ray
{
	double	ray_angle;
	double	wall_hit_x_;
	double	wall_hit_y_;
	double	distance;
	int		was_hit_vertical; // unsed
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;
	int		wall_hit_content; // unsed
	t_help	_help;
}	t_ray;

typedef struct data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*win_ptr2;
	int			square_size; // unsed
	int			height;
	int			width;
	t_player	_player;
	t_ray		my_ray[NUM_RAYS];
	char		**copy_map;
	void		*wimg;
	uint32_t	*wframe;
}	t_data;

void	handle_walk_(t_data *info);
void	render_map(char *map[]);
int		check_wall(t_data info, int keycode);
void	init_data(t_data *info, char **map);
int		move(int keycode, t_data *info);
void	handle_move(t_data *info, int keycode);
int		check_wall(t_data info, int keycode);
void	fill_copy_map(t_data *info, char **map);
void	render_player( t_data info);
void	cast_rays(t_data *info);
void	cast_ray(t_data *info, double rayAngle, int i);
void	init_info_rays(t_data *info, double rayAngle, int i);
void	handle_vert(t_data *info, int i);
void	handle_horizantal(t_data *info, int i);
void	render_3d_effect(t_data *info, int i);
int		check_wall_px(t_data info, double x, double y);
double	get_distance_(t_data info, double x, double y);
double	get_distance_vertical(t_data info, double rayAngle);
double	norm_angl(double rayangle);
int		get_player_y(char*map[]);
int		get_player_x(char*map[]);
int		get_height(char *map[]);
int		getwidth(char *map[], int idx);
int		check_direction_up(t_data info, int i);
int		check_direction_left(t_data info, int i);
int		destroy_(int key, void *p);
#endif
