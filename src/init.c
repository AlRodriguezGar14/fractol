/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:13:29 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 04:35:09by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	check_input(int argc, char **argv)
{
	if ((argc != 2 && argc != 4)
		|| (!ft_strncmp(argv[1], "mandelbrot", 10) && argc != 2)
		)
	{
		ft_fd_printf(2, "\n\tHow to use: ./fractol mandelbrot | julia\n");
		ft_fd_printf(2, "\tOptional (Julia): set x and y based on AR %dx%d\n\n",
			WIDTH, HEIGHT);
		exit(1);
	}
	if (argc == 2 && !ft_strncmp(argv[1], "help", 4))
	{
		ft_fd_printf(1, "\n\tHow to use: ./fractol mandelbrot | julia\n");
		ft_fd_printf(1, "\tOptional (Julia): set x and y based on AR %dx%d\n\n",
			WIDTH, HEIGHT);
		ft_fd_printf(1, "\n\tControls:\n");
		ft_fd_printf(1, "\t\tp : +25 operations\n\t\tm : -25 operations\n");
		ft_fd_printf(1, "\t\tc : random colors\n\t\tr : reset view\n\n");
		exit(1);
	}
}

void	init_fractal(t_fractal *fractal, char *name)
{
	fractal->name = ft_sprintf("%s", name);
	fractal->color_base = 0x553322;
	fractal->zoom = 1;
	fractal->random = -1;
	fractal->x = 0;
	fractal->y = 0;
	fractal->x_range_min = -2.0;
	fractal->x_range_max = 2.0;
	fractal->y_range_min = -2.0;
	fractal->y_range_max = 2.0;
	fractal->max_iterations = 42;
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx,
			WIDTH, HEIGHT,
			fractal->name);
	fractal->image = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	fractal->img_address = mlx_get_data_addr(fractal->image,
			&fractal->bits_per_pixel,
			&fractal->size_line,
			&fractal->endian);
}
