/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:13:29 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 16:58:53y alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_error()
{
		ft_fd_printf(2, "\n\tHow to use: ./fractol mandelbrot | julia\n");
		ft_fd_printf(2, "\tOptional (Julia): set x and y based on AR %dx%d\n\n",
			WIDTH, HEIGHT);
		ft_fd_printf(2, "\tDon't use params to set the default x-0 and y-0");
		ft_fd_printf(2, "\n\tControls:\n");
		ft_fd_printf(2, "\t\tp : +25 operations\n\t\tm : -25 operations\n");
		ft_fd_printf(2, "\t\tc : random colors\n\t\tr : reset view\n\n");
		exit(1);
}
void	check_input(int argc, char **argv)
{
	char	*x;
	char	*y;
	if (argc != 2 && argc != 4)
		init_error();
	if (argc == 4)
	{
		x = argv[2];
		y = argv[3];
		if (!ft_strncmp(argv[1], "mandelbrot", 10))
			init_error();
		while (*x || *y)
		{
			if (*x && !ft_isdigit(*x++))
				init_error();
			if (*y && !ft_isdigit(*y++))
				init_error();
		}
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
