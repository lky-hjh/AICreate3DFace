#include "ToonGenManager.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformProcess.h"
#include "ToonMeshLoader.h"
#include "HAL/FileManager.h"

void UToonGenManager::GenerateAndLoadModel(UObject* Target, const FString& ImagePath, const FString& JsonOutputPath, const FString& TextureOutputPath, UProceduralMeshComponent* MeshComponent)
{
	if (!Target || ImagePath.IsEmpty() || JsonOutputPath.IsEmpty() || TextureOutputPath.IsEmpty() || !MeshComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid parameters for GenerateAndLoadModel"));
		return;
	}
	// Generate absolute path
	FString TempDir = FPaths::Combine(FPaths::ProjectDir(), TEXT("Temp"));
	IFileManager::Get().MakeDirectory(*TempDir, true);
	FString AbsoluteImagePath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("Temp/input.jpg")));
	FString AbsoluteJsonPath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("Temp/output.json")));
	FString AbsoluteTexturePath = FPaths::ConvertRelativePathToFull(FPaths::Combine(FPaths::ProjectDir(), TEXT("Temp/cartoon_texture.jpg")));
	
	FString PythonPath = TEXT("F:/Project/AICreate3DFace/AICreate3DFaceInUE/.venv/Scripts/python.exe");
	FString PythonScriptPath = FPaths::ProjectDir() / TEXT("Plugins/FaceToonPlugin/Resources/main.py");
	FString Command = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\" \"%s\" \"%s\""), *PythonPath, *PythonScriptPath, *AbsoluteImagePath, *AbsoluteJsonPath, *AbsoluteTexturePath);

	FString Args = FString::Printf(TEXT("\"%s\" \"%s\" \"%s\" \"%s\""),
    *PythonScriptPath, *AbsoluteImagePath, *AbsoluteJsonPath, *AbsoluteTexturePath);

	FPlatformProcess::CreateProc(
    *PythonPath, 
    *Args,       
    true, false, false, nullptr, 0, nullptr, nullptr
);

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