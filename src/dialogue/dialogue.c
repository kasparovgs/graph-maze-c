#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph/graph.h"
#include "dialogue/dialogue.h"
#include "logic/logic.h"

void print_options() {
	printf("*******************\n");
    printf("1. Добавление новой вершины.\n");
    printf("2. Вставить ребро между двумя вершинами.\n");
    printf("3. Удаление заданной вершины.\n");
    printf("4. Удаление заданного ребра.\n");
    printf("5. Изменение данных, асоциированных с заданной вершиной.\n");
    printf("6. Вывод графа в виде списков смежности.\n");
    printf("7. Красивый вывод в graphviz.\n");
    printf("8. Проверка достижимости хотя бы одного из выходов из указанной точки входа (поиск в глубину).\n");
    printf("9. Поиск кратчайшего пути между указанным входом и указанным выходом (алгоритм Дейкстры).\n");
    printf("10. Определение ближайшего, к указанному входу, выхода и расстояния до него (алгоритм Флойда-Уоршалла).\n");
    printf("11. Считать из текстового файла.\n");
    printf("12. Записать в текстовый файл.\n");
    printf("13. Дополнительное задание для поиска в глубину.\n");
    printf("14. Дополнительное задание для Дейкстры.\n");
    printf("15. Дополнительное задание для Флойда-Уоршалла.\n");
    printf("0. Завершение работы.\n");
}


const char* messages[] = {
    "Ошибка: проверьте корректность вводимых данных.\n",
    "Граф пустой.\n",
    "Вершина с введённым ID уже существует.\n",
    "Ребро уже существует.\n",
    "Введённые вершины совпадают. Ребро добавлено.\n",
    "Вершина успешно добавлена.\n",
    "Ребро успешно добавлено.\n",
    "Вершина удалена.\n",
    "Ребро удалено.\n",
    "Вершина не найдена.\n",
    "Как минимум одной из ведённых вершин не существует.\n",
    "Выходов не существует.\n",
    "Новый тип комнаты совпадает со старым.\n",
    "Тип комнаты обновлен.\n",
    "Проверьте корректность введённых типов комнат.\n",
    "Из указанного входа нет пути к выходу.\n",
    "Операция успешно выполнена.\n"
};


const int len_messages = sizeof(messages) / sizeof(messages[0]);


void dial_insert_vertex(Graph* graph) {
    printf("Введите ID комнаты: ");
    char* id = NULL;
    id = get_str();
    if (id == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int type = -1;
    printf("Введите тип комнаты:\n1. Начало\n2. Переход\n3. Конец\n");
    int check = get_int(&type);
    if (check == 1) {
        free(id);
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_insert_vertex(graph, id, type);
    printf("%s", messages[flag]);
    if (flag == DUPLICATE_VERTEX) {
        free(id);
    }
}


void dial_insert_edge(Graph* graph) {
    char* first = NULL;
    char* second = NULL;
    printf("Введите ID первой вершины: ");
    first = get_str();
    if (first == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    printf("Введите ID второй вершины: ");
    second = get_str();
    if (second == NULL) {
        free(first);
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_insert_edge(graph, first, second);
    printf("%s", messages[flag]);
    free(first);
    free(second);
}


void dial_delete_vertex(Graph* graph) {
    printf("Введите ID комнаты: ");
    char* id = NULL;
    id = get_str();
    if (id == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_delete_vertex(graph, id);
    printf("%s", messages[flag]);
    free(id);
}


void dial_delete_edge(Graph* graph) {
    char* first = NULL;
    char* second = NULL;
    printf("Введите ID первой вершины: ");
    first = get_str();
    if (first == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    printf("Введите ID второй вершины: ");
    second = get_str();
    if (second == NULL) {
        free(first);
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_delete_edge(graph, first, second);
    printf("%s", messages[flag]);
    free(first);
    free(second);
}


void dial_change_type(Graph* graph) {
    printf("Введите ID комнаты: ");
    char* id = NULL;
    id = get_str();
    if (id == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int type = -1;
    printf("Введите новый комнаты:\n1. Начало\n2. Переход\n3. Конец\n");
    int check = get_int(&type);
    if (check == 1) {
        free(id);
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int flag = log_change_type(graph, id, type);
    printf("%s", messages[flag]);
    free(id);
}


void dial_find_exit(Graph* graph) {
    printf("Введите ID комнаты: ");
    char* id = NULL;
    id = get_str();
    if (id == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    int dist = 0;
    char* exit_id = NULL;
    int flag = log_find_exit(graph, id, &exit_id, &dist);
    if (flag < len_messages - 1) {
        printf("%s", messages[flag]);
    }
    else {
        printf("Ближайший к комнате \"%s\" выход - \"%s\".\nДлина пути - %d.\n", id, exit_id, dist);
    }
    free(id);
}


void dial_dfs(Graph* graph) {
    printf("Введите ID комнаты: ");
    char* id = NULL;
    id = get_str();
    if (id == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    char* exit_id = NULL;
    int flag = log_dfs(graph, id, &exit_id);
    if (flag < len_messages - 1) {
        printf("%s", messages[flag]);
    }
    else {
        printf("Из входа \"%s\" можно выйти через выход \"%s\".\n", id, exit_id);
    }
    free(id);
}


void dial_shortest_path(Graph* graph) {
    printf("Введите ID входа: ");
    char* entr_id = NULL;
    entr_id = get_str();
    if (entr_id == NULL) {
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    printf("Введите ID выхода: ");
    char* exit_id = NULL;
    exit_id = get_str();
    if (exit_id == NULL) {
        free(entr_id);
        printf("Ошибка: введены некорректные данные.\n");
        return;
    }
    char** path_id = NULL;
    int len_path = 0;
    int flag = log_shortest_path(graph, entr_id, exit_id, &path_id, &len_path);
    if (flag < len_messages - 1) {
        printf("%s", messages[flag]);
    }
    else {
        printf("Длина пути из входа \"%s\" до выхода \"%s\" - %d.\n", entr_id, exit_id, len_path);
        print_path(path_id, len_path + 1);
    }
    free(path_id);
    free(entr_id);
    free(exit_id);
}


void dial_print_graph(Graph* graph) {
    int flag = log_print_graph(graph);
    printf("%s", messages[flag]);
}


void dial_pretty_save(Graph* graph) {
    char* filename = "test.dot";
    int flag = log_pretty_save(graph, filename);
    printf("%s", messages[flag]);
}


void print_path(char** path, int len) {
    for (int i = 0; i < len - 1; i++) {
        printf("\"%s\" -> ", path[i]);
    }
    printf("\"%s\".\n", path[len - 1]);
}


void dial_read_from_file(Graph* graph) {
    printf("Введите имя файла (c форматом): ");
    char* filename = get_str();
    if (filename == NULL) {
        printf("Ошибка: введите корректное имя файла.\n");
        return;
    }
    int flag = log_read_from_file(graph, filename);
    printf("%s", messages[flag]);
}


void dial_save_to_file(Graph* graph) {
    printf("Введите имя файла (c форматом): ");
    char* filename = get_str();
    if (filename == NULL) {
        printf("Ошибка: введите корректное имя файла.\n");
        return;
    }
    int flag = log_save_to_file(graph, filename);
    printf("%s", messages[flag]);
}


void dial_dop_dfs(Graph* graph) {
    int flag = log_dop_dfs(graph);
    if (flag < len_messages) {
        printf("%s", messages[flag]);
    }
    else {
        printf("Результаты успешно записаны в файл res_dfs.dot.\n");
        printf("Данные для парсинга записаны в файл res_dfs.yaml.\n");
    }
}


void dial_dop_shortest_path(Graph* graph) {
    int flag = log_dop_shortest_path(graph);
    if (flag < len_messages) {
        printf("%s", messages[flag]);
    }
    else {
        printf("Результаты успешно записаны в файл res_deijkstr.dot.\n");
        printf("Данные для парсинга записаны в файл res_deijkstra.yaml.\n");
    }
}


void dial_dop_floyd_warshall(Graph* graph) {
    int flag = log_dop_floyd_warshall(graph);
    if (flag < len_messages) {
        printf("%s", messages[flag]);
    }
    else {
        printf("Результаты успешно записаны в файл res_floyd_warshall.dot.\n");
        printf("Данные для парсинга записаны в файл res_floyd_warshall.yaml.\n");
    }
}


char* get_str() {
/*возвращает NULL, если EOF или пустая строка*/
    char* input = (char*)calloc(1, sizeof(char));
    char* buf = (char*)calloc(81, sizeof(char));
    int n, len = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            free(input);
            free(buf);
            input = NULL;
            return input;
        }
        if (n == 0) {
            scanf("%*c");
        }
        else {
            len += strlen(buf);
            input = (char*)realloc(input, (len + 1)*sizeof(char));
            strcat(input, buf);
    }
    } while(n > 0);
    free(buf);
    if (strlen(input) == 0) {
        free(input);
        return NULL;
    }
  return input;
}


int get_int(int* temp) {
/*функция для ввода целого числа от 0 до 2.
возвращает 1, если EOF, и 0, если всё хорошо*/
	int count = 0;
	int check = scanf("%d", temp);
	while (check != 1 || *temp < 1 || *temp > 3) {
		if (check == EOF) {
			return 1;
		}
		count += 1;
		printf("Введите число от 1 до 3!\n");
		scanf("%*[^\n]");
		scanf("%*c");
		check = scanf("%d", temp);
	}
	scanf("%*c");
	return 0;
}
