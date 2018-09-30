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
	return (ret);
}

int		asm_checkargument(char *line, int begin, t_asm *data, int conv)
{
	int	i;
	int	j;
	int err;
	int	count_sep_char;

	i = 0;
	j = begin;
	err = 0;
	count_sep_char = 0;
	while (line[j] && err >= 0 && i < data->op_tab[conv].n_arg)
	{
		while (line[j] == '\t' || line[j] == ' ')
			++j;
		if (i == 0 && line[j] == SEPARATOR_CHAR)
		{
			asm_parse_file_error(data, &line, NULL);
		}
		if (line[j] == SEPARATOR_CHAR)
			j += 1 + (0 * ++count_sep_char);
		if (count_sep_char >= data->op_tab[conv].n_arg)
		{
			asm_parse_file_error(data, &line, NULL);
		}
		while (line[j] == '\t' || line[j] == ' ')
			++j;
		if (line[j] == 'r')
		{

			j += asm_checkreg(line, j, data->op_tab[conv], i, data);
		}
		else if (line[j] == LABEL_CHAR || (line[j] <= '9' && line[j] >= '0') || line[j] == '-')
		{

			j += asm_checkind(line, j, data->op_tab[conv], i);
		}
		else if (line[j] == DIRECT_CHAR)
		{
			j += asm_checkdir(line, j, data->op_tab[conv], i);
		}
		else
		{
			asm_parse_file_error(data, &line, NULL);
		}
		while (line[j] && (line[j] == '\t' || line[j] == ' '))
			++j;
		++i;
	}
	if (line[j] == '\0' && count_sep_char != data->op_tab[conv].n_arg - 1)
	{
		asm_parse_file_error(data, &line, NULL);
	}
	return ((line)[j] == '\0' ? 1 : -1);
}

int		asm_checkcmd(char *line, int begin, t_asm *data)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while ((line + begin)[j] <= 'z' && (line + begin)[j] >= 'a')
		++j;
	while (++i < 16)
	{
		if (!ft_strncmp((line + begin), data->op_tab[i].cmd, j > data->op_tab[i].len ? j : data->op_tab[i].len))
			break ;
	}
	data->error_type = UNKNOWN_FUNCTION;
	if (i == 16)
		asm_parse_file_error(data, &line, NULL);
	j = 0;
	while ((line + begin)[j] == '\t' || (line + begin)[j] == ' ')
		++j;
	data->error_type = INVALID_ARGUMENT;
	if ((line + begin)[j] == '\0')
		asm_parse_file_error(data, &line, NULL);
	if (asm_checkargument(line, begin + j + data->op_tab[i].len, data, i) == -1)
		asm_parse_file_error(data, &line, NULL);
	data->error_type = 0;
	asm_addclist(data, line, begin + j + data->op_tab[i].len, i);
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
