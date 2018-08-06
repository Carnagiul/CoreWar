/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: piquerue <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 02:16:06 by piquerue          #+#    #+#             */
/*   Updated: 2018/08/06 06:52:40 by piquerue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COREWAR_H
# define FT_COREWAR_H

# include <libft.h>
# include "op.h"

typedef struct		s_op
{
	char			*name;
	char			n_params;
	t_char			params[MAX_ARGS_NUMBER];
	char			n;
	t_uint			cycles;
	char			*comment;
	char			mask;
	char			modif;
}					t_op;

#endif
