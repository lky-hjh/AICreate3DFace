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
	void GenerateAndLoadModel(const FString& ImagePath, UProceduralMeshComponent* MeshComponent);
};