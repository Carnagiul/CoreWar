typedef struct	s_sdl_win
{
	int			w;
	int			h;
	char		*title;
}				t_sdl_win;

typedef struct	s_core_env
{
	struct s_sdl_win	win;
}				t_core_env;

void		set_win_width(char *argv, t_sdl_win *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
		ptr->w = ft_atoi(ptr);
	free_char_ss(split);
}

void		set_win_height(char *argv, t_sdl_win *ptr)
{
	char	**split;

	split = ft_strsplit(argv, '=');
	if (split[1])
		ptr->h = ft_atoi(ptr);
	free_char_ss(split);
}

t_core_env	*ft_init_env(int argc, char **argv)
{
	t_core_env	*env;
	int			i;

	env = ft_malloc(sizeof(*env));
	env->win = ft_malloc(sizeof(t_sdl_win));
	i = 0;
	env->win->w = 0;
	env->win->h = 0;
	env->win->title = NULL;
	while (++i < argc)
	{
		if (ft_strncmp(argv[i], "--width=", 8) == 0)
			set_win_width(argv[i], env->win);
		if (ft_strncmp(argv[i], "--height=", 9) == 0)
			set_win_height(argv[i], env->win);
	}
}

int		main(int argc, char **argv)
{
	t_core_env	*env;

	env = ft_init_env(argc, argv);
	env
}
