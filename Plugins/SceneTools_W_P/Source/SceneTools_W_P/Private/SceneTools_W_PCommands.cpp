// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SceneTools_W_PCommands.h"

#define LOCTEXT_NAMESPACE "FSceneTools_W_PModule"

void FSceneTools_W_PCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "SceneTools_W_P", "Bring up SceneTools_W_P window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
