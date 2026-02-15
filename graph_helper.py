from c_wrapper import Graph, AdjNode, EdgeInfo, createGraph

def printGraph(g: Graph):
    numStation = g.contents.nS

    i = 0
    for i in range(numStation):
        curr = g.contents.edges[i]
        while curr:
            node = curr.contents
            id = node.id
            if node.next:
                print("id:", id, "->", end = " ")
            else :
                print("id:", id,  "-> null", end = " ")
            curr = node.next
        print()

def getNumNodes(g: Graph) -> int: 
    return g.contents.nS

def getIdLat(g: Graph, id: int) -> float:
    return g.contents.edges[id].contents.latitude

def getIdLong(g: Graph, id: int) -> float:
    return g.contents.edges[id].contents.longitude

def getIdPollution(g: Graph, id: int) -> float:
    curr = g.contents.edges[id]
    return curr.contents.pollution_level

def getIdTemp(g: Graph, id: int) -> float:
    return g.contents.edges[id].contents.temp

def getIdHumidity(g: Graph, id: int) -> float:
    return g.contents.edges[id].contents.humidity

def getIdWindSpeed(g: Graph, id: int) -> float:
    return g.contents.edges[id].contents.wind_speed

def getIdWindDir(g: Graph, id: int) -> float:
    return g.contents.edges[id].contents.wind_dir

def readOneSample(graphFile: str, pollutionFile: str):
    g = createGraph(graphFile)

    next_pollution = read_res_pollution(pollutionFile)

    return g, next_pollution

def read_res_pollution(file: str):
    values = []
    with open(file) as f:
        for line in f:
            values.append(float(line.strip()))
    return values 