/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yofouzi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:48:18 by yofouzi           #+#    #+#             */
/*   Updated: 2025/04/13 20:48:21 by yofouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (NULL == s1 || NULL == s2 || n <= 0)
		return (0);
	while (*s1 == *s2 && n > 0 && *s1 != '\0')
	{
		++s1;
		++s2;
		--n;
	}
	return (*s1 - *s2);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	error_message(void)
{
	ft_putstr_fd("Error: Invalid input or initialization failed.\n", 2);
	ft_putstr_fd("Usage: ./fractol [fractol_name]\n", 2);
	ft_putstr_fd("Available fractals: mandelbrot\n", 2);
	ft_putstr_fd("Available fractals: julia <set> <set>\n", 2);
	exit(1);
}

int	failed(t_fractal *fractol)
{
	mlx_destroy_image(fractol->mlx_connection, fractol->imag);
	mlx_destroy_window(fractol->mlx_connection, fractol->window);
	mlx_destroy_display(fractol->mlx_connection);
	free(fractol->mlx_connection);
	error_message();
	exit(1);
}
