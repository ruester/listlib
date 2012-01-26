/*
    listlib - listlib.h

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

#ifndef LISTLIB_LIST_H
#define LISTLIB_LIST_H

struct listlib_element {
    struct listlib_element *next, *prev;
};

struct listlib_list {
    void *first, *last;
    unsigned long count;
};

extern struct listlib_list *listlib_safe_create_list(void);
extern struct listlib_list *listlib_create_list(void);

extern unsigned long listlib_free_list(struct listlib_list *);

extern void *listlib_remove_element(struct listlib_list *, void *);

extern void listlib_push(struct listlib_list *, void *);
extern void *listlib_pop(struct listlib_list *);

extern void listlib_unshift(struct listlib_list *, void *);
extern void *listlib_shift(struct listlib_list *);

extern unsigned long listlib_index_of_element(struct listlib_list *,
                                              void *);

#define listlib_first(l) ((l)->first)
#define listlib_last(l)  ((l)->last)

#define listlib_next(e) ((void *) (e).next)
#define listlib_prev(e) ((void *) (e).prev)

#define listlib_count(l) ((l)->count)

#endif
