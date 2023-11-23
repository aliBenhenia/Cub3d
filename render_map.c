#include "render_map.h"

void	line(t_data *info, int x, int y, int height)
{
	int	tmp;

	if (y < 0)
		y = 0;
	tmp = 0;
	while (tmp < y && tmp < HEIGHT)
	{
		info->wframe[tmp * WIDTH + x] = 0x5865F2;
		++tmp;
	}
	while (height-- && x < WIDTH && y < HEIGHT)
	{
		info->wframe[y * WIDTH + x] = 0x5e5b58;
		++y;
	}
	while (y < HEIGHT && x < WIDTH)
	{
		info->wframe[y * WIDTH + x] = 0x9e8747;
		++y;
	}
}

void	render_3d_effect(t_data *info, int i)
{
	double	distance_to_projection_plane;
	double	wall_height;
	int		wall_top;
	int		wall_bottom;

	distance_to_projection_plane = (WIDTH / 2) / (tan(FOV / 2));
	info->my_ray[i].distance = info->my_ray[i].distance
		* cos(info->my_ray[i].ray_angle
			- info->_player.rotation_angle);
	wall_height = (TILE_SIZE / info->my_ray[i].distance)
		* distance_to_projection_plane;
	if (wall_height > HEIGHT)
		wall_height = HEIGHT;
	if (wall_height <= 0)
		wall_height = 1;
	wall_top = ((HEIGHT / 2)) - (wall_height / 2);
	line(info, i, wall_top, wall_height);
}

int	render_(void *p)
{
	t_data	*info;

	info = (p);
	handle_walk_(info);
	turn(info);
	render_player(*info);
	mlx_clear_window(info->mlx_ptr, info->win_ptr);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->wimg, 0, 0);
}

int	release(int key, void *p)
{
	t_data	*info;

	info = (p);
	if(key == 2 || key == 124 || key == 123 || key == 0)
	{
		info->_player.is_lr = 0;
		info->_player.turn_direction = 0;
		info->_player.walk_direction = 0;
	}
	if (key == 1 || key == 13)
		info->_player.walk_direction = 0;
	return (1);
}

void	render_map(char *map[])
{
	t_data	info;

	init_data(&info, map);
	render_player(info);
	mlx_hook(info.win_ptr, 2, 0, move, &info);
	mlx_hook(info.win_ptr, 3, 0, release, &info);
	mlx_hook(info.win_ptr, 17, 0, destroy_, &info);
	mlx_loop_hook(info.mlx_ptr, render_, &info);
	mlx_loop(info.mlx_ptr);
}

int	main(void)
{
	char	**map1;
	int		i;

	i = 0;
	map1 = (char **)malloc(18 * sizeof(char *));
	map1[0] = strdup("11111111111111111111111111111");
	map1[1] = strdup("11111110000000000000000011001");
	map1[2] = strdup("11110000000000000011111110101");
	map1[3] = strdup("1010010010E000000000000000111");
	map1[4] = strdup("10000111111111111111100000011");
	map1[5] = strdup("10000111011111111110000001111");
	map1[6] = strdup("11111111000000000011111111111");
	map1[7] = NULL;
	render_map(map1);
	return (0);
}
