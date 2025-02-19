/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_event.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:18:01 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/19 08:54:27 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_data **d)
{
	double	factor;

	x = 0;
	y = 0;
	if (button == 4)
		factor = 0.9;
	else if (button == 5)
		factor = 1.1;
	else
		return (0);
	(*d)->x1 = (*d)->x1 * factor;
	(*d)->x2 = (*d)->x2 * factor;
	(*d)->y1 = (*d)->y1 * factor;
	(*d)->y2 = (*d)->y2 * factor;
	mlx_clear_window((*d)->mlx_ptr, (*d)->win_ptr);
	if ((*d)->is_mandelbrot == 1)
		draw_fractal_mandelbrot(d);
	else
		draw_fractal_julia(d);
	mlx_put_image_to_window((*d)->mlx_ptr, (*d)->win_ptr, (*d)->img_ptr, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_data **d)
{
	if (keycode == 65307)
	{
		if ((*d)->img_ptr)
			mlx_destroy_image((*d)->mlx_ptr, (*d)->img_ptr);
		if ((*d)->win_ptr)
			mlx_destroy_window((*d)->mlx_ptr, (*d)->win_ptr);
		if ((*d)->mlx_ptr)
		{
			mlx_loop_end((*d)->mlx_ptr);
			mlx_destroy_display((*d)->mlx_ptr);
			free((*d)->mlx_ptr);
		}
		free(*d);
		*d = NULL;
		exit(0);
	}
	return (0);
}

int	close_window(t_data **d)
{
	if ((*d)->img_ptr)
		mlx_destroy_image((*d)->mlx_ptr, (*d)->img_ptr);
	if ((*d)->win_ptr)
		mlx_destroy_window((*d)->mlx_ptr, (*d)->win_ptr);
	if ((*d)->mlx_ptr)
	{
		mlx_loop_end((*d)->mlx_ptr);
		mlx_destroy_display((*d)->mlx_ptr);
		free((*d)->mlx_ptr);
	}
	free(*d);
	*d = NULL;
	exit(0);
	return (0);
}

void	handling_event(t_data **d)
{
	mlx_mouse_hook((*d)->win_ptr, mouse_hook, d);
	mlx_key_hook((*d)->win_ptr, key_hook, d);
	mlx_hook((*d)->win_ptr, 17, 0, close_window, &(*d));
}
