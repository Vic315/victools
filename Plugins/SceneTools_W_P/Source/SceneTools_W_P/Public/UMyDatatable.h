#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/DataTable.h"
#include "UObject/ObjectMacros.h"
#include "Containers/UnrealString.h"
#include "UMyDatatable.generated.h"

extern FString ST_Ver;
extern FString ST_UITEXTFile;
extern FString ST_ContextString;

UCLASS()
class SCENETOOLS_W_P_API UMyDatatable : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = Character)
	//static void ST_LoadTable(int i, FString mode);
};
//創建 DataTable Row Type : ChineUIData
USTRUCT(BlueprintType)
struct FChinaUIData :public FTableRowBase	//繼承至FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIDataTable")
		FString Info;
};
