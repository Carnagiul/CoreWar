#include <asm.h>

void	asm_set_corlist(t_asm *data, t_clst **new)
{	
	int		i;

	(*new)->opcode = data->cmd;
	(*new)->nb_arg = data->nb_arg;
	(*new)->ocparam = data->ocp;
	i = -1;
	while (++i < 3)
	{
		(*new)->arg[i] = data->arg[i];
		(*new)->arg_type[i] = data->arg_type[i];
	}
}

int		asm_create_corlist(t_asm *data)
{
	t_clst	*new;
	t_clst	*tmp;

	new = NULL;
	data->error_type = MFAIL;
	if (!(new = (t_clst *)malloc(sizeof(t_clst))))
		return (asm_parse_file_error(data, NULL, NULL));
	asm_set_corlist(data, &new);
	new->next = NULL;
	if (data->begin == NULL)
	{
		data->begin = new;
		data->begin->next = NULL;
		return (1);
	}
	tmp = data->begin;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp->next->next = NULL;
	return (1);
}

void	asm_destroy_corlist(t_asm *data)
{
	t_clst	*lst;
	t_clst	*tmp;

	lst = data->begin;
	while (lst && lst->next)
	{
		tmp = lst->next;
		free(lst);
		lst = NULL;
		lst = tmp;
	}
	free(lst);
	lst = NULL;
	data->begin = NULL;
}
