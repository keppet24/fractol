/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 17:39:36 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/15 19:29:49 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	display(void)
{
	ft_putstr("Erreur\n");
	ft_putstr("Pour mandelbrot :\n");
	ft_putstr(" ./fractol mandelbrot \n");
	ft_putstr("Pour julia :\n");
	ft_putstr("./fractol julia ou ./fractol julia x1 x2");
	ft_putstr("avec x1 x2 des nombres");
	exit(0);
}

double	ft_atod(const char *str)
{
	int		i;
	int		sign;
	double	result;
	double	fraction;
	double	divisor;

	i = 0;
	sign = 1;
	result = 0.0;
	fraction = 0.0;
	divisor = 1.0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			fraction = fraction * 10.0 + (str[i] - '0');
			divisor *= 10.0;
			i++;
		}
	}
	return (sign * (result + fraction / divisor));
}

void	initialise_julia(t_data *d, t_complex *c, char **av)
{
	d->x1 = -1;
	d->x2 = 1;
	d->y1 = -1.2;
	d->y2 = 1.2;
	if (ac == 4)
	{
		c->r = atod(av[3]);
		c->i = atod(av[4]);
	}
}

void	initialise(t_data *d, t_complex *c, char **av, int ac)
{
	if (d->is_mandelbrot == 1)
	{
		(void)c;
		(void)av;
		(void)ac;
		d->x1 = -2.1;
		d->x2 = 0.6;
		d->y1 = -1.2;
		d->y2 = 1.2;
	}
	else
		initialise_julia(d, c, av, ac);
}

void	ini_atod(int *sign, double *result, double *frac, double *div)
{
	*sign = 1;
	*result = 0.0;
	*frac = 0.0;
	*div = 1.0;
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;
	double	result;
	double	frac;
	double	div;

	i = 0;
	ini_atod(&sign, &result, &frac, &div);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		else
			sign = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			frac = frac * 10.0 + (str[i] - '0');
			div *= 10.0;
			i++;
		}
	}
	return (sign * (result + frac / div));
}

void	is_mandelbrot_or_julia(char *s, t_data *d, char **av, int ac)
{
	t_complex	*c;

	if (strcmp(s, "mandelbrot") == 0 || strcmp(s, "Mandelbrot") == 0)
	{
		d->is_mandelbrot = 1;
		d->is_julia = 0;
		initialise(d, c, av, ac);
	}
	else if (strcmp(s, "julia") == 0 || strcmp(s, "Julia") == 0)
	{
		d->is_mandelbrot = 0;
		d->is_julia = 1;
		initialise(d, c, av, ac);
	}
	else
		display();
}

int	parsing(int ac, char **av, t_data *d)
{
	if (ac != 2 || ac != 4)
		display();
	is_mandelbrot_or_julia(av[1], d, av, ac);
}
