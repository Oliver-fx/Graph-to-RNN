import torch
import os
from c_wrapper import lib, createGraph, genEdge, manAddEdge, manDeleteEdge
from graph_helper import printGraph, readOneSample, read_res_pollution
from build_pygeo_graph import build_Graph
from graph_helper import getNumNodes
from NN_Structure import ECCPollution

def main():
    g = createGraph("test.txt")
    next_pollution = read_res_pollution("test_res.txt")
    genEdge(g)
    printGraph(g)
    print(next_pollution)


    num_nodes = getNumNodes(g)
    next_pollution = [0.0] * num_nodes
    data = build_Graph(g, next_pollution=next_pollution) # add parameters "next_pollution" to the function

    #read dir t_data and t_data_res
    t_data_list = sorted(os.listdir("t_data"))
    t_data_res_list = sorted(os.listdir("t_data_res"))

    # make those name into path
    files = [os.path.join("t_data", f) for f in t_data_list]
    res_files = [os.path.join("t_data_res", f) for f in t_data_res_list]

    print(t_data_list)
    print(t_data_res_list)
    print(files)
    print(res_files)

    print(data.is_undirected())
    print(data.num_nodes)
    print(data)
    
    #data = build_Graph(g, next_pollution)
    print(data.x.shape, data.edge_index.shape, data.edge_attr.shape, data.y.shape)

    model = ECCPollution(node_dim=data.x.shape[1], edge_dim=data.edge_attr.shape[1])
    model.eval()
    with torch.no_grad():
        out = model(data)
    print(out.shape)
    
    
    model = train(files, res_files)
    # After training
    torch.save(model.state_dict(), "ecc_pollution_model_40epochs_25datasets,01.pth")

    

def train(files, res_files, epochs=40, lr=0.01):
    model = ECCPollution()
    model.to(torch.device("cpu"))
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    criterion = torch.nn.MSELoss()

    for epoch in range(epochs):
        model.train()

        total_loss = 0.0

        for file, res_file in zip(files, res_files):
            next_pollution = read_res_pollution(res_file)
            next_pollution = torch.tensor(next_pollution, dtype=torch.float).view(-1, 1)
            g = createGraph(file)

            genEdge(g)

            #print("inside training loop")

            #printGraph(g)

            data = build_Graph(g, next_pollution)

            pred = model(data)

            #print(pred.shape)

            loss = criterion(pred, data.y)


            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            y_mean = next_pollution.mean()
            y_std = next_pollution.std()

            pred_denorm = pred  # since not normalized
            mae = torch.mean(torch.abs(pred_denorm - data.y))

            total_loss = total_loss + loss.item()
        print(f"Epoch {epoch+1}/{epochs}, Loss: {total_loss:.6f}, mae: {mae.item():.2f}, y_mean: {y_mean}, y_std: {y_std}")
    return model


if __name__ == "__main__":
    main()