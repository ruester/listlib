/*
    listlib - listlib.c

    Copyright (C) 2010 Matthias Ruester <ruester@molgen.mpg.de>
    Copyright (C) 2010 Max Planck Institute for Molecular Genetics

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

#include <stdlib.h>
#include <stdio.h>

#include "listlib.h"

/*
    IN:
        -
    OUT:
        allocates heap memory for a listlib_list structure
        exit if calloc fails
    RETURN:
        pointer to the allocated memory
 */
struct listlib_list *listlib_safe_create_list(void)
{
    struct listlib_list *l;

    if ((l = calloc(1, sizeof(struct listlib_list))) == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    return (l);
}

/*
    IN:
        -
    OUT:
        allocates heap memory for a listlib_list structure
    RETURN:
        pointer to the allocated memory
 */
struct listlib_list *listlib_create_list(void)
{
    return (calloc(1, sizeof(struct listlib_list)));
}

/*
    IN:
        l: listlib_list != NULL
    OUT:
        free(l)
    RETURN:
        number of elements in list
 */
unsigned long listlib_free_list(struct listlib_list *l)
{
    int count;

    count = l->count;
    free(l);

    return (count);
}

/*
    IN:
        l: listlib_list != NULL
        e: element != NULL and l contains e
    OUT:
        l \ e
    RETURN:
        element removed from list
 */
void *listlib_remove_element(struct listlib_list *l, void *e)
{
    struct listlib_element *h;

    h = e;

    if (h->prev == NULL)
        l->first = h->next;
    else
        h->prev->next = h->next;

    if (h->next == NULL)
        l->last = h->prev;
    else
        h->next->prev = h->prev;

    h->next = NULL;
    h->prev = NULL;

    l->count--;

    return (e);
}

/*
    IN:
        l: listlib_list != NULL
        e: element != NULL
    OUT:
        element is added at the end of the list
    RETURN:
        -
*/
void listlib_push(struct listlib_list *l, void *e)
{
    struct listlib_element *h;

    h = e;
    l->count++;

    if (l->first == NULL) {
        l->first = e;
        l->last = e;
        h->next = NULL;
        h->prev = NULL;
        return;
    }

    h->prev = l->last;
    h->next = NULL;
    l->last = e;
    h->prev->next = l->last;
}

/*
    IN:
        l: listlib_list != NULL
    OUT:
        last element of the list is removed
    RETURN:
        last element of the list
*/
void *listlib_pop(struct listlib_list *l)
{
    return (listlib_remove_element(l, l->last));
}

/*
    IN:
        l: listlib_list != NULL
        e: element != NULL
    OUT:
        element is added at the beginning of the list
    RETURN:
        -
*/
void listlib_unshift(struct listlib_list *l, void *e)
{
    struct listlib_element *h;

    h = e;
    l->count++;

    if (l->first == NULL) {
        l->first = e;
        l->last = e;
        h->next = NULL;
        h->prev = NULL;
        return;
    }

    h->next = l->first;
    h->prev = NULL;
    l->first = e;
    h->next->prev = l->first;
}

/*
    IN:
        l: listlib_list != NULL
    OUT:
        first element of the list is removed
    RETURN:
        first element of the list
*/
void *listlib_shift(struct listlib_list *l)
{
    return (listlib_remove_element(l, l->first));
}

/*
    IN:
        l: listlib_list != NULL
        e: listlib_element != NULL
    OUT:
        -
    RETURN:
        index of the element
*/
unsigned long listlib_index_of_element(struct listlib_list *l, void *e)
{
    unsigned long c;
    struct listlib_element *p;

    if (e == listlib_last(l))
        return (listlib_count(l));

    c = 1;

    p = listlib_first(l);

    while (p != NULL) {
        if (p == e)
            return (c);
        c++;
        p = p->next;
    }

    return (0);
}
