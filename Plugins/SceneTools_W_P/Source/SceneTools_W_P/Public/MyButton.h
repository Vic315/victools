#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SMyButton :public SCompoundWidget {
public:
	SLATE_BEGIN_ARGS(SMyButton) {}
	SLATE_END_ARGS()
	void Construct(const FArguments& InArgs);
};


