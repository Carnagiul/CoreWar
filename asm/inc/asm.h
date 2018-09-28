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


#define NO_FILE 100
#define TOO_MANY_FILES 200
#define WRONG_EXTENSION 300
#define FILE_NO_OPEN 400
#define CHAMPION_NAME_ERROR 500
#define COMMENT_ERROR 600
#define UNKNOWN_FUNCTION 700
#define INVALID_ARGUMENT 800


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
	int			fd;
	char		*str; // current line
	int			str_size; // not used yet
	char		*dot_s_name; // file name
	size_t		filelen; // not used yet
	header_t	*header; // not used yet
	t_op		op_tab[17]; // tab with all the operations
	int			name; // indicator of name encounter
	int			comment; // indicator of comment encounter
	int			lname; // name length
	int			lcom; // comment length
	int			line_error; // line that contains an error number
	t_clst		*lst; // not used yet
	int			err_type;
	int			error_one;
	char		*error_char;
};

typedef struct s_asm t_asm;

int		asm_verify_entry(int ac, char **av);
int		asm_error(int toto, char *str, t_asm *data);
void	asm_get_optab(t_asm *data);

int		asm_verify_format(t_asm *data, int *toto);
t_asm	*asm_init_data();
int		asm_destroy_data(t_asm **data);
int		asm_header(char *line, t_asm *data, char *type, int toto);
int		asm_instruction(char *line, t_asm *data);
int		asm_parse_file(t_asm *data, int *error);
char	*asm_removecomment(char *line);

int		asm_checkvalidlabel(char *line, char *label);
int		asm_checkcmd(char *line, t_asm *data);
int		asm_checklabel(char *line, char *label, t_asm *data);
int		asm_check_new_line(char *nc, t_asm *data, int *error);

int		asm_checkargument(char *s, t_asm *data, int conv);
int		asm_checkreg(char *line, t_op cmd, int nb_arg);
int		asm_checkind(char *line, t_op cmd, int nb_arg);
int		asm_checkdir(char *line, t_op cmd, int nb_arg);
int		asm_addclist(t_asm *data, char *line, int conv);
void	asm_write_color(char *color, int len, int output);

void	asm_parse_file_error(t_asm *data, char **line, char **nc, int error);


#endif
