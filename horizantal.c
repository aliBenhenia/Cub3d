#include "render_map.h"

void	check_wall_hit_horz(t_data *info, double x_step, int i)
{
	double	next_horz_x;
	double	next_horz_y;
	double	y_to_check;

	next_horz_x = info->my_ray[i]._help.x_intercept;
	next_horz_y = info->my_ray[i]._help.y_intercept;
	while (next_horz_x >= 0 && next_horz_x <= info->width  * TILE_SIZE
		&& next_horz_y >= 0 && next_horz_y <= info->height * TILE_SIZE)
	{
		y_to_check = next_horz_y + check_direction_up(*info, i);
		if (check_wall_px(*info, next_horz_x, y_to_check))
		{
			info->my_ray[i]._help.found_horz_wall_hit = 1;
			info->my_ray[i]._help.wall_hit_x = next_horz_x;
			info->my_ray[i]._help.wall_hit_y = next_horz_y;
			break ;
		}
		else
		{
			next_horz_x += x_step;
			next_horz_y += info->my_ray[i]._help.y_step;
		}
	}
}

void	handle_horizantal(t_data *info, int i)
{
	double	x_step;
	double	y_step;
	double	x_intercept;
	double	y_intercept;

	x_step = 0;
	y_step = 0;
	y_intercept = floor(info->_player.y / TILE_SIZE) * TILE_SIZE;
	if (info->my_ray[i].is_ray_facing_down)
		y_intercept += TILE_SIZE;
	x_intercept = info->_player.x + (y_intercept - info->_player.y)
		/ tan(info->my_ray[i].ray_angle);
	y_step = TILE_SIZE;
	if (info->my_ray[i].is_ray_facing_up)
		y_step *= -1;
	x_step = y_step / tan(info->my_ray[i].ray_angle);
	if ((info->my_ray[i].is_ray_facing_left && x_step > 0)
		|| (info->my_ray[i].is_ray_facing_right && x_step < 0))
		x_step *= -1;
	info->my_ray[i]._help.y_step = y_step;
	info->my_ray[i]._help.x_intercept = x_intercept;
	info->my_ray[i]._help.y_intercept = y_intercept;
	check_wall_hit_horz(info, x_step, i);
}
