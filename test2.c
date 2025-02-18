/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:48:35 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/18 13:52:21 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define KEY_ESCAPE 65307
#define KEY_PLUS   61     // touche '+' (ou '=' selon les claviers)
#define KEY_MINUS  45     // touche '-'

// Types de fractales
#define MANDELBROT 0
#define JULIA      1

// Structure principale
typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;

    int     img_width;
    int     img_height;
    double  x1;
    double  x2;
    double  y1;
    double  y2;
    int     iteration_max;

    int     fractal_type; // MANDELBROT ou JULIA
    double  julia_cr;     // constante réelle pour Julia
    double  julia_ci;     // constante imaginaire pour Julia
}   t_data;

void my_mlx_pixel_put(t_data *data, int y, int x, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_fractal(t_data *data)
{
    double zoom_x = data->img_width / (data->x2 - data->x1);
    double zoom_y = data->img_height / (data->y2 - data->y1);

    for (int py = 0; py < data->img_height; py++)
    {
        for (int px = 0; px < data->img_width; px++)
        {
            int i = 0;
            double t = 0;
            int r, g, b, color;
            double z_r, z_i, c_r, c_i;

            if (data->fractal_type == MANDELBROT)
            {
                c_r = px / zoom_x + data->x1;
                c_i = py / zoom_y + data->y1;
                z_r = 0;
                z_i = 0;
            }
            else if (data->fractal_type == JULIA)
            {
                // Pour Julia, on part de la coordonnée du pixel
                z_r = px / zoom_x + data->x1;
                z_i = py / zoom_y + data->y1;
                c_r = data->julia_cr;
                c_i = data->julia_ci;
            }
            
            while ((z_r * z_r + z_i * z_i < 4) && (i < data->iteration_max))
            {
                double tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            if (i == data->iteration_max)
                my_mlx_pixel_put(data, px, py, 0x000000);
            else
            {
                t = (double)i / data->iteration_max;
                r = (int)(sin(5.0 * t + 0.0) * 127 + 128);
                g = (int)(sin(5.0 * t + 2.0) * 127 + 128);
                b = (int)(sin(5.0 * t + 4.0) * 127 + 128);
                color = (r << 16) | (g << 8) | b;
                my_mlx_pixel_put(data, px, py, color);
            }
        }
    }
}

int mouse_hook(int button, int x, int y, t_data *data)
{
    double mouse_re = (double)x / data->img_width * (data->x2 - data->x1) + data->x1;
    double mouse_im = (double)y / data->img_height * (data->y2 - data->y1) + data->y1;
    double factor;

    if (button == 4) // Zoom avant
        factor = 0.9;
    else if (button == 5) // Zoom arrière
        factor = 1.1;
    else
        return (0);

    // Zoom centré sur la position de la souris
    data->x1 = mouse_re + (data->x1 - mouse_re) * factor;
    data->x2 = mouse_re + (data->x2 - mouse_re) * factor;
    data->y1 = mouse_im + (data->y1 - mouse_im) * factor;
    data->y2 = mouse_im + (data->y2 - mouse_im) * factor;

    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw_fractal(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    double center_re = (data->x1 + data->x2) / 2.0;
    double center_im = (data->y1 + data->y2) / 2.0;
    double factor;

    if (keycode == KEY_ESCAPE)
    {
        mlx_destroy_image(data->mlx_ptr, data->img_ptr);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        exit(0);
    }
    else if (keycode == KEY_PLUS)
        factor = 0.9;
    else if (keycode == KEY_MINUS)
        factor = 1.1;
    else
        return (0);

    data->x1 = center_re + (data->x1 - center_re) * factor;
    data->x2 = center_re + (data->x2 - center_re) * factor;
    data->y1 = center_im + (data->y1 - center_im) * factor;
    data->y2 = center_im + (data->y2 - center_im) * factor;

    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw_fractal(data);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
    return (0);
}

/*
 * Fonction appelée lorsque l'utilisateur clique sur la croix de fermeture.
 */
int close_window(t_data *data)
{
    mlx_destroy_image(data->mlx_ptr, data->img_ptr);
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(0);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 2)
    {
        printf("Usage: %s [mandelbrot|julia] [julia_cr julia_ci (optionnel pour Julia)]\n", argv[0]);
        exit(1);
    }

    /* Détermination du type de fractale à afficher */
    if (strcmp(argv[1], "mandelbrot") == 0)
        data.fractal_type = MANDELBROT;
    else if (strcmp(argv[1], "julia") == 0)
    {
        data.fractal_type = JULIA;
        if (argc >= 4)
        {
            data.julia_cr = atof(argv[2]);
            data.julia_ci = atof(argv[3]);
        }
        else
        {
            // Valeurs par défaut pour Julia
            data.julia_cr = -0.7;
            data.julia_ci = 0.27015;
        }
    }
    else
    {
        printf("Paramètre invalide. Options disponibles : mandelbrot, julia\n");
        exit(1);
    }

    /* Paramètres initiaux de l'image et de la fractale */
    data.img_width = 800;
    data.img_height = 600;
    data.iteration_max = 50;

    /* Coordonnées de la fenêtre de visualisation */
    if (data.fractal_type == MANDELBROT)
    {
        data.x1 = -2.1;
        data.x2 = 0.6;
        data.y1 = -1.2;
        data.y2 = 1.2;
    }
    else if (data.fractal_type == JULIA)
    {
        data.x1 = -1.5;
        data.x2 = 1.5;
        data.y1 = -1.2;
        data.y2 = 1.2;
    }

    /* Initialisation de MiniLibX et création de la fenêtre */
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, data.img_width, data.img_height, "Fractol");
    data.img_ptr = mlx_new_image(data.mlx_ptr, data.img_width, data.img_height);
    data.addr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.line_length, &data.endian);

    /* Dessin initial de la fractale */
    draw_fractal(&data);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);

    /* Gestion des événements */
    mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);

    mlx_loop(data.mlx_ptr);
    return (0);
}
