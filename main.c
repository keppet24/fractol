/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taqi <taqi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:14:27 by taqi              #+#    #+#             */
/*   Updated: 2025/02/11 10:37:54 by taqi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>

typedef struct s_vars {
    void    *mlx;
    void    *win;
}              t_vars;

int	close_window(int keycode, t_vars *vars)
{
    if (keycode == 65307)  // Touche Échap
    {
        mlx_destroy_window(vars->mlx, vars->win);
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
        exit(0);
    }
    return (0);
}

int	main(void)
{
    t_vars	vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 600, 600, "Hello world!");
    mlx_hook(vars.win, 2, 1L<<0, close_window, &vars);
    mlx_loop(vars.mlx);
    return (0);
}

