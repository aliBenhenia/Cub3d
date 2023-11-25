#include "render_map.h"

int	check_wall_px(t_data info, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = x / TILE_SIZE;
	map_y = y / TILE_SIZE;
	if (x < 0 || y < 0 || x >= info.width * TILE_SIZE || y >= info.height * 30)
		return (1);
	if (info.copy_map[map_y][map_x] == '1')
		return (1);
	return (0);
}

double	get_distance_vertical(t_data info, double rayAngle)
{
	double	x_intercept;
	double	y_intercept;

	y_intercept = roundf(info._player.y / TILE_SIZE) * TILE_SIZE;
	x_intercept = info._player.x + (y_intercept - info._player.y)
		/ tan(rayAngle);
	return (x_intercept);
}

void	check_wall_hit_vert(t_data *info, double x_step, int i)
{
	double	next_vertical_x;
	double	next_vertical_y;
	double	vertical_x;

	next_vertical_x = info->my_ray[i]._help.x_intercept;
	next_vertical_y = info->my_ray[i]._help.y_intercept;
	while (next_vertical_x >= 0 && next_vertical_x <= info->width * TILE_SIZE && next_vertical_y
		>= 0 && next_vertical_y <= info->height * TILE_SIZE)
	{
		vertical_x = next_vertical_x + check_direction_left(*info, i);
		if (check_wall_px(*info, vertical_x, next_vertical_y))
		{
			info->my_ray[i]._help.found_vertical_wall_hit = 1;
			info->my_ray[i]._help.vert_wall_hit_x = next_vertical_x;
			info->my_ray[i]._help.vert_wall_hit_y = next_vertical_y;
			break ;
		}
		else
		{
			next_vertical_x += x_step;
			next_vertical_y += info->my_ray[i]._help.y_step;
		}
	}
}

void	handle_vert(t_data *info, int i)
{
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;

	x_step = 0;
	y_step = 0;
	x_intercept = floor(info->_player.x / TILE_SIZE) * TILE_SIZE;
	if (info->my_ray[i].is_ray_facing_right)
		x_intercept += TILE_SIZE;
	y_intercept = info->_player.y + (x_intercept - info->_player.x)
		* tan(info->my_ray[i].ray_angle);
	x_step = TILE_SIZE;
	if (info->my_ray[i].is_ray_facing_left)
		x_step *= -1;
	y_step = x_step * tan(info->my_ray[i].ray_angle);
	if ((info->my_ray[i].is_ray_facing_up && y_step > 0)
		|| (info->my_ray[i].is_ray_facing_down && y_step < 0))
		y_step *= -1;
	info->my_ray[i]._help.y_step = y_step;
	info->my_ray[i]._help.x_intercept = x_intercept;
	info->my_ray[i]._help.y_intercept = y_intercept;
	check_wall_hit_vert(info, x_step, i);
}
