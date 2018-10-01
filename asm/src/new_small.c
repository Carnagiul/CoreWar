#include <push_swap.h>
#include <stdio.h>

int		sorted_small(t_push **params)
{
	int		tab[(*params)->max_size];
	int		len;
	int		i;
	int		j;
	int		tmp;

	len = (int)(*params)->max_size;
	i = -1;
	while (++i < len)
		tab[i] = (*params)->taba[i];
	i = 0;
	while (++i < len)
	{
		j = i - 1;
		while (tab[i] < tab[j])
			--j;
		if (j != i - 1)
		{
			tmp = tab[i];
			while (i > j)
			{
				tab[i] = tab[i - 1];
				--i;
			}
			tab[j] = tmp;
		}
	}
	push_min_max_b(tab[0], tab[len - 1], params);
}

/*
	idee : on a une liste triee en parallele
	min 1 && min 2 push sur b - pb pb + quelques ra
	if swap utile -> swap;
	exemple : 4 1 3 2 5 -> ra 1 3 2 5 4
	pb -> 3 2 5 4 -> ra 2 5 4 3
	pb -> 5 4 3 -> sa 4 5 3 -> ra 3 4 5
	pa -> 2 3 4 5
	pa -> 1 2 3 4 5
	total : 8
	exemple : 1 5 2 4 3
	pb -> 5 2 4 3 -> ra 2 4 3 5
	pb -> 4 3 5 -> sa 3 4 5
	pa -> 2 3 4 5
	pa -> 1 2 3 4 5
	total : 6
	toujours check dans la liste triee si swap utile : 
	Comment ?
		on trouve le numero actuel dans tab[i] et on regarde si tab[i + 1] == numero actuel - 1
			si oui : on swap
			sinon : on push ou on rotate
*/
