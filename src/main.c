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


/* This file is only for testing the list library */

#include <stdio.h>
#include "list.h"

void int_foreach(void *d)
{
	printf("foreach: %d\n", *(int*)d);
}

int int_cmp(void *a, void *b)
{
	if (*(int*)a > *(int*)b)
		return 1;
	else if (*(int*)a < *(int*)b)
		return -1;
	
	return 0;
}

void free_data_cb(void *data)
{
	printf("on pop: %d\n", *(int*)data);
}

int main(void)
{
	List_t *l;
	int	a, b, c, d, e;
       
	l = list_new(STACK, int_cmp, free_data_cb);
	/* l = list_new(STACK, int_cmp, free_data_cb); */

	a = 12;
	b = 40;
	c = 5;
	d = 29;
	e = 39;

	list_push(l, &a);
	list_push(l, &b);
	list_push(l, &c);
	list_push(l, &d);
	list_push(l, &e);

	list_foreach(l, 0, int_foreach);

	list_free(l);

	return 0;
}

