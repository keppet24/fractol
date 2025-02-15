/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbroot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:13:14 by taqi              #+#    #+#             */
/*   Updated: 2025/02/14 13:20:22 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>

#define WIDTH 270
#define HEIGHT 240
#define MAX_ITER 50

int main(void)
{
    void    *mlx = mlx_init();
    void    *win = mlx_new_window(mlx, WIDTH, HEIGHT, "Mandelbrot");
    void    *img = mlx_new_image(mlx, WIDTH, HEIGHT);
    char    *data = mlx_get_data_addr(img, &(int){0}, &(int){0}, &(int){0});

    const double x1 = -2.1;
    const double x2 = 0.6;
    const double y1 = -1.2;
    const double y2 = 1.2;
    
    const double zoom_x = WIDTH / (x2 - x1);
    const double zoom_y = HEIGHT / (y2 - y1);

    for (int x = 0; x < WIDTH; x++)
    {
        for (int y = 0; y < HEIGHT; y++)
        {
            double c_r = x / zoom_x + x1;
            double c_i = (HEIGHT - 1 - y) / zoom_y + y1; // Inversion Y
            double z_r = 0;
            double z_i = 0;
            int   iter = 0;

            while (z_r * z_r + z_i * z_i < 4 && iter < MAX_ITER)
            {
                double tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * tmp * z_i + c_i;
                iter++;
            }
            
            int color = (iter == MAX_ITER) ? 0x000000 : 0xFFFFFF;
            int pixel = (y * WIDTH + x) * 4;
            data[pixel] = color >> 16;       // Rouge
            data[pixel + 1] = color >> 8;    // Vert
            data[pixel + 2] = color;         // Bleu
        }
    }
    mlx_put_image_to_window(mlx, win, img, 0, 0);
    mlx_loop(mlx);
    return (0);
}
