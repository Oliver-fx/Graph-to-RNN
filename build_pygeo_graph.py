import torch
from torch_geometric.data import Data
from c_wrapper import Graph
from data import extractEdge, extractNodeInfo

def build_Graph(g: Graph, next_pollution=None):
    x = extractNodeInfo(g)
    edgeIndex, edgeAttr = extractEdge(g)

    if next_pollution is not None:
        y = torch.tensor(next_pollution, dtype=torch.float).view(-1, 1)
        data = Data(x=x, edge_index=edgeIndex, edge_attr=edgeAttr, y=y)
    else:
        data = Data(x=x, edge_index=edgeIndex, edge_attr=edgeAttr)

    return data

