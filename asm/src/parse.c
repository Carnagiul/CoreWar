#include <asm.h>

#include <stdio.h>

int	asm_header(char *line, t_asm *data, char *type, int toto)
{
//	char	*str;
	char	*tmp;
	int		len;

	len = (toto == 1 ? data->lname : data->lcom);
	if (ft_strncmp(line, type, len))
		return (0);
	if ((toto == 1 && data->name == 1) || (toto == 2 && data->comment == 1))
		return (-1);
	toto == 1 ? (data->name = 1) : (data->comment = 1);
//	str = ft_strsub(line, len, ft_strlen(line) - len);
	tmp = ft_strtrim(line + len);
//	ft_strdel(&str);
	len = ft_strlen(tmp) - 1;
	if (len > 0 && (tmp[0] != '"' || tmp[len] != '"'))
	{
		ft_strdel(&tmp);
		return (-1);
	}
//	str = ft_strsub(tmp, 1, len);
//	ft_strdel(&tmp);
	if (toto == 1)
		ft_strncpy(data->header->prog_name, tmp + 1, len - 1);
	else
		ft_strncpy(data->header->comment, tmp + 1, len - 1);
//	ft_strdel(&str);
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
	if (data->name == 0 || data->comment == 0)
		return (-1);
	label = NULL;
	j = 0;
	while (ft_strchr(LABEL_CHARS, line[j]))
		++j;
	if (line[j] == LABEL_CHAR)
		label = line + j;
	i = 0;
	if (label)
		i = asm_checklabel(line, label, data);
	if (i > -1)
	{
		j = 0;
		if (i == 1)
			j = label + 1 - line;
		while (line[j] && (line[j] == '\t' || line[j] == ' '))
			++j;
		i = line[j] == '\0' ? i : asm_checkcmd(line + j, data);
	}
	return (i);	
}

int	asm_check_new_line(char *nc, t_asm *data, int *error)
{
	int	i;
	int j;
	int l;
	int	err;

	l = -1;
	i = 0;
	j = 0;
	err = 0;
	*error = NLINE;
	if ((i = asm_header(nc, data, NAME_CMD_STRING, 1)) == -1)
		err = -1;
	*error = CLINE;
	if (!i && (j = asm_header(nc, data, COMMENT_CMD_STRING, 2)) == -1)
		err = -1;
	*error = data->line_error;
	if (!i && !j && (l = asm_instruction(nc, data)) <= -1)
		err = l;
//	ft_strdel(&nc);
	return (err <= -1 ? err : 1);
}

int	asm_parse_file(int fd, t_asm *data, int *error)
{
	char	*line1;
	char	*nc;
	int		err_type;

	line1 = NULL;
	if (!(line1 = (char *)malloc(sizeof(char))))
		return (MFAIL);
	while (get_next_line(fd, &line1) > 0)
	{
		data->str ? ft_strdel(&(data->str)) : NULL;
		data->str = ft_strdup(line1);
		*error = MFAIL;
		nc = NULL;
		if (!(nc = asm_removecomment(line1)))
		{
			ft_strdel(&line1);
			ft_strdel(&nc);
			return (-1 + 0 * close(fd) * get_next_line(fd, &line1));
		}
		data->error_char = NULL;
		ft_strdel(&line1);
		if ((err_type = asm_check_new_line(nc, data, error)) <= -1)
		{
			get_next_line(fd, &line1);
			ft_strdel(&line1);
			close(fd);
			ft_strdel(&nc);
			return (err_type);
		}
		ft_strdel(&nc);
		data->line_error++;
	}
	*error = 0 * close(fd) * get_next_line(fd, &line1);
	ft_strdel(&line1);
	return (1);
}
