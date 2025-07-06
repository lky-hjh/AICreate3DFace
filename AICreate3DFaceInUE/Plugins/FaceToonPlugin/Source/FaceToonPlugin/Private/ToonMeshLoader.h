#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Engine/Texture2D.h"
#include "ToonMeshLoader.generated.h"

UCLASS()
class UToonMeshLoader : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FaceToon")
	static void LoadMeshFromJson(const FString& JsonPath, UProceduralMeshComponent* MeshComponent);

	UFUNCTION(BlueprintCallable, Category = "FaceToon")
	static UTexture2D* LoadTextureFromFile(const FString& FilePath);
};