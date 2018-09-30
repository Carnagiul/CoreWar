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
#define INVALID_LABEL 900

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
	int			fd; // file descriptor
	char		*str; // current line
	int			str_size; // not used yet
	char		*dot_s_name; // file name
	char		*dot_cor_name; // cor file name
	size_t		filelen; // not used yet
	header_t	*header; // not used yet
	t_op		op_tab[17]; // tab with all the operations
	int			name; // indicator of name encounter
	int			comment; // indicator of comment encounter
	int			lname; // name length
	int			lcom; // comment length
	int			line_error; // line that contains an error
	t_clst		*lst; // not used yet
	int			error_type; // type of error
	int			error_one; // not used yet
	char		*error_char; // not used yet
	int			cmd; // current instruction found
	int			ocp; // calculated ocp
	int			nb_arg; // number of arguments
	int			arg[3]; // arguments value
	int			arg_type[3]; // types of arguments 1 == reg, 2 == dir, 3 == ind
	int			label_in_arg[3]; // which arg has a label
	char		*labels[3]; // label names in arg
};

typedef struct s_asm t_asm;

int		asm_verify_entry(int ac, char **av, int i);
void	asm_get_optab(t_asm *data);

int		asm_verify_format(t_asm *data);
t_asm	*asm_init_data();
int		asm_destroy_data(t_asm **data);
int		asm_header(char *line, t_asm *data, char *type, int toto);
int		asm_instruction(char *line, t_asm *data);
int		asm_parse_file(t_asm *data);
char	*asm_removecomment(char *line);

int		asm_checkvalidlabel(char *line, char *label);
int		asm_checkcmd(char *line, int begin, t_asm *data);
int		asm_checklabel(char *line, char *label, t_asm *data);
int		asm_check_new_line(char *nc, t_asm *data);

int		asm_checkargument(char *s, int begin, t_asm *data, int conv);
int		asm_checkreg(char *line, int begin, t_op cmd, int nb_arg, t_asm *data);
int		asm_checkind(char *line, int begin, t_op cmd, int nb_arg);
int		asm_checkdir(char *line, int begin, t_op cmd, int nb_arg);
int		asm_addclist(t_asm *data, char *line, int begin, int conv);

void	asm_write_color(char *color, int len, int output); // should be in libft -- uses isatty function -- this a color bonus therefore this is allowed -- checking tty is better in case you want to use a log file

void	asm_parse_file_error(t_asm *data, char **line, char **nc);

void	asm_error(int toto, char *str, t_asm *data);
void	asm_error_format_line(int format, t_asm *data);
void	asm_error_format_name_comment(int format, t_asm *data);
void	asm_gcc_format_error(char *str);


#endif
