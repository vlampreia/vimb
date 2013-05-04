/**
 * vimb - a webkit based vim like browser.
 *
 * Copyright (C) 2012-2013 Daniel Carl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */

#ifndef _HISTORY_H
#define _HISTORY_H

typedef enum {
    HISTORY_FIRST   = 0,
    HISTORY_COMMAND = 0,
    HISTORY_SEARCH,
    HISTORY_URL,
    HISTORY_LAST
} HistoryType;

void history_cleanup(void);
void history_add(HistoryType type, const char *value);
GList *history_get_all(HistoryType type);
char *history_get(const char *input, gboolean prev);
void history_rewind(void);
void history_list_free(GList **list);

#endif /* end of include guard: _HISTORY_H */