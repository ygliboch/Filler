/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_piece.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:37:17 by yhliboch          #+#    #+#             */
/*   Updated: 2019/03/19 13:36:03 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		change_map(t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	while (game->map[i])
	{
		get_next_line(0, &line);
		game->map[i] = ft_strcpy(game->map[i], line + 4);
		ft_strdel(&line);
		if (check_str("OoxX.", game->map[i]) == 0)
			return (0);
		if ((int)ft_strlen(game->map[i]) != game->sz_map->x)
			return (0);
		i++;
	}
	game->map[i] = NULL;
	return (1);
}

int		take_map(t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(0, &line);
	ft_strdel(&line);
	if (game->map != NULL)
		return (change_map(game));
	if (!(game->map = (char **)malloc(sizeof(char *) * game->sz_map->y + 1)))
		return (0);
	while (i < game->sz_map->y)
	{
		get_next_line(0, &line);
		game->map[i] = ft_strdup(line + 4);
		ft_strdel(&line);
		if (check_str("OoXx.", game->map[i]) == 0)
			return (0);
		if ((int)ft_strlen(game->map[i]) != game->sz_map->x)
			return (0);
		i++;
	}
	game->map[i] = NULL;
	return (1);
}

int		take_piece(t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	while (i < game->piece->sz_piece.y)
	{
		get_next_line(0, &line);
		ft_bzero(game->piece->piece[i], ft_strlen(game->piece->piece[i]));
		game->piece->piece[i] = ft_strcpy(game->piece->piece[i], line);
		ft_strdel(&line);
		if (check_str(".*", game->piece->piece[i]) == 0)
			return (0);
		if ((int)ft_strlen(game->piece->piece[i]) != game->piece->sz_piece.x)
			return (0);
		i++;
	}
	return (1);
}

int		size_map(t_game *game, char **line)
{
	if (game->sz_map == NULL)
	{
		game->sz_map = ft_memalloc(sizeof(t_cor));
		game->sz_map->y = ft_atoi(*line + 7);
		game->sz_map->x = ft_atoi(*line + (ft_strrchr(*line, ' ') - *line));
	}
	free((*line));
	game->min = game->sz_map->y * game->sz_map->x;
	return (take_map(game));
}

int		size_piece(t_game *game, char **line)
{
	if (game->piece == NULL)
		game->piece = ft_memalloc(sizeof(t_piece));
	game->piece->sz_piece.y = ft_atoi(*line + 6);
	game->piece->sz_piece.x = ft_atoi(*line +
				(ft_strrchr(*line, ' ') - *line));
	if (game->piece->piece == NULL)
		new_piece(game);
	free((*line));
	return (take_piece(game));
}
