███████╗██████╗  █████╗  ██████╗████████╗    ██████╗ ██╗     
██╔════╝██╔══██╗██╔══██╗██╔════╝╚══██╔══╝   ██╔═══██╗██║     
█████╗  ██████╔╝███████║██║        ██║█████╗██║   ██║██║     
██╔══╝  ██╔══██╗██╔══██║██║        ██║╚════╝██║   ██║██║     
██║     ██║  ██║██║  ██║╚██████╗   ██║      ╚██████╔╝███████╗
╚═╝     ╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝   ╚═╝       ╚═════╝ ╚══════╝
                                                             

![Hipnosapo](img/hipnosapo-min.jpeg)

# Fractol

This projects draws in a window created with the 42 native library MiniLibx the Mandelbrot and Julia sets. Instead of these being static images, the library enables some interactivity.

## Features
- When calling the executable, the user can choose between the options "help", "mandelbrot" or "julia".
-  Zoom in / zoom out with the mouse.
-  Use 'p' to add more operations when drawing the fractal. Use 'm' to reduce the number of operations.
-  Use 'c' to generate random colors within the set.
-  Use 'r' reset the view of the fractal.
-  If the chosen set is Julia, use the mouse to discover different figures based on the relative position.
-  If the chosen set is Julia, enter the x and y coordenates as inputs based on the given Aspect Ratio to start with a particular figure.
  
## Key Concepts
Both fractals exist in the real -2 to 2 and the imaginary 1.2 to -1.2 ranges.
To achieve an initial clear view of these, the most straightforward solution is to escalate the window from the given pixels to the wanted range. With the same rule of three, the relative position of the mouse is found in real time.

```c
double	scale(double unscaled, double old_max, double new_min, double new_max)
{
	return ((new_max - new_min) * (unscaled - 0) / (old_max - 0) + new_min);
}
```
The pixels are drawn in an image instead of the canvas so that using a 'buffer' improves by a lot the speed of the program. [This is a very useful guide I recommend](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html#writing-pixels-to-a-image).

## Understanding the Math of the project
The formula for the Mandelbrot set is **z = z^2 + c**, where z and c are complex numbers.
A complex number can be calculated **a + bi**, where **a** is the real part, **b** is the imaginary part, and **i is the square root of -1**.

When squaring a complex number **(z^2)**, we get **(a + bi)^2 = a^2 + 2abi - b^2** (because i^2 = -1).
This gives us a new complex number with a **real part (a^2 - b^2)** and an **imaginary part (2ab)**.

The expression (a + bi)^2 is a result of applying the **binomial theorem**, which states that (x + y)^2 = x^2 + 2xy + y^2.

So, when we say z = z^2 + c, we're actually doing two operations:
1. For the real part: z_real = (a^2 - b^2) + c_real
2. For the imaginary part: z_imaginary = (2ab) + c_imaginary

This is why we split the operation into two parts:
```c
void	draw_fractal(t_fractal *fractal)
{
	int		iteration;
	double	z_real_squared;
	double	z_imaginary_squared;

	iteration = -1;
	while (++iteration < fractal->max_iterations)
	{
		z_real_squared = fractal->z_real * fractal->z_real;
		z_imaginary_squared = fractal->z_imaginary * fractal->z_imaginary;
		fractal->z_imaginary = 2.0 * fractal->z_real
			* fractal->z_imaginary
			+ fractal->c_imaginary;
		fractal->z_real = z_real_squared - z_imaginary_squared
			+ fractal->c_real;
		if (z_real_squared + z_imaginary_squared > WIDTH)
			break ;
	}
	if (iteration == fractal->max_iterations)
		my_mlx_pixel_put(fractal, fractal->x, fractal->y, 0x000000);
	else
		my_mlx_pixel_put(fractal, fractal->x, fractal->y,
			fractal->color_base * iteration);
}
```

## Differences between Mandelbrot and Julia

**c is the position of the pixel**, which is escalated to the relative range established in the canvas. c_real is x axis, while c_imaginary is y the axis.
z starts being 0 but changes to being the result of the previous operation.

```c
void	set_fractal_for_mandelbrot(t_fractal *fractal)
{
	double	aspect_ratio;

	fractal->z_real = 0.0;
	fractal->z_imaginary = 0.0;
	aspect_ratio = (double)WIDTH / HEIGHT;
	fractal->c_real = scale(fractal->x,
			WIDTH - 1,
			fractal->x_range_min * aspect_ratio,
			fractal->x_range_max * aspect_ratio);
	fractal->c_imaginary = scale(fractal->y,
			HEIGHT - 1,
			fractal->y_range_min,
			fractal->y_range_max);
}
```

In Julia the constants are inverted, and **c**, instead of the location of the pixel, **is the mouse position**. **z is a constant**, is the position of the pixel to draw.
```c
void	set_fractal_for_julia(t_fractal *fractal)
{
	double	aspect_ratio;

	aspect_ratio = (double)WIDTH / HEIGHT;
	fractal->z_real = scale(fractal->x,
			WIDTH - 1,
			fractal->x_range_min * aspect_ratio,
			fractal->x_range_max * aspect_ratio);
	fractal->z_imaginary = scale(fractal->y,
			HEIGHT - 1,
			fractal->y_range_min,
			fractal->y_range_max);
	fractal->c_real = fractal->mouse_x;
	fractal->c_imaginary = fractal->mouse_y;
}
```

***

## Useful introductory documentation:

- [What's so special about the Mandelbrot Set? - Numberphile](https://www.youtube.com/watch?v=FFftmWSzgmk&list=PLt5AfwLFPxWL7NpD_DKO28XhS0Ugctkpu)
- [The Mandelbrot Set - Numberphile](https://www.youtube.com/watch?v=NGMRB4O922I)
- [Filled Julia Set](https://www.youtube.com/watch?v=oCkQ7WK7vuY)
- [Math's Famous Fractal: The Mandelbrot Set](https://www.youtube.com/watch?v=u9GAnW8xFJY)
- [Complex Number Multiplication](https://www.mathsisfun.com/algebra/complex-number-multiply.html)
- [Complex Numbers](https://www.mathsisfun.com/numbers/complex-numbers.html)
- [How do you find the square of a complex number?](https://www.quora.com/How-do-you-find-the-square-of-a-complex-number)
- [Scaling to match the size](https://stackoverflow.com/questions/17297296/scaling-to-match-the-size)
- [42Docs MiniLibx](https://harm-smits.github.io/42docs/libs/minilibx)
