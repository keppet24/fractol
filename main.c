/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:14:27 by taqi              #+#    #+#             */
/*   Updated: 2025/02/19 08:54:52 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	free_all(t_data **d)
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
}
//--leak-check=full --show-leak-kinds=all

void	*ft_bzero(void *pointer, size_t count)
{
	unsigned char	*p;

	p = (unsigned char *) pointer;
	while (count > 0)
	{
		*p = 0;
		p++;
		count--;
	}
	return (pointer);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	buffer = malloc(size * nmemb);
	if (!buffer)
		return (0);
	ft_bzero(buffer, size * nmemb);
	return (buffer);
}

int	main(int ac, char **av)
{
	t_data	*d;

	d = ft_calloc(1, sizeof(t_data));
	if (!d)
		exit(EXIT_FAILURE);
	parsing(ac, av, &d);
	window_and_image_init(&d);
	if (d->is_mandelbrot == 1)
	{
		draw_fractal_mandelbrot(&d);
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
		handling_event(&d);
	}
	else
	{
		draw_fractal_julia(&d);
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img_ptr, 0, 0);
		handling_event(&d);
	}
	mlx_loop(d->mlx_ptr);
	free_all(&d);
	free(d);
}
