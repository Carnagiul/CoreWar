#ifndef ASM_H
# define ASM_H
# include <stdlib.h>
# include <libft.h>
# include <unistd.h>
# include <fcntl.h>
# include <op.h>
# include <stdint.h>
# include <stdio.h>

# define ENTRY 0
# define FORMAT 1
# define MFAIL 2

# define WFILE -1
# define NLINE -2
# define CLINE -3
# define INFILE -4


/*
struct	s_op
{
	const char		*cmd;
	uint8_t			n_arg;
	uint32_t		*arg;
	uint8_t			opc;
	uint16_t		cycles;
	const char		*desc;
	uint8_t			ocp;
	uint8_t			jane_doe;
};

typedef struct s_op t_op;*/

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

typedef struct s_asm t_asm;

int		asm_verify_entry(int ac, char **av);
int		asm_error(int toto, int err);
void	asm_get_optab(t_asm *data);

int		asm_verify_format(char *av, t_asm *data, int *toto);
t_asm	*asm_init_data();
int		asm_destroy_data(t_asm **data);
int		asm_header(char *line, t_asm *data, char *type, int toto);
int		asm_instruction(char *line, t_asm *data);
int		asm_parse_file(int fd, t_asm *data, int *error);
char	*asm_removecomment(char *line);

int		asm_checkvalidlabel(char *line, char *label);
int		asm_checkcmd(char *line, t_asm *data);
int		asm_checklabel(char *line, char *label, t_asm *data);
int		asm_check_new_line(char *nc, t_asm *data, int *error, int fd);

int		asm_checkargument(char *s, t_asm *data, int conv);
int		asm_checkreg(char *line, t_op cmd, int nb_arg);




#endif
