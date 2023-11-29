#include "render_map.h"

int	get_player_x(char*map[])
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < get_height(map))
	{
		x = 0;
		while (x < getwidth(map, y))
		{
			if (map[y][x] == 'N' ||map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
				return (x * TILE_SIZE + 1) ;
			x++;
		}
		y++;
	}
	return (0);
}

int	get_player_y(char*map[])
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < get_height(map))
	{
		x = 0;
		while (x < getwidth(map, y))
		{
			if (map[y][x] == 'N' ||map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
				return (y * TILE_SIZE + 1);
			x++;
		}
		y++;
	}
	return (0);
}

void	fill_copy_map(t_data *info, char **map)
{
	int	i;

	i = 0;
	info->copy_map = malloc(info->height * sizeof(char *));
	while (i < info->height)
	{
		info->copy_map[i] = map[i];
		i++;
	}
}

void	render_player( t_data info)
{
	cast_rays(&info);
}
