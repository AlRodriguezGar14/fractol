/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:01:42 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/03 00:56:18 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	move_left(t_fractal *fractal)
{
    double move_amount = 0.05 * fractal->zoom;
	printf("zoom: %f\n", fractal->zoom);
    fractal->x_range_min -= move_amount;
    fractal->x_range_max -= move_amount;
    draw(fractal);
}

void	move_right(t_fractal *fractal)
{
    double move_amount = 0.05 * fractal->zoom;
    fractal->x_range_min += move_amount;
    fractal->x_range_max += move_amount;
    draw(fractal);
}

void	move_down(t_fractal *fractal)
{
    double move_amount = 0.05 * fractal->zoom;
    fractal->y_range_min += move_amount;
    fractal->y_range_max += move_amount;
    draw(fractal);
}

void	move_up(t_fractal *fractal)
{
    double move_amount = 0.05 * fractal->zoom;
    fractal->y_range_min -= move_amount;
    fractal->y_range_max -= move_amount;
    draw(fractal);
}