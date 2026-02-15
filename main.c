#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_env.h"
#include "read_file.h"

void check_connection(Graph g);

int main (int argc, char *argv[]) {
    if (argc > 2) {
        return -1;
    }

    char file_name[100];
    strncpy(file_name, argv[1], sizeof(file_name) - 1);
    file_name[sizeof(file_name) - 1] = '\0';

    Graph g = readStation(file_name);

    // TODO
    // check first step read graph, check all teh functions in graph_env works properly
    printf("%s", g->area_name);
    // float lat = g->edges[1]->latitude;
    // float longi = g->edges[1]->longitude;
    // char s_name[100];
    // strncpy(s_name, g->edges[1]->S_name, sizeof(s_name) - 1);
    // s_name[sizeof(s_name) - 1] = '\0';
    // float w_dir = g->edges[1]->wind_dir;
    // float w_speed = g->edges[1]->wind_speed;
    // float p_level = g->edges[1]->pollution_level;
    // float hum = g->edges[1]->humidity;
    // float temp = g->edges[1]->temp;
    // printf("%f, %f, %s, %f, %f, %f, %f, %f\n", lat, longi, s_name, w_dir, w_speed, p_level, hum, temp);

    for (int i = 0; i < g->nS; i++) {
        if (g->edges[i] == NULL) {
            continue;   // skip empty nodes if any
        }

        float lat    = g->edges[i]->latitude;
        float longi  = g->edges[i]->longitude;

        char s_name[100];
        strncpy(s_name, g->edges[i]->S_name, sizeof(s_name) - 1);
        s_name[sizeof(s_name) - 1] = '\0';

        float w_dir  = g->edges[i]->wind_dir;
        float w_speed = g->edges[i]->wind_speed;
        float p_level = g->edges[i]->pollution_level;
        float hum     = g->edges[i]->humidity;
        float temp    = g->edges[i]->temp;

        int id = g->edges[i]->id;

        printf( "id %d: %f, %f, %s, %f, %f, %f, %f, %f\n",id, lat, longi, s_name, w_dir, w_speed, p_level, temp, hum);
    }



    // test gen_edge
    gen_edge(g);

    //check edges connection
    printf("/////\n");
    g = man_add_edge(g, 2, 3);
    check_connection(g);



    return 0;
}

void check_connection(Graph g) {

    struct adjNode *curr = g->edges[2];
    while (curr != NULL) {
        if (curr->next == NULL) {
            printf("id:%d", curr->id);
            printf("compass_angle: %d, dist: %f, from_id: %d, to_id: %d, temp_lag: %f ", curr->e.compass_angle, curr->e.dist, curr->e.from_id, curr->e.to_id, curr->e.temp_lag);
        } else {
            printf("id:%d ", curr->id);
            printf("root_node_wind: %f, compass_angle: %d, dist: %f, from_id: %d, to_id: %d, temp_lag: %f \n ",g->edges[10]->wind_dir, curr->e.compass_angle, curr->e.dist, curr->e.from_id, curr->e.to_id, curr->e.temp_lag);
        }
        curr = curr->next;
    }

}