/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 23:12:15 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/09 17:10:34 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "../.mlx/mlx.h"
# include "../utils/libft.h"

# define WIDTH 864 
# define HEIGHT 486 

# define ZOOM_IN 4 
# define ZOOM_OUT 5 
# define ESC 53 
# define LEFT 123 
# define RIGHT 124 
# define UP 126 
# define DOWN 125 
# define PLUS 35 
# define MINUS 46 
# define RESET 15 
# define ON_MOUSE_MOVE 6
# define COLOR_RANDOM 8
# define PRESS_X 17

typedef struct s_fractal
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*img_address;
	char	*name;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		color_base;
	int		max_iterations;
	int		random;
	double	x;
	double	y;
	double	mouse_x;
	double	mouse_y;
	double	offset_x;
	double	offset_y;
	double	zoom;
	double	z_real;
	double	z_imaginary;
	double	c_real;
	double	c_imaginary;
	double	x_range_min;
	double	x_range_max;
	double	y_range_min;
	double	y_range_max;

}	t_fractal;

// Init
void	check_input(int argc, const char **argv);
void	init_fractal(t_fractal *fractal, char *name);
void	init_mlx(t_fractal *fractal);

// Scale canvas
double	scale(double unscaled, double old_max, double new_min, double new_max);

// Set fractals
void	set_fractal_for_mandelbrot(t_fractal *fractal);
void	set_fractal_for_julia(t_fractal *fractal);

// Draw
void	draw(t_fractal *fractal);
void	my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color);

// Hooks
int		end_program(t_fractal *fractal);
int		mouse_hook(int keycode, int x, int y, t_fractal *fractal);
int		key_hook(int keycode, t_fractal *fractal);
int		mouse_pos(int x, int y, t_fractal *fractal);
void	zoom_out(t_fractal *fractal, int x, int y);
void	zoom_in(t_fractal *fractal, int x, int y);
int		change_color(t_fractal *fractal);
void	reset(t_fractal *fractal);
void	plus(t_fractal *fractal);
void	minus(t_fractal *fractal);

// Movement
void	move_left(t_fractal *fractal);
void	move_right(t_fractal *fractal);
void	move_down(t_fractal *fractal);
void	move_up(t_fractal *fractal);
#endif
