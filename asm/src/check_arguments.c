/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 05:53:04 by snassour          #+#    #+#             */
/*   Updated: 2018/10/01 05:53:07 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		asm_checklabelarg(char *line, int start, t_asm *data, int nb_arg)
{
	int		i;
	char	c;

	i = 0;
	while (line[i + start] && ft_strchr(LABEL_CHARS, line[i + start]))
		++i;
	if (i != 0 && (line[i + start] == SEPARATOR_CHAR || line[i + start] == '\t'
		|| line[i + start] == ' ' || line[i + start] == '\0'))
	{
		data->label_in_arg[nb_arg] = LABEL_SET;
		c = line[i + start];
		line[i + start] = 0;
		line[i + start] = c;
		return (i);
	}
	return (-1);
}

int		asm_checkdir(char *line, int begin, t_asm *data, int nb_arg)
{
	int		i;
	int		nb;
	char	c;

	if (*(line + begin) != DIRECT_CHAR)
		return (-1);
	i = 1;
	if ((data->op_tab[data->cmd].arg[nb_arg] & T_DIR) == 0)
		return (-1);
	if ((line + begin)[i] == LABEL_CHAR)
	{
		i = asm_checklabelarg(line, begin + 1 + i, data, nb_arg);
		data->arg_type[nb_arg] = 2;
		return (i == -1 ? i : i + 2);
	}
	if ((line + begin)[i] == '-')
		++i;
	while ((line + begin)[i] <= '9' && (line + begin)[i] >= '0')
		i++;
	if (i == 1 || ((line + begin)[1] == '-' && i == 2))
		return (-1);
	c = (line + begin)[i];
	(line + begin)[i] = '\0';
	nb = ft_atoi((line + begin) + 1);
	(line + begin)[i] = c;
	data->arg[nb_arg] = nb;
	data->arg_type[nb_arg] = 2;
	return (i);
}

int		asm_checkind(char *line, int begin, t_asm *data, int nb_arg)
{
	int		i;
	char	c;
	int		nb;

	i = 0;
	if ((line + begin)[i] == LABEL_CHAR)
	{
		i = asm_checklabelarg(line, begin + 1, data, nb_arg);
		data->arg_type[nb_arg] = 3;
		if (i == -1)
			return (-1);
		return (i + 1);
	}
	if ((data->op_tab[data->cmd].arg[nb_arg] & T_IND) == 0)
		return (-1);
	if ((line + begin)[i] == '-')
		++i;
	while ((line + begin)[i] <= '9' && (line + begin)[i] >= '0')
		i++;
	if (i == 0 || ((line + begin)[0] == '-' && i == 1))
		return (-1);
	c = (line + begin)[i];
	(line + begin)[i] = '\0';
	nb = ft_atoi((line + begin));
	(line + begin)[i] = c;
	data->arg[nb_arg] = nb;
	data->arg_type[nb_arg] = 3;
	return (i);
}

int		asm_checkreg(char *line, int begin, int nb_arg, t_asm *data)
{
	int		i;
	int		nb;
	char	c;

	if (*(line + begin) != 'r')
		return (-1);
	i = 1;
	if ((data->op_tab[data->cmd].arg[nb_arg] & T_REG) == 0)
		return (-1);
	while ((line + begin)[i] <= '9' && (line + begin)[i] >= '0')
		i++;
	if (i == 1 || i > 3)
		return (-1);
	c = (line + begin)[i];
	(line + begin)[i] = '\0';
	nb = ft_atoi((line + begin) + 1);
	(line + begin)[i] = c;
	if (nb > REG_NUMBER || nb < 1)
		asm_parse_file_error(data, &line, NULL);
	data->arg[nb_arg] = nb;
	data->arg_type[nb_arg] = 1;
	return ((nb > REG_NUMBER || nb < 1) ? -1 : i);
}
