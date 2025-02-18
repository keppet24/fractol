/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:14:27 by taqi              #+#    #+#             */
/*   Updated: 2025/02/18 16:14:11 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_data	*d;

	d = calloc(1, sizeof(t_data));
	if (!d)
		exit(EXIT_FAILURE);
	parsing(ac, av, &d);
	window_and_image_init(&d);
	if (d->is_mandelbrot == 1)
	{
		draw_fractal_mandelbrot(&d);
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
	}
	else
	{
		draw_fractal_julia(&d);
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
	}
	// handling_events();
	// close_function();
	mlx_loop(d->mlx_ptr);
	//free(d);
}
