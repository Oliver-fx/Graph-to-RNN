import torch
import torch.nn as nn
from torch_geometric.nn import NNConv
from torch_geometric.data import Data
from c_wrapper import genEdge, createGraph
from build_pygeo_graph import build_Graph
from NN_Structure import ECCPollution

model = ECCPollution()
state_dict = torch.load("ecc_pollution_model_40epochs_25datasets,01.pth")
model.load_state_dict(state_dict)
model.eval()

file = "test.txt"

g = createGraph(file)
next_pollutoin_list = torch.zeros((12, 1))
genEdge(g)
data = build_Graph(g, next_pollutoin_list)

with torch.no_grad():
    pred = model(data)

pred_denorm = pred * 2.542487382888794 + 2.8333332538604736
print("predictions:", pred_denorm)

