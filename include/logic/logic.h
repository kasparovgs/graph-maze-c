#ifndef LOGIC_H
#define LOGIC_H

int log_insert_vertex(Graph* graph, char* id, int type);
int log_insert_edge(Graph* graph, char* first, char* second);
int log_delete_vertex(Graph* graph, char* id);
int log_delete_edge(Graph* graph, char* first, char* second);
int log_change_type(Graph* graph, char* id, int type);
int log_find_exit(Graph* graph, char* id, char** exit_id, int* dist);
int log_dfs(Graph* graph, char* id, char** exit);
int log_shortest_path(Graph* graph, char* entr_id, char* exit_id, char*** path_id, int* len_path);
int log_print_graph(Graph* graph);
int log_pretty_save(Graph* graph, char* filename);

int log_read_from_file(Graph* graph, char* filename);
int log_save_to_file(Graph* graph, char* filename);
int do_normal_str(char* str, char*** arr);
char* get_str_from_file(FILE* file, int* end_flag);
void free_arr(char** arr, int len);
int is_upper(char* str, int i);

int log_dop_dfs(Graph* graph);
int log_dop_shortest_path(Graph* graph);
int log_dop_floyd_warshall(Graph* graph);

#endif