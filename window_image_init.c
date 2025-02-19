/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_image_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 15:21:36 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/19 08:01:15 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void window_and_image_init(t_data **d)
{
	(*d)->img_height = 600;
	(*d)->img_width = 800;
	(*d)->iteration_max = 20;
	(*d)->mlx_ptr = mlx_init();
	(*d)->win_ptr = mlx_new_window((*d)->mlx_ptr, (*d)->img_width, (*d)->img_height, "Fractol");
	(*d)->img_ptr = mlx_new_image((*d)->mlx_ptr, (*d)->img_width, (*d)->img_height);
	(*d)->addr = mlx_get_data_addr((*d)->img_ptr, &(*d)->bits_per_pixel, &(*d)->line_length, &(*d)->endian);
}
