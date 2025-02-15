#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define KEY_ESCAPE 65307
#define KEY_PLUS   61     // touche '+' (ou '=' selon les claviers)
#define KEY_MINUS  45     // touche '-'

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
}   t_data;


void my_mlx_pixel_put(t_data *data, int x, int y, int color)
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
            double c_r = px / zoom_x + data->x1;
            double c_i = py / zoom_y + data->y1;
            double z_r = 0;
            double z_i = 0;
            int i = 0;
            while ((z_r * z_r + z_i * z_i < 4) && (i < data->iteration_max))
            {
                double tmp = z_r;
                z_r = z_r * z_r - z_i * z_i + c_r;
                z_i = 2 * z_i * tmp + c_i;
                i++;
            }
            if (i == data->iteration_max)
            {
                // Si le point appartient à l'ensemble, on le dessine en noir.
                my_mlx_pixel_put(data, px, py, 0x000000);
            }
            else
            {
                // Calcul d'une couleur psychédélique en fonction de la profondeur.
                double t = (double)i / data->iteration_max;
                int r = (int)(sin(5.0 * t + 0.0) * 127 + 128);
                int g = (int)(sin(5.0 * t + 2.0) * 127 + 128);
                int b = (int)(sin(5.0 * t + 4.0) * 127 + 128);
                int color = (r << 16) | (g << 8) | b;
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
 * Cette fonction est appelée lorsque l'utilisateur clique sur la croix
 * de fermeture de la fenêtre. Elle détruit la fenêtre et quitte le programme.
 */
int close_window(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    exit(0);
    return (0);
}

int main(void)
{
    t_data data;

    // Paramètres initiaux de l'image et de la fractale
    data.img_width = 800;
    data.img_height = 600;
    data.x1 = -2.1;
    data.x2 = 0.6;
    data.y1 = -1.2;
    data.y2 = 1.2;
    data.iteration_max = 50;

    // Initialisation de MiniLibX et création de la fenêtre
    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, data.img_width, data.img_height, "Mandelbrot Psychedelic");
    data.img_ptr = mlx_new_image(data.mlx_ptr, data.img_width, data.img_height);
    data.addr = mlx_get_data_addr(data.img_ptr, &data.bits_per_pixel, &data.line_length, &data.endian);

    // Dessin initial de la fractale
    draw_fractal(&data);
    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);

    // Gestion des événements
    mlx_mouse_hook(data.win_ptr, mouse_hook, &data);
    mlx_key_hook(data.win_ptr, key_hook, &data);
    // Gestion de la fermeture par la croix
    mlx_hook(data.win_ptr, 17, 0, close_window, &data);

    mlx_loop(data.mlx_ptr);
    return (0);
}



