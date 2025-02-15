/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:39:29 by taqi              #+#    #+#             */
/*   Updated: 2025/02/15 18:48:49 by oettaqi          ###   ########.fr       */
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
}               t_data;

typedef struct s_complex
{
	double	r;
	double	i;
}				t_complex;

#endif