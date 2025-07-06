#include "ToonGenManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformProcess.h"
#include "ToonMeshLoader.h"

void UToonGenManager::GenerateAndLoadModel(const FString& ImagePath, UProceduralMeshComponent* MeshComponent)
{
	if (!MeshComponent) return;
	FString PythonPath = TEXT("F:/Project/AICreate3DFace/AICreate3DFaceInUE/.venv/Scripts/python.exe");
	FString PythonScriptPath = FPaths::ProjectDir() / TEXT("Plugins/FaceToonPlugin/Resources/main.py");
	FString JsonOutputPath = FPaths::ProjectDir() / TEXT("Temp/output.json");
	FString TextureOutputPath = FPaths::ProjectDir() / TEXT("Temp/cartoon_texture.jpg");

	FString Command = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\" \"%s\" \"%s\""), *PythonPath, *PythonScriptPath, *ImagePath, *JsonOutputPath, *TextureOutputPath);
	FPlatformProcess::CreateProc(*Command, nullptr, true, false, false, nullptr, 0, nullptr, nullptr);

	FPlatformProcess::Sleep(5.0f);
	UToonMeshLoader::LoadMeshFromJson(JsonOutputPath, MeshComponent);
	UTexture2D* Texture = UToonMeshLoader::LoadTextureFromFile(TextureOutputPath);
	if (Texture)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(MeshComponent->GetMaterial(0), MeshComponent);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetTextureParameterValue("BaseColor", Texture);
			MeshComponent->SetMaterial(0, DynamicMaterial);
		}
	}
}