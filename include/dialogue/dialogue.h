#ifndef DIALOGUE_H
#define DIALOGUE_H

void print_options();
char* get_str();
int get_int(int* temp);

void dial_insert_vertex(Graph* graph);
void dial_insert_edge(Graph* graph);
void dial_delete_vertex(Graph* graph);
void dial_delete_edge(Graph* graph);
void dial_change_type(Graph* graph);
void dial_dfs(Graph* graph);
void dial_shortest_path(Graph* graph);
void print_path(char** path, int len);
void dial_read_from_file(Graph* graph);
void dial_save_to_file(Graph* graph);
void dial_find_exit(Graph* graph);
void dial_print_graph(Graph* graph);
void dial_pretty_save(Graph* graph);

void dial_dop_dfs(Graph* graph);
void dial_dop_shortest_path(Graph* graph);
void dial_dop_floyd_warshall(Graph* graph);

#endif