#ifndef GRAPH_H
#define GRAPH_H


typedef struct Table Table;

typedef enum Type {
    ENTR = 1,
    CONT,
    EXIT
} Type;

typedef enum Errors {
    EMPTY_GRAPH = 1,
    DUPLICATE_VERTEX,
    DUPLICATE_EDGE,
    MATCHING_VERTICES,
    VERTEX_ADDED,
    EDGE_ADDED,
    VERTEX_DELETED,
    EDGE_DELETED,
    VERTEX_NOT_FOUND,
    VERTICES_NOT_FOUND,
    NO_EXITS,
    MATCHING_TYPES,
    TYPE_UPDATED,
    WRONG_TYPE,
    PATH_NOT_FOUND,
    OK,
} Errors;

typedef struct Vertex {
    char* id;
    int type;
} Vertex;

typedef struct Node {
    Vertex* vertex;
    struct Node* next; //указатель на след вершину в списке вершин
} Node;


typedef struct List { //список вершин
    Vertex* vertex;
    Node* adjacent;
    struct List* next;
} List;

typedef struct Graph {
    int size;
    int count_exits;
    List* head;
} Graph;

Graph* init_graph();
Node* init_node(Vertex* vertex);
Vertex* init_vertex(char* id, int type);
int print_graph(Graph* graph);
int insert_vertex(Graph* graph, char* id, int type);
List* find_vertex(Graph* graph, char* id);
int delete_vertex(Graph* graph, char* id);
int delete_edge(Graph* graph, char* first, char* second);
int insert_edge(Graph* graph, char* first, char* second);
int change_type(Graph* graph, char* id, int new_type);
int find_exit(Graph* graph, char* id, char** exit_id, int* dist);
int dfs(Graph* graph, char* id, char** exit);
int shortest_path(Graph* graph, char* entr_id, char* exit_id, char*** path_id, int* len_path);
int** init_matr_paths(Graph* graph, Table* table);
List* get_min_dist(Graph* graph, Table* table, int* dist, int* visited);
void pretty_save(Graph* graph, FILE* file);

void save_to_file(Graph* graph, FILE* file);
void save_in_yaml(Graph* graph, FILE* file);
char* get_id_by_index(Graph* graph, int index);
char* disconnected_exist(Graph* graph);
char* get_entr(Graph* graph, char* entr);
char* get_exit(Graph* graph, char* exit);

int is_empty(Graph* graph);

void free_graph(Graph* graph);
void clear_graph(Graph* graph);

#endif