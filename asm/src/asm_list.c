#include <asm.h>

/*
struct s_clst
{
	char			*str;
	int				len;
	struct s_clst	*prec;
	struct s_clst	*next;
};

typedef struct s_clst t_clst;

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
	t_clst		*lst;
};

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
*/

/*
*	ACTUELLEMENT :
*
*	TESTS en little endian -- 
*
*	TESTS avec gestion de label : si label dans commande on met 1
*
*	TESTS avec indirect = valeur direct
*/

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
	int 	neg;

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
		if ((line + begin)[j] == 'r' || (line + begin)[j] == DIRECT_CHAR)
		{
			if ((line + begin)[j] == 'r')
				ocp |= 1;
			else if ((line + begin)[j] == DIRECT_CHAR)
				ocp |= 2;
			++j;
		}
		else
			ocp |= 3;
		if ((!(op.arg[i] & T_REG) && (ocp & 1) == 1)
			|| (!(op.arg[i] & T_DIR) && (ocp & 2) == 1)
			|| (!(op.arg[i] & T_IND) && (ocp & 1) == 1 && (ocp & 2) == 1))
		{
			ft_strdel(&line);
			asm_error(INVALID_ARGUMENT, NULL, data);
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
