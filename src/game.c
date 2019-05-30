/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:24:41 by yhliboch          #+#    #+#             */
/*   Updated: 2019/03/19 13:35:54 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	del_map(char **map1)
{
	int	i;

	i = 0;
	while (map1[i])
	{
		if (map1[i] != NULL)
		{
			free(map1[i]);
			map1[i] = NULL;
		}
		i++;
	}
	if (map1 != NULL)
		free(map1);
	map1 = NULL;
}

char	**empty_map(t_game *game)
{
	char	**map1;
	int		i;
	int		j;

	i = 0;
	if (!(map1 = (char **)malloc(sizeof(char *) * game->sz_map->y + 1)))
		return (NULL);
	while (i < game->sz_map->y)
	{
		map1[i] = ft_strnew(game->sz_map->x);
		map1[i] = ft_memset(map1[i], '.', game->sz_map->x);
		i++;
	}
	map1[i] = NULL;
	return (map1);
}

char	**copy_to_big(char **map1, t_game *game, t_cor *m, int temp)
{
	t_cor	tmp;
	t_cor	p;

	p.y = -1;
	tmp.y = 0;
	while (++p.y < game->piece->sz_piece.y)
	{
		p.x = -1;
		temp == 0 ? tmp.x = 0 : 0;
		while (game->piece->piece[p.y][++p.x])
		{
			if (game->piece->piece[p.y][p.x] == '*')
			{
				if (p.y + m->y - tmp.y < game->sz_map->y)
					map1[p.y + m->y - tmp.y][p.x + m->x - tmp.x] = '*';
				else
					return (NULL);
				temp = 1;
			}
			temp == 0 ? tmp.x++ : 0;
		}
		temp == 0 ? tmp.y++ : 0;
	}
	map1[game->sz_map->y] = NULL;
	return (map1);
}

int		make_choose2(int point, t_game *game, char **map1, t_cor *res)
{
	t_cor	m;

	m.y = 0;
	m.x = point;
	if (m.x > game->sz_map->x - 1)
	{
		m.x = point % game->sz_map->x;
		m.y = point / game->sz_map->x;
	}
	if (copy_to_big(map1, game, &m, 0) != NULL &&
				valid_map(map1, game->map, game) != 0
				&& check_num(map1, game->piece->piece, game) != 0)
		short_dist(map1, game, res);
	return (game->min);
}

int		make_choose(t_game *game)
{
	char		**map1;
	int			point;
	t_cor		res;

	point = 0;
	res.y = 0;
	res.x = 0;
	while (point != game->sz_map->x * game->sz_map->y)
	{
		map1 = empty_map(game);
		make_choose2(point, game, map1, &res);
		del_map(map1);
		point++;
	}
	ft_printf("%d %d\n", res.y, res.x);
	if (game->min == game->sz_map->y * game->sz_map->x)
		return (0);
	return (1);
}
