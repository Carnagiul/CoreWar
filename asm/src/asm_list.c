/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 05:52:25 by snassour          #+#    #+#             */
/*   Updated: 2018/10/01 05:52:29 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		asm_addclist(t_asm *data, char *line, int begin, int conv)
{
	char	s[4][13];
	int		i;
	int		j;
	int		save;
	int		cpy;
	int		tab[3];
	t_op	op;
	int		ocp;
	int		neg;

	i = -1;
	while (++i < 4)
		ft_bzero(s[i], 13);
	i = -1;
	j = 0;
	op = data->op_tab[conv];
	ocp = 0;
	while (++i < data->op_tab[conv].n_arg)
	{
		neg = 0;
		while ((line + begin)[j] == ' ' || (line + begin)[j] == '\t')
			++j;
		if ((line + begin)[j] == 'r' && (op.arg[i] & T_REG))
			ocp |= 1;
		else if ((line + begin)[j] == DIRECT_CHAR && (op.arg[i] & T_DIR))
			ocp |= 2;
		else if ((op.arg[i] & T_IND))
			ocp |= 3;
		else
		{
			asm_error(INVALID_ARGUMENT, NULL, data);
			return (-1);
		}
		ocp <<= 2;
		save = j;
		if ((line + begin)[j] == LABEL_CHAR)
			++j;
		else if ((line + begin)[j] == '-')
			j += ++neg;
		while ((line + begin)[j] != SEPARATOR_CHAR && (line + begin)[j] && (line + begin)[j] != ' ' && (line + begin)[j] != '\t')
			++j;
		cpy = 0;
		while (save < j)
		{
			s[i][cpy] = (line + begin)[save];
			save++;
			cpy++;
		}
		s[i][cpy] = '\0';
		while ((line + begin)[j] == ' ' || (line + begin)[j] == '\t')
			++j;
		if ((line + begin)[j] == SEPARATOR_CHAR)
			++j;
		tab[i] = (s[i][0] == LABEL_CHAR ? 1 : ft_atoi(s[i]));
	}
	op.ocp = (op.ocp == 0 ? 0 : ocp);
	return (1);
}
