/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal_julia.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:49:32 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/18 16:54:16 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include "fractol.h"

void	initialise_z(t_data **d, int py, int px)
{
	double	zoom_x;
	double	zoom_y;

	zoom_x = (double)(*d)->img_width / ((*d)->x2 - (*d)->x1);
	zoom_y = (double)(*d)->img_height / ((*d)->y2 - (*d)->y1);
	(*d)->z_r = px / zoom_x + (*d)->x1;
	(*d)->z_i = py / zoom_y + (*d)->y1;
}

void	draw_fractal_julia(t_data **d)
{
	double	tmp;
	int		py;
	int		px;
	int		i;

	py = 0;
	while (py < (*d)->img_height)
	{
		px = -1;
		while (++px < (*d)->img_width)
		{
			i = 0;
			initialise_z(d, py, px);
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
