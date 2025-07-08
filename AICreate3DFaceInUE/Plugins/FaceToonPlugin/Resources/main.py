import cv2
import mediapipe as mp
import os
from cartoon_filter import cartoonify
from utils import export_json
import sys

def main():
    # 1. 处理命令行参数
    if len(sys.argv) >= 4:
        img_path = sys.argv[1]
        json_output_path = sys.argv[2]  # 你可以用它来保存obj
        cartoon_path = sys.argv[3]
    else:
        script_dir = os.path.dirname(os.path.abspath(__file__))
        img_path = os.path.join(script_dir, "input.jpg")
        json_output_path = "output/stylized_face.json"
        cartoon_path = "output/cartoon_texture.jpg"

    # 创建输出目录
    out_dir = os.path.dirname(json_output_path)
    if out_dir and not os.path.exists(out_dir):
        os.makedirs(out_dir, exist_ok=True)
    
    # 读取输入图像
    if not os.path.exists(img_path):
        print(f"找不到输入图片: {img_path}")
        return
    
    img = cv2.imread(img_path)
    if img is None:
        print("无法读取图片，请检查文件格式")
        return
    
    # 卡通风格处理
    print("应用卡通滤镜...")
    cartoon = cartoonify(img)
    cv2.imwrite(cartoon_path, cartoon)
    print(f"卡通纹理已保存至: {cartoon_path}")
    
    # 初始化FaceMesh
    print("提取3D人脸网格...")
    mp_face_mesh = mp.solutions.face_mesh
    face_mesh = mp_face_mesh.FaceMesh(
        static_image_mode=True,
        max_num_faces=1,
        refine_landmarks=True,
        min_detection_confidence=0.5
    )
    
    # 处理图像
    results = face_mesh.process(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    
    if not results.multi_face_landmarks:
        print("未检测到人脸，请尝试更清晰的正脸照片")
        return
    
    # 获取第一个检测到的人脸
    face_landmarks = results.multi_face_landmarks[0]
    
    # 导出3D模型
    print("生成3D模型...")
    export_json(face_landmarks.landmark, cartoon_path, json_output_path)
    
    print("="*50)
    print("✅ 处理完成!")
    print(f"3D模型文件: {json_output_path}")
    print(f"纹理贴图: {cartoon_path}")
    print("="*50)

if __name__ == "__main__":
    main()
    input("按回车键退出...")