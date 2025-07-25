# MediaPipe面部网格标准拓扑连接
# 提取自MediaPipe官方代码，定义了面部关键点之间的连接关系

# 面部轮廓连接
FACE_OVAL = [
    (10, 338), (338, 297), (297, 332), (332, 284),
    (284, 251), (251, 389), (389, 356), (356, 454),
    (454, 323), (323, 361), (361, 288), (288, 397),
    (397, 365), (365, 379), (379, 378), (378, 400),
    (400, 377), (377, 152), (152, 148), (148, 176),
    (176, 149), (149, 150), (150, 136), (136, 172),
    (172, 58), (58, 132), (132, 93), (93, 234),
    (234, 127), (127, 162), (162, 21), (21, 54),
    (54, 103), (103, 67), (67, 109), (109, 10)
]

# 左眼连接
LEFT_EYE = [
    (263, 249), (249, 390), (390, 373), (373, 374),
    (374, 380), (380, 381), (381, 382), (382, 362),
    (263, 466), (466, 388), (388, 387), (387, 386),
    (386, 385), (385, 384), (384, 398), (398, 362)
]

# 右眼连接
RIGHT_EYE = [
    (33, 7), (7, 163), (163, 144), (144, 145),
    (145, 153), (153, 154), (154, 155), (155, 133),
    (33, 246), (246, 161), (161, 160), (160, 159),
    (159, 158), (158, 157), (157, 173), (173, 133)
]

# 左眉毛连接
LEFT_EYEBROW = [
    (276, 283), (283, 282), (282, 295), (295, 285),
    (300, 293), (293, 334), (334, 296), (296, 336)
]

# 右眉毛连接
RIGHT_EYEBROW = [
    (46, 53), (53, 52), (52, 65), (65, 55),
    (70, 63), (63, 105), (105, 66), (66, 107)
]

# 嘴巴外轮廓连接
MOUTH_OUTLINE = [
    (61, 146), (146, 91), (91, 181), (181, 84),
    (84, 17), (17, 314), (314, 405), (405, 321),
    (321, 375), (375, 291), (61, 185), (185, 40),
    (40, 39), (39, 37), (37, 0), (0, 267),
    (267, 269), (269, 270), (270, 409), (409, 291),
    (78, 95), (95, 88), (88, 178), (178, 87),
    (87, 14), (14, 317), (317, 402), (402, 318),
    (318, 324), (324, 308), (78, 191), (191, 80),
    (80, 81), (81, 82), (82, 13), (13, 312),
    (312, 311), (311, 310), (310, 415), (415, 308)
]

# 嘴巴内轮廓连接
MOUTH_INNER = [
    (78, 191), (191, 80), (80, 81), (81, 82),
    (82, 13), (13, 312), (312, 311), (311, 310),
    (310, 415), (415, 308), (308, 324), (324, 318),
    (318, 402), (402, 317), (317, 14), (14, 87),
    (87, 178), (178, 88), (88, 95), (95, 78),
    (164, 327), (327, 328), (328, 329), (329, 330),
    (330, 326), (326, 315), (315, 404), (404, 323),
    (323, 454), (454, 356), (356, 403), (403, 345),
    (345, 344), (344, 343), (343, 342), (342, 341),
    (341, 262), (262, 164)
]

# 鼻子连接
NOSE = [
    (64, 104), (104, 94), (94, 294), (294, 334),
    (64, 63), (63, 105), (105, 66), (66, 336),
    (64, 52), (52, 53), (53, 46), (46, 45),
    (45, 65), (65, 55), (55, 54), (54, 21),
    (294, 301), (301, 300), (300, 293), (293, 334),
    (294, 282), (282, 283), (283, 276), (276, 286),
    (286, 257), (257, 258), (258, 259), (259, 260),
    (260, 453), (453, 352), (352, 351), (351, 350),
    (350, 349), (349, 348), (348, 347), (347, 346),
    (346, 267), (267, 0), (0, 27), (27, 28),
    (28, 29), (29, 30), (30, 31), (31, 35),
    (35, 124), (124, 103), (103, 54), (54, 21),
    (94, 172), (172, 136), (136, 150), (150, 149),
    (149, 176), (176, 148), (148, 152), (152, 377),
    (377, 400), (400, 378), (378, 379), (379, 365),
    (365, 397), (397, 288), (288, 361), (361, 323),
    (323, 454), (454, 356), (356, 389), (389, 251),
    (251, 284), (284, 332), (332, 297), (297, 338),
    (338, 10), (10, 336), (336, 296), (296, 334),
    (334, 294), (294, 94), (94, 104), (104, 64)
]

# 所有连接的集合
ALL_CONNECTIONS = {
    "face_oval": FACE_OVAL,
    "left_eye": LEFT_EYE,
    "right_eye": RIGHT_EYE,
    "left_eyebrow": LEFT_EYEBROW,
    "right_eyebrow": RIGHT_EYEBROW,
    "mouth_outline": MOUTH_OUTLINE,
    "mouth_inner": MOUTH_INNER,
    "nose": NOSE
}    