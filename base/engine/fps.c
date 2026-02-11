/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 22:10:00 by mbrighi           #+#    #+#             */
/*   Updated: 2026/02/11 21:20:55 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>

double	clamp_positive(double value)
{
	if (value < 0.0)
		return (0.0);
	return (value);
}

void	update_buffered_fps(t_game *g, double *buff_fps, double *last_update)
{
	double	current_time;

	current_time = now_ms();
	if (current_time - *last_update >= 1000.0)
	{
		if (g->perf.fps > 0.0)
			*buff_fps = g->perf.fps;
		else
			*buff_fps = g->perf.fps_raw;
		*last_update = current_time;
	}
}

double	now_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void	perf_update(t_perf *p)
{
	const double	alpha = 0.12;
	double			t;
	double			dt;
	double			fps_now;

	if (!p)
		return ;
	t = now_ms();
	if (p->last_ms == 0.0)
	{
		p->last_ms = t;
		return ;
	}
	dt = clamp_positive(t - p->last_ms);
	p->last_ms = t;
	if (dt <= 0.0)
		return ;
	fps_now = 1000.0 / dt;
	p->fps_raw = fps_now;
	if (p->fps == 0.0)
		p->fps = fps_now;
	else
		p->fps = p->fps * (1.0 - alpha) + fps_now * alpha;
}

void	draw_fps_overlay(t_game *g)
{
	static double	last_update = 0.0;
	static double	buffered_fps = 0.0;
	char			*fps_num;
	char			*fps_str;

	if (!g || !g->mlx_init || !g->win)
		return ;
	update_buffered_fps(g, &buffered_fps, &last_update);
	fps_num = ft_itoa((int)buffered_fps);
	fps_str = ft_strjoin("FPS: ", fps_num);
	free(fps_num);
	mlx_string_put(g->mlx_init, g->win, 10, 20, 0xFFFFFF, fps_str);
	free(fps_str);
}
