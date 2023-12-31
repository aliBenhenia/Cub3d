#include "render_map.h"

static double	get_wall_hit_x(double horiz_hit_distance,
	double vertic_hit_distance, t_data info, int i)
{
	if (horiz_hit_distance < vertic_hit_distance)
		return (info.my_ray[i]._help.wall_hit_x);
	return (info.my_ray[i]._help.vert_wall_hit_x);
}

static double	get_wall_hit_y(double horiz_hit_distance,
	double vertic_hit_distance, t_data info, int i)
{
	if (horiz_hit_distance < vertic_hit_distance)
		return (info.my_ray[i]._help.wall_hit_y);
	return (info.my_ray[i]._help.vert_wall_hit_y);
}

void	helper_func(t_data *info, double horiz_hit_distance,
	double vertic_hit_distance, int i)
{
	if (horiz_hit_distance < vertic_hit_distance)
		info->my_ray[i].distance = horiz_hit_distance;
	else if (horiz_hit_distance > vertic_hit_distance)
		info->my_ray[i].distance = vertic_hit_distance ;
	render_3d_effect(info, i);
}

void	cast_ray(t_data *info, double rayAngle, int i)
{
	double	horiz_hit_distance;
	double	vertic_hit_distance;

	init_info_rays(info, rayAngle, i);
	handle_horizantal(info, i);
	handle_vert(info, i);
	if (info->my_ray[i]._help.found_horz_wall_hit)
		horiz_hit_distance = get_distance_(*info,
				info->my_ray[i]._help.wall_hit_x,
				info->my_ray[i]._help.wall_hit_y);
	else
		horiz_hit_distance = INT_MAX;
	if (info->my_ray[i]._help.found_vertical_wall_hit)
		vertic_hit_distance = get_distance_(*info,
				info->my_ray[i]._help.vert_wall_hit_x,
				info->my_ray[i]._help.vert_wall_hit_y);
	else
		vertic_hit_distance = INT_MAX;
	info->my_ray[i].wall_hit_x_ = get_wall_hit_x(horiz_hit_distance,
			vertic_hit_distance, *info, i);
	info->my_ray[i].wall_hit_y_ = get_wall_hit_y(horiz_hit_distance,
			vertic_hit_distance, *info, i);
	helper_func(info, horiz_hit_distance, vertic_hit_distance, i);
}

void	cast_rays(t_data *info)
{
	double	ray_angle;
	int		i;

	ray_angle = info->_player.rotation_angle - (FOV / 2);
	info->_player.rotation_angle = norm_angl(info->_player.rotation_angle);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(info, ray_angle, i);
		i++;
		ray_angle += FOV / NUM_RAYS;
	}
}
