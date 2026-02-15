import torch
from c_wrapper import Graph
from graph_helper import getNumNodes, getIdHumidity, getIdPollution, getIdTemp, getIdWindDir, getIdWindSpeed, getIdLat, getIdLong

def extractNodeInfo(g: Graph):
    nodeFeatures = []

    num_nodes = getNumNodes(g)
    # re arrange the paramenters you want to take or res adjust the features in the 
    # nn struc that way is a bit sompler, they both alright, but this way could make 
    # the whole machine learning maybe more precise
    for i in range(num_nodes):
        lat = getIdLat(g, i)
        long = getIdLong(g, i)
        p = getIdPollution(g, i)
        t = getIdTemp(g, i)
        h = getIdHumidity(g, i)
        ws = getIdWindSpeed(g, i)
        wd = getIdWindDir(g, i)

        nodeFeatures.append([lat, long, p, t, h, ws, wd])


    x = torch.tensor(nodeFeatures, dtype=torch.float)

    return x

def extractEdge(g: Graph):
    fromList = []
    tolist = []
    edgeAttr = []

    num_nodes = getNumNodes(g)

    for i in range(num_nodes):
        curr = g.contents.edges[i]
        while curr:
            toId = curr.contents.e.to_id
            fromList.append(i)
            tolist.append(toId)

            dist = curr.contents.e.dist
            angle = curr.contents.e.compass_angle
            lag = curr.contents.e.temp_lag

            edgeAttr.append([dist, angle, lag])

            curr = curr.contents.next

    edgeIndex = torch.tensor([fromList, tolist], dtype=torch.long)

    edge_attr = torch.tensor(edgeAttr, dtype=torch.float)

    return edgeIndex, edge_attr



