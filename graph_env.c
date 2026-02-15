#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph_env.h"

/*
struct graph {
    // num of station
    int nS;
    // 
    char area_name[100];
    struct adjNode **edges;
};

struct adjNode {
    int id;
    char S_name[100];
    int wind_dir;
    float wind_speed;
    float pollution_level;
    float temp;
    float humidity;
    float latitude;
    float longitude;
    struct edgeInfo e;
    struct adjNode *next;
};

struct edgeInfo {
    int dist;
    int compass_angle;
    float temp_lag;
};*/

struct node *newNode(double val, int id) {
    struct node *new = malloc(sizeof(struct node));
    new->id = id;
    new->val = val;
    new->next = NULL;
    return new;
}


Graph graphNew(char a_name[100]) {
    Graph g = malloc(sizeof(*g));

    g->nS = 0;
    strncpy(g->area_name, a_name, sizeof(g->area_name) - 1);
    g->area_name[sizeof(g->area_name) - 1] = '\0';
    g->edges = calloc(1000, sizeof(struct adjNode *));

    return g;
}



// connect id 2 to id 1
Graph man_add_edge(Graph g, int id1, int id2) {
    if (id1 == id2) {
        return g;
    }
    struct adjNode *curr = g->edges[id1];
    struct adjNode *id2_copy = copyNode(g->edges[id2]);

    int check = 0;
    while (curr != NULL) {
        if (curr->id == id2) {
            check = 1;
        }
        curr = curr->next;
    }

    curr = g->edges[id1];
    
    if (check == 0) {

        if (curr->next == NULL) {
            curr->next = id2_copy;
        } else {
            id2_copy->next = curr->next;
            curr->next = id2_copy;
        }
        // calculate the edgeinfo from id1 to id2 
        // e.g. compass_angle in id2 shoud be the
        // angle from id1 to id2
        // TODO
    
        id2_copy->e.compass_angle = wind_dir_index(curr->latitude, curr->longitude, id2_copy->latitude, id2_copy->longitude);
        id2_copy->e.dist = sqrt((curr->latitude - id2_copy->latitude) * (curr->latitude - id2_copy->latitude) +
                                (curr->longitude - id2_copy->longitude) * (curr->longitude - id2_copy->longitude));
    
        id2_copy->e.from_id = id1;
        id2_copy->e.to_id = id2;

        if (fabs(id2_copy->e.compass_angle - curr->wind_dir) <= 30) {
            id2_copy->e.temp_lag = id2_copy->e.dist / curr->wind_speed;
        } else {
            id2_copy->e.temp_lag = 1000;
        }

    }
    

    return g;
}

// delete id2 that is connected in id1
Graph man_delete_edge(Graph g, int id1, int id2) {
    if (id1 == id2) {
        return g;
    }
    struct adjNode *curr = g->edges[id1];
    struct adjNode *prev = NULL;
    while (curr != NULL) {
        if (curr->id == id2) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    prev->next = curr->next;
    free(curr);


    return g;

}




struct adjNode *copyNode(struct adjNode *node) {
    struct adjNode *new = malloc(sizeof(struct adjNode));
    new->id = node->id;
    strncpy(new->S_name, node->S_name, sizeof(node->S_name) - 1);
    new->S_name[sizeof(new->S_name) - 1] = '\0';

    new->wind_dir = node->wind_dir;
    new->wind_speed = node->wind_speed;
    new->pollution_level = node->pollution_level;
    new->temp = node->temp;
    new->humidity = node->humidity;
    new->latitude = node->latitude;
    new->longitude = node->longitude;

    new->e.from_id = -1;
    new->e.to_id = -1;

    // recalculate dist with new node
    new->e.dist = -1;
    // check how to calculate compass angle between two stations
    new->e.compass_angle = -1;
    // recalculate temp lag with new edge;
    new->e.temp_lag = -1;


    new->next = NULL;


    return new;

}


// implement read graph from txt file, implement create graph use kth smallest principle to create it, 
void add_station(Graph g, float latitude, float longitude, char name[100], float wind_dir, float wind_speed, float p_level, float temp, float humidity) {
    struct adjNode *newNode = malloc(sizeof(struct adjNode));

    newNode->id = g->nS;
    newNode->latitude = latitude;
    newNode->longitude = longitude;
    strncpy(newNode->S_name, name, sizeof(newNode->S_name) - 1);
    newNode->S_name[sizeof(newNode->S_name) - 1] = '\0';
    newNode->wind_dir = wind_dir;
    newNode->wind_speed = wind_speed;
    newNode->pollution_level = p_level;
    newNode->temp = temp;
    newNode->humidity = humidity;

    g->edges[g->nS] = newNode;

    g->nS++;
}

void clearListKeepHead(struct node *head) {
    struct node *current = head->next; // start after head
    struct node *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    // Reset head
    head->val = -1;
    head->id = -1;
    head->next = NULL;
}


void gen_edge(Graph g) {
    
    int num_s = g->nS;
    
    struct node *head = newNode(-1, -1);
    for (int i = 0; i < num_s; i++) {
        struct adjNode *curr = g->edges[i];
        for (int j = 0; j < num_s; j++) {
            struct adjNode *curr1 = g->edges[j];
            if (curr1->id != curr->id) {
                // calculate the dist between curr and curr1
                // store them in the list in descedning order
                // add first 3 into curr list

                // calculate dist
                double dist = sqrt((curr->latitude - curr1->latitude) * (curr->latitude - curr1->latitude) +
                                    (curr->longitude - curr1->longitude) * (curr->longitude - curr1->longitude));
                                    
                if (head->val == -1 && head->id == -1) {
                    head->val = dist;
                    head->id = curr1->id;
                } else {
                    // the list is in aescedning order
                    head = des_list(head, dist, curr1->id);
                }

            }

        }

        // int count = 0;
        // struct node *tmp = head;

        // while (tmp != NULL) {
        //     printf("list node: id=%d val=%f\n", tmp->id, tmp->val);
        //     tmp = tmp->next;
        //     count++;
        // }

        // printf("TOTAL LIST NODES = %d\n", count);

        struct node *l_curr = head;
        for (int r = 0; r < 3; r++) {
            int id1 = curr->id;
            int id2 = l_curr->id;
            double dist = l_curr->val;

            adj_add(g, id1, id2, dist);

            l_curr = l_curr->next;
        }

        // rewind link list
        // free the whole list
        clearListKeepHead(head);

    }


}



void adj_add(Graph g, int id1, int id2, double dist) {
    struct adjNode *curr2 = g->edges[id2];
    struct adjNode *curr1 = g->edges[id1];

    int check1 = 0;
    while (curr1 != NULL) {
        if (curr1->id == id2) {
            check1 = 1;
        }
        curr1 = curr1->next;
    }
    curr1 = g->edges[id1];

    if (check1 == 0) {
        struct adjNode *cpy_node2 = copyNode(curr2);
        cpy_node2->e.dist = dist;
        cpy_node2->e.from_id = id1;
        cpy_node2->e.to_id = id2;
        cpy_node2->e.compass_angle = wind_dir_index(curr1->latitude, curr1->longitude, cpy_node2->latitude, cpy_node2->longitude);
        if (fabs(curr1->wind_dir - cpy_node2->e.compass_angle) <= 30) {
            cpy_node2->e.temp_lag = cpy_node2->e.dist / curr1->wind_speed;
        } else {
            cpy_node2->e.temp_lag = 1000;
        }
        
        cpy_node2->next = curr1->next;
        curr1->next = cpy_node2;
    }
    
    int check2 = 0;
    while (curr2 != NULL) {
        if (curr2->id == id1) {
            check2 = 1;
        }
        curr2 = curr2->next;
    }
    curr2 = g->edges[id2];

    if (check2 == 0) {
        struct adjNode *cpy_node1 = copyNode(curr1);
        cpy_node1->e.dist = dist;
        cpy_node1->e.from_id = id2;
        cpy_node1->e.to_id = id1;
        cpy_node1->e.compass_angle = wind_dir_index(curr2->latitude, curr2->longitude, cpy_node1->latitude, cpy_node1->longitude);
        if (fabs(curr2->wind_dir - cpy_node1->e.compass_angle) <= 30) {
            cpy_node1->e.temp_lag = cpy_node1->e.dist / curr2->wind_speed;
        } else {
            cpy_node1->e.temp_lag = 1000;
        }
    
        cpy_node1->next = curr2->next;
        curr2->next = cpy_node1;
    }

}

int wind_dir_index(double lat1, double lon1,
                   double lat2, double lon2) {
    // degrees → radians
    double φ1 = lat1 * M_PI / 180.0;
    double φ2 = lat2 * M_PI / 180.0;
    double λ1 = lon1 * M_PI / 180.0;
    double λ2 = lon2 * M_PI / 180.0;

    // flat-map approximation
    double dx = (λ2 - λ1) * cos((φ1 + φ2) / 2.0);
    double dy = (φ2 - φ1);

    // bearing from north, clockwise
    double angle = atan2(dx, dy) * 180.0 / M_PI;
    angle = fmod(angle + 360.0, 360.0);

    double snapped = round(angle / 22.5) * 22.5;

    if (snapped >= 360.0)
        snapped = 0.0;

    return snapped;
}



struct node *des_list(struct node *head, double dist, int id) {
    if (head == NULL) {
        return newNode(dist, id);
    }

    if (dist > head->val) {
        struct node *new = newNode(dist, id);
        new->next = head;
        return new;
    }

    head->next = des_list(head->next, dist, id);

    return head;
}



