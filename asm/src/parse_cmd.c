/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 05:53:53 by snassour          #+#    #+#             */
/*   Updated: 2018/10/01 05:53:56 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

int		asm_checkvalidlabel(char *line, char *label)
{
	int	i;

	i = 0;
	while (line[i] != LABEL_CHAR && ft_strchr(LABEL_CHARS, line[i]))
		++i;
	if (i != 0 && line[i] == LABEL_CHAR)
		return (1);
	return (-1);
}

int		asm_checklabel(char *line, char *label, t_asm *data)
{
	int		ret;

	ret = 0;
	if (label)
		ret = asm_checkvalidlabel(line, label);
	if (ret < 0)
	{
		data->error_type = INVALID_LABEL;
		asm_parse_file_error(data, NULL, NULL);
		return (-1);
	}
	return (ret);
}

int		asm_blank(char *line, int begin)
{
	int j;

	j = 0;
	while (line[begin] && (line[begin + j] == '\t' || line[begin + j] == ' '))
		++j;
	return (j);
}

int		asm_check_type_arg(char **line, int j, int i, t_asm *data)
{
	int		err;

	err = -1;
	if ((*line)[j] == 'r' && (err = asm_checkreg(*line, j, i, data)) < 0)
		return (-1);
	else if ((*line)[j] == DIRECT_CHAR)
	{
		if ((err = asm_checkdir(*line, j, data->op_tab[data->cmd], i)) < 0)
			return (-1);
	}
	else if (((*line)[j] == LABEL_CHAR
		|| ((*line)[j] <= '9' && (*line)[j] >= '0') || (*line)[j] == '-'))
	{
		if ((err = asm_checkind(*line, j, data->op_tab[data->cmd], i)) < 0)
			return (-1);
	}
	else if (err == -1)
		return (asm_parse_file_error(data, line, NULL));
	return (err);
}

int		asm_checkargument(char *line, int begin, t_asm *data, int conv)
{
	int	i;
	int	j;
	int err;
	int	sep_char;

	i = -1;
	j = begin;
	sep_char = 0;
	while (++i < data->op_tab[conv].n_arg && line[j] && err >= 0)
	{
		j += asm_blank(line, j);
		j = (line[j] == SEPARATOR_CHAR ? ((j + 1) + (0 * ++sep_char)) : j);
		if ((i == 0 && sep_char == 1) || (sep_char >= data->op_tab[conv].n_arg))
			return (asm_parse_file_error(data, &line, NULL));
		j += asm_blank(line, j);
		err = asm_check_type_arg(&line, j, i, data);
		if (err == -1)
			return (-1);
		j += err;
		j += asm_blank(line, j);
	}
	if (sep_char != data->op_tab[conv].n_arg - 1 || line[j] != '\0')
		return (asm_parse_file_error(data, &line, NULL));
	return (1);
}

int		asm_max(int a, int b)
{
	return (a > b ? a : b);
}

int		asm_checkcmd(char *l, int b, t_asm *d)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while ((l + b)[j] <= 'z' && (l + b)[j] >= 'a')
		++j;
	while (++i < 16)
		if (!ft_strncmp(l + b, d->op_tab[i].cmd, asm_max(d->op_tab[i].len, j)))
			break ;
	d->error_type = UNKNOWN_FUNCTION;
	if (i == 16)
		return (asm_parse_file_error(d, &l, NULL));
	j += asm_blank(l, b + d->op_tab[i].len);
	d->error_type = INVALID_ARGUMENT;
	if ((l + b)[j] == '\0')
		return (asm_parse_file_error(d, &l, NULL));
	d->cmd = i;
	d->nb_arg = d->op_tab[i].n_arg;
	if (asm_checkargument(l, b + j, d, i) == -1)
		return (-1);
	if (asm_addclist(d, l, b + j, i) == -1)
		return (-1);
	return (1);
}

char	*asm_removecomment(char *line)
{
	char	*loc;

	if ((loc = ft_strchr(line, COMMENT_CHAR)))
		*loc = '\0';
	if ((loc = ft_strchr(line, END_COMMENT_CHAR)))
		*loc = '\0';
	loc = NULL;
	loc = ft_strtrim(line);
	return (loc);
}
