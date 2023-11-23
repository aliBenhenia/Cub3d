#include "render_map.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	getwidth(char *map[], int idx)
{
	return (ft_strlen(map[idx]));
}

int	get_height(char *map[])
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	check_wall(t_data info, int keycode)
{
	int	new_x;
	int	new_y;
	int	map_x;
	int	map_y;

	new_x = info._player.x;
	new_y = info._player.y;
	if (keycode == 126)
		new_y -= 5;
	else if (keycode == 124)
		new_x += 5;
	else if (keycode == 123)
		new_x -= 5;
	else if (keycode == 125)
		new_y += 5;
	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (map_x >= 0 && map_x < info.width && map_y >= 0 && map_y < info.height)
	{
		if (info.copy_map[map_y][map_x] == '1')
			return (1);
	}
	else
		return (1);
	return (0);
}

double update_angle(char dir)
{
	if (dir == 'N')
		return (0); // 0 angle
	if (dir == 'S')
		return (PI); // 180 angle
	if (dir == 'W')
		return (-(PI / 2)); // -90 angle
	if (dir == 'E')
		return (PI / 2); // 90 angle
	printf("%C\n", dir);
	return (0); // default
}

double handle_direction(t_data *info)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < get_height(info->copy_map))
	{
		x = 0;
		while (x < getwidth(info->copy_map, y))
		{
			if (info->copy_map[y][x] == 'N' || info->copy_map[y][x] == 'S' ||info->copy_map[y][x] == 'W' || info->copy_map[y][x] == 'E')
			{
				return (update_angle(info->copy_map[y][x]));
			}
			x++;
		}
		y++;
	}
}

void	init_data(t_data *info, char **map)
{
	int	tmp;

	info->square_size = 30;
	info->mlx_ptr = mlx_init();
	info->height = get_height(map);
	info->width = getwidth(map, 0);
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIDTH,  HEIGHT, "cube");
	info->wimg = mlx_new_image(info->mlx_ptr, WIDTH,  HEIGHT);
	info->wframe = mlx_get_data_addr(info->wimg, &tmp, &tmp,&tmp);
	info->_player.x = get_player_x(map);
	info->_player.y = get_player_y(map);
	info->_player.turn_direction = 0;
	info->_player.walk_direction = 0;
	info->_player.move_speed = 5;
	info->_player.rotation_speed = (PI2 * 5) / 360.0;
	fill_copy_map(info, map);
	info->_player.rotation_angle = handle_direction(info);
}

void	init_info_rays(t_data *info, double rayAngle, int i)
{
	info->my_ray[i].ray_angle = norm_angl(rayAngle);
	info->my_ray[i].is_ray_facing_down = info->my_ray[i].ray_angle > 0
		&& info->my_ray[i].ray_angle < PI;
	info->my_ray[i].is_ray_facing_up = !info->my_ray[i].is_ray_facing_down;
	info->my_ray[i].is_ray_facing_right = info->my_ray[i].ray_angle < 0.5 * PI 
		|| info->my_ray[i].ray_angle > 1.5 * PI;
	info->my_ray[i].is_ray_facing_left = !info->my_ray[i].is_ray_facing_right;
	info->my_ray[i]._help.found_vertical_wall_hit = 0;
	info->my_ray[i]._help.vert_wall_hit_x = 0;
	info->my_ray[i]._help.vert_wall_hit_y = 0;
	info->my_ray[i]._help.found_horz_wall_hit = 0;
	info->my_ray[i]._help.wall_hit_x = 0;
	info->my_ray[i]._help.wall_hit_y = 0;
	info->my_ray[i].distance = 0;
}
