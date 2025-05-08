#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "table/table.h"

Table* init_table(int size) {
    Table* table = (Table*)calloc(1, sizeof(Table));
    table->ks = (KeySpace**)calloc(size, sizeof(KeySpace*));
    table->msize = size;
    return table;
}


void add_node(Table* table, Vertex* vertex) {
    int index = hash(vertex->id) % table->msize;
    KeySpace* new = (KeySpace*)malloc(sizeof(KeySpace));
    new->vertex = vertex;
    new->index = table->csize;
    table->csize += 1;
    KeySpace* temp = table->ks[index];
    if (temp != NULL) {
        table->is_collision = 1;
    }
    table->ks[index] = new;
    new->next = temp;
}


int search_node(Table* table, Vertex* vertex) {
/*функция для поиска записи в таблице.
возвращает индекс в МАТРИЦЕ СМЕЖНОСТИ/РАССТОЯНИЙ*/
    int index = hash(vertex->id) % table->msize;
    KeySpace* current = table->ks[index];
    while (current != NULL) {
        if (current->vertex == vertex) {
            return current->index;
        }
        current = current->next;
    }
    return -1;
}


int is_collision(Table* table) {
    return table->is_collision;
}


void free_table(Table* table) {
    clear_table(table);
    free(table->ks);
    free(table);
}


void clear_table(Table* table) {
    for (int i = 0; i < table->msize; i++) {
        KeySpace* current = table->ks[i];
        while (current != NULL) {
            KeySpace* prev = current;
            current = current->next;
            free(prev);
        }
        table->ks[i] = NULL;
    }
    table->csize = 0;
}


int hash(char* str) {
	int hash = INT_MAX;
    for (int i = 0; i < strlen(str); i++) {
		hash = 37 * hash + str[i];
	}
	return abs(hash);
}


int get_msize(Table* table) {
    return table->msize;
}


void change_table(Table* table, int new_size) {
    Table* new_table = init_table(new_size);
    table->csize = 0;
    table->is_collision = 0;
    for (int i = 0; i < table->msize; i++) {
        KeySpace* current = table->ks[i];
        while (current != NULL) {
            int index = hash(current->vertex->id) % new_size;
            KeySpace* prev = current;
            current = current->next;
            KeySpace* temp = new_table->ks[index];
            if (temp == NULL) {
                table->csize += 1;
            }
            else {
                table->is_collision = 1;
            }
            new_table->ks[index] = prev;
            prev->next = temp;
        }
    }
    free(table->ks);
    table->ks = new_table->ks;
    free(new_table);;
    table->msize = new_size;
}


int get_prime_num(int num) {
	if (num == 1 || num == 2) {
		return 3;
	}
	for (int i = num + 1; i < 5 * num; i++) {
		int flag = 0;
		for (int j = 2; j < i; j++) {
			if ((i%j) == 0) {
				flag = 1;
				break;
			}
		}
		if (flag != 1) {
			return i;
		}
	}
}
