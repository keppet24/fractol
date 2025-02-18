/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:12:21 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/18 16:17:14 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	display_error_and_exit(t_data **d)
{
	ft_putstr("Erreur\n");
	ft_putstr("Pour mandelbrot :\n");
	ft_putstr(" ./fractol mandelbrot \n");
	ft_putstr("Pour julia :\n");
	ft_putstr("./fractol julia ou ./fractol julia x1 x2\n");
	ft_putstr("avec x1 x2 des nombres compris entre -2 et 2.");
	free(d);
	exit(0);
}
