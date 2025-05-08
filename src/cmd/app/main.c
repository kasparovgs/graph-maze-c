#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graph/graph.h"
#include "dialogue/dialogue.h"

int main() {
	srand(time(NULL));
    void (*menu[])(Graph*) = {NULL, dial_insert_vertex, dial_insert_edge,
		dial_delete_vertex, dial_delete_edge, dial_change_type, 
		dial_print_graph, dial_pretty_save, dial_dfs, dial_shortest_path, 
		dial_find_exit, dial_read_from_file, dial_save_to_file,
		dial_dop_dfs, dial_dop_shortest_path, dial_dop_floyd_warshall};
    int count_of_options = sizeof(menu)/sizeof(menu[0]);
	int option = -1;
    Graph* graph = init_graph();
	do {
		option = -1;
		print_options();
		int r = scanf("%d", &option);
		if (r == EOF) {
			free_graph(graph);
			return 1;
		}
		scanf("%*[^\n]");
		scanf("%*c");
		if (option >= 1 && option < count_of_options) {
			menu[option](graph);
		}
	} while(option != 0);
	free_graph(graph);
    return 0;
}
