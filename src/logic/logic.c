#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph/graph.h"
#include "logic/logic.h"
#define DELIM " "

int log_insert_vertex(Graph* graph, char* id, int type) {
    int flag = insert_vertex(graph, id, type);
    return flag;
}


int log_insert_edge(Graph* graph, char* first, char* second) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = insert_edge(graph, first, second);
    return flag;
}


int log_delete_vertex(Graph* graph, char* id) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = delete_vertex(graph, id);
    return flag;
}


int log_delete_edge(Graph* graph, char* first, char* second) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = delete_edge(graph, first, second);
}


int log_change_type(Graph* graph, char* id, int type) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = change_type(graph, id, type);
    return flag;
}


int log_find_exit(Graph* graph, char* id, char** exit_id, int* dist) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = find_exit(graph, id, exit_id, dist);
    return flag;
}


int log_dfs(Graph* graph, char* id, char** exit) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = dfs(graph, id, exit);
    return flag;
}


int log_shortest_path(Graph* graph, char* entr_id, char* exit_id, char*** path_id, int* len_path) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = shortest_path(graph, entr_id, exit_id, path_id, len_path);
    return flag;
}


int log_print_graph(Graph* graph) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    int flag = print_graph(graph);
    return flag;
}


int log_pretty_save(Graph* graph, char* filename) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(file);
        return 0;
    }
    fprintf(file, "digraph Maze{\n");
    fprintf(file, "\trankdir=LR;\n");
    pretty_save(graph, file);
    fprintf(file, "}");
    fclose(file);
    return OK;
}


int log_save_to_file(Graph* graph, char* filename) {
    if (is_empty(graph)) {
        free(filename);
        return EMPTY_GRAPH;
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(file);
        free(filename);
        return 0;
    }
    save_to_file(graph, file);
    fclose(file);
    free(filename);
    return OK;
}


int log_read_from_file(Graph* graph, char* filename) {
    clear_graph(graph);
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        free(file);
        free(filename);
        return 0;
    }
    int count = 0;
    int end_flag = 0;
    while (end_flag != -1) {
        char* str = NULL;
        char** arr_words = NULL;
        str = get_str_from_file(file, &end_flag);
        if (end_flag == -1) {
            continue;
        }
        int len = do_normal_str(str, &arr_words);
        if (len == 2) {
            int type = atoi(arr_words[1]);
            if (type < 1 || type > 3) {
                free_arr(arr_words, len);
                continue;
            }
            free(arr_words[1]);
            int flag = insert_vertex(graph, arr_words[0], type);
            if (flag == 1) {
                free(arr_words[0]);
            }
        }
        else {
            insert_edge(graph, arr_words[0], arr_words[2]);
            free(arr_words[0]);
            free(arr_words[1]);
            free(arr_words[2]);
        }
        free(arr_words);
        count += 1;
    }
    fclose(file);
    free(filename);
    return OK;
}


int do_normal_str(char* str, char*** arr) {
/*на вход получает строку и адрес вектора указателей.
из строки str с помощью strtok'а разбивает её по
словам, каждое слово приводит к нижнему регистру и 
добавляет в вектор. возвращает количество добавленных
в массив слов (длину вектора)*/
    int size = 0;
    int len = strlen(str);
    char* word = NULL;
    word = strtok(str, DELIM);
    while (word != NULL) {
        size += 1;
        *arr = realloc(*arr, size * sizeof(char*));
        (*arr)[size - 1] = strdup(word);
        word = strtok(NULL, DELIM);
    }
    for (int i = 0; i < size; i++) {
        char* word = (*arr)[i];
        for(int k = 0; k < strlen(word); k++) {
            if (is_upper(word, k)) {
                word[k] += 32;
            }
        }
    }
    free(str);
    return size;
}


char* get_str_from_file(FILE* file, int* end_flag) {
	char* input = (char*)calloc(1, sizeof(char));
	char* buf = (char*)calloc(21, sizeof(char));
	int n, len = 0;
	do {
        n = fscanf(file, "%20[^\n]", buf);
        if (n < 0) {
            free(input);
            free(buf);
            input = NULL;
            *end_flag = -1;
            return input;
        }
        if (n == 0) {
            fscanf(file, "%*c");
        }
        else {
            len += strlen(buf);
            input = (char*)realloc(input, (len + 1)*sizeof(char));
            strcat(input, buf);
        }
    } while(n > 0);
	free(buf);
	if (strlen(input)==0) {
		free(input);
		return NULL;
	}
	return input;
}


void free_arr(char** arr, int len) {
    for (int i = 0; i < len; i++) {
        free(arr[i]);
    }
    free(arr);
}


int is_upper(char* str, int i) {
    return (str[i]>64 && str[i]<91);
}


int log_dop_dfs(Graph* graph) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    char* entr = get_entr(graph, NULL);
    char* exit = NULL;
    while (entr != NULL) {
        int flag = dfs(graph, entr, &exit);
        if (flag == OK) {
            break;
        }
        entr = get_entr(graph, entr);
    }
    char* filename = "res_dfs.dot";
    char* filename_yaml = "res_dfs.yaml";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(file);
        return 0;
    }
    fprintf(file, "digraph Maze{\n");
    fprintf(file, "\trankdir=LR;\n");
    pretty_save(graph, file);
    fprintf(file, "\t\"%s\" -> \"%s\" [color=orange, penwidth=2, headclip=false];\n", entr, exit);
    fprintf(file, "}");
    fclose(file);
    file = fopen(filename_yaml, "w");
    if (file == NULL) {
        free(file);
        return 0;
    }
    save_in_yaml(graph, file);
    fprintf(file, "dfs:\n");
    fprintf(file, "    -   from: %s\n", entr);
    fprintf(file, "        to: %s\n", exit);
    fclose(file);
    return 100;
}


int log_dop_shortest_path(Graph* graph) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    char* entr = get_entr(graph, NULL);
    int flag = -5;
    char** path_id = NULL;
    int len = 0;
    while (entr != NULL && flag == -5) {
        char* exit = get_exit(graph, NULL);
        while (exit != NULL) {
            flag = shortest_path(graph, entr, exit, &path_id, &len);
            if (flag != PATH_NOT_FOUND) {
                break;
            }
            exit = get_exit(graph, exit);
        }
        entr = get_entr(graph, entr);
    }
    char* filename = "res_deijkstra.dot";
    char* filename_yaml = "res_deijkstra.yaml";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(file);
        return 0;
    }
    fprintf(file, "digraph Maze{\n");
    fprintf(file, "\trankdir=LR;\n");
    pretty_save(graph, file);
    for (int i = 0; i < len; i++) {
        char* first = path_id[i];
        char* second = path_id[i + 1];
        fprintf(file, "\t\"%s\" -> \"%s\" [color=orange, penwidth=2, headclip=false];\n", first, second);
    }
    fprintf(file, "}");
    fclose(file);
    file = fopen(filename_yaml, "w");
    if (file == NULL) {
        free(file);
        free(path_id);
        return 0;
    }
    save_in_yaml(graph, file);
    fprintf(file, "deijkstra:\n");
    fprintf(file, "    -   from: %s\n", path_id[0]);
    fprintf(file, "        to: %s\n", path_id[len]);
    fprintf(file, "        len: %d\n", len);
    fprintf(file, "        path: ");
    for (int i = 1; i < len; i++) {
        fprintf(file, "%s -> ", path_id[i]);
    }
    fprintf(file, "%s\n", path_id[len]);
    fclose(file);
    free(path_id);
    return 100;
}


int log_dop_floyd_warshall(Graph* graph) {
    if (is_empty(graph)) {
        return EMPTY_GRAPH;
    }
    char* entr = get_entr(graph, NULL);
    char* exit = NULL;
    int len = 0;
    while (entr != NULL) {
        int flag = find_exit(graph, entr, &exit, &len);
        if (flag == OK) {
            break;
        }
        entr = get_entr(graph, entr);
    }
    if (exit == NULL) {
        return NO_EXITS;
    }
    char* filename = "res_floyd_warshall.dot";
    char* filename_yaml = "res_floyd_warshall.yaml";
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        free(file);
        return 0;
    }
    fprintf(file, "digraph Maze{\n");
    fprintf(file, "\trankdir=LR;\n");
    pretty_save(graph, file);
    fprintf(file, "\t\"%s\" -> \"%s\" [color=orange, penwidth=2, headclip=false];\n", entr, exit);
    fprintf(file, "}");
    fclose(file);
    file = fopen(filename_yaml, "w");
    if (file == NULL) {
        free(file);
        return 0;
    }
    save_in_yaml(graph, file);
    fprintf(file, "dfs:\n");
    fprintf(file, "    -   from: %s\n", entr);
    fprintf(file, "        to: %s\n", exit);
    fprintf(file, "        len: %d\n", len);
    fclose(file);
    return 100;
}
