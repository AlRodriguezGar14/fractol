/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:00:41 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/30 01:13:57y alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		color_a;
	int		color_b;
    t_data  img;
}	t_vars;


void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
    dst = data->addr + offset;
    *(unsigned int*)dst = color;
}

int print_boxes(t_vars *vars)
{
   // Draw first set of colors
    int idx = 0;
    int jdx = 0;
    while (idx++ < HEIGHT / 2)
    {
        jdx = 0;
        while (jdx++ < WIDTH - 1)
            my_mlx_pixel_put(&(*vars).img, jdx, idx, (*vars).color_a);
    }

    // Display first set of colors
    mlx_put_image_to_window((*vars).mlx, (*vars).win, (*vars).img.img, 0, 0);

    // Draw second set of colors
    idx = HEIGHT / 2;
    jdx = 0;
    while (idx++ < HEIGHT - 1)
    {
        jdx = 0;
        while (jdx++ < WIDTH - 1)
            my_mlx_pixel_put(&(*vars).img, jdx, idx, (*vars).color_b);
    }

    // Display second set of colors
    mlx_put_image_to_window((*vars).mlx, (*vars).win, (*vars).img.img, 0, 0);

    // Display the final image
    mlx_put_image_to_window((*vars).mlx, (*vars).win, (*vars).img.img, 0, 0);

	(*vars).color_a -= 2000;
	(*vars).color_b += 2000;
    return (0);
}


int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	printf("Hi from the key hook: %d\n", keycode);
	return (0);
}

int	mouse_hook(int keycode, t_vars *vars)
{
	(void)vars;
	printf("Hi from the mouse hook: %d\n", keycode);
	return (0);
}

int	mouse_position(int x, int y, t_vars *vars)
{
	(void)vars;
	printf("mouse position:\n\tx: %d\n\ty: %d\n", x, y);
	return (0);
}

int	close_window()
{
	exit(1);
}

int main(void)
{
    t_data  img;
	t_vars	vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");

    img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    vars.img = img;

	vars.color_a = 0xffff00;
	vars.color_b = 0x0000ff;

	// print_boxes(&vars);
	
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_hook(vars.win, 6, 0, mouse_position, &vars);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
    mlx_loop_hook(vars.mlx, print_boxes, &vars);
    mlx_loop(vars.mlx);

    return (0);
}
