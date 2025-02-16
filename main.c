/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:14:27 by taqi              #+#    #+#             */
/*   Updated: 2025/02/16 14:20:57 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	parsing(ac, av, d);
	// window_and_image_init();
	// draw_fractal();
	// handling_events();
	// close_function();
	free(d);
}
