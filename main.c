#include <ft_corewar.h>

typedef struct	s_sdl_win
{
	int			w;
	int			h;
	char		*title;
}				t_sdl_win;

typedef struct		s_champions
{
	t_header		header;
	int				fd;
}					t_champions;

typedef struct	s_core_env
{
	struct s_sdl_win	*win;
	int					n;
	int					dump;
	int					debug;
	int					champ_id;
	int					fd[4];
	int					error;
	struct s_champions	champions[4];
}				t_core_env;

int			bendian(int n)
{
	int		r;

	r = (n & 0xFF000000) / 0x1000000;
	r += (n & 0xFF0000) / 0x100;
	r += (n & 0xFF00) * 0x100;
	r += (n & 0xFF) * 0x10000;
	return (r);
}

void		set_win_width(char *argv, t_sdl_win *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
		ptr->w = ft_atoi(split[1]);
	free_char_ss(split);
}

void		set_win_height(char *argv, t_sdl_win *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
		ptr->h = ft_atoi(split[1]);
	free_char_ss(split);
}

void		set_win_title(char *argv, t_sdl_win *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
	{
		if (ptr->title != NULL)
			free(ptr->title);
		ptr->title = ft_strdup(split[1]);
	}
	free_char_ss(split);
}

void		set_dump_value(char *argv, t_core_env *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
		ptr->dump = ft_atoi(split[1]);
	free_char_ss(split);
}

void		set_n_value(char *argv, t_core_env *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
		ptr->n = ft_atoi(split[1]);
	free_char_ss(split);
}

int			insert_new_champion(char *file, t_core_env *env)
{
	int		fd;
	char	*ext;

	ext = ft_get_extension(file);
	if (ext && ft_strcmp(ext, "cor") != 0)
	{
		ft_strdel(&ext);
		return (2);
	}
	ft_strdel(&ext);
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (1);
	env->fd[env->champ_id] = fd;
	env->champ_id += 1;
	return (0);
}

t_core_env	*ft_init_env(int argc, char **argv)
{
	t_core_env	*env;
	int			i;
	int			ret;

	env = ft_malloc(sizeof(t_core_env));
	env->win = ft_malloc(sizeof(t_sdl_win));
	i = 0;
	env->n = 0;
	env->debug = 0;
	env->dump = 0;
	env->champ_id = 0;
	env->win->w = 0;
	env->win->h = 0;
	env->win->title = NULL;
	while (++i < argc)
	{
		ret = 0;
		if (ft_strncmp(argv[i], "--width=", 8) == 0)
			set_win_width(argv[i], env->win);
		else if (ft_strncmp(argv[i], "--height=", 9) == 0)
			set_win_height(argv[i], env->win);
		else if (ft_strncmp(argv[i], "--title=", 8) == 0)
			set_win_height(argv[i], env->win);
		else if (ft_strncmp(argv[i], "--debug", 7) == 0)
			env->debug = 1;
		else if (ft_strncmp(argv[i], "--dump=", 7) == 0)
			set_dump_value(argv[i], env);
		else if (ft_strncmp(argv[i], "--n=", 4) == 0)
			set_n_value(argv[i], env);
		else
			ret = insert_new_champion(argv[i], env);
		env->error = ret;
		if (ret >= 1)
			return (env);
	}
	if (env->win->h <= 0)
		env->win->h = 720;
	if (env->win->w <= 0)
		env->win->w = 1280;
	return (env);
}

int		ft_core_error(t_core_env *env)
{
	int	id;
	t_log	*lst;

	if (env->error == 1)
		lst = ft_log_create("main.c", 144, 2, "Erreur lors de l'ouverture du fichier. Il semblerait qu'il soit inexistant ou que l'on a pas les droits dessus...\n");
	if (env->error == 2)
		lst = ft_log_create("main.c", 144, 2, "Il semblerait que l'un des fichiers ne soit pas un fichier .cor...\n");
	if (env->error == 3)
		lst = ft_log_create("main.c", 144, 2, "Il semblerait que l'un des fichiers ne soit pas un fichier .cor...\n");
	id = 0;
	while (id < env->champ_id)
	{
		close(env->fd[id]);
		id++;
	}
	if (env->win->title)
		free(env->win->title);
	free(env->win);
	free(env);
	ft_log_display(lst);
	ft_log_del(lst);
	while (1)
		;
	return (0);
}

int		verify_header_champion(t_core_env *env)
{
	t_champions	*champion[4];
	int			i;
	t_header	h;

	i = 0;
	while (i < env->champ_id)
	{
		if (read(env->fd[i], &h, sizeof(t_header)) < (long)sizeof(t_header))
			return (2);
		h.magic = bendian(h.magic);
		h.prog_size = bendian(h.prog_size);
		if (h.magic != COREWAR_EXEC_MAGIC)
			return (2);
		if (h,prog_size > CHAMP_SIZE_MAX)
			return (2);
		env->champions[i].fd = env->fd[i];
		env->champions[i].header = h;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_core_env	*env;

	env = ft_init_env(argc, argv);
	if (env->error > 0)
		return (ft_core_error(env));
	verify_header_champion(env);
	for (int i = 0; i < env->champ_id; i++)
	{
		ft_printf("NEW CHAMPION LOAD :: \n");
		ft_printf("CHAMP NAME :: %s\n", env->champions[i].header.prog_name);
		ft_printf("CHAMP COMMENT :: %s\n", env->champions[i].header.comment);
		ft_printf("CHAMP SIZE :: %u\n", env->champions[i].header.prog_size);
	}
	while (1)
		;
	return (0);
}
