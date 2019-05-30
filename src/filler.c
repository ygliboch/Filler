/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 11:17:52 by yhliboch          #+#    #+#             */
/*   Updated: 2019/03/19 13:35:41 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_piece(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sz_map->y)
	{
		free(game->piece->piece[i]);
		game->piece->piece[i] = NULL;
		i++;
	}
	free(game->piece->piece);
	game->piece->piece = NULL;
}

void	which_player(t_game *game)
{
	char	*line;

	get_next_line(0, &line);
	if (ft_strstr(line, "exec p1 :") && ft_strstr(line, "yhliboch.filler"))
	{
		game->player = "oO";
		game->bot = "xX";
	}
	else if (ft_strstr(line, "exec p2 :") && ft_strstr(line, "yhliboch.filler"))
	{
		game->player = "xX";
		game->bot = "oO";
	}
	ft_strdel(&line);
}

int		play(t_game *game)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (ft_strstr(line, "Plateau") != NULL)
		{
			if (size_map(game, &line) == 0)
				return (0);
		}
		else if (ft_strstr(line, "Piece") != NULL)
		{
			if (size_piece(game, &line) == 0)
				return (0);
			return (make_choose(game));
		}
		else
		{
			if (line != NULL)
				ft_strdel(&line);
			return (0);
		}
	}
	return (1);
}

int		main(void)
{
	t_game	game;
	int		point;

	which_player(&game);
	while (1)
	{
		if (play(&game) == 0)
			break ;
	}
	free_piece(&game);
	del_map(game.map);
	if (game.sz_map != NULL)
		free(game.sz_map);
	if (game.piece != NULL)
		free(game.piece);
	return (0);
}
