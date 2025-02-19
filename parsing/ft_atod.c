/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oettaqi <oettaqi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:44:58 by oettaqi           #+#    #+#             */
/*   Updated: 2025/02/19 09:24:18 by oettaqi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	ini_atod(int *sign, double *result, double *frac, double *div)
{
	*sign = 1;
	*result = 0.0;
	*frac = 0.0;
	*div = 1.0;
}

double	ft_atod(char *str)
{
	int		i;
	int		sign;
	double	result;
	double	frac;
	double	div;

	i = 0;
	ini_atod(&sign, &result, &frac, &div);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		else
			sign = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	parse_fraction(str, &i, &frac, &div);
	return (sign * (result + frac / div));
}

void	parse_fraction(char *str, int *i, double *frac, double *div)
{
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			*frac = *frac * 10.0 + (str[*i] - '0');
			*div *= 10.0;
			(*i)++;
		}
	}
}
