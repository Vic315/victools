// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SceneTools_W_PStyle.h"

class FSceneTools_W_PCommands : public TCommands<FSceneTools_W_PCommands>
{
public:

	FSceneTools_W_PCommands()
		: TCommands<FSceneTools_W_PCommands>(TEXT("SceneTools_W_P"), NSLOCTEXT("Contexts", "SceneTools_W_P", "SceneTools_W_P Plugin"), NAME_None, FSceneTools_W_PStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};