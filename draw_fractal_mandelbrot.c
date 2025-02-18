/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal_mandelbrot.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:33:29 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/18 13:53:30 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void my_mlx_pixel_put(t_data **d, int y, int x, int color)
{
    char *dst;

    dst = (*d)->addr + (y * (*d)->line_length + x * ((*d)->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void	initialise_complex(t_data **d, int py, int px)
{
	double	zoom_x;
	double	zoom_y;

	zoom_x = (double)(*d)->img_width / ((*d)->x2 - (*d)->x1);
	zoom_y = (double)(*d)->img_height / ((*d)->y2 - (*d)->y1);
	(*d)->c_r = px / zoom_x + (*d)->x1;
	(*d)->c_i = py / zoom_y + (*d)->y1;
	(*d)->z_r = 0;
	(*d)->z_i = 0;
}

void	iterate_complex(t_data **d, int *i, double *tmp)
{
	*tmp = (*d)->z_r;
	(*d)->z_r = (*d)->z_r * (*d)->z_r - (*d)->z_i * (*d)->z_i + (*d)->c_r;
	(*d)->z_i = 2 * (*d)->z_i * *tmp + (*d)->c_i;
	(*i)++;
}

void	color_fractal(t_data **d, int py, int px, int i)
{
	int	color;

	(*d)->t = (double)i / (*d)->iteration_max;
	(*d)->r = (int)(sin(5.0 * (*d)->t + 0.0) * 127 + 128);
	(*d)->g = (int)(sin(5.0 * (*d)->t + 2.0) * 127 + 128);
	(*d)->b = (int)(sin(5.0 * (*d)->t + 4.0) * 127 + 128);
	color = ((*d)->r << 16) | ((*d)->g << 8) | (*d)->b;
	my_mlx_pixel_put(d, px, py, color);
}

void	draw_fractal_mandelbrot(t_data **d)
{
	double	tmp;
	int		py;
	int		px;
	int		i;

	py = 0;
	i = 0;
	while (py < (*d)->img_height)
	{
		px = -1;
		while (++px < (*d)->img_width)
		{
			i = 0;
			initialise_complex(d, py, px);
			tmp = (*d)->z_r;
			while (((*d)->z_r * (*d)->z_r + (*d)->z_i * (*d)->z_i < 4)
				&& (i < (*d)->iteration_max))
				iterate_complex(d, &i, &tmp);
			if (i == (*d)->iteration_max)
				my_mlx_pixel_put(d, py, px, 0x000000);
			else
				color_fractal(d, py, px, i);
		}
		py++;
	}
}
