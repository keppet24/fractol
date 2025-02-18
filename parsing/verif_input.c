/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:23:37 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/18 16:17:05 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	verif_input_1_user(char *input_1, t_data **d)
{
	char	*p;

	p = input_1;
	if (*p == '-')
		p++;
	while (*p != '.')
	{
		if (is_digit(*p) == 0)
			display_error_and_exit(d);
		p++;
	}
	if (*p != '.')
		display_error_and_exit(d);
	p++;
	while (*p)
	{
		if (is_digit(*p) == 0)
			display_error_and_exit(d);
		p++;
	}
	if (ft_atod(input_1) > 2.0 || ft_atod(input_1) < -2.0)
		display_error_and_exit(d);
}

void	verif_input_2_user(char *input_2, t_data **d)
{
	char	*p;

	p = input_2;
	if (*p == '-')
		p++;
	while (*p != '.')
	{
		if (is_digit(*p) == 0)
			display_error_and_exit(d);
		p++;
	}
	if (*p != '.')
		display_error_and_exit(d);
	p++;
	while (*p)
	{
		if (is_digit(*p) == 0)
			display_error_and_exit(d);
		p++;
	}
	if (ft_atod(input_2) > 2.0 || ft_atod(input_2) < -2.0)
		display_error_and_exit(d);
}
