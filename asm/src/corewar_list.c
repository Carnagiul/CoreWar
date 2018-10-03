#include <asm.h>

int		asm_create_corlist(t_asm *data)
{
	t_clst	*new;
	t_clst	*tmp;

	new = NULL;
	new = (t_clst *)malloc(sizeof(t_clst));
	data->error_type = MFAIL;
	if (!new)
		return (asm_parse_file_error(data, NULL, NULL));
	new->opcode = data->cmd;
	new->nb_arg = data->nb_arg;
	new->ocparam = 0;
	new->arg[0] = data->arg[0];
	new->arg[1] = data->arg[1];
	new->arg[2] = data->arg[2];
	new->next = NULL;
	if (data->begin == NULL)
	{
		data->begin = new;
		data->begin->next = NULL;
		return (1);
	}
	tmp = data->begin;
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
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
}
