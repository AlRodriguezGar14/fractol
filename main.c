/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:45:01 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/06 13:51:43 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:00:22 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/04 00:03:17 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	if (argc != 2)
	{
		ft_fd_printf(2, "How to use: ./fractol mandelbrot | julia\n");
		return (1);
	}
	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		return (1);
	init_fractal(fractal, argv[1]);
	init_mlx(fractal);

	draw(fractal);

	mlx_key_hook(fractal->window, key_hook, fractal);
	mlx_mouse_hook(fractal->window, mouse_hook, fractal);
	mlx_hook(fractal->window, PRESS_X, 0, end_program, fractal);
	mlx_hook(fractal->window, ON_MOUSE_MOVE, 0, mouse_pos, fractal);
	mlx_loop(fractal->mlx);

	return (0);	
}
