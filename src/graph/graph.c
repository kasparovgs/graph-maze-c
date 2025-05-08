#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "graph/graph.h"
#include "table/table.h"
#include "stack/stack.h"

Graph* init_graph() {
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    return graph;
}


Node* init_node(Vertex* vertex) {
    Node* new = (Node*)calloc(1, sizeof(Node));
    new->vertex = vertex;
    return new;
}


Vertex* init_vertex(char* id, int type) {
    Vertex* new = (Vertex*)malloc(sizeof(Vertex));
    new->id = id;
    new->type = type;
    return new;
}


int insert_vertex(Graph* graph, char* id, int type) {
    List* current = graph->head;
    List* prev = NULL;
    while (current != NULL) {
        if (strcmp(id, current->vertex->id) == 0) {
            return DUPLICATE_VERTEX;
        }
        prev = current;
        current = current->next;
    }
    List* new_list_node = (List*)calloc(1, sizeof(List));
    if (current == graph->head) {
        graph->head = new_list_node;
    }
    else {
        prev->next = new_list_node;
    }
    Vertex* new_vertex = init_vertex(id, type);
    new_list_node->vertex = new_vertex;
    graph->size += 1;
    if (type == EXIT) {
        graph->count_exits += 1;
    }
    return VERTEX_ADDED;
}


int delete_vertex(Graph* graph, char* id) {
    List* current = graph->head;
    List* prev = NULL;
    Node* adj_node = NULL;
    Node* prev_adj_node = NULL;
    int flag = VERTEX_NOT_FOUND;
    Vertex* vertex_for_del = NULL;
    while (current != NULL) {
        /*в этом if удаляются все ноды с вершинами, которые
        смежны в заданной. сама удаляемая вершина записывается,
        а не чистится сразу, так как дальше используется для удаления*/
        if (strcmp(id, current->vertex->id) == 0) {
            graph->size -= 1;
            if (current->vertex->type == EXIT) {
                graph->count_exits -= 1;
            }
            flag = VERTEX_DELETED;
            adj_node = current->adjacent;
            prev_adj_node = NULL;
            while (adj_node != NULL) {
                prev_adj_node = adj_node;
                adj_node = adj_node->next;
                free(prev_adj_node);
            }
            if (prev == NULL) {
                graph->head = current->next;
            }
            else {
                prev->next = current->next;
            }
            vertex_for_del = current->vertex;
            List* current_next = current->next;
            free(current);
            current = current_next;
            continue;
        }
        adj_node = current->adjacent;
        prev_adj_node = NULL;
        /*в этом цикле while удаляется вершина не в своём списке смежности,
        то есть в списке, в котором она просто нода в list->adjacenty*/
        while (adj_node != NULL) {
            if (strcmp(id, adj_node->vertex->id) == 0) {
                if (prev_adj_node == NULL) {
                    current->adjacent = adj_node->next;
                }
                else {
                    prev_adj_node->next = adj_node->next;
                }
                free(adj_node);
                break;
            }
            prev_adj_node = adj_node;
            adj_node = adj_node->next;
        }
        prev = current;
        current = current->next;
    }
    if (flag == VERTEX_DELETED) {
    /*удаление самой вершины и её поля id*/
        free(vertex_for_del->id);
        free(vertex_for_del);
    }
    return flag;
}


int insert_edge(Graph* graph, char* first, char* second) {
    List* current = graph->head;
    List* list_first = NULL;
    List* list_second = NULL;
    while (current != NULL) {
        if (strcmp(current->vertex->id, first) == 0) {
            list_first = current;
        }
        if (strcmp(current->vertex->id, second) == 0) {
            list_second = current;
        }
        current = current->next;
    }
    if (list_first == NULL || list_second == NULL) {
        return VERTICES_NOT_FOUND; // хотя бы одной из введенных вершин не существует
    }

    Node* adj_first = list_first->adjacent;
    Node* prev_adj_first = NULL;
    while (adj_first != NULL) {
        if (strcmp(adj_first->vertex->id, second) == 0) {
            return DUPLICATE_EDGE;
        }
        prev_adj_first = adj_first;
        adj_first = adj_first->next;
    }
    Node* new_adj_first = init_node(list_second->vertex);
    if (prev_adj_first == NULL) {
        list_first->adjacent = new_adj_first;
    }
    else {
        prev_adj_first->next = new_adj_first;
    }
    if (list_first == list_second) {
        return MATCHING_VERTICES;
    }

    Node* adj_second = list_second->adjacent;
    Node* prev_adj_second = NULL;
    while (adj_second != NULL) {
        if (strcmp(adj_second->vertex->id, first) == 0) {
            return DUPLICATE_EDGE;
        }
        prev_adj_second = adj_second;
        adj_second = adj_second->next;
    }
    Node* new_adj_second = init_node(list_first->vertex);
    if (prev_adj_second == NULL) {
        list_second->adjacent = new_adj_second;
    }
    else {
        prev_adj_second->next = new_adj_second;
    }
    return EDGE_ADDED;
}


int delete_edge(Graph* graph, char* first, char* second) {
    List* current = graph->head;
    List* list_first = NULL;
    List* list_second = NULL;
    while (current != NULL) {
        if (strcmp(current->vertex->id, first) == 0) {
            list_first = current;
        }
        if (strcmp(current->vertex->id, second) == 0) {
            list_second = current;
        }
        current = current->next;
    }
    if (list_first == NULL || list_second == NULL) {
        return VERTICES_NOT_FOUND;
    }
    Node* adj_first = list_first->adjacent;
    Node* prev_adj_first = NULL;
    while (adj_first != NULL) {
        if (strcmp(adj_first->vertex->id, second) == 0) {
            if (adj_first == list_first->adjacent) {
                list_first->adjacent = adj_first->next;
            }
            else {
                prev_adj_first->next = adj_first->next;
            }
            free(adj_first);
            break;
        }
        prev_adj_first = adj_first;
        adj_first = adj_first->next;
    }
    if (list_first == list_second) {
        return EDGE_DELETED;
    }
    Node* adj_second = list_second->adjacent;
    Node* prev_adj_second = NULL;
    while (adj_second != NULL) {
        if (strcmp(adj_second->vertex->id, first) == 0) {
            if (adj_second == list_second->adjacent) {
                list_second->adjacent = adj_second->next;
            }
            else {
                prev_adj_second->next = adj_second->next;
            }
            free(adj_second);
            break;
        }
        prev_adj_second = adj_second;
        adj_second = adj_second->next;
    }
    return EDGE_DELETED;
}


int change_type(Graph* graph, char* id, int new_type) {
    List* current = find_vertex(graph, id);
    if (current == NULL) {
        return VERTEX_NOT_FOUND;
    }
    if (current->vertex->type == new_type) {
        return MATCHING_TYPES;
    }
    if (current->vertex->type == EXIT) {
        graph->count_exits -= 1;
    }
    else if (new_type == EXIT) {
        graph->count_exits += 1;
    }
    current->vertex->type = new_type;
    return TYPE_UPDATED;
}


int find_exit(Graph* graph, char* id, char** exit_id, int* dist) {
/*функция для определения ближайшего, к указанному входу,
выхода и расстояния до него с помощью алгоритма
Флойда-Уоршелла*/

    /*ищем заданную вершину. если не нашли - отказ
    если нашли - проверяем, является ли она входом.
    если нет - отказ*/
    
    List* entr = find_vertex(graph, id);
    if (entr == NULL) {
        return VERTEX_NOT_FOUND; // вершина не найдена
    }
    if (entr->vertex->type != ENTR) {
        return WRONG_TYPE; // вершина не является входом
    }
    if (graph->count_exits < 1) {
        return NO_EXITS; // выходов во всём графе не существует
    }

    Table* table = init_table(2 * graph->size);
    /*добавляем все вершины в хэш-таблицу, после чего
    проверяем есть ли коллизии. Если да, то расширяем до момента,
    пока коллизий нет*/
    List* current = graph->head;
    while (current != NULL) {
        add_node(table, current->vertex);
        current = current->next;
    }
    while (is_collision(table)) {
        int size = get_prime_num(get_msize(table));
        change_table(table, size);
    }

    int** matr_paths = init_matr_paths(graph, table);

    /*алгоритм Флойда-Уоршелла*/
    for (int k = 0; k < graph->size; k++) {
        for (int i = 0; i < graph->size; i++) {
            for (int j = 0; j < graph->size; j++) {
                if (matr_paths[i][k] != INT_MAX && matr_paths[k][j] != INT_MAX &&
                    (matr_paths[i][j] > matr_paths[i][k] + matr_paths[k][j])) {
                        matr_paths[i][j] = matr_paths[i][k] + matr_paths[k][j];
                }
            }
        }
    }

    int from = search_node(table, entr->vertex);
    int min_dist = INT_MAX;
    current = graph->head;
    Vertex* exit_vert = NULL;
    while (current != NULL) {
        if (current->vertex->type == EXIT) {
            int to = search_node(table, current->vertex);
            if (matr_paths[from][to] < min_dist) {
                min_dist = matr_paths[from][to];
                exit_vert = current->vertex;
            }
        }
        current = current->next;
    }
    int flag = PATH_NOT_FOUND;
    if (min_dist != INT_MAX) {
        *exit_id = exit_vert->id;
        *dist = min_dist;
        flag = OK;
    }
    free_table(table);
    for (int i = 0; i < graph->size; i++) {
        free(matr_paths[i]);
    }
    free(matr_paths);
    return flag;
}


int** init_matr_paths(Graph* graph, Table* table) {
/*функция инициализации матрицы путей*/
    /*сначала везде ставим INT_MAX, кроме главной диагонали*/
    int** matr_paths = (int**)malloc(graph->size*sizeof(int*));
    for (int i = 0; i < graph->size; i++) {
        matr_paths[i] = (int*)calloc(graph->size, sizeof(int));
    }
    for (int i = 0; i < graph->size; i++) {
        for (int j = 0; j < graph->size; j++) {
            if (i != j) {
                matr_paths[i][j] = INT_MAX;
            }
        }
    }

    /*добавляются смежности между вершинами*/
    List* current = graph->head;
    while (current != NULL) {
        Node* adj = current->adjacent;
        while (adj != NULL) {
            matr_paths[search_node(table, current->vertex)]
                      [search_node(table, adj->vertex)] = 1;
            adj = adj->next;
        }
        current = current->next;
    }
    return matr_paths;
}


int dfs(Graph* graph, char* id, char** exit) {
/*ищем заданную вершину. если не нашли - отказ
если нашли - проверяем, является ли она входом.
если нет - отказ*/
    List* entr = find_vertex(graph, id);
    if (entr == NULL) {
        return VERTEX_NOT_FOUND; // вершина не найдена
    }
    if (entr->vertex->type != ENTR) {
        return WRONG_TYPE; // вершина не является входом
    }
    if (graph->count_exits < 1) {
        return NO_EXITS; // выходов во всём графе не существует
    }
    Stack* stack = init_stack();
    Table* table_visited = init_table(2 * graph->size);
    stack_push(stack, entr);
    add_node(table_visited, entr->vertex);
    Stack* stack_adj = init_stack();
    while (!is_empty_stack(stack)) {
        List* poped = stack_pop(stack);
        if (poped->vertex->type == EXIT) { // выход найден
            *exit = poped->vertex->id;
            free_stack(stack);
            free_stack(stack_adj);
            free_table(table_visited);
            return OK;
        }
        Node* adj = poped->adjacent;
        while (adj != NULL) {
            if (search_node(table_visited, adj->vertex) == -1) { // вершина еще не просмотрена
                add_node(table_visited, adj->vertex);
                List* new = find_vertex(graph, adj->vertex->id);
                stack_push(stack_adj, new);
            }
            adj = adj->next;
        }

        while (!is_empty_stack(stack_adj)) {
            List* new = stack_pop(stack_adj);
            stack_push(stack, new);
        }
    }
    free_stack(stack);
    free_stack(stack_adj);
    free_table(table_visited);
    return PATH_NOT_FOUND;
}


int shortest_path(Graph* graph, char* entr_id, char* exit_id, char*** path_id, int* len_path) {
/*функция для поиска кратчайшего пути между двумя вершинами с помощью
алгоритма Дейкстры*/
    List* entr = find_vertex(graph, entr_id);
    if (entr == NULL) {
        return VERTICES_NOT_FOUND;
    }
    if (entr->vertex->type != ENTR) {
        return WRONG_TYPE;
    }
    List* exit = find_vertex(graph, exit_id);
    if (exit == NULL) {
        return VERTICES_NOT_FOUND;
    }
    if (exit->vertex->type != EXIT) {
        return WRONG_TYPE;
    }
    int* dist = (int*)malloc(graph->size*sizeof(int));
    for (int i = 0; i < graph->size; i++) {
        dist[i] = INT_MAX;
    }
    int* visited = (int*)calloc(graph->size, sizeof(int));
    Vertex** path = (Vertex**)calloc(graph->size, sizeof(Vertex*));
    Table* table = init_table(2 * graph->size);
    List* current = graph->head;
    while (current != NULL) {
        add_node(table, current->vertex);
        current = current->next;
    }
    dist[search_node(table, entr->vertex)] = 0;
    int min_dist = 0;
    for (int i = 0; i < graph->size - 1; i++) {
        List* min_list = get_min_dist(graph, table, dist, visited);
        visited[search_node(table, min_list->vertex)] = 1;
        int from = search_node(table, min_list->vertex);
        Node* adj = min_list->adjacent;
        while (adj != NULL) {
            int to = search_node(table, adj->vertex);
            if (!visited[to] && dist[from] != INT_MAX &&
                dist[from] + 1 < dist[to]) {
                    dist[to] = dist[from] + 1;
                    path[to] = min_list->vertex;
            }
            adj = adj->next;
        }
    }

    if (dist[search_node(table, exit->vertex)] == INT_MAX) {
        free(path);
        free_table(table);
        free(dist);
        free(visited);
        return PATH_NOT_FOUND;
    }
    *len_path = dist[search_node(table, exit->vertex)];
    *path_id = realloc(*path_id, (*len_path + 1)*sizeof(char**));
    Vertex* exit_vert = exit->vertex;
    int index = *len_path;
    while (exit_vert != NULL) {
        (*path_id)[index] = exit_vert->id;
        exit_vert = path[search_node(table, exit_vert)];
        index -= 1;
    }
    free(path);
    free_table(table);
    free(dist);
    free(visited);
    return OK;
}


List* get_min_dist(Graph* graph, Table* table, int* dist, int* visited) {
    List* current = graph->head;
    List* min_list = NULL;
    int min_dist = INT_MAX;
    while (current != NULL) {
        int index = search_node(table, current->vertex);
        if (!visited[index] && dist[index] <= min_dist) {
            min_dist = dist[index];
            min_list = current;
        }
        current = current->next;
    }
    return min_list;
}


List* find_vertex(Graph* graph, char* id) {
    List* current = graph->head;
    while (current != NULL) {
        if (strcmp(id, current->vertex->id) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


int print_graph(Graph* graph) {
    List* current = graph->head;
    while (current != NULL) {
        printf("Список смежности вершины \"%s\": ", current->vertex->id);
        Node* adj = current->adjacent;
        while (adj != NULL) {
            printf("\"%s\" ", adj->vertex->id);
            adj = adj->next;
        }        
        current = current->next;
        printf("\n");
    }
    return OK;
}


void pretty_save(Graph* graph, FILE* file) {
    List* current = graph->head;
    int pos = 0;
    int grid = (int)ceil(sqrt(graph->size));
    while (current != NULL) {
        int x = pos % grid;
        int y = pos / grid;
        Node* adj = current->adjacent;
        int type = current->vertex->type;
        fprintf(file, "\t\"%s\" [color=%s, pos=\"%d,%d!\"];\n", current->vertex->id, type == ENTR ? "green" : (type == EXIT ? "red" : "black"), x, y);
        while (adj != NULL) {
            if (strcmp(current->vertex->id, adj->vertex->id) <= 0) {
                fprintf(file, "\t\"%s\" -> \"%s\" [dir=none];\n", current->vertex->id, adj->vertex->id);
            }
            adj = adj->next;
        }
        pos += 1;
        current = current->next;
    }
}


void save_in_yaml(Graph* graph, FILE* file) {
    List* current = graph->head;
    fprintf(file, "vertices:\n");
    while (current != NULL) {
        fprintf(file, "    -    id: %s\n", current->vertex->id);
        fprintf(file, "         type: %d\n", current->vertex->type);
        current = current->next;
    }
    current = graph->head;
    fprintf(file, "edges:\n");
    while (current != NULL) {
        Node* adj = current->adjacent;
        while (adj != NULL) {
            fprintf(file, "    -    %s --- %s\n", current->vertex->id, adj->vertex->id);
            adj = adj->next;
        }
        current = current->next;
    }
}


int is_empty(Graph* graph) {
    return (graph->size == 0);
}


void free_graph(Graph* graph) {
    clear_graph(graph);
    free(graph);
}


void clear_graph(Graph* graph) {
    List* list = graph->head;
    List* prev_list = NULL;
    while (list != NULL) {
        Node* adj = list->adjacent;
        Node* prev = NULL;
        while (adj != NULL) {
            prev = adj;
            adj = adj->next;
            free(prev);
        }
        prev_list = list;
        list = list->next;
        free(prev_list->vertex->id);
        free(prev_list->vertex);
        free(prev_list);
    }
    graph->size = 0;
    graph->count_exits = 0;
    graph->head = NULL;
}


void save_to_file(Graph* graph, FILE* file) {
    List* current = graph->head;
    while (current != NULL) {
        fprintf(file, "%s %d\n", current->vertex->id, current->vertex->type);
        current = current->next;
    }
    current = graph->head;
    while (current != NULL) {
        Node* adj = current->adjacent;
        while (adj != NULL) {
            fprintf(file, "%s -- %s\n", current->vertex->id, adj->vertex->id);
            adj = adj->next;
        }
        current = current->next;
    }
}


char* get_id_by_index(Graph* graph, int index) {
    List* current = graph->head;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    if (current == NULL) {
        return NULL;
    }
    return current->vertex->id;
}


char* disconnected_exist(Graph* graph) {
    List* current = graph->head;
    while (current != NULL) {
        if (current->adjacent == NULL) {
            return current->vertex->id;
        }
        current = current->next;
    }
    return NULL;
}


char* get_entr(Graph* graph, char* entr) {
    static List* prev = NULL;
    List* current;
    if (entr == NULL) {
        current = graph->head;
    }
    else {
        current = prev;
    }
    while (current != NULL) {
        if (current->vertex->type == ENTR) {
            prev = current->next;
            return current->vertex->id;
        }
        current = current->next;
    }
    return NULL;
}


char* get_exit(Graph* graph, char* exit) {
    static List* prev = NULL;
    List* current;
    if (exit == NULL) {
        current = graph->head;
    }
    else {
        current = prev;
    }
    while (current != NULL) {
        if (current->vertex->type == EXIT) {
            prev = current->next;
            return current->vertex->id;
        }
        current = current->next;
    }
    return NULL;
}
