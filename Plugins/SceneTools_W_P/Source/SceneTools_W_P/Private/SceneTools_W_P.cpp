// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SceneTools_W_P.h"
#include "SceneTools_W_PStyle.h"
#include "SceneTools_W_PCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "EditorStyle.h"
// #include "Widgets/Layout/SBox.h"
// #include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "SlateMain.h"

static const FName SceneTools_W_PTabName("SceneTools_W_P");

#define LOCTEXT_NAMESPACE "FSceneTools_W_PModule"

FString ST_Ver = "v1.9.12(b)";
void FSceneTools_W_PModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FSceneTools_W_PStyle::Initialize();
	FSceneTools_W_PStyle::ReloadTextures();

	FSceneTools_W_PCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FSceneTools_W_PCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FSceneTools_W_PModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("windowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FSceneTools_W_PModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FSceneTools_W_PModule::AddToolbarExtension));
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	const FString vers = FString::Printf(TEXT("SceneTools  %s"), *ST_Ver);
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(SceneTools_W_PTabName, FOnSpawnTab::CreateRaw(this, &FSceneTools_W_PModule::OnSpawnPluginTab))
		.SetDisplayName(FText::FromString(*vers))
		// .SetDisplayName(LOCTEXT("FSceneTools_W_PTabTitle", "SceneTools"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
	//FString ver = FString::Printf(TEXT("场景辅助工具 %s"), *ST_Ver);
	//GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, *ver);
}

void FSceneTools_W_PModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FSceneTools_W_PStyle::Shutdown();

	FSceneTools_W_PCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(SceneTools_W_PTabName);
}

TSharedRef<SDockTab> FSceneTools_W_PModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FSceneTools_W_PModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("SceneTools_W_P.cpp"))
		);

		return SNew(SDockTab).TabRole(ETabRole::NomadTab)//通过将 TabRole 设置为 ETabRole::NomadTab，窗口将自动适应内容的大小(只适用于tab)
		.ShouldAutosize(true)	//控件保持自身大小，不受界面窗口大小影响
		[
			SAssignNew(SlateMain, SSlateMain)
		];
		//.TabRole(ETabRole::NomadTab)
		//[
		//	// Put your tab content here!
		//	SNew(SBox)
		//	.HAlign(HAlign_Center)
		//	.VAlign(VAlign_Center)
		//	[
		//		SNew(STextBlock)
		//		.Text(WidgetText)
		//	]
		//];
}
void FSceneTools_W_PModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(SceneTools_W_PTabName);
}

void FSceneTools_W_PModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FSceneTools_W_PCommands::Get().OpenPluginWindow);
}

void FSceneTools_W_PModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FSceneTools_W_PCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSceneTools_W_PModule, SceneTools_W_P)
