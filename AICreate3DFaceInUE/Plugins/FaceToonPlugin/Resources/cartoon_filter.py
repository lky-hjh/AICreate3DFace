import cv2
import numpy as np

def cartoonify(img):
    # 转换为灰度图
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    
    # 应用中值模糊减少噪点
    gray = cv2.medianBlur(gray, 7)
    
    # 边缘检测
    edges = cv2.adaptiveThreshold(
        gray, 255,
        cv2.ADAPTIVE_THRESH_MEAN_C,
        cv2.THRESH_BINARY,
        blockSize=9,
        C=7
    )
    
    # 颜色量化
    img_quantized = img.copy()
    for _ in range(2):
        img_quantized = cv2.bilateralFilter(img_quantized, 9, 75, 75)
    
    # 合并边缘和颜色
    cartoon = cv2.bitwise_and(img_quantized, img_quantized, mask=edges)
    
    # 增强颜色
    cartoon = cv2.stylization(cartoon, sigma_s=100, sigma_r=0.3)
    
    return cartoon