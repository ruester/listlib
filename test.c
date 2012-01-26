/*
    listlib - test.c

    Copyright (C) 2010 Matthias Ruester <ruester@molgen.mpg.de>
    Copyright (C) 2010 Max Planck Institut for Molecular Genetics

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
#include "listlib.h"

struct my_type {
    struct listlib_element h;
    int a;
    float b;
};

struct type {
    struct listlib_element h;
    char c;
};

union un {
    struct my_type m;
    struct type t;
};

int main(int argc, char *argv[])
{
    struct listlib_list *l;
    struct my_type *test, *p;
    struct type *k, *q;
    struct listlib_element *h;
    union un *a, *t;
    int failed;

    if ((test = calloc(1, sizeof(struct my_type))) == NULL
        || (k = calloc(1, sizeof(struct type))) == NULL
        || (a = calloc(1, sizeof(union un))) == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    test->a = 1;
    test->b = 2.25;
    k->c = 'h';
    a->t.c = 'i';

    printf("testing listlib_create_list\t\t");
    fflush(stdout);

    if ((l = listlib_create_list()) == NULL) {
        perror("listlib_create_list");
        exit(EXIT_FAILURE);
    }

    if (l->first == NULL && l->last == NULL && l->count == 0)
        printf("success\n");
    else
        printf("failed\n");
    fflush(stdout);

    failed = 0;
    printf("testing listlib_push\t\t\t");
    fflush(stdout);

    listlib_push(l, k);

    if (l->count != 1)
        failed = 1;

    listlib_push(l, test);

    if (l->count != 2)
        failed = 1;

    listlib_push(l, a);

    if (l->count != 3)
        failed = 1;

    /* check if list was build right */
    h = l->first;

    if ((void *) h != k || (void *) h->next != test || h->prev != NULL)
        failed = 1;

    h = h->next;

    if ((void *) h != test || (void *) h->next != a
        || (void *) h->prev != k)
        failed = 1;

    h = l->last;

    if ((void *) h != a || h->next != NULL || (void *) h->prev != test)
        failed = 1;

    if (failed)
        printf("failed\n");
    else
        printf("success\n");
    fflush(stdout);

    failed = 0;
    printf("testing listlib_pop\t\t\t");
    fflush(stdout);

    if (l->count != 3)
        failed = 1;

    t = listlib_pop(l);

    if (l->count != 2)
        failed = 1;

    p = listlib_pop(l);

    if (l->count != 1)
        failed = 1;

    q = listlib_pop(l);

    if (t->t.c == 'i' && p->a == 1 && p->b == 2.25 && q->c == 'h'
        && l->first == NULL && l->last == NULL && l->count == 0 && !failed)
        printf("success\n");
    else
        printf("failed\n");
    fflush(stdout);

    test->a = 2;
    test->b = -216.75;
    k->c = '!';
    a->m.a = -1;
    a->m.b = -356.375;

    failed = 0;
    printf("testing listlib_unshift\t\t\t");
    fflush(stdout);

    if (l->count != 0)
        failed = 1;

    listlib_unshift(l, k);

    if (l->count != 1)
        failed = 1;

    listlib_unshift(l, test);

    if (l->count != 2)
        failed = 1;

    listlib_unshift(l, a);

    if (l->count != 3)
        failed = 1;

    h = l->first;

    if ((void *) h != a || h->prev != NULL || (void *) h->next != test)
        failed = 1;

    h = h->next;

    if ((void *) h != test || (void *) h->next != k
        || (void *) h->prev != a)
        failed = 1;

    h = l->last;

    if ((void *) h != k || h->next != NULL || (void *) h->prev != test)
        failed = 1;

    if (failed)
        printf("failed\n");
    else
        printf("success\n");
    fflush(stdout);

    failed = 0;
    printf("testing listlib_shift\t\t\t");
    fflush(stdout);

    if (l->count != 3)
        failed = 1;

    t = listlib_shift(l);

    if (l->count != 2)
        failed = 1;

    p = listlib_shift(l);

    if (l->count != 1)
        failed = 1;

    q = listlib_shift(l);

    if (t->m.a == -1 && t->m.b == -356.375 && p->a == 2
        && p->b == -216.75 && q->c == '!' && !failed
        && l->first == NULL && l->last == NULL && l->count == 0)
        printf("success\n");
    else
        printf("failed\n");
    fflush(stdout);

    listlib_push(l, k);
    listlib_unshift(l, test);
    listlib_push(l, a);

    failed = 0;
    printf("testing listlib_remove_element\t\t");
    fflush(stdout);

    if (l->count != 3)
        failed = 1;

    if (listlib_remove_element(l, k) != k)
        failed = 1;

    if (l->count != 2)
        failed = 1;

    h = l->first;
    if ((void *) h != test || (void *) h->next != a || h->prev != NULL)
        failed = 1;

    h = l->last;
    if ((void *) h != a || h->next != NULL || (void *) h->prev != test)
        failed = 1;

    if (listlib_remove_element(l, test) != test)
        failed = 1;

    if (l->count != 1)
        failed = 1;

    h = l->first;
    if ((void *) h != a || h->next != NULL || h->prev != NULL)
        failed = 1;

    h = l->last;
    if ((void *) h != a || h->next != NULL || h->prev != NULL)
        failed = 1;

    if (listlib_remove_element(l, a) != a)
        failed = 1;

    if (l->first != NULL || l->last != NULL || l->count != 0)
        failed = 1;

    if (failed)
        printf("failed\n");
    else
        printf("success\n");

    listlib_push(l, test);
    listlib_push(l, k);
    listlib_unshift(l, a);

    failed = 0;
    printf("testing listlib_free_list\t\t");
    fflush(stdout);

    if (listlib_free_list(l) != 3)
        printf("failed\n");
    else
        printf("success\n");
    fflush(stdout);

    printf("testing listlib_safe_create_list\t");
    fflush(stdout);

    l = listlib_safe_create_list();
    if (l == NULL)
        printf("failed\n");
    else
        printf("success\n");
    fflush(stdout);

    failed = 0;
    printf("testing listlib_index_of_element\t");
    fflush(stdout);

    listlib_push(l, test);
    listlib_push(l, k);
    listlib_push(l, a);

    if (listlib_index_of_element(l, test) != 1)
        failed = 1;

    if (listlib_index_of_element(l, k) != 2)
        failed = 1;

    if (listlib_index_of_element(l, a) != 3)
        failed = 1;

    if (failed)
        printf("failed\n");
    else
        printf("success\n");

    failed = 0;
    printf("testing macros\t\t\t\t");

    if (listlib_first(l) != test)
        failed = 1;

    if (listlib_last(l) != a)
        failed = 1;

    if (listlib_next(test->h) != k)
        failed = 1;

    if (listlib_prev(test->h) != NULL)
        failed = 1;

    if (listlib_next(k->h) != a)
        failed = 1;

    if (listlib_prev(k->h) != test)
        failed = 1;

    if (listlib_next(a->t.h) != NULL)
        failed = 1;

    if (listlib_prev(a->t.h) != k)
        failed = 1;

    if (failed)
        printf("failed\n");
    else
        printf("success\n");

    listlib_free_list(l);

    free(test);
    free(k);
    free(a);

    printf("program terminated\n");
    fflush(stdout);

    return (0);
}
