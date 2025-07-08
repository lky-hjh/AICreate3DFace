import json
import numpy as np
from scipy.spatial import Delaunay
import os

def export_json(landmarks, texture_file, output_path):
    # 准备顶点数据
    points = []
    for lm in landmarks:
        points.append([lm.x, lm.y, lm.z])
    
    # 转换为2D点进行三角剖分
    points_2d = np.array([[lm.x, lm.y] for lm in landmarks])
    tri = Delaunay(points_2d)
    
    # UV坐标
    uvs = []
    for p in points_2d:
        uvs.append([p[0], 1 - p[1]])  # Y轴翻转
    
    # 三角面索引
    triangles = tri.simplices.flatten().tolist()
    
    # 组织json结构
    mesh_data = {
        "vertices": points,
        "triangles": triangles,
        "uvs": uvs
    }
    
    # 创建目录
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    
    # 写入json文件
    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(mesh_data, f)