#include "ToonMeshLoader.h"
#include "Serialization/JsonSerializer.h"
#include "Modules/ModuleManager.h"
#include "IImageWrapperModule.h"
#include "Engine/Texture2D.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UToonMeshLoader::LoadMeshFromJson(const FString& JsonPath, UProceduralMeshComponent* MeshComponent)
{
    FString JsonString;
    if (FFileHelper::LoadFileToString(JsonString, *JsonPath))
    {
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
        TSharedPtr<FJsonObject> JsonObject;
        if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
        {
            TArray<FVector> Vertices;
            TArray<int32> Triangles;
            TArray<FVector2D> UVs;

            const TArray<TSharedPtr<FJsonValue>>* VerticesArray;
            if (JsonObject->TryGetArrayField(TEXT("vertices"), VerticesArray))
            {
                for (const TSharedPtr<FJsonValue>& Vertex : *VerticesArray)
                {
                    const TArray<TSharedPtr<FJsonValue>>* VertexArray = &Vertex->AsArray();
                    Vertices.Add(FVector(
                        (*VertexArray)[0]->AsNumber(),
                        (*VertexArray)[1]->AsNumber(),
                        (*VertexArray)[2]->AsNumber()
                    ));
                }
            }

            const TArray<TSharedPtr<FJsonValue>>* TrianglesArray;
            if (JsonObject->TryGetArrayField(TEXT("triangles"), TrianglesArray))
            {
                for (const TSharedPtr<FJsonValue>& Triangle : *TrianglesArray)
                {
                    Triangles.Add(Triangle->AsNumber());
                }
            }

            const TArray<TSharedPtr<FJsonValue>>* UVsArray;
            if (JsonObject->TryGetArrayField(TEXT("uvs"), UVsArray))
            {
                for (const TSharedPtr<FJsonValue>& UV : *UVsArray)
                {
                    const TArray<TSharedPtr<FJsonValue>>* UVArray = &UV->AsArray();
                    UVs.Add(FVector2D(
                        (*UVArray)[0]->AsNumber(),
                        (*UVArray)[1]->AsNumber()
                    ));
                }
            }

            MeshComponent->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVs, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
        }
    }
}

UTexture2D* UToonMeshLoader::LoadTextureFromFile(const FString& FilePath)
{
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

    TArray<uint8> RawFileData;
    if (FFileHelper::LoadFileToArray(RawFileData, *FilePath))
    {
        if (ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
        {
            TArray<uint8> UncompressedBGRA;
            if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
            {
                UTexture2D* NewTexture = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
                if (NewTexture)
                {
                    FTexture2DMipMap& Mip = NewTexture->GetPlatformData()->Mips[0];
                    void* TextureData = Mip.BulkData.Lock(LOCK_READ_WRITE);
                    FMemory::Memcpy(TextureData, UncompressedBGRA.GetData(), UncompressedBGRA.Num());
                    Mip.BulkData.Unlock();
                    NewTexture->UpdateResource();
                    return NewTexture;
                }
            }
        }
    }
    return nullptr;
}