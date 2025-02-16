/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:29 by taqi              #+#    #+#             */
/*   Updated: 2025/02/16 14:36:21 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	void	*mlx_ptr;
	int		is_julia;
	int		is_mandelbrot;
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	int		img_width;
	int		img_height;

	double	julia_cr;
	double	julia_ci;
}				t_data;

// DOSSIER PARSING
// utils_parsing.c

int		ft_strcmp(char *s1, char *s2);
void	parse_fraction(char *str, int *i, double *frac, double *div);
void	display_error_and_exit(t_data *d);
double	ft_atod(char *str);

// verif_input.c
int		is_digit(char c);
void	verif_input_1_user(char *input_1, t_data *d);
void	verif_input_2_user(char *input_2, t_data *d);

//parsing.c
int		parsing(int ac, char **av, t_data *d);
void	is_mandelbrot_or_julia(char *s, t_data *d, char **av, int ac);
void	initialise(t_data *d, char **av, int ac);
void	initialise_julia(t_data *d, char **av, int ac);

//ft_atod.c
double	ft_atod(char *str);

#endif