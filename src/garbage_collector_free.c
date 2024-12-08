#include "../includes/minishell.h"

void	gc_free_memrefs(t_memref *mem_ref)
{
	t_memref	*tmp;

	if (!mem_ref)
		return ;
	while (mem_ref)
	{
		tmp = mem_ref;
		mem_ref = mem_ref->next;
		free(tmp->mem_data);
		tmp->mem_data = NULL;
		free(tmp);
	}
}

void	gc_free_specific_memref(t_memref **mem_ref_head,
		t_memref *mem_ref_to_free)
{
	t_memref	*curr;
	t_memref	*prev;

	if (!mem_ref_head || !mem_ref_to_free)
		return ;
	curr = *mem_ref_head;
	prev = NULL;
	while (curr)
	{
		if (curr == mem_ref_to_free)
		{
			if (prev)
				prev->next = curr->next;
			else
				*mem_ref_head = curr->next;
			free(curr->mem_data);
			curr->mem_data = NULL;
			free(curr);
			curr = NULL;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_memgrp(int mem_group_id)
{
	t_memgroup	**mem_groups;
	t_memgroup	*prev;
	t_memgroup	*current;

	mem_groups = gc_get_memgroups();
	current = *mem_groups;
	prev = NULL;
	while (current)
	{
		if (current->id == mem_group_id)
		{
			if (prev)
				prev->next = current->next;
			else
				*mem_groups = current->next;
			gc_free_memrefs(current->mem_refs);
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	gc_free_all(void)
{
	t_memgroup	**mem_groups;
	t_memgroup	*current;
	t_memgroup	*tmp;

	mem_groups = gc_get_memgroups();
	current = *mem_groups;
	while (current)
	{
		tmp = current;
		current = current->next;
		gc_free_memrefs(tmp->mem_refs);
		free(tmp);
	}
	*mem_groups = NULL;
}
