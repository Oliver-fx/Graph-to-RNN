import torch
from torch_geometric.nn import NNConv

class ECCPollution(torch.nn.Module):
    def __init__(self, node_dim=7, edge_dim=3, hidden_dim=64):
        super().__init__()

        self.edge_mlp1 = torch.nn.Sequential(
            torch.nn.Linear(edge_dim, 32),
            torch.nn.ReLU(),
            torch.nn.Dropout(0.2),
            torch.nn.Linear(32, node_dim * hidden_dim)
        )

        self.edge_mlp2 = torch.nn.Sequential(
            torch.nn.Linear(edge_dim, 32),
            torch.nn.ReLU(),
            torch.nn.Dropout(0.2),
            torch.nn.Linear(32, 1 * hidden_dim)
        )

        self.conv1 = NNConv(node_dim, hidden_dim, self.edge_mlp1)
        self.conv2 = NNConv(hidden_dim, 1, self.edge_mlp2)


    def forward(self, data):
        x = data.x
        edge_index = data.edge_index
        edge_attr = data.edge_attr

        x = self.conv1(x, edge_index, edge_attr)
        x = torch.relu(x)
        x = self.conv2(x, edge_index, edge_attr)

        return x