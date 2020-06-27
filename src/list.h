/*
   This file is part of dl_list (double linked list) implementation. 
   Copyright (C) 2016 Anssi Kulju 

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

#ifndef LIST_H
#define LIST_H

typedef enum ListType_e ListType_t;
enum ListType_e
{
	STACK = 0,
	QUEUE
};

typedef struct ListNode_s ListNode_t;
struct ListNode_s
{
	void *data;

	ListNode_t *next, *prev;
};

typedef struct List_s List_t;
struct List_s
{
	ListNode_t *first;
	ListNode_t *last;
	ListType_t type;
	size_t n_count;
	int (*on_cmp_cb)(void*, void*);
	int (*on_pop_cb)(void*);
};

List_t *list_new(ListType_t type, void *on_cmp_fn, void *on_pop_fn);
void list_push(List_t *l, void *data);
int list_pop(List_t *l);
int list_remove_node(List_t *l, void *data);
void list_free(List_t* l);
void list_foreach(List_t *l, int reverse, void (*on_foreach_cb)(void*));
size_t list_count(List_t* l);

#endif

