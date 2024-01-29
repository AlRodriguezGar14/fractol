/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberrod <alberrod@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 20:00:41 by alberrod          #+#    #+#             */
/*   Updated: 2024/01/29 23:30:16 by alberrod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

typedef struct s_data
{
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
}   t_data;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
    int     offset;

    offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
    dst = data->addr + offset;
    *(unsigned int*)dst = color;
}

int main(void)
{
    t_data  img;
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");

    img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    // Draw first set of colors
    int idx = 0;
    int jdx = 0;
    while (idx++ < HEIGHT / 2)
    {
        jdx = 0;
        while (jdx++ < WIDTH - 1)
            my_mlx_pixel_put(&img, jdx, idx, 0x00ffff00);
    }

    // Display first set of colors
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    // Draw second set of colors
    idx = HEIGHT / 2;
    jdx = 0;
    while (idx++ < HEIGHT - 1)
    {
        jdx = 0;
        while (jdx++ < WIDTH - 1)
            my_mlx_pixel_put(&img, jdx, idx, 0x000000ff);
    }

    // Display second set of colors
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    // Display the final image
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);

    mlx_loop(mlx);

    return (0);
}
