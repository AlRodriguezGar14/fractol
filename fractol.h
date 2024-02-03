/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:05:53 by alberrod          #+#    #+#             */
/*   Updated: 2024/02/03 01:10:02 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FRACTOL_H
#	define FRACTOL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "mlx/mlx.h"
# include "utils/libft.h"

// #define WIDTH 400 
// #define HEIGHT 240 
#define WIDTH 864 
#define HEIGHT 486 

#define ZOOM_IN 4 
#define ZOOM_OUT 5 
#define ESC 53 
#define LEFT 123 
#define RIGHT 124 
#define UP 126 
#define DOWN 125 
#define PLUS 35 
#define MINUS 46 
#define RANDOM 15 


typedef struct s_fractal
{
	void	*mlx;
	void	*window;
    void    *image;
    char    *img_address;
	char	*name;
    int     bits_per_pixel;
    int     size_line;
    int     endian;
	int		color_base;
	int		x;
	int		y;
	int		max_iterations;
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
void	init_fractal(t_fractal *fractal, char *name);
void	init_mlx(t_fractal *fractal);

// Scale canvas
double	scale(double unscaled, double old_max, double new_min, double new_max);

// Draw
void	draw(t_fractal *fractal);
void    my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color);

// Hooks
int	close_window(t_fractal *fractal);
int	mouse_hook(int keycode, int x, int y, t_fractal *fractal);
int	key_hook(int keycode, t_fractal *fractal);

// Movement
void	move_left(t_fractal *fractal);
void	move_right(t_fractal *fractal);
void	move_down(t_fractal *fractal);
void	move_up(t_fractal *fractal);
# endif