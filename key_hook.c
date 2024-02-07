/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:50:13 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/07 11:57:11 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	change_color(t_fractal *fractal)
{
	fractal->random *= -1;
	if (fractal->random > 0)
	{
		fractal->color_base += 2;
		draw(fractal);
	}
	return (0);
}

void	reset(t_fractal *fractal)
{
	fractal->zoom = 1;
	fractal->random = -1;
	fractal->x_range_min = -2.0;
	fractal->x_range_max = 2.0;
	fractal->y_range_min = -2.0;
	fractal->y_range_max = 2.0;
	draw(fractal);
}

void	plus(t_fractal *fractal)
{
	fractal->max_iterations += 25;
	draw(fractal);
}

void	minus(t_fractal *fractal)
{
	if (fractal->max_iterations > 50)
		fractal->max_iterations -= 25;
	draw(fractal);
}
