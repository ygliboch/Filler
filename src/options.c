/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:48:31 by yhliboch          #+#    #+#             */
/*   Updated: 2019/02/25 16:48:35 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	new_piece(t_game *game)
{
	int	i;

	i = 0;
	game->piece->piece = (char **)malloc(sizeof(char *) * game->sz_map->y);
	while (i < game->sz_map->y)
	{
		game->piece->piece[i] = ft_strnew(game->sz_map->x);
		i++;
	}
	game->piece->piece[i] = NULL;
}

int		check_str(char *str, char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (ft_strchr(str, map[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int		num_piece(char **piece, t_game *game)
{
	t_cor	temp;
	int		num;

	temp.y = 0;
	num = 0;
	while (temp.y < game->piece->sz_piece.y)
	{
		temp.x = 0;
		while (piece[temp.y][temp.x])
		{
			if (piece[temp.y][temp.x] == '*')
				num++;
			temp.x++;
		}
		temp.y++;
	}
	return (num);
}

int		check_num(char **map1, char **piece, t_game *game)
{
	t_cor	temp;
	int		num;

	temp.y = 0;
	num = 0;
	while (map1[temp.y])
	{
		temp.x = 0;
		while (map1[temp.y][temp.x])
		{
			if (map1[temp.y][temp.x] == '*')
				num++;
			temp.x++;
		}
		temp.y++;
	}
	if (num != num_piece(piece, game))
		return (0);
	return (1);
}

int		valid_map(char **map1, char **map, t_game *game)
{
	t_cor	m;
	int		f;

	m.y = -1;
	f = 0;
	while (map1[++m.y] != NULL)
	{
		m.x = -1;
		while (map1[m.y][++m.x])
		{
			if (map1[m.y][m.x] == '*' &&
				ft_strchr(game->player, map[m.y][m.x]) && f != 0)
				return (0);
			else if (map1[m.y][m.x] == '*' &&
				ft_strchr(game->bot, map[m.y][m.x]))
				return (0);
			else if (map1[m.y][m.x] == '*' &&
				ft_strchr(game->player, map[m.y][m.x])
				&& f == 0 && m.x + 1 != '\0')
				f++;
		}
	}
	return (f == 1 ? 1 : 0);
}
