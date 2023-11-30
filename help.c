#include "render_map.h"

double	get_distance_(t_data info, double x, double y)
{
	return (sqrt((x - info._player.x) * (x - info._player.x)
			+ (y - info._player.y) * (y - info._player.y)));
}

double	norm_angl(double rayangle)
{
	rayangle = remainder(rayangle, PI2);
	if (rayangle < 0)
		rayangle = PI2 + rayangle;
	return (rayangle);
}

int	check_direction_left(t_data info, int i)
{
	if (info.my_ray[i].is_ray_facing_left)
		return (-1);
	return (0);
}

int	check_direction_up(t_data info, int i)
{
	if (info.my_ray[i].is_ray_facing_up)
		return (-1);
	return (0);
}

int	destroy_(int key, void *p)
{
	exit(1);
	return (1);
}
