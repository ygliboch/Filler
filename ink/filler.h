/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhliboch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 15:24:39 by yhliboch          #+#    #+#             */
/*   Updated: 2019/02/14 15:24:40 by yhliboch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft.h"
# define ABS(x) ((x < 0) ? (-x) : (x))

typedef struct		s_cor
{
	int				x;
	int				y;
}					t_cor;

typedef	struct		s_piece
{
	char			**piece;
	t_cor			sz_piece;
}					t_piece;

typedef	struct		s_game
{
	char			*player;
	char			*bot;
	char			**map;
	t_cor			*sz_map;
	t_piece			*piece;
	int				min;
}					t_game;

int					make_choose(t_game *game);
int					valid_map(char **map1, char **map, t_game *game);
int					check_num(char **map1, char **piece, t_game *game);
void				del_map(char **map1);
void				short_dist(char **map1, t_game *game, t_cor *res);
int					size_map(t_game *game, char **line);
int					size_piece(t_game *game, char **line);
void				clear_leaks(t_game *game);
int					check_str(char *str, char *map);
void				new_piece(t_game *game);

#endif
