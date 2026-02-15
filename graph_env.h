#ifndef GRAPH_H
#define GRAPH_H

struct graph {
    // num of station
    int nS;
    // 
    char area_name[100];
    struct adjNode **edges;
};

struct edgeInfo {
    int from_id;
    int to_id;
    double dist;
    int compass_angle;
    float temp_lag;
};

struct adjNode {
    int id;
    char S_name[100];
    float wind_dir;
    float wind_speed;
    float pollution_level;
    float temp;
    float humidity;
    float latitude;
    float longitude;
    struct edgeInfo e;
    struct adjNode *next;
};

struct node {
    int id;
    double val;
    struct node *next;
};


typedef struct graph *Graph;

struct node *newNode(double val, int id);

Graph graphNew(char a_name[100]);

// connect id 2 to id 1
Graph man_add_edge(Graph g, int id1, int id2);

// delete id2 that is connected in id1
Graph man_delete_edge(Graph g, int id1, int id2);

void add_station(Graph g, float latitude, float longitude, char name[100], float wind_dir, float wind_speed, float p_level, float temp, float humidity);

struct adjNode *copyNode(struct adjNode *node);

void clearListKeepHead(struct node *head);

void gen_edge(Graph g);

struct node *des_list(struct node *head, double dist, int id);

void adj_add(Graph g, int id1, int id2, double dist);

int wind_dir_index(double lat1, double lon1, double lat2, double lon2);

#endif