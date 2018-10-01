#include <asm.h>

int		asm_header(char *line, t_asm *data, char *type, int toto)
{
	char	*tmp;
	int		len;

	len = (toto == 1 ? data->lname : data->lcom);
	if (ft_strncmp(line, type, len))
		return (0);
	data->error_type = (toto == 1 ? CHAMPION_NAME_ERROR : COMMENT_ERROR);
	if ((toto == 1 && data->name == 1) || (toto == 2 && data->comment == 1))
		return (asm_parse_file_error(data, &line, NULL));
	tmp = ft_strtrim(line + len);
	len = ft_strlen(tmp) - 1;
	if (len > 0 && (tmp[0] != '"' || tmp[len] != '"'))
		return (asm_parse_file_error(data, &line, &tmp));
	data->name = (toto == 1 ? 1 : data->name);
	data->comment = (toto == 2 ? 1 : data->comment);
	if (toto == 1)
		ft_strncpy(data->header->prog_name, tmp + 1, len - 1);
	else
		ft_strncpy(data->header->comment, tmp + 1, len - 1);
	ft_strdel(&tmp);
	return (1);
}

int		asm_instruction(char *line, t_asm *data)
{
	int		i;
	int		j;
	char	*label;

	if (!ft_strcmp(line, ""))
		return (0);
	data->error_type = data->name == 0 ? CHAMPION_NAME_ERROR : COMMENT_ERROR;
	if (data->name == 0 || data->comment == 0)
		return (asm_parse_file_error(data, &line, NULL));
	label = NULL;
	j = 0;
	while (ft_strchr(LABEL_CHARS, line[j]))
		++j;
	if (line[j] == LABEL_CHAR)
		label = line + j;
	i = 0;
	if (label)
		i = asm_checklabel(line, label, data);
	if (i < 0)
		return (-1);
	j = (i == 1 ? label + 1 - line : 0);
	while (line[j] && (line[j] == '\t' || line[j] == ' '))
		++j;
	i = (line[j] == '\0' ? i : asm_checkcmd(line, j, data));
	return (i);
}

int		asm_check_new_line(char *nc, t_asm *data)
{
	int		i;

	i = 0;
	if ((i = asm_header(nc, data, NAME_CMD_STRING, 1)) == 0)
		if ((i = asm_header(nc, data, COMMENT_CMD_STRING, 2)) == 0)
			if ((i = asm_instruction(nc, data)) >= 0)
				return (1);
	return (i < 0 ? -1 : 1);
}

int		asm_parse_file_error(t_asm *data, char **line, char **nc)
{
	ft_strdel(nc);
	ft_strdel(line);
	close(data->fd);
	get_next_line(data->fd, line);
	asm_error(data->error_type, NULL, data);
	return (-1);
}

int		asm_parse_file(t_asm *data)
{
	char	*nc;
	char	*line;

	ft_strdel(&(data->str));
	if (!(data->str = (char *)malloc(sizeof(char))))
		asm_error(MFAIL, NULL, data);
	while (get_next_line(data->fd, &(data->str)) > 0)
	{
		data->error_type = MFAIL;
		data->error_char = NULL;
		nc = NULL;
		line = ft_strdup(data->str);
		if (!(nc = asm_removecomment(data->str)))
			return (asm_parse_file_error(data, &line, &nc));
		ft_strdel(&line);
		if (asm_check_new_line(nc, data) != 1)
			return (-1);
		ft_strdel(&nc);
		data->line_error++;
	}
	close(data->fd);
	ft_strdel(&(data->str));
	get_next_line(data->fd, &(data->str));
	asm_exit_success(data);
	return (1);
}
