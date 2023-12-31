#include "render_map.h"

static int	is_wall(t_data *info, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_x >= 0 && map_x < info->map_width
		&& map_y >= 0 && map_y < info->map_height)
		return (info->pars->map[map_y][map_x] == '1');
    return (1);
}

static int	has_wall_in_path(t_data *info,double x2, double y2)
{
	double	dx;
	double	dy;
	double	distance;
	double	step;
	double	t;
	double	x;
	double	y;

	dx = x2 - info->_player.x;
	dy = y2 - info->_player.y;
	t = 0;
	distance = sqrt(dx * dx + dy * dy);
	step = 0.1;
	while (t <= distance)
	{
		x = info->_player.x + t * (x2 - info->_player.x) / distance;
		y = info->_player.y + t * (y2 - info->_player.y) / distance;
		if (is_wall(info, x, y))
			return (1);
		t += step;
	}
	return (0);
}

static void	handle_walk_(t_data *info)
{
	double	end_x;
	double	end_y;
	int		map_x;
	int		map_y;

	if (info->_player.is_lr)
	{
		end_x = info->_player.x + cos(info->_player.rotation_angle
				+ (M_PI / 2)) * info->_player.walk_direction;
		end_y = info->_player.y + sin(info->_player.rotation_angle
				+ (M_PI / 2)) * info->_player.walk_direction;
	}
	else
	{
		end_x = info->_player.x
					+ cos(info->_player.rotation_angle)
					* info->_player.walk_direction;
		end_y = info->_player.y
					+ sin(info->_player.rotation_angle)
					* info->_player.walk_direction;
	}
	map_x = end_x / TILE_SIZE;
	map_y = end_y / TILE_SIZE;
	if (!has_wall_in_path(info, end_x, end_y))
	{
		info->_player.x = end_x;
		info->_player.y = end_y;
	}
}

static void	handle_walk_back(t_data *info)
{
	double	end_x;
	double	end_y;
	int		map_x;
	int		map_y;

	end_x = (*info)._player.x + (cos((*info)._player.rotation_angle) * 7) * -1;
	end_y = (*info)._player.y + (sin((*info)._player.rotation_angle) * 7) * -1;
	map_x = end_x / TILE_SIZE;
	map_y = end_y / TILE_SIZE;
	if (map_x >= 0 && map_x < info->width && map_y >= 0 && map_y < info->height)
	{
		if (map_y )
			return ;
		if (info->copy_map[map_y][map_x] != '1')
		{
			info->_player.x = end_x;
			info->_player.y = end_y;
		}
	}
}

void	turn(t_data *info)
{
	if (info->_player.turn_direction == 1)
		info->_player.rotation_angle += info->_player.rotation_speed;
	else if (info->_player.turn_direction == -1)
		info->_player.rotation_angle -= info->_player.rotation_speed;
	if (info->_player.rotation_angle > PI2)
		info->_player.rotation_angle = info->_player.rotation_angle - PI2;
	if (info->_player.rotation_angle < 0.0)
		info->_player.rotation_angle = PI2 - fabs(info->_player.rotation_angle);
}

void	handle_move(t_data *info, int keycode)
{
	if (keycode == 124)
		info->_player.turn_direction = 1;
	else if (keycode == 123)
		info->_player.turn_direction = -1;
	if (keycode == 13) // up
	{
		info->_player.walk_direction = 1;
		info->_player.is_lr = 0;
	}
	if (keycode == 1) // down
	{
		info->_player.walk_direction = -1;
		info->_player.is_lr = 0;
	}
	if (keycode == 0) // left
	{
		info->_player.is_lr = 1;
		info->_player.walk_direction = -1;
	}
	if (keycode == 2) // right
	{
		info->_player.is_lr = 1;
		info->_player.walk_direction = 1;
	}
	if (keycode == 53)
		exit(1);
	handle_walk_(info);
	turn(info);
}

int	move(int keycode, t_data *info)
{
	handle_move(info, keycode);
	return (0);
}
