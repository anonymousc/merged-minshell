#include "../includes/minishell.h"

void	gc_add(int mem_group_id, void *mem, t_memref **store_memref)
{
	t_memref	**mem_ref;
	t_memref	*new_mem_ref;
	t_memref	*curr;

	if (!mem)
		return ;
	new_mem_ref = ft_calloc(sizeof(t_memref), 1);
	if (!new_mem_ref)
	{
		free(mem);
		exit_minishell(12); 	
	}
	new_mem_ref->mem_data = mem;
	mem_ref = gc_get_memrefs(mem_group_id);
	if (!*mem_ref)
		*mem_ref = new_mem_ref;
	else
	{
		curr = *mem_ref;
		while (curr->next)
			curr = curr->next;
		curr->next = new_mem_ref;
	}
	if (store_memref)
		*store_memref = new_mem_ref;
}

void gc_add_double(int mem_group_id, void **mem, t_memref **store_memref)
{
	int i;

	i = 0;
	while (mem && mem[i])
	{
		gc_add(mem_group_id, mem[i], store_memref);
		i++;
	}
	gc_add(mem_group_id, mem, store_memref);
}

void	*gc_calloc(int mem_group_id, size_t count, size_t size,
		t_memref **store_memref)
{
	void	*mem;

	if (count != 0 && ULONG_MAX / count < size)
	{
		return (NULL);
	}
	mem = malloc(count * size);
	if (!mem)
		exit_minishell(12); 
	ft_bzero(mem, count * size);
	gc_add(mem_group_id, mem, store_memref);
	return (mem);
}

void	*gc_malloc(int mem_group_id, size_t size, t_memref **store_memref)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
		exit_minishell(12);
	gc_add(mem_group_id, mem, store_memref);
	return (mem);
}
