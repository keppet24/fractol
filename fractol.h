/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:29 by taqi              #+#    #+#             */
/*   Updated: 2025/02/18 17:39:22 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		is_julia;
	int		is_mandelbrot;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	int		img_width;
	int		img_height;
	int		iteration_max;

	double	julia_cr;
	double	julia_ci;
	double	z_r;
	double	z_i;
	double	c_r;
	double	c_i;

	double	t;
	int		r;
	int		g;
	int		b;	
}				t_data;

// DOSSIER PARSING
// utils_parsing.c

int		ft_strcmp(char *s1, char *s2);
void	parse_fraction(char *str, int *i, double *frac, double *div);
void	display_error_and_exit(t_data **d);
double	ft_atod(char *str);

// verif_input.c
int		is_digit(char c);
void	verif_input_1_user(char *input_1, t_data **d);
void	verif_input_2_user(char *input_2, t_data **d);

//parsing.c
int		parsing(int ac, char **av, t_data **d);
void	is_mandelbrot_or_julia(char *s, t_data **d, char **av, int ac);
void	initialise(t_data **d, char **av, int ac);
void	initialise_julia(t_data **d, char **av, int ac);

//ft_atod.c
double	ft_atod(char *str);

// FICHIER WINDOW_IMAGE_INIT.C
void	window_and_image_init(t_data **d);

// DOSSIER DRAW
// draw_fractal_mandelbrot.c
void	draw_fractal_mandelbrot(t_data **d);
void	color_fractal(t_data **d, int py, int px, int i);
void	my_mlx_pixel_put(t_data **d, int y, int x, int color);
void	iterate_complex(t_data **d, int *i, double *tmp);

//draw_fractal_julia.c
void	draw_fractal_julia(t_data **d);

//DOSSIER HANDLING_EVENT
// handling_event.c
void	handling_event(t_data **d);

#endif