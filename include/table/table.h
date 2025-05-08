#ifndef TABLE_H
#define TABLE_H

#include "graph/graph.h"

typedef struct KeySpace {
    Vertex* vertex;
    int index; // индекс в матрице смежности/расстояний
    struct KeySpace* next;
} KeySpace;

typedef struct Table {
    KeySpace** ks;
    int is_collision;
    int msize;
    int csize;
} Table;

Table* init_table(int table_size);
int is_collision(Table* table);
void print_table(Table* table);
void free_table(Table* table);

void add_node(Table* table, Vertex* vertex);
int search_node(Table* table, Vertex* vertex);
void clear_table(Table* table);
int hash(char* key);
int get_msize(Table* table);
void change_table(Table* table, int new_size);

int get_prime_num(int num);

#endif