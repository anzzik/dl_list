/*
   This file is part of dl_list (double linked list) implementation. 
   Copyright (C) 2020 Anssi Kulju 

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static ListNode_t *list_node_new();
static ListNode_t *list_node_search(List_t *l, void *data);
static void list_node_free(List_t *l, ListNode_t *ln);

static ListNode_t *list_node_new()
{
	ListNode_t *ln;

	ln = malloc(sizeof(ListNode_t));
	ln->data = 0;
	ln->next = 0;
	ln->prev = 0;

	return ln;
}

static void list_node_free(List_t *l, ListNode_t *ln)
{
	if (!ln)
		return;

	if (ln == l->first)
		l->first = ln->next;

	if (ln == l->last)
		l->last = ln->prev;

	if (l->on_pop_cb)
		l->on_pop_cb(ln->data);

	free(ln);

	l->n_count--;
}

static ListNode_t *list_node_search(List_t *l, void *data)
{
	ListNode_t *ln;
	int	    r;

	ln = l->first;
	while (ln)
	{
		r = l->on_cmp_cb(ln->data, data);
		if (!r)
			return ln;

		ln = ln->next;
	}

	return 0;
}

List_t *list_new(ListType_t type, void *on_cmp_fn, void *on_pop_fn)
{
	List_t *l = malloc(sizeof(List_t));

	l->type = type;
	l->on_cmp_cb  = on_cmp_fn;
	l->on_pop_cb = on_pop_fn;
	l->first = 0;
	l->last = 0;
	l->n_count = 0;

	return l;
}

void list_push(List_t *l, void *data)
{
	ListNode_t *ln;

	ln = list_node_new();
	ln->data = data;

	if (!l->first)
	{
		l->first = ln;
		l->last = ln;
		return;
	}

	switch (l->type)
	{
		case STACK:
			l->first->prev = ln;
			ln->next = l->first;
			l->first = ln;
			break;

		case QUEUE:
			l->last->next = ln;
			ln->prev = l->last;
			l->last = ln;
			break;
	}

	l->n_count++;
}

int list_pop(List_t *l)
{
	ListNode_t *ln;

	if (!l->first)
		return -1;

	switch (l->type)
	{
		case STACK:
			ln = l->first->next;
			list_node_free(l, l->first);
			if (ln)
				ln->prev = 0;
			break;

		case QUEUE:
			ln = l->last->prev;
			list_node_free(l, l->last);
			if (ln)
				ln->next = 0;
			break;
	}

	return 0; 
}

int list_remove_node(List_t *l, void *data)
{
	ListNode_t *ln;

	ln = list_node_search(l, data);
	if (!ln)
		return -1;

	ln->prev->next = ln->next;
	ln->next->prev = ln->prev;
	list_node_free(l, ln);

	return 0;
}

void list_free(List_t* l)
{
	while (l->first)
		list_pop(l);

	free(l);
}

size_t list_count(List_t* l)
{
	return l->n_count;
}

void list_foreach(List_t *l, int reverse, void (*on_foreach_cb)(void*))
{
	ListNode_t *ln, *next;

	ln = l->first;
	if (reverse)
		ln = l->last;

	while (ln)
	{
		next = ln->next;
		if (reverse)
			next = ln->prev;

		on_foreach_cb(ln->data);
		ln = next;
	}
}

