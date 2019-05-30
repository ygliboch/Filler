/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_dist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:35:07 by yhliboch          #+#    #+#             */
/*   Updated: 2019/03/19 13:36:10 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		remember(char **piece, char **map1, t_cor *res, t_cor *p)
{
	t_cor	r;

	r.y = 0;
	r.x = 0;
	while (map1[r.y] && map1[r.y][r.x] != '*')
	{
		r.x = 0;
		while (map1[r.y][r.x] && map1[r.y][r.x] != '*')
			r.x++;
		if (map1[r.y][r.x] != '*')
			r.y++;
	}
	while (piece[p->y] && piece[p->y][p->x] != '*')
	{
		p->x = 0;
		while (piece[p->y][p->x] && piece[p->y][p->x] != '*')
			p->x++;
		if (piece[p->y][p->x] != '*')
			p->y++;
	}
	if (r.y - p->y < 0 || r.x - p->x < 0)
		return (0);
	res->y = r.y - p->y;
	res->x = r.x - p->x;
	return (1);
}

int		min_dist(t_cor *me, t_cor *bot)
{
	int	y;
	int	x;

	y = me->y - bot->y;
	x = me->x - bot->x;
	x = (x < 0 ? -x : x);
	y = (y < 0 ? -y : y);
	return (x + y);
}

t_cor	*next_bot(char **map, char *bt)
{
	static	t_cor	*bot;

	if (bot == NULL)
	{
		bot = (t_cor *)malloc(sizeof(t_cor));
		bot->y = 0;
		bot->x = 0;
	}
	else
		bot->x++;
	while (map[bot->y] != NULL)
	{
		while (map[bot->y][bot->x])
		{
			if (ft_strchr(bt, map[bot->y][bot->x]) != NULL)
				return (bot);
			bot->x++;
		}
		bot->x = 0;
		bot->y++;
	}
	free(bot);
	bot = NULL;
	return (bot);
}

t_cor	*next_me(char **map)
{
	static	t_cor	*me;

	if (me == NULL)
	{
		me = (t_cor *)malloc(sizeof(t_cor));
		me->y = 0;
		me->x = 0;
	}
	else
		me->x++;
	while (map[me->y] != NULL)
	{
		while (map[me->y][me->x])
		{
			if (map[me->y][me->x] == '*')
				return (me);
			me->x++;
		}
		me->x = 0;
		me->y++;
	}
	free(me);
	me = NULL;
	return (me);
}

void	short_dist(char **map1, t_game *game, t_cor *res)
{
	t_cor	*me;
	t_cor	*bot;
	t_cor	p;
	int		min;
	int		temp;

	p.y = 0;
	p.x = 0;
	min = game->sz_map->x * game->sz_map->y;
	while ((me = next_me(map1)) != NULL)
	{
		while ((bot = next_bot(game->map, game->bot)) != NULL)
		{
			temp = min_dist(me, bot);
			if (temp <= min)
				min = temp;
		}
	}
	if (min <= game->min)
	{
		if (remember(game->piece->piece, map1, res, &p))
			game->min = min;
	}
}
