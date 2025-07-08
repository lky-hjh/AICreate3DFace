#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProceduralMeshComponent.h"
#include "ToonGenManager.generated.h"

UCLASS()
class UToonGenManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "FaceToon")
	static void GenerateAndLoadModel(UObject* Target, const FString& ImagePath, const FString& JsonOutputPath, const FString& TextureOutputPath, UProceduralMeshComponent* MeshComponent);
};