#include <asm.h>

#include <stdio.h>

int	asm_header(char *line, t_asm *data, char *type, int toto)
{
	char	*tmp;
	int		len;

	len = (toto == 1 ? data->lname : data->lcom);
	if (ft_strncmp(line, type, len))
		return (0);
	if ((toto == 1 && data->name == 1) || (toto == 2 && data->comment == 1))
	{
		ft_strdel(&line);
		asm_error(toto == 1 ? CHAMPION_NAME_ERROR : COMMENT_ERROR, NULL, data);
	}
	toto == 1 ? (data->name = 1) : (data->comment = 1);
	tmp = ft_strtrim(line + len);
	len = ft_strlen(tmp) - 1;
	if (len > 0 && (tmp[0] != '"' || tmp[len] != '"'))
	{
		ft_strdel(&tmp);
		ft_strdel(&line);
		asm_error(toto == 1 ? CHAMPION_NAME_ERROR : COMMENT_ERROR, NULL, data);
	}
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
	if (data->name == 0 || data->comment == 0)
		return (data->name == 0 ? CHAMPION_NAME_ERROR : COMMENT_ERROR);
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
		i = (line[j] == '\0' ? i : asm_checkcmd(line, j, data));
	}
	return (i);	
}

int	asm_check_new_line(char *nc, t_asm *data)
{
	int	i;
	int j;
	int l;
	int	err;

	l = -1;
	i = 0;
	j = 0;
	err = 0;
	if ((i = asm_header(nc, data, NAME_CMD_STRING, 1)) == -1)
		err = -1;
	if (!i && (j = asm_header(nc, data, COMMENT_CMD_STRING, 2)) == -1)
		err = -1;
	if ((!i && !j && (l = asm_instruction(nc, data)) <= -1) || l == CHAMPION_NAME_ERROR || l == COMMENT_ERROR)
		err = l;
	return (err <= -1 || l == CHAMPION_NAME_ERROR || l == COMMENT_ERROR ? err : 1);
}

void	asm_parse_file_error(t_asm *data, char **line, char **nc)
{
	ft_strdel(nc);
	ft_strdel(line);
	close(data->fd);
	get_next_line(data->fd, line);
	asm_error(data->error_type <= -1 ? UNKNOWN_FUNCTION : data->error_type, NULL, data);
}

void	asm_exit_success(t_asm *data)
{
	asm_write_color("\033[1;32m", ft_strlen("\033[1;32m"), 1);
	ft_putstr("Generating Corewar file for ");
	ft_putendl(data->dot_s_name);
	asm_write_color("\033[0m", ft_strlen("\033[0m"), 1);
	asm_destroy_data(&data);
	exit(EXIT_SUCCESS);
}

int	asm_parse_file(t_asm *data)
{
	char	*line1;
	char	*nc;

	line1 = NULL;
	if (!(line1 = (char *)malloc(sizeof(char))))
		asm_error(MFAIL, NULL, data);
	while (get_next_line(data->fd, &line1) > 0)
	{
		ft_strdel(&(data->str));
		data->str = ft_strdup(line1);
		nc = NULL;
		if (!(nc = asm_removecomment(line1)))
		{
			data->error_type = -1;
			asm_parse_file_error(data, &line1, &nc);
		}
		data->error_char = NULL;
		if ((data->error_type = asm_check_new_line(nc, data)) <= -1)
			asm_parse_file_error(data, &line1, &nc);
		if (data->error_type == CHAMPION_NAME_ERROR || data->error_type == COMMENT_ERROR)
			asm_parse_file_error(data, &line1, &nc);
		ft_strdel(&nc);
		data->line_error++;
	}
	close(data->fd);
	ft_strdel(&line1);
	get_next_line(data->fd, &line1);
	ft_strdel(&line1);
	asm_exit_success(data);
	return (1);
}
