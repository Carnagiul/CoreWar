#include <asm.h>

/*

typedef struct		s_op
{
	const char		*cmd;
	uint8_t			n_arg;
	uint32_t		arg[3];
	uint8_t			opc;
	uint16_t		cycles;
	const char		*desc;
	uint8_t			ocp;
	uint8_t			carry;
	uint8_t			len;		
} t_op;

struct s_asm
{
	char		*str;
	int			str_size;
	size_t		filelen;
	header_t	*header;
	t_op		op_tab[17];
	int			name;
	int			comment;
	int			lname;
	int			lcom;
	int			line_error;
};

*/

#include <stdio.h>

t_asm	*asm_init_data(void)
{
	t_asm	*data;

	if (!(data = ft_memalloc(sizeof(t_asm))))
		return (NULL);
	data->header = NULL;
	data->header = (header_t *)ft_memalloc(sizeof(header_t));
	if (!(data->header))
	{
		asm_destroy_data(&data);
		return (NULL);
	}
	data->str = NULL;
	ft_bzero(data->header->prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(data->header->comment, COMMENT_LENGTH + 1);
	data->filelen = 0;
	data->name = 0;
	data->comment = 0;
	data->lname = ft_strlen(NAME_CMD_STRING);
	data->lcom = ft_strlen(COMMENT_CMD_STRING);
	data->line_error = 0;
	data->lst = NULL;
	data->error_type = 0;
	data->error_one = 0;
	data->error_char = NULL;
	data->cmd = 0;
	data->ocp = 0;
	data->nb_arg = 0;
	asm_get_optab(data);
	return (data);
}

int		asm_destroy_data(t_asm **data)
{
	if (data)
		if (*data)
		{
			ft_strdel(&((*data)->str));
			ft_memdel((void **)&((*data)->header));
			ft_memdel((void **)data);
		}
	return (0);
}