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
	double	vertic_hit_distance;int jj = 0;

	init_info_rays(info, rayAngle, i);
	handle_horizantal(info, i);
	handle_vert(info, i);
	if (info->my_ray[i]._help.found_horz_wall_hit)
		horiz_hit_distance = get_distance_(*info,
				info->my_ray[i]._help.wall_hit_x,
				info->my_ray[i]._help.wall_hit_y);
	else
	{
		// printf("hor : %d \n",i++);
		horiz_hit_distance = INT_MAX;
	}
	if (info->my_ray[i]._help.found_vertical_wall_hit)
		vertic_hit_distance = get_distance_(*info,
				info->my_ray[i]._help.vert_wall_hit_x,
				info->my_ray[i]._help.vert_wall_hit_y);
	else
	{
		// printf("vert : %d \n",i++);
		vertic_hit_distance = INT_MAX;
	}
	info->my_ray[i].wall_hit_x_ = get_wall_hit_x(horiz_hit_distance,
			vertic_hit_distance, *info, i);
	info->my_ray[i].wall_hit_y_ = get_wall_hit_y(horiz_hit_distance,
			vertic_hit_distance, *info, i);
	helper_func(info, horiz_hit_distance, vertic_hit_distance, i);
}
void rect(t_data *data, int map_width, int map_height) {
   int x, y;

    for (y = 0; y < map_height; y++) {
        for (x = 0; x < map_width; x++) {
            int color;

            if (data->copy_map[y][x] == '1') {
                // Wall color (Green)
                color = 0x00FF00;
            } else {
                // Empty space color (White)
                color = 0xFFFFFF;
            }

            // Draw filled square
            int start_x = x * TILE_SIZE;
            int start_y = y * TILE_SIZE;
            for (int i = 0; i < TILE_SIZE; i++) {
                for (int j = 0; j < TILE_SIZE; j++) {
                    mlx_pixel_put(data->mlx_ptr, data->win_ptr2, start_x + i, start_y + j, color);
                }
            }
        }
    }
}

void mlx_pixel_put_line(t_data *data, int x, int y, int color) {
    mlx_pixel_put(data->mlx_ptr, data->win_ptr2, x, y, color);
}

void drawline(t_data *data, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put_line(data, x0, y0, color);

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
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
	// rect(info, info->width, info->height);
    // i = 0;
    // while (i < NUM_RAYS)
	// {
	// 	drawline(info, info->_player.x, info->_player.y, info->my_ray[i].wall_hit_x_, info->my_ray[i].wall_hit_y_, 0xFF0000);
	// 	i++;
	// }
	
}
