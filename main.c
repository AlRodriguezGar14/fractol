/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:00:22 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/02 18:16:41y alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"


int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	if (argc != 2)
	{
		ft_fd_printf(2, "How to use: ./fractol mandelbrot\n");
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
	mlx_hook(fractal->window, 17, 0, close_window, fractal);
	mlx_loop(fractal->mlx);

	return (0);	
}