/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:39:36 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/18 12:14:18 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	initialise_julia(t_data *d, char **av, int ac)
{
	d->x1 = -2;
	d->x2 = 2;
	d->y1 = -1.2;
	d->y2 = 1.2;
	if (ac == 4)
	{
		verif_input_1_user(av[2], d);
		verif_input_2_user(av[3], d);
		d->julia_cr = ft_atod(av[2]);
		d->julia_ci = ft_atod(av[3]);
	}
}

void	initialise(t_data *d, char **av, int ac)
{
	if (d->is_mandelbrot == 1)
	{
		(void)av;
		(void)ac;
		d->x1 = -2.1;
		d->x2 = 0.6;
		d->y1 = -1.2;
		d->y2 = 1.2;
	}
	else
		initialise_julia(d, av, ac);
}

void	is_mandelbrot_or_julia(char *s, t_data *d, char **av, int ac)
{
	if (ft_strcmp(s, "mandelbrot") == 0 || ft_strcmp(s, "Mandelbrot") == 0)
	{
		if (ac != 2)
			display_error_and_exit(d);
		d->is_mandelbrot = 1;
		d->is_julia = 0;
		initialise(d, av, ac);
	}
	else if (ft_strcmp(s, "julia") == 0 || ft_strcmp(s, "Julia") == 0)
	{
		d->is_mandelbrot = 0;
		d->is_julia = 1;
		initialise(d, av, ac);
	}
	else
		display_error_and_exit(d);
}

int	parsing(int ac, char **av, t_data *d)
{
	if (ac != 2 && ac != 4)
		display_error_and_exit(d);
	is_mandelbrot_or_julia(av[1], d, av, ac);
	return (0);
}
