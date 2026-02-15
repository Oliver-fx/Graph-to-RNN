import ctypes
lib = ctypes.CDLL('./libgraph.so')

# pyhton wrapper structure
class EdgeInfo(ctypes.Structure):
    _fields_ = [
        ("from_id", ctypes.c_int),
        ("to_id", ctypes.c_int),
        ("dist", ctypes.c_double),
        ("compass_angle", ctypes.c_int),
        ("temp_lag", ctypes.c_float),
    ]

class AdjNode(ctypes.Structure):
    pass
AdjNode._fields_ = [
    ("id", ctypes.c_int),
    ("S_name", ctypes.c_char * 100),
    ("wind_dir", ctypes.c_float),
    ("wind_speed", ctypes.c_float),
    ("pollution_level", ctypes.c_float),
    ("temp", ctypes.c_float),
    ("humidity", ctypes.c_float),
    ("latitude", ctypes.c_float),
    ("longitude", ctypes.c_float),
    ("e", EdgeInfo),
    ("next", ctypes.POINTER(AdjNode)),
]

class Graph(ctypes.Structure):
   _fields_ = [
      ("nS", ctypes.c_int),
      ("area_name", ctypes.c_char * 100),
      ("edges", ctypes.POINTER(ctypes.POINTER(AdjNode))),
   ]

# python wrapper function
lib.readStation.argtypes = [ctypes.c_char_p]
lib.readStation.restype = ctypes.POINTER(Graph)

lib.gen_edge.argtypes = [ctypes.POINTER(Graph)]
lib.gen_edge.restype = None

lib.man_add_edge.argtypes = [ctypes.POINTER(Graph), ctypes.c_int, ctypes.c_int]
lib.man_add_edge.restype = ctypes.POINTER(Graph)

lib.man_delete_edge.argtypes = [ctypes.POINTER(Graph), ctypes.c_int, ctypes.c_int]
lib.man_delete_edge.restype = ctypes.POINTER(Graph)

def createGraph(fileName: str):
    return lib.readStation(fileName.encode("utf-8"))

def genEdge(g: Graph):
    lib.gen_edge(g)

def manAddEdge(g: Graph, id1: int, id2: int):
    return lib.man_add_edge(g, id1, id2)

def manDeleteEdge(g: Graph, id1: int, id2: int):
    return lib.man_delete_edge(g, id1, id2)


# numStation = g.contents.nS

# i = 0
# for i in range(numStation):
#     curr = g.contents.edges[i]
#     while curr:
#         node = curr.contents
#         id = node.id
#         if node.next:
#             print("id:", id, "->", end = " ")
#         else :
#             print("id:", id,  "-> null", end = " ")
#         curr = node.next
#     print()


