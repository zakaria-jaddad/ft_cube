/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zajaddad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:12:36 by zajaddad          #+#    #+#             */
/*   Updated: 2025/08/06 17:39:11 by zajaddad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_bonus.h"

void	free_mlx(t_mlx *mlx)
{
	if (mlx == NULL)
		return ;
	if (mlx->img != NULL)
	{
		mlx_delete_image(mlx->mlx, mlx->img);
		mlx->img = NULL;
	}
	if (mlx->mlx != NULL)
	{
		mlx_close_window(mlx->mlx);
		mlx->mlx = NULL;
	}
	free(mlx);
}

t_mlx	*init_mlx(void)
{
	t_mlx	*mlx;

	mlx = malloc(sizeof(t_mlx));
	if (mlx == NULL)
		return (NULL);
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "ft_cube", true);
	if (mlx->mlx == NULL)
		return (free(mlx), NULL);
	mlx->img = mlx_new_image(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (mlx->img == NULL)
	{
		mlx_close_window(mlx->mlx);
		free(mlx);
		return (NULL);
	}
	if (mlx_image_to_window(mlx->mlx, mlx->img, 0, 0) == -1)
		return (free_mlx(mlx), NULL);
	return (mlx);
}
