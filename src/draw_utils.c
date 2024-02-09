/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:24:24 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/07 11:24:39 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	scale(double unscaled, double old_max, double new_min, double new_max)
{
	return ((new_max - new_min) * (unscaled - 0) / (old_max - 0) + new_min);
}

void	my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
	char	*dst;
	int		y_offset;
	int		x_offset;

	y_offset = y * fractal->size_line;
	x_offset = x * fractal->bits_per_pixel / 8;
	dst = fractal->img_address + y_offset + x_offset;
	*(unsigned int *)dst = color;
}
