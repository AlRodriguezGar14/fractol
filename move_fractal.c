/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:01:42 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 22:28:12 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_left(t_fractal *fractal)
{
	fractal->x_range_min -= 0.25;
	fractal->x_range_max -= 0.25;
	draw(fractal);
}

void	move_right(t_fractal *fractal)
{
	fractal->x_range_min += 0.25;
	fractal->x_range_max += 0.25;
	draw(fractal);
}

void	move_down(t_fractal *fractal)
{
	fractal->y_range_min += 0.25;
	fractal->y_range_max += 0.25;
	draw(fractal);
}

void	move_up(t_fractal *fractal)
{
	fractal->y_range_min -= 0.25;
	fractal->y_range_max -= 0.25;
	draw(fractal);
}