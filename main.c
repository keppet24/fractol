/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:14:27 by taqi              #+#    #+#             */
/*   Updated: 2025/02/18 12:51:24 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

int	main(int ac, char **av)
{
	// t_data	*d;

	// d = malloc(sizeof(t_data));
	t_data *d = calloc(1, sizeof(t_data));
	if (!d)
    	exit(EXIT_FAILURE);
	parsing(ac, av, d);
	window_and_image_init(&d);
	if (d->is_mandelbrot == 1)
		draw_fractal_mandelbrot(&d);
	// handling_events();
	// close_function();
	mlx_loop(d->mlx_ptr);
	free(d);
}
