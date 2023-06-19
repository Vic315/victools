#include "SlateMain.h"
// #include "SceneTools_W_P.h"
#include <string>
#include <iostream>
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SExpandableArea.h"
// #include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/SWindow.h"
// #include "Widgets/Docking/SDockTab.h"
// #include "Framework/SlateDelegates.h" // 包含 Slate 事件委托的头文件
// #include "Framework/Application/SlateApplication.h"

#include "AssetRegistryModule.h"
#include "Engine/UserDefinedStruct.h"
#include "Logging/LogMacros.h"
#include "Misc/FileHelper.h"
#include "Editor.h"

#include "Engine/AssetManager.h"
#include "AssetToolsModule.h"
#include "Engine/Engine.h"
#include "Engine/Selection.h"
#include "Engine/Texture.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"

#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Misc/MessageDialog.h"
#include "UObject/UObjectGlobals.h"

#include "CustomFN.h"
//#include "Commandlets/Commandlet.h"
#include "Editor/EditorEngine.h"
#include "PerPlatformProperties.h"
// #include "Engine/StaticMeshSocket.h"
#include "Components/StaticMeshComponent.h"
// #include "UObject/ConstructorHelpers.h"
#include "FileHelpers.h"
#include "StaticMeshResources.h"
// #include <iso646.h>

//#include "Editor/UnrealEd/Public/Editor.h"
#include "Editor/UnrealEd/Public/AssetSelection.h"
// #include "Editor/UnrealEd/Public/ObjectTools.h"
// #include "Editor/UnrealEd/Public/EditorViewportClient.h"

#include "ContentBrowserModule.h"	//获取资源管理器选中对象
#include "IContentBrowserSingleton.h"
#include "AssetRegistry/Private/AssetRegistry.h"

#include "Components/TextRenderComponent.h"
#include "Evaluation/MovieScenePropertyTemplate.h"
#include "Kismet/GameplayStatics.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Templates/SharedPointer.h"
#include "Editor/Persona/Private/PersonaMeshDetails.h"
#include "Developer/SkeletalMeshUtilitiesCommon/Public/LODUtilities.h"
#include "Engine/SkeletalMeshLODSettings.h"
#include "Editor/Persona/Private/PersonaMeshDetails.h"
// #include "Features/EditorFeatures.h"

// #include "SkeletalMeshTypes.h"
// #include "Toolkits/AssetEditorManager.h"

#define LOCTEXT_NAMESPACE "SlateMain"

FString pppp=""; //全局变量
FString lodpppp="";
FString s_suffix="";
FString s_equal="";
FString s_seltext="";
int s_searchV=1024;
int s_powV=7;
float ScreenS_0=1.0;
float ScreenS_1=0.2;
float ScreenS_2=0.11;
float ScreenS_3=0.06;
int PercentT_0=100;
int PercentT_1=40;
int PercentT_2=16;
int PercentT_3=8;
int s_rowNum;
int s_Matrix;
FString s_setV="512";
bool colla1;
bool colla2;
FString IniPath = (FPaths::ProjectPluginsDir() + "SceneTools_W_P/settings.ini");
CustomFN CFN;

void SSlateMain::Construct(const FArguments& InArgs)
{
	//FString vers = FString::Printf(TEXT("%s %s"), *na, *ST_Ver);
	// const FString vers = FString::Printf(TEXT("SceneTools  %s"), *ST_Ver);
	
	//记录读取
	if (FPaths::FileExists(*(FPaths::ProjectPluginsDir() + "SceneTools_W_P/settings.ini")))
	{
		CFN.ReadIniValue(FString("SceneTools"), FString("SelText"), s_seltext, *IniPath);
		CFN.ReadIniValue(FString("SceneTools"), FString("Path"), pppp, *IniPath);
		CFN.ReadIniValue(FString("SceneTools"), FString("LodDataPath"), lodpppp, *IniPath);
		if(lodpppp == "") lodpppp = "Mesh/Common/LOD_Setting";
		// LoadLODData(*lodpppp);
		CFN.ReadIniValue(FString("SceneTools"), FString("Suffix"), s_suffix, *IniPath);
		CFN.ReadIniValue(FString("SceneTools"), FString("Equal"), s_equal, *IniPath);
		CFN.ReadIniValue(FString("SceneTools"), FString("SetV"), s_setV, *IniPath);
		FString s_SV;
		CFN.ReadIniValue(FString("SceneTools"), FString("SearchV"), s_SV, *IniPath);
		s_searchV = FCString::Atoi(*s_SV);
		FString s_PV;
		CFN.ReadIniValue(FString("SceneTools"), FString("PowV"), s_PV, *IniPath);
		s_powV = FCString::Atoi(*s_PV);
		
		FString SS_PV0;
		CFN.ReadIniValue(FString("SceneTools"), FString("ScreenSize_0"), SS_PV0, *IniPath);
		ScreenS_0 = FCString::Atof(*SS_PV0);
		FString SS_PV1;
		CFN.ReadIniValue(FString("SceneTools"), FString("ScreenSize_1"), SS_PV1, *IniPath);
		ScreenS_1 = FCString::Atof(*SS_PV1);
		FString SS_PV2;
		CFN.ReadIniValue(FString("SceneTools"), FString("ScreenSize_2"), SS_PV2, *IniPath);
		ScreenS_2 = FCString::Atof(*SS_PV2);
		FString SS_PV3;
		CFN.ReadIniValue(FString("SceneTools"), FString("ScreenSize_3"), SS_PV3, *IniPath);
		ScreenS_3 = FCString::Atof(*SS_PV3);
		//---
		FString PT_PV0;
		CFN.ReadIniValue(FString("SceneTools"), FString("PercentTriangles_0"), PT_PV0, *IniPath);
		PercentT_0 = FCString::Atoi(*PT_PV0);
		FString PT_PV1;
		CFN.ReadIniValue(FString("SceneTools"), FString("PercentTriangles_1"), PT_PV1, *IniPath);
		PercentT_1 = FCString::Atoi(*PT_PV1);
		FString PT_PV2;
		CFN.ReadIniValue(FString("SceneTools"), FString("PercentTriangles_2"), PT_PV2, *IniPath);
		PercentT_2 = FCString::Atoi(*PT_PV2);
		FString PT_PV3;
		CFN.ReadIniValue(FString("SceneTools"), FString("PercentTriangles_3"), PT_PV3, *IniPath);
		PercentT_3 = FCString::Atoi(*PT_PV3);
		
		FString s_ROW;
		CFN.ReadIniValue(FString("SceneTools"), FString("RowNum"), s_ROW, *IniPath);
		if (s_ROW == "")
			s_rowNum = 1;
		else
			s_rowNum = FCString::Atoi(*s_ROW);
		FString s_Matr;
		CFN.ReadIniValue(FString("SceneTools"), FString("Matrix"), s_Matr, *IniPath);
		if (s_Matr == "")
			s_Matrix = 2;
		else
			s_Matrix = FCString::Atoi(*s_Matr);
		FString cick;
		CFN.ReadIniValue(FString("SceneTools"),FString("collapse"),cick,IniPath);
		if (cick == "true")
		{
			colla1=false;
			colla2=true;
		}else{
			colla1=true;
			colla2=false;
		}
	}else
	{
		CFN.WriteIni(FString("SceneTools"), FString("SelText"), "STBox", *IniPath);
	}
	if (FPaths::FileExists(*(FPaths::ProjectPluginsDir() + "SceneTools_W_P/ST.txt")))
	{
		ReflashHist();
	}
	else
	{
		WriteTxt("", (FPaths::ProjectPluginsDir() + "SceneTools_W_P/ST.txt"));
	}
	LODGrpOpations.Add(MakeShareable(new FString("LevelArchitecture")));
	LODGrpOpations.Add(MakeShareable(new FString("LargeProp")));
	LODGrpOpations.Add(MakeShareable(new FString("SmallProp")));
	compOpations.Add(MakeShareable(new FString("Default")));
	compOpations.Add(MakeShareable(new FString("NormalMap")));
	compOpations.Add(MakeShareable(new FString("BC7")));
	equalSel.Add(MakeShareable(new FString(TEXT("大于等于"))));
	equalSel.Add(MakeShareable(new FString(TEXT("等于"))));
	ChildSlot
	[
		SNew(SVerticalBox) //創建主垂直面板
            // + SVerticalBox::Slot()
            //   .VAlign(VAlign_Bottom)
            //   .HAlign(HAlign_Center).AutoHeight()
            //   .Padding(2.0f)
            // [
            // 	SNew(STextBlock).Text(FText::FromString(*vers))
            // ]
            + SVerticalBox::Slot().AutoHeight()
                                  .Padding(2.0f) //间距
            [
                SAssignNew(Expnv1,SExpandableArea) //可折疊面板
                .AreaTitle(LOCTEXT("MyExpandable", "Scene Tools"))
                .InitiallyCollapsed(colla1)
                .Padding(2.0f)
                .HeaderContent()
                [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().AutoWidth()
                                            .HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(5.0f)
                    [SNew(STextBlock).Text(LOCTEXT("batch", "批处理:")).ColorAndOpacity(FLinearColor(0.2, 0.5, 0.98, 1.0))
                    ]
                    + SHorizontalBox::Slot()
                      .HAlign(HAlign_Left).AutoWidth()
                      .Padding(2.0f)[
                        SAssignNew(phComBox, SComboBox<TSharedPtr<FString>>)
                        .OptionsSource(&phOpations)
                        .OnGenerateWidget(this, &SSlateMain::comp_ComboItem)
                        .OnSelectionChanged(this, &SSlateMain::HandleSourceComboChanged)
                        .IsFocusable(true)[
                        	SNew(SBox)
                        ]
                      ]
                    + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        SNew(STextBlock).Text(FText::FromString("Content/"))
                    ]
                    + SHorizontalBox::Slot()
                      .HAlign(HAlign_Left)
                      .AutoWidth()
                      .MaxWidth(150)
                      .Padding(2.0f)
                    [
                        SAssignNew(texPath, SEditableTextBox).Text(FText::FromString(*pppp)).MinDesiredWidth(150)
                        .BackgroundColor(FLinearColor(0.66,0.66,0.66,1.0))
                        .OnTextChanged(this, &SSlateMain::OnPathText)
                    ]
                    + SHorizontalBox::Slot()
                      .HAlign(HAlign_Left).AutoWidth()
                      .Padding(2.f)
                    [
                        SNew(SButton).Text(FText::FromString("Save"))
                                     .ToolTipText(LOCTEXT("save", "保存當前路徑(填Content后的路径,前后都不要有斜杠!)"))
                                     .OnClicked(this, &SSlateMain::SaveButtom)
                    ]
                    + SHorizontalBox::Slot()
                      .HAlign(HAlign_Right).AutoWidth()
                    [
                        SAssignNew(RPath, SCheckBox)
                        .Content()[
                        	SNew(STextBlock).Text(LOCTEXT("RecursivePaths", "子目錄"))
                        	                .ToolTipText(LOCTEXT("rpTooltip", "搜索子目錄，注意文件多時需要耐心等待"))
                        ]
                    ]
                    + SHorizontalBox::Slot()
                        	  .HAlign(HAlign_Fill).VAlign(VAlign_Center).FillWidth(20)
                        	  .Padding(2.0f)[
                        	  	SNew(SBox).WidthOverride(160.0f)[
                        		SNew(SButton).Text(FText::FromString(TEXT("↑  ―― collapse ――  ↓"))).ButtonColorAndOpacity(FLinearColor(0.01,0.02,0.07,1.0))
                        .ForegroundColor(FLinearColor(0.79,0.79,0.79,1.0)).HAlign(HAlign_Center)
                        .OnClicked(this, &SSlateMain::testClicked)
                        	]]
                ]
                .BodyContent()[
                    SNew(SVerticalBox)
                    + SVerticalBox::Slot().AutoHeight()
                                          .Padding(2.0f) //间距
                    [
                        SNew(SHorizontalBox)
    
                        + SHorizontalBox::Slot().AutoWidth()
                                                .HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
                        [SNew(STextBlock).Text(LOCTEXT("batchN", "压缩格式批处理: "))
                        ]
                        + SHorizontalBox::Slot().Padding(2.0f)
                                                .HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
                        [
                        	SNew(SButton)
                        .Text(LOCTEXT("go", "设置法线图_N"))
                        .ToolTipText(LOCTEXT("goTooltip", "只设置法线贴图压缩格式"))
                        .OnClicked(this, &SSlateMain::OnGoButtonClicked)
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(4.0f)
                        [
                        	SNew(SButton)
                        .Text(LOCTEXT("goMap", "设置贴图"))
                        .ToolTipText(LOCTEXT("goMapTooltip", "批量设置所有贴图压缩格式"))
                        .OnClicked(this, &SSlateMain::OnGoMapButtonClicked)
                        ]
                        + SHorizontalBox::Slot().Padding(3.0f).HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
                        [
                        	SNew(SComboBox<TSharedPtr<FString>>)
                        	.OptionsSource(&compOpations)
                        	.OnGenerateWidget(this, &SSlateMain::comp_ComboItem)
                        	.OnSelectionChanged(this, &SSlateMain::comp_ComboChanged)
                        	.IsFocusable(true)[
                        		SNew(SBox)
                        	]
                        ]
                        + SHorizontalBox::Slot().Padding(3.0f).HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
                        [
                        	SAssignNew(texComp, SEditableTextBox).Text(FText::FromString("Default"))
                        	.BackgroundColor(FLinearColor(0.1f,0.1f,0.1f,0.0f))
                        	.ForegroundColor(FLinearColor(0.9f,1.0f,0.8f,1.0f))
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(4.0f)
                        [
                        	SNew(SButton)
                        .Text(FText::FromString(TEXT("UI贴图压缩"))).ButtonColorAndOpacity(FLinearColor(0.9,0.77,0.67,1.0))
                        .ToolTipText(FText::FromString(TEXT("批量设置资源管理器中选择的UI贴图压缩质量：最高 Highest\n(Compression Quality 与 Compression Quality By Size)")))
                        .OnClicked(this, &SSlateMain::SetUITextureClicked)
                        ]
                    ]
                    //1.7新功能
                    + SVerticalBox::Slot().AutoHeight()
                                          .Padding(2.0f)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth()
                                                .HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
                        [SNew(STextBlock).Text(LOCTEXT("batchAdj", "贴图调整批处理: "))]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SNew(SButton)
                        .Text(LOCTEXT("goAdju", "重置贴图调整"))
                        .ToolTipText(LOCTEXT("goAdjuTooltip", "批量重置所有贴图调整参数(右边填写后缀名挑选文件,输出在D盘)"))
                        .OnClicked(this, &SSlateMain::SeachAdjustmentTexture)
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SNew(STextBlock).Text(FText::FromString(TEXT("搜索关键字:")))
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SAssignNew(suffixSeach, SEditableTextBox).Text(FText::FromString(*s_suffix)).MinDesiredWidth(30)
                        	.BackgroundColor(FLinearColor(0.66,0.66,0.66,1.0))
                        	.OnTextChanged(this,&SSlateMain::OnSubfixText)
                        ]
                    ]
                    //1.8 批量设置贴图尺寸
                    + SVerticalBox::Slot().AutoHeight()
                                          .Padding(2.0f)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth()
                        						.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
                        [SNew(STextBlock).Text(LOCTEXT("settex", "          : "))]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SNew(SButton)
                        .Text(LOCTEXT("resetLB", "重置LODBias"))
                        .ToolTipText(LOCTEXT("resettp", "批量重置LOD Bias为0(上面填写后缀名挑选文件,输出在D盘)"))
                        .OnClicked(this, &SSlateMain::ResetTextureLODBias)
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SNew(SButton)
                        .Text(LOCTEXT("msize", "MaxSize"))
                        .ToolTipText(LOCTEXT("msTooltip", "批量设置贴图尺寸(上面填写后缀名挑选文件,输出在D盘)"))
                        .OnClicked(this, &SSlateMain::SetTextureMax)
                        ]
                        + SHorizontalBox::Slot().VAlign(VAlign_Center)
                        						.HAlign(HAlign_Left).AutoWidth().Padding(2.0f)
                        [
                        	SNew(SComboBox<TSharedPtr<FString>>)
                        	.OptionsSource(&equalSel)
                        	.OnGenerateWidget(this,&SSlateMain::comp_ComboItem)
                        	.OnSelectionChanged(this,&SSlateMain::comp_equalText)
                        	.IsFocusable(true)[SNew(SBox)]
                        ]
                        + SHorizontalBox::Slot().AutoWidth()
                                            	.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
                        [SNew(STextBlock).Text(FText::FromString(TEXT("查找")))]
                        + SHorizontalBox::Slot().AutoWidth()
                                            	.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
                        [
                            SAssignNew(equalText,SEditableTextBox).Text(FText::FromString(*s_equal)).MinDesiredWidth(10)
                            .BackgroundColor(FLinearColor(0.1f,0.1f,0.1f,0.0f))
                            .ForegroundColor(FLinearColor(0.9f,1.0f,0.8f,1.0f))
                        ]
                        + SHorizontalBox::Slot().VAlign(VAlign_Center)
                        						.HAlign(HAlign_Left).AutoWidth().Padding(2.0f)
                        [
                        	SAssignNew(searchSize, SSpinBox<int>).MaxValue(4096).MinValue(32).Value(s_searchV).SliderExponent(3)
                        	.ToolTipText(FText::FromString(TEXT("拖动来设置查找贴图尺寸")))
                        	.OnEndSliderMovement(this,&SSlateMain::SearchSizeValueSet)
                        ]
                        + SHorizontalBox::Slot().AutoWidth()
                                            	.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
                        [SNew(STextBlock).Text(LOCTEXT("setmapValtp", "设置尺寸为:"))]
                        + SHorizontalBox::Slot().VAlign(VAlign_Center)
                        						.HAlign(HAlign_Left).AutoWidth().Padding(2.0f)
                        						[
                        SNew(SBox)
                        .WidthOverride(70.0f)
                        [
                        	SAssignNew(spn360,SSpinBox<int>).MaxValue(11).MinValue(1).Value(s_powV)//.MinDesiredWidth(28)
                        	.ToolTipText(LOCTEXT("setmapVal", "输入2的次方数"))
                        	.OnValueChanged(this, &SSlateMain::SetSizeValue)
                        ]]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SAssignNew(SizeValue, SEditableTextBox).Text(FText::FromString(*s_setV)).MinDesiredWidth(30)
                        	.BackgroundColor(FLinearColor(0.1f,0.1f,0.1f,0.0f))
                        	.ForegroundColor(FLinearColor(0.0,0.92,0.1,1.0))
                        	]
                    ]
            //LOD批处理 v1.9
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                        SNew(SHorizontalBox)
                        + SHorizontalBox::Slot().AutoWidth()
                        						.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(1.0f)
                        [
                        	SNew(STextBlock).Text(FText::FromString(TEXT("LOD批处理: ")))
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SNew(SButton).Text(FText::FromString(TEXT("添加MinimumLOD"))).ButtonColorAndOpacity(FLinearColor(0.89,0.57,0.77,1.0))
                        	.ToolTipText(FText::FromString(TEXT("批量设置指定目录中静态网格MinimumLOD添加Mobile为1，并取消勾选AutoComputeLODScreenSize\n(处理列表文件保存到 D:盘根目录：Add-MinimumLOD_文件夹名.txt)")))
                        	.OnClicked(this, &SSlateMain::LODset)
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(1.0f)[
                        	SNew(SButton).Text(FText::FromString(TEXT("清除MinimumLOD"))).ButtonColorAndOpacity(FLinearColor(0.80,0.57,0.77,1.0))
                        	.ToolTipText(FText::FromString(TEXT("批量清除MinimumLOD参数Mobile项，重置Defuse为0，并取消勾选AutoComputeLODScreenSize\n(处理列表文件保存到 D:盘根目录：Remove-MinimumLOD_文件夹名.txt)")))
                        	.OnClicked(this, &SSlateMain::miniLODset_removeM)
                        	]
                        	+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(1.0f)[
                        		SNew(SButton).Text(FText::FromString(TEXT(" - "))).ButtonColorAndOpacity(FLinearColor(0.80,0.57,0.77,1.0))
                        		.ToolTipText(FText::FromString(TEXT("清除选择的MinimumLOD参数Mobile项，重置Defuse为0\n(处理列表文件保存到 D:盘根目录：Remove-MinimumLOD_Selects.txt)")))
                        		.OnClicked(this, &SSlateMain::removeM_Sel)
                        	]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)[
                        	SNew(SButton).Text(FText::FromString(TEXT("LOD详情"))).ButtonColorAndOpacity(FLinearColor(0.97,0.9,0.67,1.0))
                        	.ToolTipText(FText::FromString(TEXT("列出指定目录中的所有静态网格的LOD等级和每一级的三角面数\n(处理列表文件保存到 D:盘根目录：LOD-LargeProp_文件夹名.txt)")))
                        	.OnClicked(this, &SSlateMain::listLODdetails)
                        ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(0)[
                        	SAssignNew(openTxt, SCheckBox)
                        	.Content()[
                        		SNew(STextBlock).Text(FText::FromString(TEXT("打开文本")))
                        						.ToolTipText(FText::FromString(TEXT("处理完成打开编辑记录文本")))
                        	]
                        ]
                    ]
                    //LOD批处理 第二行
                    + SVerticalBox::Slot().AutoHeight().Padding(2.0f)
                    [
                    SNew(SHorizontalBox)
                    + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(3.0f)[
                    	SNew(SBox)
						.WidthOverride(100.0f)[
                        	SNew(SButton).Text(FText::FromString(TEXT("→ 提取参数"))).ButtonColorAndOpacity(FLinearColor(0.7,0.7,0.7,1.0)).HAlign(HAlign_Right)
                        	// .ToolTipText(FText::FromString(TEXT("提取ContentBrowser中选择的静态模型的 LOD 参数")))
                        	.OnClicked(this, &SSlateMain::GetLODsets_Sel)
                        ]]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(0.0f)[
                                            	SNew(SButton).Text(FText::FromString(TEXT("LOD批处理"))).ButtonColorAndOpacity(FLinearColor(0.4,0.9,0.9,1.0))
                                            	.ToolTipText(FText::FromString(TEXT("批处理指定目录里包含关键字的静态模型 LOD，如果要列出全部文件搜索关键字输入：allmesh\n(处理列表文件保存到 D:盘根目录以文件夹命名) (仅支持StaticMesh类型)")))
                                            	.OnClicked(this, &SSlateMain::largePropLODsets)
                                            ]
                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(0.0f)[
                            SNew(SButton).Text(FText::FromString(TEXT("设置选择"))).ButtonColorAndOpacity(FLinearColor(0.9,0.4,0.9,1.0))
                            .ToolTipText(FText::FromString(TEXT("批处理ContentBrowser中选择的静态模型 LOD\n(支持 StaticMesh 与 SkeletalMesh 两种类型)")))
                            .OnClicked(this, &SSlateMain::largePropLODsets_Sel)
                            ]
                            + SHorizontalBox::Slot().Padding(1.0f).HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
                        											[
                        												SNew(SComboBox<TSharedPtr<FString>>).ToolTipText(FText::FromString(TEXT("选择LOD组定义LOD的级数")))
                        												.OptionsSource(&LODGrpOpations)
                        												.OnGenerateWidget(this, &SSlateMain::comp_ComboItem)
                        												.OnSelectionChanged(this, &SSlateMain::LOD_ComboChanged)
                        												.IsFocusable(true)[
                        													SNew(SBox)
                        												]
                        											]
                        	+ SHorizontalBox::Slot().Padding(1.0f).HAlign(HAlign_Left).VAlign(VAlign_Center).MaxWidth(100)
                        	[
                        		SAssignNew(LODGroupTxt, SEditableTextBox).Text(FText::FromString("LargeProp"))
                        		.BackgroundColor(FLinearColor(0.09f,0.075f,0.13f,1.0f))
                        		.ForegroundColor(FLinearColor(0.6,0.54,0.94,1.0f))
                        	]
                        	+ SHorizontalBox::Slot()
                        	  .HAlign(HAlign_Left).AutoWidth()
                        	[
                        		SAssignNew(autoCompute, SCheckBox).HAlign(HAlign_Left).IsEnabled(false)
                        		.Content()[
                        			SNew(STextBlock).Text(FText::FromString("Auto Compute LOD Distances"))
                        							.ToolTipText(FText::FromString(TEXT("显示Auto Compute LOD Distances参数状态")))
                        		]
                        	]
                    ]
                    + SVerticalBox::Slot().AutoHeight().Padding(1.0f)
                    [
                        SNew(SUniformGridPanel).SlotPadding(0.4f)
                        + SUniformGridPanel::Slot(0, 0)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(STextBlock).Text(LOCTEXT("scres", "Screen Size:"))
                        ]
                        + SUniformGridPanel::Slot(1, 0)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(STextBlock).Text(LOCTEXT("percentp", "Percent Triangles:"))
                        ]
                        
                        + SUniformGridPanel::Slot(0, 1)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                                SAssignNew(SS_0, SSpinBox<float>).MaxValue(1.0).MinValue(0.0).Value(ScreenS_0).ToolTipText(FText::FromString(TEXT("输入第一级LOD自定义窗口大小")))
                                .OnValueChanged(this, &SSlateMain::ssValue_0)
                            ]
                        ]
                        + SUniformGridPanel::Slot(0, 2)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                                SAssignNew(SS_1, SSpinBox<float>).MaxValue(1.0).MinValue(0.0).Value(ScreenS_1).ToolTipText(FText::FromString(TEXT("输入第二级LOD自定义窗口大小")))
                                .OnValueChanged(this, &SSlateMain::ssValue_1)
                            ]
                        ]
                        + SUniformGridPanel::Slot(0, 3)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                                SAssignNew(SS_2, SSpinBox<float>).MaxValue(1.0).MinValue(0.0).Value(ScreenS_2).ToolTipText(FText::FromString(TEXT("输入第三级LOD自定义窗口大小")))
                                .OnValueChanged(this, &SSlateMain::ssValue_2)
                            ]
                        ]
                        + SUniformGridPanel::Slot(0, 4)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                                SAssignNew(SS_3, SSpinBox<float>).MaxValue(1.0).MinValue(0.0).Value(ScreenS_3).ToolTipText(FText::FromString(TEXT("输入第四级LOD自定义窗口大小")))
                                .OnValueChanged(this, &SSlateMain::ssValue_3).Visibility(EVisibility::Collapsed)
                            ]
                        ]
                        + SUniformGridPanel::Slot(1, 1)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                            SAssignNew(PT_0,SSpinBox<int>).MaxValue(100).MinValue(0).Value(PercentT_0)//.MinDesiredWidth(28)
                        	   .ToolTipText(FText::FromString(TEXT("输入第一级LOD自定义删面百分比值")))
                        	   .OnValueChanged(this, &SSlateMain::ptValue_0)
                            ]
                        ]
                        + SUniformGridPanel::Slot(1, 2)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                            SAssignNew(PT_1,SSpinBox<int>).MaxValue(100).MinValue(0).Value(PercentT_1)//.MinDesiredWidth(28)
                        	   .ToolTipText(FText::FromString(TEXT("输入第二级LOD自定义删面百分比值")))
                        	   .OnValueChanged(this, &SSlateMain::ptValue_1)
                            ]
                        ]
                        + SUniformGridPanel::Slot(1, 3)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                            SAssignNew(PT_2,SSpinBox<int>).MaxValue(100).MinValue(0).Value(PercentT_2)//.MinDesiredWidth(28)
                        	   .ToolTipText(FText::FromString(TEXT("输入第三级LOD自定义删面百分比值")))
                        	   .OnValueChanged(this, &SSlateMain::ptValue_2)
                            ]
                        ]
                        + SUniformGridPanel::Slot(1, 4)
                          .HAlign(HAlign_Center).VAlign(VAlign_Center)
                        [
                            SNew(SBox).WidthOverride(260.0f)[
                            SAssignNew(PT_3,SSpinBox<int>).MaxValue(100).MinValue(0).Value(PercentT_3)//.MinDesiredWidth(28)
                        	   .ToolTipText(FText::FromString(TEXT("输入第四级LOD自定义删面百分比值")))
                        	   .OnValueChanged(this, &SSlateMain::ptValue_3).Visibility(EVisibility::Collapsed)
                            ]
                        ]
                        ]
                        + SVerticalBox::Slot().VAlign(VAlign_Center)
                        [
                        	SNew(SHorizontalBox)
                            + SHorizontalBox::Slot().HAlign(HAlign_Center).VAlign(VAlign_Center)
                            [
                                SAssignNew(DisplayLODTri,STextBlock).Text(FText::FromString(TEXT(""))).ColorAndOpacity(FLinearColor(0.39,0.84,0.333,1.0))
                            ]
                        ]
                        + SVerticalBox::Slot().AutoHeight().Padding(1.0f)
                        [
                        	SNew(SHorizontalBox)
                            + SHorizontalBox::Slot().AutoWidth()
                                                	.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(1.0f)
                            [
                                SNew(STextBlock).Text(FText::FromString(TEXT(" Content/"))).ColorAndOpacity(FLinearColor(FLinearColor(0.79,0.114,0.333,1.0)))
                            ]
                        	+ SHorizontalBox::Slot()
                        	  .HAlign(HAlign_Left)
                        	  .AutoWidth()
                        	  .MaxWidth(197)
                        	  .Padding(2.0f)
                        	[
                        		SAssignNew(loddataPath, SEditableTextBox).Text(FText::FromString(*lodpppp)).MinDesiredWidth(150)
                        		.BackgroundColor(FLinearColor(0.66,0.66,0.66,1.0))
                        		.OnTextChanged(this, &SSlateMain::LodDataOnPathText)
                        		]
                        		+ SHorizontalBox::Slot()
                        		  .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(4).AutoWidth()
                        		  .Padding(2.0f)[
                        			SNew(SButton).Text(FText::FromString(TEXT("刷新"))).ButtonColorAndOpacity(FLinearColor(0.3,0.14,0.18,1.0)).ForegroundColor(FLinearColor(0.89,0.214,0.433,1.0))
                        			.ToolTipText(FText::FromString(TEXT("刷新SkeletalMeshLODSettings列表")))
                        			.OnClicked(this, &SSlateMain::LoadLODDataUI)
                        		]
                        		+ SHorizontalBox::Slot().Padding(1.0f).HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
                        												[
                        													SAssignNew(LODdataComb,SComboBox<TSharedPtr<FString>>).ToolTipText(FText::FromString(TEXT("当没有指定LOD Data时将使用上面的LOD组来定义LOD级数")))	//需要使用LODdataComb->RefreshOptions()刷新列表
                        													.OptionsSource(&LODDataOpations)
                        													.OnGenerateWidget(this, &SSlateMain::comp_ComboItem)
                        													.OnSelectionChanged(this, &SSlateMain::LODData_ComboChanged)
                        													.IsFocusable(true)[
                        														SNew(SBox)
                        													]
                        												]
                        		+ SHorizontalBox::Slot().Padding(1.0f).HAlign(HAlign_Left).VAlign(VAlign_Center).MaxWidth(97)
                        		[
                        			SAssignNew(LODDataTxt, SEditableTextBox).Text(FText::FromString("")).MinDesiredWidth(97)
                        			.BackgroundColor(FLinearColor(0.09f,0.075f,0.13f,1.0f))
                        			.ForegroundColor(FLinearColor(0.89,0.214,0.433,1.0))
                        		]
                        		+ SHorizontalBox::Slot().AutoWidth()
                        							.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(1.0f)
                        		[
                        			SAssignNew(LDcount,STextBlock).Text(FText::FromString(TEXT("：0"))).ColorAndOpacity(FLinearColor(FLinearColor(0.6,0.6,0.6,1.0)))
                        		]
								+ SHorizontalBox::Slot()
								  .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(4).AutoWidth()
								  .Padding(2.0f)[
									SAssignNew(getLodBtn,SButton).Text(FText::FromString(TEXT("读取"))).ButtonColorAndOpacity(FLinearColor(0.3,0.14,0.18,1.0)).ForegroundColor(FLinearColor(0.89,0.214,0.433,1.0))
									.ToolTipText(FText::FromString(TEXT("读取SkeletalMeshLODSettings参数")))
									.OnClicked(this, &SSlateMain::LodlodsetVal)
								]
		                        + SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(0)[
                        			SAssignNew(useLODData, SCheckBox)
                        			.Content()[
                        				SNew(STextBlock).Text(FText::FromString(TEXT("载入")))
                        								.ToolTipText(FText::FromString(TEXT("勾选时在设置骨骼模型LOD时会载入选择的预设，取消时将会设置为None")))
                        			]
		                        ]
								+ SHorizontalBox::Slot()
								  .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(4).AutoWidth()
								  .Padding(2.0f)[
									SAssignNew(getLodBtn,SButton).Text(FText::FromString(TEXT("保存"))).ButtonColorAndOpacity(FLinearColor(0.3,0.14,0.18,1.0)).ForegroundColor(FLinearColor(0.89,0.214,0.433,1.0))
									.ToolTipText(FText::FromString(TEXT("保存选中的LOD预设")))
									.OnClicked(this, &SSlateMain::Createlodset)
								]
                        ]
            //LOD-end-
                    ]
                    ]//层级与对齐 垂直折叠面板
                    + SVerticalBox::Slot().AutoHeight()
                                          .Padding(2.0f) //间距
                    [
                        SAssignNew(Expnv12, SExpandableArea) //可折疊面板
                        .AreaTitle(LOCTEXT("v12expn", "AlignParent"))
                    .InitiallyCollapsed(colla2)
                    .Padding(2.0f)
                    .HeaderContent()
                        [
                            SNew(SHorizontalBox)
      
                            + SHorizontalBox::Slot()
                              .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(15.0f).AutoWidth()
                              .Padding(2.0f)[
                                SNew(STextBlock).Text(LOCTEXT("v12", "层级与对齐：")).ColorAndOpacity(FLinearColor(0.2,0.5,0.98,1.0))
                            ]
                            + SHorizontalBox::Slot()
                              .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(8).AutoWidth()
                              .Padding(2.0f)[
                                SNew(SButton).Text(FText::FromString(TEXT("前缀命名"))).ButtonColorAndOpacity(FLinearColor(0.67,0.97,0.67,1.0))
                                .ToolTipText(FText::FromString(TEXT("对选中的物体添加右边文本边框中的前缀")))
                                .OnClicked(this, &SSlateMain::AddPerfix)
                            ]
                            + SHorizontalBox::Slot()
                              .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(4).AutoWidth()
                              .Padding(2.0f)[
                                SNew(SButton).Text(FText::FromString(TEXT("选中"))).ButtonColorAndOpacity(FLinearColor(0.87,0.97,0.57,1.0))
                                .ToolTipText(FText::FromString(TEXT("选中包含右边名字的物体")))
                                .OnClicked(this, &SSlateMain::SelectFromText)
                            ]
                            + SHorizontalBox::Slot()
                              .HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(5)
                              .Padding(2.0f)[
                              SAssignNew(selText, SEditableTextBox).Text(FText::FromString(*s_seltext))
                        	  .BackgroundColor(FLinearColor(0.66,0.66,0.66,1.0))
                        	  .OnTextChanged(this, &SSlateMain::OnSelTextChanged)
                            ]
                            
                        ].BodyContent()[
                            SNew(SVerticalBox)
                            + SVerticalBox::Slot().AutoHeight()
                                                  .Padding(2.0f) //间距
                            [
                                SNew(SHorizontalBox)
                                + SHorizontalBox::Slot()
                                  .HAlign(HAlign_Left).Padding(5.0f)
                                [
                                    SNew(SButton)
                    .Text(LOCTEXT("parent", "设置父子层级"))
                    .ToolTipText(LOCTEXT("parentTT", "选择要设置层级关系的物体，最后选择的为父物体"))
                    .OnClicked(this, &SSlateMain::ParentHelpClicked)
                                ]
                                + SHorizontalBox::Slot()
                                  .HAlign(HAlign_Right).VAlign(VAlign_Center).AutoWidth().Padding(2.0f)
                                [
                                    SNew(STextBlock).Text(LOCTEXT("align", "变换匹配:"))
                                ]
                                + SHorizontalBox::Slot().VAlign(VAlign_Center).AutoWidth()
                                                        .HAlign(HAlign_Right).Padding(2.0f)
                                [
                                    SNew(SButton)
                    .Text(FText::FromString("Location")).VAlign(VAlign_Center).ButtonColorAndOpacity(FLinearColor(0.92,0.84,0.3,1.0))
                    .ToolTipText(LOCTEXT("alignPosTT", "对齐物体（位移）到最后选择的物体"))
                    .OnClicked(this, &SSlateMain::AlignPosClicked)
                                ]
                                + SHorizontalBox::Slot().VAlign(VAlign_Center).AutoWidth()
                                                        .HAlign(HAlign_Right).Padding(2.0f)
                                [
                                    SNew(SButton)
                        .Text(FText::FromString("Rotation")).ButtonColorAndOpacity(FLinearColor(0.92,0.84,0.3,1.0))
                    .ToolTipText(LOCTEXT("alignRotTT", "对齐物体（旋转）到最后选择的物体，右边值大于‘0’将取随机角度"))
                    .OnClicked(this, &SSlateMain::AlignRotClicked)
                                ]
                                + SHorizontalBox::Slot().VAlign(VAlign_Center)
                                                        .HAlign(HAlign_Left).AutoWidth().Padding(2.0f)
                                [
                                    SAssignNew(randomAngle, SSpinBox<int>).MaxValue(360).MinValue(0).Value(0).MinDesiredWidth(36)
                                    .ToolTipText(LOCTEXT("randval", "值大于‘0’将按该值随机角度旋转"))
                                    .OnValueChanged(this, &SSlateMain::btn360)
                                ]
                                + SHorizontalBox::Slot().VAlign(VAlign_Center).AutoWidth()
                                                        .HAlign(HAlign_Right).Padding(2.0f)
                                [
                                    SNew(SButton)
                        .Text(FText::FromString("Scale")).ButtonColorAndOpacity(FLinearColor(0.92,0.84,0.3,1.0))
                    .ToolTipText(LOCTEXT("alignSclTT", "对齐物体（缩放）到最后选择的物体"))
                    .OnClicked(this, &SSlateMain::AlignSclClicked)
                                ]
                            ]
                            + SVerticalBox::Slot().AutoHeight()
                                                  .Padding(2.0f)
                            [
                                SNew(SUniformGridPanel).SlotPadding(3.0f)
      
                                + SUniformGridPanel::Slot(0, 0)
                                  .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                    SNew(STextBlock).Text(LOCTEXT("mo", "行数"))
                                ]
                                + SUniformGridPanel::Slot(1, 0)
                                  .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                    SNew(STextBlock).Text(LOCTEXT("spacing", "列间距"))
                                ]
                                + SUniformGridPanel::Slot(2, 0)
                                  .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                    SNew(STextBlock).Text(LOCTEXT("moSp", "行间距"))
                                ]
                                + SUniformGridPanel::Slot(0, 2)
                                  .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                                    .Text(LOCTEXT("aX", "[X]■■■")).ButtonColorAndOpacity(FLinearColor(0.94,0.2,0.2,1.0))
                                    .ToolTipText(LOCTEXT("aXtt", "按 X 轴排列"))
                                    .OnClicked(this, &SSlateMain::XArray_Clicked)
                                ]
                                + SUniformGridPanel::Slot(0, 1)
                                  .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                	SNew(SBox).MaxDesiredWidth(70)[
                                    SAssignNew(arrayRow, SSpinBox<int>).MaxValue(100).MinValue(1).Value(s_rowNum).MinDesiredWidth(70)
                                    .OnValueChanged(this,&SSlateMain::RowNumSave)
                                ]]
                                + SUniformGridPanel::Slot(1, 1)
                                  .HAlign(HAlign_Fill).VAlign(VAlign_Center)
                                [
									SNew(SBox).MaxDesiredWidth(70)[
                                    SAssignNew(arraySpace, SSpinBox<float>).MaxValue(8000.0f).MinValue(-300.0f).Value(0.0f).SliderExponent(21).MinDesiredWidth(70)
                        			.OnValueChanged(this,&SSlateMain::XArray_slide)
                                ]]
                                + SUniformGridPanel::Slot(2, 1)
                                  .HAlign(HAlign_Fill).VAlign(VAlign_Center)
                                [SNew(SBox).MaxDesiredWidth(70)[
                                    SAssignNew(arrayRowSp, SSpinBox<float>).MaxValue(8000.0).MinValue(-300.0).Value(0.0).SliderExponent(21).MinDesiredWidth(70)
                        			.OnValueChanged(this,&SSlateMain::XArray_slide)
                                ]]
                                + SUniformGridPanel::Slot(3, 1)
                                  .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [
                                    SAssignNew(matrixNum, SSpinBox<int>).MaxValue(10000).MinValue(1).Value(s_Matrix).SliderExponent(100).MinDesiredWidth(57)
                                    .OnValueChanged(this, &SSlateMain::maixSave)
                                ]
                                + SUniformGridPanel::Slot(1, 2)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                                    .Text(LOCTEXT("aY", "[Y]■■■")).ButtonColorAndOpacity(FLinearColor(0.2,0.94,0.2,1.0))
                                    .ToolTipText(LOCTEXT("aYtt", "按 Y 轴排列"))
                                    .OnClicked(this, &SSlateMain::YArray_Clicked)
                                ]
                                + SUniformGridPanel::Slot(2, 2)
                                .HAlign(HAlign_Center)
                                [
                        			SNew(SButton).Text(LOCTEXT("arrTT", "输出坐标")).ToolTipText(FText::FromString(TEXT("输出所选择的物体名称与位置信息到文本,到C盘")))
                        			.OnClicked(this,&SSlateMain::OutPutActorPos)
                                ]
                        //         + SUniformGridPanel::Slot(3, 3)
                        //         .HAlign(HAlign_Center)
                        //         [
                        //             SNew(SButton)
                        // .Text(FText::FromString(TEXT("矩阵Box")))
                        // .ToolTipText(LOCTEXT("maix", "根据上面数量创建辅助盒子矩阵"))
                        // .OnClicked(this, &SSlateMain::CreateBoxs)
                        //         ]
                                + SUniformGridPanel::Slot(3, 2)
                                .HAlign(HAlign_Center)
                                [
                                    SNew(SButton)
                        .Text(FText::FromString(TEXT("克隆对象")))
                        .ToolTipText(FText::FromString(TEXT("根据上面数量克隆选中的模型对象")))
                        .OnClicked(this, &SSlateMain::CloneActor)
                                ]
                                + SUniformGridPanel::Slot(2, 3)
                                .HAlign(HAlign_Center)
                                [
                                    SNew(SButton)
                        .Text(FText::FromString(TEXT("选择相同"))).ButtonColorAndOpacity(FLinearColor(0.87,0.97,0.57,1.0))
                        .ToolTipText(FText::FromString(TEXT("根据选中的第一个StaticMeshActor对象,选择前段相同名称的对象")))
                        .OnClicked(this, &SSlateMain::SelSameObj)
                                ]
                                //----------------------------
                                + SUniformGridPanel::Slot(3, 0)
                                  .HAlign(HAlign_Center).VAlign(VAlign_Center)
                                [SNew(STextBlock).Text(LOCTEXT("bound", "矩阵数"))
                                ]
                                + SUniformGridPanel::Slot(4, 0)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("Xadd", "X←")).ButtonColorAndOpacity(FLinearColor(0.94,0.2,0.2,1.0))
                        .ToolTipText(LOCTEXT("Xo", "对齐至X轴边界"))
                        .OnClicked(this, &SSlateMain::XoAlignX_Clicked)
                                ]
                                + SUniformGridPanel::Slot(6, 0)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("-Xadd", "←X")).ButtonColorAndOpacity(FLinearColor(0.94,0.2,0.2,1.0))
                        .ToolTipText(LOCTEXT("oX", "对齐至-X轴边界"))
                    .OnClicked(this, &SSlateMain::oXAlignX_Clicked)
                                ]
                                + SUniformGridPanel::Slot(5, 0)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("cXadd", "→X←")).ButtonColorAndOpacity(FLinearColor(0.94,0.2,0.2,1.0))
                        .ToolTipText(LOCTEXT("oXo", "对齐至X轴中间"))
                    .OnClicked(this, &SSlateMain::oXoAlignX_Clicked)
                                ]
      
                                + SUniformGridPanel::Slot(4, 1)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("Yadd", "Y←")).ButtonColorAndOpacity(FLinearColor(0.2,0.94,0.2,1.0))
                        .ToolTipText(LOCTEXT("Yo", "对齐至Y轴边界"))
                    .OnClicked(this, &SSlateMain::YoAlignY_Clicked)
                                ]
                                + SUniformGridPanel::Slot(6, 1)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("-Yadd", "←Y")).ButtonColorAndOpacity(FLinearColor(0.2,0.94,0.2,1.0))
                        .ToolTipText(LOCTEXT("oY", "对齐至-Y轴边界"))
                    .OnClicked(this, &SSlateMain::oYAlignY_Clicked)
                                ]
                                + SUniformGridPanel::Slot(5, 1)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("cYadd", "→Y←")).ButtonColorAndOpacity(FLinearColor(0.2,0.94,0.2,1.0))
                        .ToolTipText(LOCTEXT("oYo", "对齐至Y轴中间"))
                    .OnClicked(this, &SSlateMain::oYoAlignY_Clicked)
                                ]
      
                                + SUniformGridPanel::Slot(4, 2)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("Zadd", "Z←")).ButtonColorAndOpacity(FLinearColor(0.2,0.2,0.94,1.0))
                        .ToolTipText(LOCTEXT("Zo", "对齐至Z轴边界"))
                    .OnClicked(this, &SSlateMain::ZoAlignZ_Clicked)
                                ]
                                + SUniformGridPanel::Slot(6, 2)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("-Zadd", "←Z")).ButtonColorAndOpacity(FLinearColor(0.2,0.2,0.94,1.0))
                        .ToolTipText(LOCTEXT("oZ", "对齐至-Z轴边界"))
                    .OnClicked(this, &SSlateMain::oZAlignZ_Clicked)
                                ]
                                + SUniformGridPanel::Slot(5, 2)
                                .HAlign(HAlign_Fill)
                                [
                                    SNew(SButton)
                        .Text(LOCTEXT("cZadd", "→Z←")).ButtonColorAndOpacity(FLinearColor(0.2,0.2,0.94,1.0))
                        .ToolTipText(LOCTEXT("oZo", "对齐至Z轴中间"))
                    .OnClicked(this, &SSlateMain::oZoAlignZ_Clicked)
                                ]
                            ]
                        ]
                    ]
		// ]
	];
}

FReply SSlateMain::testClicked()
{
	FString cick;
	if (Expnv12->IsExpanded())
	{
		Expnv12->SetExpanded(false);
		Expnv1->SetExpanded(true);
		cick = "true";
		TSharedPtr<SWindow> ActiveWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
		if(ActiveWindow.IsValid())
		{
			ActiveWindow->SetViewportSizeDrivenByWindow(true);
		}
	}
	else
	{
		Expnv12->SetExpanded(true);
		Expnv1->SetExpanded(false);
		cick = "false";
	}
	CFN.WriteIni(FString("SceneTools"),FString("collapse"),cick,IniPath);
	//UE_LOG(LogTemp, Error, TEXT("test %i"), arrayRow);
	return FReply::Handled();
}

FReply SSlateMain::ParentHelpClicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 0)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				Actor->AttachToActor(ppp, FAttachmentTransformRules::KeepWorldTransform);
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
			}
		}
		GEditor->SelectNone(false, true);
		GEditor->SelectActor(ppp, true, true);
	}
	return FReply::Handled();
}

//===================[Array]==============================

void SSlateMain::maixSave(FPlatformTypes::int32 val)
{
	CFN.WriteIni(FString("SceneTools"), FString("Matrix"), FString::FromInt(val), IniPath);
}
void SSlateMain::RowNumSave(FPlatformTypes::int32 val)
{
	SSlateMain::XArray_slide(1.0);
	CFN.WriteIni(FString("SceneTools"), FString("RowNum"), FString::FromInt(val), IniPath);
}

void SSlateMain::XArray_slide(float val)
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
    if (SelectionSet->Num() > 1)
    {
    	TArray<AActor*> SelectedActors;
    	SelectedActors.Reserve(SelectionSet->Num());
    	SelectionSet->GetSelectedObjects(SelectedActors);
    	AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
    	FVector pO, pE;
    	ppp->GetActorBounds(true, pO, pE);
    	float SpAdd = pO.Y;
    	float RowSp = pO.X;
    	int CN = 0;
    	int Rows = arrayRow->GetValue();
    	for (AActor* Actor : SelectedActors)
    	{
    		if (Actor->GetFName() != ppp->GetFName())
    		{
    			FVector Origin, Extent;
    			Actor->GetActorBounds(true, Origin, Extent);  //Orgin=中心坐标,Extent=基于中心的边界位置
    			CN++;
    			SpAdd += (pE.Y + Extent.Y + float(arrayRowSp->GetValue()));
    			if (CN % Rows == 0)
    			{
    				SpAdd = pO.Y;
    				RowSp += float(arraySpace->GetValue()) + pE.X * 2;
    			}
    			// FVector newp = FVector(RowSp, SpAdd, pO.Z - pE.Z);
    			FVector newp = FVector(RowSp, SpAdd, ppp->GetActorLocation().Z);
    			Actor->SetActorLocation(newp);
    		}
    	}
    }
}
/*
FReply SSlateMain::CreateBoxs()
{
	FVector Cpos = FVector::ZeroVector;
	FVector Cscl = FVector(1,1,1);
	FRotator Crot = FRotator::ZeroRotator;
	USelection* SelectionSet = GEditor->GetSelectedActors();
	AActor* ppp;
	FVector pO, pE;
    UWorld* World = GEditor->GetEditorWorldContext().World();
     if (SelectionSet->Num() == 1)
     {
     	TArray<AActor*> SelectedActors;
     	SelectedActors.Reserve(SelectionSet->Num());
     	SelectionSet->GetSelectedObjects(SelectedActors);
		ppp = SelectedActors[0];
		ppp->GetActorBounds(true, pO, pE);
     	Cpos=ppp->GetActorLocation();
     	Crot=ppp->GetActorRotation();
     	Cscl=ppp->GetActorScale();

     	// FActorSpawnParameters Par;
     	// Par.Template = SelectedActors[0];
     	
     }
	SelectionSet->DeselectAll();
	FString boxname;
	FString levN;
	FString LLL = World->GetCurrentLevel()->GetPathName();
	LLL.Split(".",nullptr,&levN);
	levN.Split(":", &levN, nullptr);
	FString STLevel = "";
	CFN.ReadIniValue(FString("SceneTools"), levN, STLevel, IniPath);
	int STcunt;
	STcunt = FCString::Atoi(*STLevel);
	if (STcunt > 0)
	{
		int CEO=0; //计算场景有多少组矩阵盒子
		TArray<AActor*> ActorsToFind;
		if(World)
		{ // GetAllActorsOfClass(World, 类型的::StaticClass(), 定义的存放数组);
			UGameplayStatics::GetAllActorsOfClass(World, AStaticMeshActor::StaticClass(), ActorsToFind);
		}
		for (int i = 1; i <= STcunt; i++)	//遍历场景中所有的StaticMeshActor物体,查找是否存在矩阵盒子,如果没有将记录归为1
		{
			for (AActor* inActor: ActorsToFind){
				//这里查找名字是否包含用Find,不能用GetName()==".." 否则在第二次创建物体时会误判为找不到名称
				if(inActor->GetName().Find(FString::Printf(TEXT("STBox%i"), i))>-1)
					CEO+=1;
			}
		}
		if (CEO > 0)
		{
			STcunt += 1;
            CFN.WriteIni(FString("SceneTools"), levN, FString::FromInt(STcunt), IniPath);
		}else
		{
			CFN.WriteIni(FString("SceneTools"), levN, "1", IniPath);
			STcunt = 1;
		}
		
	}else{
		CFN.WriteIni(FString("SceneTools"), levN, "1", IniPath);
		STcunt = 1;
	}
    for (int i = 1; i <= matrixNum->GetValue(); i++)
    {
    	AStaticMeshActor* MyActor = World->SpawnActor<AStaticMeshActor>(bpZMaitrexClass, (FVector(0,(pE.Y * 2),0)+Cpos), Crot);
        boxname = "STBox"+FString::FromInt(STcunt)+"_" + FString::FromInt(i);
        MyActor->SetActorLabel(boxname);
        MyActor->SetFolderPath("STBox_Folder");
    	MyActor->SetActorScale3D(Cscl);
        SelectionSet->Select(MyActor);	//选中对象
    	// if (i==1) SelectionSet->ToggleSelect(MyActor);
        TArray<UActorComponent*> comps;
        MyActor->GetComponents(comps);
        auto* textComp = Cast<UTextRenderComponent>(comps[comps.Num()-1]);
        // auto* boxmesh = Cast<UStaticMeshComponent>(comps[1]);
        // boxmesh->SetRelativeScale3D(Cscl);	//设置物体组件模型缩放值
        FString TTT = FString::Printf(TEXT("%s\n"), *boxname);
        textComp->SetText(FText::FromString(TTT));
        // textComp->SetWorldSize(14*Cscl.Y);
        textComp->bHiddenInGame = true;
    }
	SSlateMain::XArray_slide(1.0);
	return FReply::Handled();
}
*/
FReply SSlateMain::OutPutActorPos()
{
	// auto* obj = FindObject<AActor>(ANY_PACKAGE,*suffixSeach->GetText().ToString());
	//  FString sn = "No Obj";
	// if (obj) sn = obj->GetActorLocation().ToString();
	//GEngine->AddOnScreenDebugMessage(-1, 16.f, FColor::Green, FString::Printf(TEXT("选择物体: %s"), *sn));
	USelection* SelectionSet = GEditor->GetSelectedActors();
    if (SelectionSet->Num() > 1)
    {
    	TArray<AActor*> SelectedActors;
    	SelectedActors.Reserve(SelectionSet->Num());
    	SelectionSet->GetSelectedObjects(SelectedActors);
    	if (SelectedActors[0]->GetName().Left(5)=="STBox")
    	{
    		FString outtext="";
    	
    		for (AActor* actor: SelectedActors)
    		{
    			FString boxname = actor->GetName();
    			FString postext = FString::Printf(TEXT("X: %i  Y: %i  Z: %i"), int(actor->GetActorLocation().X), int(actor->GetActorLocation().Y), int(actor->GetActorLocation().Z));
    			TArray<UActorComponent*> comps;
    			actor->GetComponents(comps);
    			UTextRenderComponent* textComp = Cast<UTextRenderComponent>(comps[comps.Num()-1]);
    			FString TTT = FString::Printf(TEXT("%s\n%s"), *boxname, *postext);
    			textComp->SetText(FText::FromString(TTT));
    			outtext += FString::Printf(TEXT("%s\t:\t%s\n"),*boxname, *postext);
    		}
		
    		FString outFile = "D:/ActorPos.txt";
    		WriteTxt(outtext, outFile);
    		//打开创建的txt文本
            if (openTxt->IsChecked())
            {
	            FString FP = FString::Printf(TEXT("start %s"), *outFile);
            	system(TCHAR_TO_UTF8(*FP));
            }
    	}
    }
	return FReply::Handled();
}

FReply SSlateMain::XArray_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		float SpAdd = pO.Y;
		float RowSpAdd = 0.f;
		float RowSp = pO.X;
		int CN = 0;
		int Rows = arrayRow->GetValue();
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				CN++;
				SpAdd += pE.Y + Extent.Y + float(arrayRowSp->GetValue());
				if (CN % Rows == 0)
				{
					SpAdd = pO.Y;
					RowSp += float(arraySpace->GetValue()) + pE.X * 2;
				}
				FVector newp = FVector(RowSp, SpAdd, ppp->GetActorLocation().Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::YArray_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		float SpAdd = pO.X;
		float RowSpAdd = 0.f;
		float RowSp = pO.Y;
		int CN = 0;
		int Rows = arrayRow->GetValue();
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				CN++;
				SpAdd += pE.X + Extent.X + float(arrayRowSp->GetValue());
				if (CN % Rows == 0)
				{
					SpAdd = pO.X;
					RowSp += float(arraySpace->GetValue()) + Extent.Y * 2;
				}
				FVector newp = FVector(SpAdd, RowSp, ppp->GetActorLocation().Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

//===================[Align]==============================
FReply SSlateMain::XoAlignX_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X + pE.X + Extent.X, Origin.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::oXAlignX_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X - pE.X - Extent.X, Origin.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::oXoAlignX_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, Origin.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::YoAlignY_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, pO.Y + pE.Y + Extent.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::oYAlignY_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, pO.Y - pE.Y - Extent.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::oYoAlignY_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, pO.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::ZoAlignZ_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, Origin.Y, pO.Z + pE.Z + Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::oZAlignZ_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, Origin.Y, pO.Z - pE.Z - Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::oZoAlignZ_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, Origin.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

//----------------------------------------------

FReply SSlateMain::cAlignX_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X + pE.X + Extent.X, pO.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::cAlignNX_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X - pE.X - Extent.X, pO.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::cAlignY_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y + pE.Y + Extent.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::cAlignNY_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y - pE.Y - Extent.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::cAlignZ_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y, pO.Z + pE.Z + Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::cAlignNZ_Clicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y, pO.Z - pE.Z - Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

//==============================================
FReply SSlateMain::AlignPosClicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				Actor->SetActorLocation(ppp->GetActorLocation());
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

FReply SSlateMain::AlignRotClicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 0)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (randomAngle->GetValue() == 0)
			{
				if (Actor->GetFName() != ppp->GetFName())
				{
					Actor->SetActorRotation(ppp->GetActorRotation());
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
				}
			}
			else
			{
				Actor->SetActorRotation(FRotator(0.f, float(FMath::RandRange(-int(randomAngle->GetValue()), int(randomAngle->GetValue()))), 0.f)+Actor->GetActorRotation());
			}
		}
	}
	return FReply::Handled();
}

FReply SSlateMain::AlignSclClicked()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1)
	{
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName())
			{
				Actor->SetActorScale3D(ppp->GetActorScale3D());
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
			}
		}
	}
	else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}


FReply SSlateMain::ResetTextureLODBias()
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","贴图批处理");
	FString meg = FString::Printf(TEXT("确认要批量重置 LOD Bias?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
    	TArray<FAssetData> AssetDatas;
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
        FARFilter Filter;
        FString pName;
        if (pp != "")
        {
            //查找路径是否是反斜杠，如果是切割并替换成正斜杠
            if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
            {
                FString newP = "";
                TArray<FString> SArr;
                pp.ParseIntoArray(SArr, TEXT("\\"), false);
                for (const FString sss : SArr)
                {
                	newP += sss + "/";
                }
                pp = newP;
            }
            FString en = pp.Right(1);
            if (en == "/")
                pp = pp.LeftChop(1);
            //提取最后一个目录名 pName
            TArray<FString> SArr;
            pp.ParseIntoArray(SArr, TEXT("/"), false);
            pName = SArr[SArr.Num() - 1];
            Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
        }else
        {
            pName = "Content";
            Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
        }
        Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());  //添加过滤文件类型
        if (RPath->IsChecked())
        {
            //遞歸搜尋路径，查找子目录
            Filter.bRecursivePaths = true;
        }
        else
        {
            Filter.bRecursivePaths = false;
        }
        Filter.bRecursiveClasses = true;
        AssetRegistryModule.Get().GetAssets(Filter, AssetDatas);
    
        FString mess = FString::Printf(TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
        GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, *mess);
        UE_LOG(LogTemp, Warning, TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
        int cou = 0;
        FString FileName = FString::Printf(TEXT("d:/TexResetLODBiasList-%s.txt"), *pName);
        FString Content;
        for (const FAssetData& AssetData : AssetDatas)
        {
            UTexture2D* MatObj = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr,
                                                               (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
            if (MatObj->GetName().Right(suffixSeach->GetText().ToString().Len()) == suffixSeach->GetText().ToString())
            {
            	
                if ( MatObj->LODBias >= 1) {
                	MatObj->LODBias = 0;
                	//標記未保存星號
                	MatObj->AddToRoot();
                	MatObj->UpdateResource();
                	MatObj->MarkPackageDirty();
                	cou += 1;
                	//文件路径写入文本
                	FString MatPath = *MatObj->GetPathName();
                	FString MatLeft;
                	MatPath.Split(".", &MatLeft, nullptr);
                	Content += FString::Printf(TEXT("%s\n"), *MatLeft);
                }
            }
        }
        if (cou > 0)
        {
            Content += FString::Printf(TEXT("共搜索 %i 个贴图文件, 如上 %i 个文件调整\n"),AssetDatas.Num() ,cou);
            UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
            FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            //打开创建的txt文本
            if (openTxt->IsChecked())
            {
	            FString FP = FString::Printf(TEXT("start %s"), *FileName);
            	system(TCHAR_TO_UTF8(*FP));
            }
            UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个贴图文件"), cou);
            GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个贴图文件"), cou));
        }
    }else
    {
    	GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("取消"));
    }
	return FReply::Handled();
}

FReply SSlateMain::GetLODsets_Sel()	//提取参数
{
	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    TArray<FAssetData> SelectedAssets;
    ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);
	if(SelectedAssets.Num()>0)
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::White, FString::Printf(TEXT("类型：(%s)"), *SelectedAssets[0].AssetClass.ToString()));
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("未选择资源管理器文件"));
	}
    if (SelectedAssets.Num() == 1)
    {
	    TArray<TSharedPtr<SSpinBox<float>>> allSS = {SS_0, SS_1, SS_2, SS_3};	//初始化数组存放变量
	    TArray<TSharedPtr<SSpinBox<int>>> allPT = {PT_0, PT_1, PT_2, PT_3};
	    FString lodTriangles=""; 
	    if(SelectedAssets[0].AssetClass == UStaticMesh::StaticClass()->GetFName())
	    {
		    UStaticMesh* StaticMesh = Cast<UStaticMesh>(SelectedAssets[0].GetAsset());
	    	if (StaticMesh)
	    	{
	            const FText LG = FText::FromString(StaticMesh->LODGroup.ToString());	//注意LG变量在下面使用中的类型匹配！
	    		LODGroupTxt->SetText(LG);
	    		//错误提示指出在调用TArray::Contains函数时，使用了错误的比较类型FText。应该使用TSharedPtr<FString, ESPMode::NotThreadSafe>作为比较类型，因为数组LODGrpOpations中存储的是TSharedPtr<FString, ESPMode::NotThreadSafe>类型的指针。
	    		// TSharedPtr<FString, ESPMode::NotThreadSafe> NewOption = MakeShared<FString>(LG.ToString());
	    	//转换uint8类型为TAttribute<ECheckBoxState>，用于设置CheckBox控件
	    		uint8 Value = StaticMesh->bAutoComputeLODScreenSize;
	            const TAttribute<ECheckBoxState> Attribute = TAttribute<ECheckBoxState>::Create(
	    			[Value]() {
	    				return (Value != 0) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
	    			}
	    		);
	    		autoCompute->SetIsChecked(Attribute);
	    		// autoCompute->SetIsChecked(StaticMesh->bAutoComputeLODScreenSize);
	    		int Lods = StaticMesh->GetNumLODs();
	    		if (Lods > 4){Lods = 4;}
	    		for(int I = 0; I < Lods; I++)
	    		{
	    			const FStaticMeshSourceModel& SourceModel = StaticMesh->GetSourceModel(I);
	    			if(lodTriangles=="")
	    				lodTriangles+=FString::Printf(TEXT("(LOD%i:▲ %i )"),I,StaticMesh->RenderData->LODResources[I].GetNumTriangles());
	                else
						lodTriangles+=FString::Printf(TEXT("\t(LOD%i:▲ %i )"),I,StaticMesh->RenderData->LODResources[I].GetNumTriangles());
	    			allSS[I]->SetValue(SourceModel.ScreenSize.Default);
	    			allPT[I]->SetValue(static_cast<int>(round(SourceModel.ReductionSettings.PercentTriangles * 100)));	//使用static_cast<int>(round(...))将小数计算自动四舍五入输出整数
	    		}
	    		DisplayLODTri->SetText(lodTriangles);
	    		if(Lods == 1)
	    		{
	    			SS_1->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    			PT_1->SetVisibility(EVisibility::Hidden);
	    			SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    			PT_2->SetVisibility(EVisibility::Hidden);
	    			SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    			PT_3->SetVisibility(EVisibility::Hidden);
	    		}else if(Lods == 2)
	    		{
	    			SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
	    			PT_1->SetVisibility(EVisibility::Visible);
	    			SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    			PT_2->SetVisibility(EVisibility::Hidden);
	    			SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    			PT_3->SetVisibility(EVisibility::Hidden);
	    		}else if(Lods == 3)
                {
                    SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
                    PT_1->SetVisibility(EVisibility::Visible);
                    SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
                    PT_2->SetVisibility(EVisibility::Visible);
	    			SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    			PT_3->SetVisibility(EVisibility::Hidden);
	    		}else if(Lods == 4)
                {
                    SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
                    PT_1->SetVisibility(EVisibility::Visible);
                    SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
                    PT_2->SetVisibility(EVisibility::Visible);
                    SS_3->SetVisibility(EVisibility::Visible);	//显示::Visible
                    PT_3->SetVisibility(EVisibility::Visible);
                }
	    	}
	    }
	    else if(SelectedAssets[0].AssetClass == *USkeletalMesh::StaticClass()->GetName())	//这里前面的AssetClass未使用.ToString()，USkeletalMesh前面需要加指针
	    {
	    	autoCompute->SetIsChecked(ECheckBoxState::Unchecked);
	    	USkeletalMesh* SKMesh = Cast<USkeletalMesh>(SelectedAssets[0].GetAsset());
	    	if(SKMesh->LODSettings == nullptr)
	    		useLODData->SetIsChecked(ECheckBoxState::Unchecked);
	        else
				useLODData->SetIsChecked(ECheckBoxState::Checked);
	        const int Lods = SKMesh->GetLODNum();
	    	if(Lods == 1)
	    	{
	    		LODGroupTxt->SetText(FText::FromString("None"));
	    		SS_1->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    		PT_1->SetVisibility(EVisibility::Hidden);
	    		SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    		PT_2->SetVisibility(EVisibility::Hidden);
	    		SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    		PT_3->SetVisibility(EVisibility::Hidden);
	    	}else if(Lods == 2)
	    	{
	    		LODGroupTxt->SetText(FText::FromString("SmallProp"));
	    		SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
	    		PT_1->SetVisibility(EVisibility::Visible);
	    		SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    		PT_2->SetVisibility(EVisibility::Hidden);
	    		SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    		PT_3->SetVisibility(EVisibility::Hidden);
	    	}else if(Lods == 3)
            {
	    		LODGroupTxt->SetText(FText::FromString("LargeProp"));
                SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
                PT_1->SetVisibility(EVisibility::Visible);
                SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
                PT_2->SetVisibility(EVisibility::Visible);
	    		SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
	    		PT_3->SetVisibility(EVisibility::Hidden);
	    	}else if(Lods == 4)
            {
	    		LODGroupTxt->SetText(FText::FromString("LevelArchitecture"));
                SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
                PT_1->SetVisibility(EVisibility::Visible);
                SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
                PT_2->SetVisibility(EVisibility::Visible);
                SS_3->SetVisibility(EVisibility::Visible);	//显示::Visible
                PT_3->SetVisibility(EVisibility::Visible);
            }
	    	for(int32 LODi = 0; LODi < Lods; ++LODi)
	    	{
		        const FSkeletalMeshLODInfo* LODInfo = SKMesh->GetLODInfo(LODi);
	    		allSS[LODi]->SetValue(LODInfo->ScreenSize.Default);
	    		const FSkeletalMeshOptimizationSettings& ReductionSettings = LODInfo->ReductionSettings;
	    		allPT[LODi]->SetValue(ReductionSettings.NumOfTrianglesPercentage * 100.0f);
	    		if(lodTriangles=="")
	    			lodTriangles+=FString::Printf(TEXT("(LOD%i:▲ %i )"),LODi,SKMesh->GetResourceForRendering()->LODRenderData[LODi].GetTotalFaces());
	    		else
	    			lodTriangles+=FString::Printf(TEXT("\t(LOD%i:▲ %i )"),LODi,SKMesh->GetResourceForRendering()->LODRenderData[LODi].GetTotalFaces());
	    		DisplayLODTri->SetText(lodTriangles);
	    		// GEngine->AddOnScreenDebugMessage(-1, 126.f, FColor::Blue, FString::Printf(TEXT("NumOfTrianglesPercentage : %f "), ReductionSettings.NumOfTrianglesPercentage));
	    	}
	    }
    	DisplayLODTri->SetColorAndOpacity(FLinearColor(0.39,0.84,0.333,1.0));
    }
	return FReply::Handled();
}
FReply SSlateMain::largePropLODsets_Sel()	//批量处理资源管理器中选择的模型LODLargeProp
{	FText const Title = LOCTEXT("title1","LOD批处理");
	FText const DialogText = LOCTEXT("queren","批量设置资源管理器中选中对象的LOD参数\n（需要选择StaticMesh或SkeletalMesh类型的模型文件）");
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
	    // USelection* SelectedAssets = GEditor->GetSelectedObjects();
	    const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    	TArray<FAssetData> SelectedAssets;
    	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

	    const int Sels = SelectedAssets.Num();
    	GEngine->AddOnScreenDebugMessage(-1, 26.f, FColor::Yellow, FString::Printf(TEXT("共选择 %i 个文件"), Sels));
        if (Sels > 0)
        {
	        const FString FileName = FString::Printf(TEXT("d:/LOD-LODSets_Selects.txt"));
			int cou = 0;
            FString Content;

	        for (const FAssetData& AssetData : SelectedAssets)
	        {
                const float PTval_0 = PT_0->GetValue();
                const float PTval_1 = PT_1->GetValue();
                const float PTval_2 = PT_2->GetValue();
                const float PTval_3 = PT_3->GetValue();
	        	TArray<float> SSize = {SS_0->GetValue(), SS_1->GetValue(), SS_2->GetValue(), SS_3->GetValue()};
	        	TArray<float> PTria = {(PTval_0/100.0f), (PTval_1/100.0f), (PTval_2/100.0f), (PTval_3/100.0f)};
	        	if (AssetData.AssetClass == UStaticMesh::StaticClass()->GetFName())
	        	{
	        		UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetData.GetAsset());
	        		if (StaticMesh){
	        			FString Nam = StaticMesh->GetName();
	        			StaticMesh->SetLODGroup(*LODGroupTxt->GetText().ToString());
	        			StaticMesh->bAutoComputeLODScreenSize = false;
	        			FStaticMeshRenderData& RenderData = *StaticMesh->RenderData;	//获取静态网格渲染数据
	        			int32 Rc = 0;
	                    const int32 LODs = StaticMesh->GetNumLODs();
	        			for (FStaticMeshLODResources& LODR : RenderData.LODResources)
	        			{
	        				FStaticMeshSourceModel& SourceModel = StaticMesh->GetSourceModel(Rc);	//获取每一级LOD中的ScreenSize值（SourceModel.ScreenSize.Default）
	        				SourceModel.ScreenSize.Default = SSize[Rc];
	        				SourceModel.ReductionSettings.PercentTriangles = PTria[Rc];
	        				Rc += 1;
	        				if (LODs > 2 && (Rc+1) == LODs)
	        				{
	                            const int32 Secs = LODR.Sections.Num();
	        					GEngine->AddOnScreenDebugMessage(-1, 66.f, FColor::Yellow, FString::Printf(TEXT("%s 共 %i 个材质球"), *Nam, Secs));
	        					if (Secs > 0)
	        					{
	        						for (int S=0; S<Secs; S++)	//设置最后一级LOD材质球关闭阴影
	        						{
	        							FMeshSectionInfo Info = StaticMesh->GetSectionInfoMap().Get(Rc, S);
	        							Info.bCastShadow = false;
	        							StaticMesh->GetSectionInfoMap().Set(Rc, S, Info);
	        						}
	        					}
	        				}
	        			}
	        			Content += FString::Printf(TEXT("%s\n"), *Nam);
	        			//GEngine->AddOnScreenDebugMessage(-1, 156.f, FColor::Green, FString::Printf(TEXT("%s   LODs:%i)  (%s)"), *Nam, LRN, *SSNS));
                    
	        			cou += 1;
	        			//设置bCastShadow等LOD参数刷新必需要这两项
	        			StaticMesh->Modify();
	        			StaticMesh->PostEditChange();
	        			//标记为修改*
	        			StaticMesh->AddToRoot();
	        			StaticMesh->MarkPackageDirty();
	        		}
        			if (cou > 0)
		            {
		                Content += FString::Printf(TEXT("共选择 %i 个模型文件, 如上 %i 个文件修改\n"),Sels ,cou);
		                UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
		                FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
		                //打开创建的txt文本
		                if (openTxt->IsChecked()) {
			                const FString FP = FString::Printf(TEXT("start %s"), *FileName);
            				system(TCHAR_TO_UTF8(*FP));
		                }
		                UE_LOG(LogTemp, Warning, TEXT("共修改 %i 个文件"), cou);
		                GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Yellow, FString::Printf(TEXT("共处理 %i 个文件"), cou));
		            }
	        	}
	            else if(AssetData.AssetClass == *USkeletalMesh::StaticClass()->GetName())	//这里的USkeletalMesh前面需要加指针
	            {
		            USkeletalMesh* SKMesh = Cast<USkeletalMesh>(AssetData.GetAsset());
	            	// const int32 Lods = SKMesh->GetLODNum();
	            	//定义用于Cast获取类型文件传入Name参数，需要通过FString赋予到TCHAR类型字符
	            	TCHAR Pat[512];
	            	FString LODtt;
	            	int32 numbofset;
	            	if(LODdataComb->GetSelectedItem())
	            	{
	            		LODtt = *LODdataComb->GetSelectedItem();
	            		FString LODpp = FString::Printf(TEXT("SkeletalMeshLODSettings'/Game/%s/%s.%s'"),*lodpppp,*LODtt,*LODtt);
	            		FCString::Strncpy(Pat, *LODpp, 511);
	            		USkeletalMeshLODSettings* SKMSettings = Cast<USkeletalMeshLODSettings>(StaticLoadObject(USkeletalMeshLODSettings::StaticClass(), nullptr, Pat));
	            		do {  } while (SKMSettings[0].SetLODSettingsFromMesh(nullptr));
	            		if(SKMSettings && useLODData->IsChecked()){
	            			SKMesh->LODSettings = SKMSettings;
	            			numbofset = SKMesh->LODSettings->GetNumberOfSettings();
	            			GEngine->AddOnScreenDebugMessage(-1, 16.f, FColor::Red, FString::Printf(TEXT("%s Setting: %i"), *AssetData.AssetName.ToString(), numbofset));
	            		}else{
                            SKMesh->LODSettings=nullptr;
                             const FString LodG = LODGroupTxt->GetText().ToString();
                             if(LodG == "SmallProp")
                             {
                                 numbofset = 2;
                             }
                             else if(LodG == "LargeProp")
                             {
                                 numbofset = 3;
                             }
                             else
                             {
                                 numbofset = 4;
                             }
                         }
	            	}else{
		            	SKMesh->LODSettings=nullptr;
                        const FString LodG = LODGroupTxt->GetText().ToString();
                        if(LodG == "SmallProp")
                        {
                            numbofset = 2;
                        }
                        else if(LodG == "LargeProp")
                        {
                            numbofset = 3;
                        }
                        else
                        {
                            numbofset = 4;
                        }
                    }
	            	FLODUtilities::RegenerateLOD(SKMesh, numbofset, false, true);
	            	for(int32 LODi = 0; LODi < numbofset; ++LODi)
	            	{
	            		FSkeletalMeshLODInfo* LODInfo = SKMesh->GetLODInfo(LODi);
	            		LODInfo->ScreenSize.Default = SSize[LODi];
	            		FSkeletalMeshOptimizationSettings& ReductionSettings = LODInfo->ReductionSettings;
	            		ReductionSettings.NumOfTrianglesPercentage = PTria[LODi];
	            		
	            	}
	            	SKMesh->Modify();
	            	SKMesh->PostEditChange();
	            	SKMesh->MarkPackageDirty();	//更新资源修改
	            }
            }
        }
    }
	return FReply::Handled();
}
FReply SSlateMain::removeM_Sel()	//批量处理资源管理器中选择的模型MinimumLOD
{	FText const Title = LOCTEXT("title1","清除MinimumLOD");
	FText const DialogText = LOCTEXT("queren","确认要批量清除选择的MinimumLOD参数Mobile项\n（需要选择StaticMesh类型的模型文件）");
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
	    // USelection* SelectedAssets = GEditor->GetSelectedObjects();
	    const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
    	TArray<FAssetData> SelectedAssets;
    	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);

	    const int Sels = SelectedAssets.Num();
        if (Sels > 0)
        {
	        const FString FileName = FString::Printf(TEXT("d:/Remove-MinimumLOD_Selects.txt"));
			int cou = 0;
            FString Content;

	        for (const FAssetData& AssetData : SelectedAssets)
	        {
	        	if (AssetData.AssetClass == UStaticMesh::StaticClass()->GetFName())
	        	{
	        		UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetData.GetAsset());
	        		if (StaticMesh){
	        			FString Nam = StaticMesh->GetName();
	        			const int32 Gnl = StaticMesh->GetNumLODs();	//获取LOD数量
	        			StaticMesh->bAutoComputeLODScreenSize = false;	//取消勾选(Auto Compute LOD Distances)

	        			TMap<FName, int32> PlatformMinimumLODs;	//创建一个TMap<FName, int32>对象，用于承载获取静态网格的Minimum LOD 参数值
	        			StaticMesh->GetMinimumLODForPlatforms(PlatformMinimumLODs);
	        			if (StaticMesh->MinLOD.Default > 0){StaticMesh->MinLOD.Default = 0;}
	        			if (PlatformMinimumLODs.Contains(TEXT("Mobile")))	//判断是否有添加Mobile移动端的的最小LOD等级
	        				{
	        				StaticMesh->MinLOD = 0;	//设置静态网格资源 LOD Settings > Minimum LOD 参数
	        				GEngine->AddOnScreenDebugMessage(-1, 56.f, FColor::Green, FString::Printf(TEXT("%s   MinimumLOD清除成功 (LOD组：%s) (LOD数：%i)"), *Nam, *StaticMesh->LODGroup.ToString(), Gnl));
	        				}
	        			Content += FString::Printf(TEXT("%s\t[LOD数量:%i] \n"), *Nam, Gnl);
	        			cou += 1;
	        			StaticMesh->AddToRoot();
	        			StaticMesh->MarkPackageDirty();
	        		}
	        	}
            }
        	if (cou > 0)
            {
                Content += FString::Printf(TEXT("共选择 %i 个模型文件, 如上 %i 个文件修改\n"),Sels ,cou);
                UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
                FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
                //打开创建的txt文本
                if (openTxt->IsChecked()) {
	                const FString FP = FString::Printf(TEXT("start %s"), *FileName);
            		system(TCHAR_TO_UTF8(*FP));
                }
                UE_LOG(LogTemp, Warning, TEXT("共修改 %i 个文件"), cou);
                GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Yellow, FString::Printf(TEXT("共处理 %i 个文件"), cou));
            }
        }
    }
	return FReply::Handled();
}
FReply SSlateMain::largePropLODsets()	//批量处理LODLargeProp
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","LOD批处理");
	FString meg = FString::Printf(TEXT("批量设置LOD?\n目录：Content/%s"), *pp);
    FText const DialogText = FText::FromString(*meg);
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
        FString pName;
        TArray<FAssetData> AssetDataList;
        FARFilter Filter;
        if (pp != "")
        {
        	//查找路径是否是反斜杠，如果是切割并替换成正斜杠
        	if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
        	{
        		FString newP = "";
        		TArray<FString> SArr;
        		pp.ParseIntoArray(SArr, TEXT("\\"), false);
        		for (const FString sss : SArr)
        		{
        			newP += sss + "/";
        		}
        		pp = newP;
        	}
        	FString en = pp.Right(1);
        	if (en == "/")
        		pp = pp.LeftChop(1);
        	//提取最后一个目录名 pName
        	TArray<FString> SArr;
        	pp.ParseIntoArray(SArr, TEXT("/"), false);
        	pName = SArr[SArr.Num() - 1];
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
        }else
        {
        	pName = "Content";
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
        }
        const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
        const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
     
        Filter.ClassNames.Add(UStaticMesh::StaticClass()->GetFName());	//获取静态网格类名
        if (RPath->IsChecked())
        {
        	//遞歸搜尋路径，查找子目录
        	Filter.bRecursivePaths = true;
        }
        else
        {
        	Filter.bRecursivePaths = false;
        }
        Filter.bRecursiveClasses = true;
        AssetRegistry.GetAssets(Filter, AssetDataList);
        
        FString FileName = FString::Printf(TEXT("d:/LOD-LargeProp_%s.txt"), *pName);
		UE_LOG(LogTemp, Warning, TEXT("共搜索 %i 个文件"), AssetDataList.Num());
		GEngine->AddOnScreenDebugMessage(-1, 26.f, FColor::Yellow, FString::Printf(TEXT("共搜索 %i 个文件"), AssetDataList.Num()));
		int cou = 0;
		FString Content;
		FString AutoCom;
        for (const FAssetData& AssetData : AssetDataList)
        {
        	FStringAssetReference AssetRef(AssetData.ObjectPath.ToString());
        	UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetRef.TryLoad());
        	if (StaticMesh)
        	{
        		FString Nam = *StaticMesh->GetName();
        		// 在这里修改 StaticMesh 对象
        		if (Nam.Find(suffixSeach->GetText().ToString()) >= 0 || suffixSeach->GetText().ToString() == "allmesh")
        		{
					// const int32 Gnl = StaticMesh->GetNumLODs();	//获取LOD数量
        			// StaticMesh->bAutoComputeLODScreenSize = false;	//取消勾选(Auto Compute LOD Distances)
					// RenderData.ScreenSize;
        			StaticMesh->SetLODGroup(*LODGroupTxt->GetText().ToString());
        			StaticMesh->bAutoComputeLODScreenSize = false;
        			FStaticMeshRenderData& RenderData = *StaticMesh->RenderData;	//获取静态网格渲染数据
						        			
        			int32 Rc = 0;
	                const int32 LODs = StaticMesh->GetNumLODs();
        			const float PTval_0 = PT_0->GetValue();
        			const float PTval_1 = PT_1->GetValue();
        			const float PTval_2 = PT_2->GetValue();
        			const float PTval_3 = PT_3->GetValue();
        			TArray<float> SSize = {SS_0->GetValue(), SS_1->GetValue(), SS_2->GetValue(), SS_3->GetValue()};
        			TArray<float> PTria = {(PTval_0/100.0f), (PTval_1/100.0f), (PTval_2/100.0f), (PTval_3/100.0f)};
        			for (FStaticMeshLODResources& LODR : RenderData.LODResources)
        			{
        				FStaticMeshSourceModel& SourceModel = StaticMesh->GetSourceModel(Rc);	//获取每一级LOD中的ScreenSize值（SourceModel.ScreenSize.Default）
        				SourceModel.ScreenSize.Default = SSize[Rc];
        				SourceModel.ReductionSettings.PercentTriangles = PTria[Rc];
        				Rc += 1;
        				if (LODs > 2 && (Rc+1) == LODs)
        				{
        					const int32 Secs = LODR.Sections.Num();
        					GEngine->AddOnScreenDebugMessage(-1, 66.f, FColor::Yellow, FString::Printf(TEXT("%s 共 %i 个材质球"), *Nam, Secs));
        					if (Secs > 0)
        					{
        						for (int S=0; S<Secs; S++)
        						{
        							FMeshSectionInfo Info = StaticMesh->GetSectionInfoMap().Get(Rc, S);
                                    Info.bCastShadow = false;
                                    StaticMesh->GetSectionInfoMap().Set(Rc, S, Info);
        						}
        					}
        				}
        			}
        			Content += FString::Printf(TEXT("%s\n"), *Nam);
        			//GEngine->AddOnScreenDebugMessage(-1, 156.f, FColor::Green, FString::Printf(TEXT("%s   LODs:%i)  (%s)"), *Nam, LRN, *SSNS));
        			
					cou += 1;
        			//标记为修改*
        			StaticMesh->Modify();
        			StaticMesh->PostEditChange();
                    StaticMesh->AddToRoot();
                    StaticMesh->MarkPackageDirty();
        		}
        	}
        }
        if (cou > 0)
        {
            Content += FString::Printf(TEXT("共搜索 %i 个模型文件, 如上 %i 个文件修改\n"),AssetDataList.Num() ,cou);
            UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
            FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            //打开创建的txt文本
            if (openTxt->IsChecked()) {
                FString FP = FString::Printf(TEXT("start %s"), *FileName);
				system(TCHAR_TO_UTF8(*FP));
            }
            UE_LOG(LogTemp, Warning, TEXT("共修改 %i 个文件"), cou);
            GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Yellow, FString::Printf(TEXT("共处理 %i 个文件"), cou));
        }
    }
    return FReply::Handled();
}
FReply SSlateMain::listLODdetails()	//列出静态网格模型的LOD细节
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","列出LOD详情");
	FString meg = FString::Printf(TEXT("是否列出指定目录中的所有静态网格的LOD等级和每一级的三角面数?\n如果要列出全部文件，搜索关键字输入：allmesh\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
        FARFilter Filter;
        FString pName;
        if (pp != "")
        {
        	//查找路径是否是反斜杠，如果是切割并替换成正斜杠
        	if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
        	{
        		FString newP = "";
        		TArray<FString> SArr;
        		pp.ParseIntoArray(SArr, TEXT("\\"), false);
        		for (const FString sss : SArr)
        		{
        			newP += sss + "/";
        		}
        		pp = newP;
        	}
        	FString en = pp.Right(1);
        	if (en == "/")
        		pp = pp.LeftChop(1);
        	//提取最后一个目录名 pName
        	TArray<FString> SArr;
        	pp.ParseIntoArray(SArr, TEXT("/"), false);
        	pName = SArr[SArr.Num() - 1];
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
        }else
        {
        	pName = "Content";
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
        }
        const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
        const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

        TArray<FAssetData> AssetDataList;
        // Filter.ClassNames.Add(UStaticMesh::StaticClass()->GetFName());
        // Filter.ClassNames.Add(USkeletalMesh::StaticClass()->GetFName());
        if (RPath->IsChecked())
        {   //遞歸搜尋路径，查找子目录
        	Filter.bRecursivePaths = true;
        }
        else
        {
        	Filter.bRecursivePaths = false;
        }
        Filter.bRecursiveClasses = true;
        AssetRegistry.GetAssets(Filter, AssetDataList);
        FString FileName = FString::Printf(TEXT("d:/LOD-Resource_%s.txt"), *pName);
		UE_LOG(LogTemp, Warning, TEXT("共搜索 %i 个文件"), AssetDataList.Num());
		GEngine->AddOnScreenDebugMessage(-1, 26.f, FColor::Yellow, FString::Printf(TEXT("共搜索 %i 个文件"), AssetDataList.Num()));
		int cou = 0;
		FString Content;
        for (const FAssetData& AssetData : AssetDataList)
        {
        	FString Nam = *AssetData.AssetName.ToString();
            if (Nam.Find(suffixSeach->GetText().ToString()) >= 0 || suffixSeach->GetText().ToString() == "allmesh")
        	if (AssetData.AssetClass.ToString() == UStaticMesh::StaticClass()->GetName())
        	{
        		FStringAssetReference AssetRef(AssetData.ObjectPath.ToString());
        		UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetRef.TryLoad());
                if (StaticMesh)
                {
                	*StaticMesh->GetName();
                    // 在这里修改 StaticMesh 对象
					FString AutoCom;
                    // const int32 Gnl = StaticMesh->GetNumLODs();	//获取LOD数量
                    // StaticMesh->bAutoComputeLODScreenSize = false;	//取消勾选(Auto Compute LOD Distances)
                    if (StaticMesh->bAutoComputeLODScreenSize == false)
                    {
                        AutoCom = FString::Printf(TEXT("取消"));
                    }
                    else
                    {
                        AutoCom = FString::Printf(TEXT("勾选"));
                    }
                    cou += 1;
                    FStaticMeshRenderData& RenderData = *StaticMesh->RenderData;	//获取静态网格渲染数据
                    // RenderData.ScreenSize;
                    FString SSNS = "";
                    FString SSerr = "";
                    FString bound = StaticMesh->GetBounds().BoxExtent.ToString();
                    const int32 LRN = RenderData.LODResources.Num();
                    if (LRN > 0)
                    {
                        int32 Rc = 0;
                        for (FStaticMeshLODResources& LODR : RenderData.LODResources)
                        {
                            const FStaticMeshSourceModel& SourceModel = StaticMesh->GetSourceModel(Rc);	//获取每一级LOD中的ScreenSize值（SourceModel.ScreenSize.Default）
                            float ScrSize = SourceModel.ScreenSize.Default;
                            float PT = SourceModel.ReductionSettings.PercentTriangles;
                            SSNS += FString::Printf(TEXT(" ◆[LOD_%i:▲%i]  [Screen_Size:%s] [PrecentTri:%s] "), Rc, LODR.GetNumTriangles(), *RemoveTrailingZeros(ScrSize), *RemoveTrailingZeros(PT));
                            if (ScrSize == 0.0f){
                            	SSerr += FString::Printf(TEXT(" [LOD_%i]●ScreenSize设置有误"),Rc);
                            }
                            Rc += 1;
                        }
                        if(SSerr != ""){SSerr = FString::Printf(TEXT("  【%s】"),*SSerr);}
                        // LODResource.Sections[0].bCastShadow=false;
                        Content += FString::Printf(TEXT("%s\t[StaticMesh][LOD数量:%i]  (%s)  [Auto_Compute_LOD_Distances:%s] [Bounds:%s] %s\n"), *Nam, LRN, *SSNS, *AutoCom, *bound, *SSerr);
                        //GEngine->AddOnScreenDebugMessage(-1, 156.f, FColor::Green, FString::Printf(TEXT("%s   LODs:%i)  (%s)"), *Nam, LRN, *SSNS));
                    }
                    //标记为修改*
                    // StaticMesh->AddToRoot();
                    // StaticMesh->MarkPackageDirty();
                }
        	}
            else if(AssetData.AssetClass.ToString() == USkeletalMesh::StaticClass()->GetName())
            {
                FStringAssetReference AssetRef(AssetData.ObjectPath.ToString());
                USkeletalMesh* SKMesh = Cast<USkeletalMesh>(AssetRef.TryLoad());
                if (SKMesh)
                {
                	FString SSNS = "";
                	FString SSerr = "";
                	FString bound = SKMesh->GetBounds().BoxExtent.ToString();
                	const int Lods = SKMesh->GetLODNum();
                	cou += 1;
                	if (Lods > 0)
                	{
                		for(int32 LODi = 0; LODi < Lods; ++LODi)
                		{
                			const FSkeletalMeshLODInfo* LODInfo = SKMesh->GetLODInfo(LODi);
                			float ScrSize = LODInfo->ScreenSize.Default;
                			const FSkeletalMeshOptimizationSettings& ReductionSettings = LODInfo->ReductionSettings;
                			float PT = ReductionSettings.NumOfTrianglesPercentage;
                			
                			SSNS += FString::Printf(TEXT(" ◆[LOD_%i:▲%i]  [Screen_Size:%s] [PrecentTri:%s] "), LODi, SKMesh->GetResourceForRendering()->LODRenderData[LODi].GetTotalFaces(), *RemoveTrailingZeros(ScrSize), *RemoveTrailingZeros(PT));
                			if (ScrSize == 0.0f){
                				SSerr += FString::Printf(TEXT(" [LOD_%i]●ScreenSize设置有误"),LODi);
                			}
                			// GEngine->AddOnScreenDebugMessage(-1, 126.f, FColor::Blue, FString::Printf(TEXT("NumOfTrianglesPercentage : %f "), ReductionSettings.NumOfTrianglesPercentage));
                		}
                        Content += FString::Printf(TEXT("%s\t[SkeletalMesh][LOD数量:%i]  (%s)  [Bounds:%s] %s\n"), *Nam, Lods, *SSNS, *bound, *SSerr);
                	}
                }
            }
        }
        if (cou > 0)
        {
            Content += FString::Printf(TEXT("共搜索 %i 个模型文件, 如上列出 %i 个文件\n"),AssetDataList.Num() ,cou);
            UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
            FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            //打开创建的txt文本
            if (openTxt->IsChecked())
            {
                FString FP = FString::Printf(TEXT("start %s"), *FileName);
                system(TCHAR_TO_UTF8(*FP));
            }
            UE_LOG(LogTemp, Warning, TEXT("共修改 %i 个文件"), cou);
            GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Yellow, FString::Printf(TEXT("共处理 %i 个文件"), cou));
        }
    }
    return FReply::Handled();
}
FString SSlateMain::RemoveTrailingZeros(float value)	//约束小数点在3位数
{
	FString formattedString = FString::Printf(TEXT("%.3f"), value);	//使用合适的精度设置

	int32 dotPos = INDEX_NONE;
	formattedString.FindChar('.', dotPos);

	int32 lastNonZero = formattedString.Len() - 1;
	if (dotPos != INDEX_NONE)
	{
		for (int32 i = formattedString.Len() - 1; i > dotPos; --i)
		{
			if (formattedString[i] != '0')
			{
				lastNonZero = i;
				break;
			}
		}
	}

	return formattedString.Left(lastNonZero + 1);
}
FReply SSlateMain::miniLODset_removeM()	//设置minimum LOD
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","批量清除MinimumLOD");
	FString meg = FString::Printf(TEXT("确认要批量清除MinimumLOD参数Mobile项?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
        FARFilter Filter;
        FString pName;
        if (pp != "")
        {
        	//查找路径是否是反斜杠，如果是切割并替换成正斜杠
        	if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
        	{
        		FString newP = "";
        		TArray<FString> SArr;
        		pp.ParseIntoArray(SArr, TEXT("\\"), false);
        		for (const FString sss : SArr)
        		{
        			newP += sss + "/";
        		}
        		pp = newP;
        	}
        	FString en = pp.Right(1);
        	if (en == "/")
        		pp = pp.LeftChop(1);
        	//提取最后一个目录名 pName
        	TArray<FString> SArr;
        	pp.ParseIntoArray(SArr, TEXT("/"), false);
        	pName = SArr[SArr.Num() - 1];
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
        }else
        {
        	pName = "Content";
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
        }
        const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
        const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
		FString FileName = FString::Printf(TEXT("d:/Remove-MinimumLOD_%s.txt"), *pName);
        TArray<FAssetData> AssetDataList;
        Filter.ClassNames.Add(UStaticMesh::StaticClass()->GetFName());
        if (RPath->IsChecked())
        {
        	//遞歸搜尋路径，查找子目录
        	Filter.bRecursivePaths = true;
        }
        else
        {
        	Filter.bRecursivePaths = false;
        }
		Filter.bRecursiveClasses = true;
        AssetRegistry.GetAssets(Filter, AssetDataList);
		int cou = 0;
		FString Content;
        for (const FAssetData& AssetData : AssetDataList)
        {
        	FStringAssetReference AssetRef(AssetData.ObjectPath.ToString());
        	UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetRef.TryLoad());
        	if (StaticMesh)
        	{
        		FString Nam = *StaticMesh->GetName();
        		// 在这里修改 StaticMesh 对象
        		if (Nam.Find(suffixSeach->GetText().ToString()) != -1)
        		{
					const int32 Gnl = StaticMesh->GetNumLODs();	//获取LOD数量
        			StaticMesh->bAutoComputeLODScreenSize = false;	//取消勾选(Auto Compute LOD Distances)
        			
        			TMap<FName, int32> PlatformMinimumLODs;	//创建一个TMap<FName, int32>对象，用于承载获取静态网格的Minimum LOD 参数值
        			StaticMesh->GetMinimumLODForPlatforms(PlatformMinimumLODs);
        			if (StaticMesh->MinLOD.Default > 0){StaticMesh->MinLOD.Default = 0;}
    				if (PlatformMinimumLODs.Contains(TEXT("Mobile")))	//判断是否有添加Mobile移动端的的最小LOD等级
    				{
    					StaticMesh->MinLOD = 0;	//设置静态网格资源 LOD Settings > Minimum LOD 参数
        				GEngine->AddOnScreenDebugMessage(-1, 56.f, FColor::Green, FString::Printf(TEXT("%s   MinimumLOD清除成功 (LOD组：%s) (LOD数：%i)"), *Nam, *StaticMesh->LODGroup.ToString(), Gnl));
    				}
        			Content += FString::Printf(TEXT("%s\t[LOD数量:%i] \n"), *Nam, Gnl);
					cou += 1;
                    StaticMesh->AddToRoot();
                    StaticMesh->MarkPackageDirty();
        		}
        	}
        }
        if (cou > 0)
        {
            Content += FString::Printf(TEXT("共搜索 %i 个模型文件, 如上 %i 个文件修改\n"),AssetDataList.Num() ,cou);
            UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
            FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            //打开创建的txt文本
            if (openTxt->IsChecked())
            {
                FString FP = FString::Printf(TEXT("start %s"), *FileName);
                system(TCHAR_TO_UTF8(*FP));
            }
            UE_LOG(LogTemp, Warning, TEXT("共修改 %i 个文件"), cou);
            GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Yellow, FString::Printf(TEXT("共处理 %i 个文件"), cou));
        }
    }
    return FReply::Handled();
}
FReply SSlateMain::LODset()	//设置LOD
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","LOD批处理");
	FString meg = FString::Printf(TEXT("确认要批处理静态网格添加MinimumLOD吗?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
    	FARFilter Filter;
        FString pName;
    	if (pp != "")
    	{
    		//查找路径是否是反斜杠，如果是切割并替换成正斜杠
    		if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
    		{
    			FString newP = "";
    			TArray<FString> SArr;
    			pp.ParseIntoArray(SArr, TEXT("\\"), false);
    			for (const FString sss : SArr)
    			{
    				newP += sss + "/";
    			}
    			pp = newP;
    		}
    		FString en = pp.Right(1);
    		if (en == "/")
    			pp = pp.LeftChop(1);
    		//提取最后一个目录名 pName
    		TArray<FString> SArr;
    		pp.ParseIntoArray(SArr, TEXT("/"), false);
    		pName = SArr[SArr.Num() - 1];
    		Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
    	}else
    	{
    		pName = "Content";
    		Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
    	}
    	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
		FString FileName = FString::Printf(TEXT("d:/Add-MinimumLOD_%s.txt"), *pName);

    	TArray<FAssetData> AssetDataList;
    	Filter.ClassNames.Add(UStaticMesh::StaticClass()->GetFName());
    	if (RPath->IsChecked())
    	{
    		//遞歸搜尋路径，查找子目录
    		Filter.bRecursivePaths = true;
    	}
    	else
    	{
    		Filter.bRecursivePaths = false;
    	}
        Filter.bRecursiveClasses = true;
    	AssetRegistry.GetAssets(Filter, AssetDataList);
		int cou = 0;
		FString Content;
    	for (const FAssetData& AssetData : AssetDataList)
    	{
    		FStringAssetReference AssetRef(AssetData.ObjectPath.ToString());
    		UStaticMesh* StaticMesh = Cast<UStaticMesh>(AssetRef.TryLoad());
    		if (StaticMesh)
    		{
    			FString Nam = *StaticMesh->GetName();
    			// 在这里修改 StaticMesh 对象
    			if (Nam.Find(suffixSeach->GetText().ToString()) != -1)
    			{
                    // StaticMesh->SetLODGroup("LargeProp");
	                const int32 Gnl = StaticMesh->GetNumLODs();	//获取LOD数量
    				StaticMesh->bAutoComputeLODScreenSize = false;
    				
    				TMap<FName, int32> PlatformMinimumLODs;	//创建一个TMap<FName, int32>对象，用于承载获取静态网格的Minimum LOD 参数值
    				StaticMesh->GetMinimumLODForPlatforms(PlatformMinimumLODs);	//获取 Minimum LOD 参数值
					if (!PlatformMinimumLODs.Contains(TEXT("Mobile")))	//判断没有添加Mobile移动端的最小LOD等级
					{
    					//设置添加Minimum LOD参数值
    					PlatformMinimumLODs.Add(TEXT("Mobile"),1);
    					StaticMesh->MinLOD.PerPlatform = PlatformMinimumLODs;
						Content += FString::Printf(TEXT("%s\t[LOD数量:%i] \n"), *Nam, Gnl);
    					cou += 1;
						GEngine->AddOnScreenDebugMessage(-1, 56.f, FColor::Green, FString::Printf(TEXT("%s   MinimumLOD Mobile添加成功 (LOD组：%s) (LOD数：%i)"), *Nam, *StaticMesh->LODGroup.ToString(), Gnl));
					}
                    StaticMesh->AddToRoot();
                    StaticMesh->MarkPackageDirty();
    			}
    		}
    	}
        if (cou > 0)
        {
            Content += FString::Printf(TEXT("共搜索 %i 个模型文件, 如上 %i 个文件修改\n"),AssetDataList.Num() ,cou);
            UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
            FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            //打开创建的txt文本
        	if (openTxt->IsChecked())
        	{
        		FString FP = FString::Printf(TEXT("start %s"), *FileName);
        		system(TCHAR_TO_UTF8(*FP));
        	}
            UE_LOG(LogTemp, Warning, TEXT("共修改 %i 个文件"), cou);
            GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Yellow, FString::Printf(TEXT("共处理 %i 个文件"), cou));
        }
    }
	return FReply::Handled();
}
FReply SSlateMain::SetTextureMax()
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","贴图批处理");
	FString meg = FString::Printf(TEXT("确认要批处理贴图尺寸?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
    EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
    if (ReturnType == EAppReturnType::Type::Ok)
    {
    	TArray<FAssetData> AssetDatas;
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
        FAssetRegistryModule>("AssetRegistry");
        FARFilter Filter;
        FString pName;
        if (pp != "")
        {
            //查找路径是否是反斜杠，如果是切割并替换成正斜杠
            if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
            {
                FString newP = "";
                TArray<FString> SArr;
                pp.ParseIntoArray(SArr, TEXT("\\"), false);
                for (const FString sss : SArr)
                {
                	newP += sss + "/";
                }
                pp = newP;
            }
            FString en = pp.Right(1);
            if (en == "/")
                pp = pp.LeftChop(1);
            //提取最后一个目录名 pName
            TArray<FString> SArr;
            pp.ParseIntoArray(SArr, TEXT("/"), false);
            pName = SArr[SArr.Num() - 1];
            Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
        }else
        {
            pName = "Content";
            Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
        }
        Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());  //添加过滤文件类型
        if (RPath->IsChecked())
        {
            //遞歸搜尋路径，查找子目录
            Filter.bRecursivePaths = true;
        }
        else
        {
            Filter.bRecursivePaths = false;
        }
        Filter.bRecursiveClasses = true;
        AssetRegistryModule.Get().GetAssets(Filter, AssetDatas);
    
        FString mess = FString::Printf(TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
        GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, *mess);
        UE_LOG(LogTemp, Warning, TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
        int cou = 0;
        FString FileName = FString::Printf(TEXT("d:/TexResizeList-%s.txt"), *pName);
        FString Content;
    	FString absd = equalText->GetText().ToString();
        for (const FAssetData& AssetData : AssetDatas)
        {
            UTexture2D* MatObj = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr,
                                                               (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
            if (MatObj->GetName().Right(suffixSeach->GetText().ToString().Len()) == suffixSeach->GetText().ToString())
            {
            	if (absd == TEXT("等于"))
            	{
            		if ( MatObj->GetImportedSize().Y == searchSize->GetValue()) {
            			MatObj->MaxTextureSize = FCString::Atoi(*SizeValue->GetText().ToString());
            			//標記未保存星號
            			MatObj->AddToRoot();
            			MatObj->UpdateResource();
            			MatObj->MarkPackageDirty();
            			cou += 1;
            			//文件路径写入文本
            			FString MatPath = *MatObj->GetPathName();
            			FString MatLeft;
            			MatPath.Split(".", &MatLeft, nullptr);
            			Content += FString::Printf(TEXT("%s\n"), *MatLeft);
            		}
            	}else{
            		if ( MatObj->GetImportedSize().Y >= searchSize->GetValue()) {
                        MatObj->MaxTextureSize = FCString::Atoi(*SizeValue->GetText().ToString());
                        //標記未保存星號
                        MatObj->AddToRoot();
                        MatObj->UpdateResource();
                        MatObj->MarkPackageDirty();
                        cou += 1;
                        //文件路径写入文本
                        FString MatPath = *MatObj->GetPathName();
                        FString MatLeft;
                        MatPath.Split(".", &MatLeft, nullptr);
                        Content += FString::Printf(TEXT("%s\n"), *MatLeft);
                    }
            	}
            }
        }
        if (cou > 0)
        {
            Content += FString::Printf(TEXT("共搜索 %i 个贴图文件, 如上 %i 个文件调整\n"),AssetDatas.Num() ,cou);
            UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
            FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
            //打开创建的txt文本
            if (openTxt->IsChecked())
            {
	            FString FP = FString::Printf(TEXT("start %s"), *FileName);
            	system(TCHAR_TO_UTF8(*FP));
            }
            UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个贴图文件"), cou);
            GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个贴图文件"), cou));
        }
    }else
    {
    	GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("取消"));
    }
	return FReply::Handled();
}
FReply SSlateMain::SeachAdjustmentTexture()
{
    FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title1","贴图调整批处理");
	FString meg = FString::Printf(TEXT("确认批处理重置贴图调整?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
	EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
	if (ReturnType == EAppReturnType::Type::Ok)
	{
		TArray<FAssetData> AssetDatas;
        FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
        FAssetRegistryModule>("AssetRegistry");
        FARFilter Filter;
        FString pName;
        if (pp != "")
        {
        	//查找路径是否是反斜杠，如果是切割并替换成正斜杠
        	if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
        	{
        		FString newP = "";
        		TArray<FString> SArr;
        		pp.ParseIntoArray(SArr, TEXT("\\"), false);
        		for (const FString sss : SArr)
        		{
        			newP += sss + "/";
        		}
        		pp = newP;
        	}
        	FString en = pp.Right(1);
        	if (en == "/")
        		pp = pp.LeftChop(1);
        	//提取最后一个目录名 pName
        	TArray<FString> SArr;
        	pp.ParseIntoArray(SArr, TEXT("/"), false);
        	pName = SArr[SArr.Num() - 1];
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
        }else
        {
        	pName = "Content";
        	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
        }
        Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());  //添加过滤文件类型
        if (RPath->IsChecked())
        {
        	//遞歸搜尋路径，查找子目录
        	Filter.bRecursivePaths = true;
        }
        else
        {
        	Filter.bRecursivePaths = false;
        }
        Filter.bRecursiveClasses = true;
        AssetRegistryModule.Get().GetAssets(Filter, AssetDatas);
    
        FString mess = FString::Printf(TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
        GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, *mess);
        UE_LOG(LogTemp, Warning, TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
        int cou = 0;
        FString FileName = FString::Printf(TEXT("d:/TextureList-%s.txt"), *pName);
        FString Content;
        for (const FAssetData& AssetData : AssetDatas)
        {
        	UTexture* MatObj = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), nullptr,
        	                                                   (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
        	if (MatObj->GetName().Right(suffixSeach->GetText().ToString().Len()) == suffixSeach->GetText().ToString())
        	{
        		if (MatObj->AdjustHue != 0)
        		{
        			MatObj->AdjustHue = 0;
        			//標記未保存星號
        			MatObj->AddToRoot();
        			MatObj->UpdateResource();
        			MatObj->MarkPackageDirty();
        			cou += 1;
        			//文件路径写入文本
        			FString MatPath = *MatObj->GetPathName();
        			FString MatLeft;
        			MatPath.Split(".", &MatLeft, nullptr);
        			Content += FString::Printf(TEXT("%s\n"), *MatLeft);
        			//获取路径与文件名
        			//UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.PackageName.ToString());
        		}
        	}
        }
        if (cou > 0)
        {
        	Content += FString::Printf(TEXT("共搜索 %i 个贴图文件, 如上 %i 个文件调整\n"),AssetDatas.Num() ,cou);
        	UE_LOG(LogTemp, Log, TEXT("【%s】"), *FileName);
        	FFileHelper::SaveStringToFile(Content, *FileName, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
        	//打开创建的txt文本
            if (openTxt->IsChecked())
            {
	            FString FP = FString::Printf(TEXT("start %s"), *FileName);
            	system(TCHAR_TO_UTF8(*FP));
            }
        	UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个贴图文件"), cou);
        	GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个贴图文件"), cou));
        }
	}else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("取消"));
	}
	return FReply::Handled();
}

FReply SSlateMain::OnGoButtonClicked()
{
	//UE_LOG(LogTemp, Warning, TEXT("AssetName:%s"), *MatObj->GetName());
	FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title2","法线贴图压缩设置批处理");
	FString meg = FString::Printf(TEXT("确认批处理后缀名为\"_N\"的法线贴图压缩设置格式?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
	EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
	if (ReturnType == EAppReturnType::Type::Ok)
	{
		TArray<FAssetData> AssetDatas;
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
			FAssetRegistryModule>("AssetRegistry");
		FARFilter Filter;
		//查找路径是否是反斜杠，如果是切割并替换成正斜杠
		if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
		{
			FString newP = "";
			TArray<FString> SArr;
			pp.ParseIntoArray(SArr, TEXT("\\"), false);
			for (const FString sss : SArr)
			{
				newP += sss + "/";
			}
			pp = newP;
		}
		FString en = pp.Right(1);
		if (en == "/")
			pp = pp.LeftChop(1);
		Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //需要FName類型字符 *FString 前面加星號解引出來使用
		Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());
		if (RPath->IsChecked())
		{
			//遞歸搜尋路徑，查找子目錄
			Filter.bRecursivePaths = true;
		}
		else
		{
			Filter.bRecursivePaths = false;
		}
		Filter.bRecursiveClasses = true;
		AssetRegistryModule.Get().GetAssets(Filter, AssetDatas);

		FString mess = FString::Printf(TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, *mess);
		UE_LOG(LogTemp, Warning, TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
		int cou;
		cou = 0;
		for (const FAssetData& AssetData : AssetDatas)
		{
			UTexture* MatObj = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), nullptr,
															   (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::FromInt(MatObj->CompressionSettings.GetValue()));
			if (texComp->GetText().ToString() == "Default")
			{
				if (MatObj->CompressionSettings.GetValue() == 1)
				{
					MatObj->CompressionSettings = TC_Default;
					//標記未保存星號
					MatObj->AddToRoot();
					MatObj->UpdateResource();
					MatObj->MarkPackageDirty();
					cou += 1;
					UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
				}
			}

			if (texComp->GetText().ToString() == "NormalMap")
			{
				if (MatObj->GetFName().ToString().Right(2) == "_N")
				{
					if (MatObj->CompressionSettings.GetValue() != 1)
					{
						MatObj->CompressionSettings = TC_Normalmap;
						//標記未保存星號
						MatObj->AddToRoot();
						MatObj->UpdateResource();
						MatObj->MarkPackageDirty();
						cou += 1;
						UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
					}
				}
			}
		}
		if (cou > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个法线贴图文件"), cou);
			GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个法线贴图文件"), cou));
		}
	}else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("取消"));
	}
	return FReply::Handled();
}

FReply SSlateMain::SetUITextureClicked()
{//获取资源管理器选择的
	const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	TArray<FAssetData> SelectedAssets;
	ContentBrowserModule.Get().GetSelectedAssets(SelectedAssets);
	if(SelectedAssets.Num()>0)
	{
		for (const FAssetData& AssetData : SelectedAssets)
		{
			if(AssetData.AssetClass == UTexture2D::StaticClass()->GetFName())
			{
				UTexture2D* MatObj = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), nullptr,
															  (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
				MatObj->CompressionQuality = TCQ_Highest;	//设置贴图的压缩质量参数
                //MatObj->CompressionQualityBySize = TCQ_Highest;
		//标记已修改
				MatObj->AddToRoot();
				MatObj->UpdateResource();
				MatObj->MarkPackageDirty();
			}
		}
	}
	return FReply::Handled();
}
FReply SSlateMain::OnGoMapButtonClicked()
{
	FString pp = texPath->GetText().ToString();
	FText const Title = LOCTEXT("title3","贴图压缩设置批处理");
	FString meg = FString::Printf(TEXT("确认批处理贴图压缩设置格式?\n目录：Content/%s"), *pp);
	FText const DialogText = FText::FromString(*meg);
	EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
	if (ReturnType == EAppReturnType::Type::Ok)
	{
		TArray<FAssetData> AssetDatas;
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<
			FAssetRegistryModule>("AssetRegistry");
		FARFilter Filter;
		if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
		{
			FString newP = "";
			TArray<FString> SArr;
			pp.ParseIntoArray(SArr, TEXT("\\"), false);
			for (const FString sss : SArr)
			{
				newP += sss + "/";
			}
			pp = newP;
		}
		FString en = pp.Right(1);
		if (en == "/")
			pp = pp.LeftChop(1);
		Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //需要FName類型字符 *FString 前面加星號解引出來使用
		Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());
		if (RPath->IsChecked())
		{
			//遞歸搜尋路徑，查找子目錄
			Filter.bRecursivePaths = true;
		}
		else
		{
			Filter.bRecursivePaths = false;
		}
		Filter.bRecursiveClasses = true;
		AssetRegistryModule.Get().GetAssets(Filter, AssetDatas);

		FString mess = FString::Printf(TEXT("共搜索 %i 个贴图文件"), AssetDatas.Num());
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, *mess);
		int cou;
		cou = 0;
		for (const FAssetData& AssetData : AssetDatas)
		{
			UTexture* MatObj = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), nullptr,
															   (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::FromInt(MatObj->CompressionSettings.GetValue()));
			if (texComp->GetText().ToString() == "Default")
			{
				MatObj->CompressionSettings = TC_Default;
				//標記未保存星號
				MatObj->AddToRoot();
				MatObj->UpdateResource();
				MatObj->MarkPackageDirty();
				cou += 1;
				UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
			}

			if (texComp->GetText().ToString() == "BC7")
			{
				MatObj->CompressionSettings = TC_BC7;
				//標記未保存星號
				MatObj->AddToRoot();
				MatObj->UpdateResource();
				MatObj->MarkPackageDirty();
				cou += 1;
				UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
			}
		}
		if (cou > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个贴图文件"), cou);
			GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个贴图文件"), cou));
		}
	}else
	{
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("取消"));
	}
	return FReply::Handled();
}

bool SSlateMain::DiffPathText(FString path)
{
	int con = 0;
	FString aaa = ReadTxt("ST.txt");
	TArray<FString> arr;
	aaa.ParseIntoArray(arr, TEXT("\n"), false);  //将读取的文本以换行符拆分到数组arr中
	for (const FString hist : arr)
	{
		if (hist == path)
			con += 1;
	}
	if (con == 0)
	{
		aaa += (path + "\n");
		WriteTxt(aaa, (FPaths::ProjectPluginsDir() + "SceneTools_W_P/ST.txt"));
		return true;
	}
	else
	{
		return false;
	}
}

void SSlateMain::OnSubfixText(const FText& Text)
{
	CFN.WriteIni(FString("SceneTools"), FString("Suffix"), Text.ToString(), IniPath);
}
void SSlateMain::OnPathText(const FText& Text)
{
	if(FPaths::DirectoryExists(*(FPaths::ProjectContentDir() + Text.ToString()))){
		CFN.WriteIni(FString("SceneTools"), FString("Path"), Text.ToString(), IniPath);
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT(" %s 目录存在"), *Text.ToString()));
	}else
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT(" %s 目录不存在"), *Text.ToString()));
}
void SSlateMain::LodDataGetVal(const FString LODtt)
{
	//定义用于Cast获取类型文件传入Name参数，需要通过FString赋予到TCHAR类型字符
	if(LODtt != "")
	{	TArray<TSharedPtr<SSpinBox<float>>> allSS = {SS_0, SS_1, SS_2, SS_3};	//初始化数组存放变量
		TArray<TSharedPtr<SSpinBox<int>>> allPT = {PT_0, PT_1, PT_2, PT_3};
		TCHAR Pat[512];	//用于
		const FString LODpp = FString::Printf(TEXT("SkeletalMeshLODSettings'/Game/%s/%s.%s'"),*lodpppp,*LODtt,*LODtt);
        FCString::Strncpy(Pat, *LODpp, 511);
		const USkeletalMeshLODSettings* SKMSettings = Cast<USkeletalMeshLODSettings>(StaticLoadObject(USkeletalMeshLODSettings::StaticClass(), nullptr, Pat));
		if(SKMSettings)
		{
			int Lods = SKMSettings->GetNumberOfSettings();
            if (Lods > 4){Lods = 4;}
            for(int I = 0; I < Lods; I++)
            {
            	allSS[I]->SetValue(SKMSettings->GetSettingsForLODLevel(I).ScreenSize.Default);
            	allPT[I]->SetValue(static_cast<int>(round(SKMSettings->GetSettingsForLODLevel(I).ReductionSettings.NumOfTrianglesPercentage * 100)));	//使用static_cast<int>(round(...))将小数计算自动四舍五入输出整数
            }
            if(Lods == 1)
            {
            	LODGroupTxt->SetText(FText::FromString("None"));
            	SS_1->SetVisibility(EVisibility::Hidden);	//显示::Visible
            	PT_1->SetVisibility(EVisibility::Hidden);
            	SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
            	PT_2->SetVisibility(EVisibility::Hidden);
            	SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
            	PT_3->SetVisibility(EVisibility::Hidden);
            }else if(Lods == 2)
            {
            	LODGroupTxt->SetText(FText::FromString("SmallProp"));
            	SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
            	PT_1->SetVisibility(EVisibility::Visible);
            	SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
            	PT_2->SetVisibility(EVisibility::Hidden);
            	SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
            	PT_3->SetVisibility(EVisibility::Hidden);
            }else if(Lods == 3)
            {
            	LODGroupTxt->SetText(FText::FromString("LargeProp"));
            	SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
            	PT_1->SetVisibility(EVisibility::Visible);
            	SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
            	PT_2->SetVisibility(EVisibility::Visible);
            	SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
            	PT_3->SetVisibility(EVisibility::Hidden);
            }else if(Lods == 4)
            {
            	LODGroupTxt->SetText(FText::FromString("LevelArchitecture"));
            	SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
            	PT_1->SetVisibility(EVisibility::Visible);
            	SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
            	PT_2->SetVisibility(EVisibility::Visible);
            	SS_3->SetVisibility(EVisibility::Visible);	//显示::Visible
            	PT_3->SetVisibility(EVisibility::Visible);
            }
            GEngine->AddOnScreenDebugMessage(-1, 16.f, FColor::White, FString::Printf(TEXT("%s > %i 级LOD"), *LODtt, Lods));
		}
		
	}
}
FReply SSlateMain::Createlodset()
{
	if(LODDataOpations.Num()>0){
	if(LODdataComb->GetSelectedItem()){
		const FString dname = LODDataTxt->GetText().ToString();
		const FString bname = *LODdataComb->GetSelectedItem();
		// USkeletalMesh* mymesh = NewObject<USkeletalMesh>();
		TCHAR Pat[512];
		TCHAR aPat[512];
		// FString LODpp = FString::Printf(TEXT("SkeletalMeshLODSettings'/Game/%s/%s.%s'"),*lodpppp,*dname,*dname);
		const FString LODpp = FString::Printf(TEXT("/Game/%s/%s.%s"),*lodpppp,*bname,*bname);
		const FString assetLODpp = FString::Printf(TEXT("SkeletalMeshLODSettings'/Game/%s/%s.%s'"),*lodpppp,*dname,*dname);
		FCString::Strncpy(aPat, *assetLODpp, 511);
		USkeletalMeshLODSettings* aMyDataAsset = Cast<USkeletalMeshLODSettings>(StaticLoadObject(USkeletalMeshLODSettings::StaticClass(), nullptr, aPat));
		const FString dLODpp = FString::Printf(TEXT("%s/%s/%s.uasset"),*FPaths::ProjectContentDir(),*lodpppp,*bname);
		const FString cLODpp = FString::Printf(TEXT("%s/%s/%s.uasset"),*FPaths::ProjectContentDir(),*lodpppp,*dname);
		FCString::Strncpy(Pat, *LODpp, 511);
		USkeletalMeshLODSettings* MyDataAsset = Cast<USkeletalMeshLODSettings>(StaticLoadObject(USkeletalMeshLODSettings::StaticClass(), nullptr, Pat));
		// USkeletalMeshLODSettings* MyDataAsset = LoadObject<USkeletalMeshLODSettings>(nullptr, Pat, nullptr, LOAD_None, nullptr);
		if(MyDataAsset)
		{
			const float PTval_0 = PT_0->GetValue();
			const float PTval_1 = PT_1->GetValue();
			const float PTval_2 = PT_2->GetValue();
			const float PTval_3 = PT_3->GetValue();
			TArray<float> SSize = {SS_0->GetValue(), SS_1->GetValue(), SS_2->GetValue(), SS_3->GetValue()};
			TArray<float> PTria = {(PTval_0/100.0f), (PTval_1/100.0f), (PTval_2/100.0f), (PTval_3/100.0f)};
			//const USkeletalMeshLODSettings* MyEdit = const_cast<const USkeletalMeshLODSettings*>(MyDataAsset);
			//USkeletalMeshLODSettings *MyEdit = const_cast<USkeletalMeshLODSettings *>(MyDataAsset->GetSettingsForLODLevel(1).ScreenSize.Default);
			const int lodnum = MyDataAsset->GetNumberOfSettings();
			if(lodnum>0)
			{
				//设置SkeletalMeshLODGroupSettings AssetData文件参数
				for(int i = 0; i < lodnum; i++)
				{
					const FSkeletalMeshLODGroupSettings& ConstSettings = MyDataAsset->GetSettingsForLODLevel(i);
		            FSkeletalMeshLODGroupSettings& MutableSettings = const_cast<FSkeletalMeshLODGroupSettings&>(ConstSettings);	//常量引用转换为非常量引用
					MutableSettings.ScreenSize=SSize[i];
                    MutableSettings.ReductionSettings.NumOfTrianglesPercentage = PTria[i];
				}
			}
			MyDataAsset->Modify();

			GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Yellow, FString::Printf(TEXT("Test: %i"),lodnum));
		}
		if(dname!="")
		{
			bool sameN = true;
			for(const TSharedPtr<FString>& data : LODDataOpations)
			{
				if (dname == **data)
				{
					sameN = false;
					//GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Red, FString::Printf(TEXT("注意：输入的LOD预设名重名（输入的预设名称与目录中文件重名）")));
					break;
				}
			}
			if(sameN){
				// 使用FPlatformFileManager创建一个文件管理器
				// IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
				IFileManager& FileManager = IFileManager::Get();

				// 检查源文件是否存在
				if (FileManager.FileExists(*dLODpp))
				{
					// 创建目标文件夹
					// const FString DestinationFolder = FPaths::GetPath(dLODpp);
					// PlatformFile.CreateDirectoryTree(*DestinationFolder);
					FileManager.Copy(*cLODpp, *dLODpp);
					FAssetRegistryModule::AssetCreated(aMyDataAsset);
					// 复制文件
					// if (bCopyResult)
					// {
					// 	// 复制成功
					// 	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Yellow, FString::Printf(TEXT("文件复制成功: %s -> %s"), *dLODpp, *cLODpp));
					// 	UE_LOG(LogTemp, Log, TEXT("文件复制成功: %s -> %s"), *dLODpp, *cLODpp);
					// }
					// else
					// {
					// 	// 复制失败
					// 	UE_LOG(LogTemp, Error, TEXT("文件复制失败: %s -> %s"), *dLODpp, *cLODpp);
					// 	GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Yellow, FString::Printf(TEXT("文件复制失败: %s -> %s"), *dLODpp, *cLODpp));
					// }
				}else{
					// 源文件不存在
					UE_LOG(LogTemp, Warning, TEXT("源文件不存在: %s"), *dLODpp);
					GEngine->AddOnScreenDebugMessage(-1, 7.f, FColor::Yellow, FString::Printf(TEXT("源文件不存在: %s"),*dLODpp));
				}
				// USkeletalMeshLODSettings* MyDataAsset = NewObject<USkeletalMeshLODSettings>(GetTransientPackage(),USkeletalMeshLODSettings::StaticClass());
				// const FString PackagePath = FPackageName::GetLongPackagePath(FString::Printf(TEXT("/Game/%s/%s"),*lodpppp,*dname));
				// UPackage* Package = CreatePackage(nullptr, *PackagePath);
				// Package->FullyLoad();
				// Package->MarkPackageDirty();
				// FAssetRegistryModule::AssetCreated(MyDataAsset);
				// Package->SetDirtyFlag(true);
				// FString PackageFileName = FPackageName::LongPackageNameToFilename(PackagePath, FPackageName::GetAssetPackageExtension());
				// bool bSuccess = UPackage::SavePackage(Package, MyDataAsset, EObjectFlags::RF_Public | EObjectFlags::RF_Standalone, *PackageFileName, GError, nullptr, true, true, SAVE_NoError);
				// if(bSuccess)
				// 	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT("创建成功")));
				// else
				// 	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("创建未成功")));
			}
		}else
     		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("请在中间文本框输入保存的LOD预设文件名")));
	}else
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("◆下拉列表中选择一个预设")));
	}else
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT("请先点击【刷新】按钮")));
	return FReply::Handled();
}
FReply SSlateMain::LodlodsetVal()
{
	if(LODdataComb->GetSelectedItem())
		LodDataGetVal(*LODdataComb->GetSelectedItem());
	return FReply::Handled();
}
void SSlateMain::LodDataOnPathText(const FText& Text)
{
	FString ppp = Text.ToString();
	if(ppp.Right(1) == "/")
	{
		ppp = ppp.LeftChop(1);
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT(" %s 路径结尾不能有斜杠！"), *Text.ToString()));
	}
	if(FPaths::DirectoryExists(*(FPaths::ProjectContentDir() + ppp)))
	{
		// LoadLODData(*lodpppp);
		CFN.WriteIni(FString("SceneTools"), FString("LodDataPath"), ppp, IniPath);
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green, FString::Printf(TEXT(" %s 目录存在"), *ppp));
	}else{
		LODDataOpations.Empty();
		LODDataTxt->SetText(FText::FromString(""));
		LDcount->SetText(FText::FromString(": 0"));
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, FString::Printf(TEXT(" %s 目录不存在"), *Text.ToString()));
	}
}
void SSlateMain::SearchSizeValueSet(FPlatformTypes::int32 val)
{
	for (int i=5; i <= 11;i++)
	{
		int sss =pow(2,i);
		if (val >= sss && val < pow(2,(i+1)))
		{
			searchSize->SetValue(sss);
            CFN.WriteIni(FString("SceneTools"), FString("SearchV"), FString::FromInt(sss), IniPath);
		}
			
	}
	
}
void SSlateMain::btn360(FPlatformTypes::int32 val)
{
	//spn360->SetSliderExponent(val);
	return;
}
void SSlateMain::SetSizeValue(FPlatformTypes::int32 val)
{
	if (val <= 11)
	{
		int vvv = pow(2,val);
        SizeValue->SetText(FText::FromString(FString::FromInt(vvv)));
        CFN.WriteIni(FString("SceneTools"), FString("SetV"), FString::FromInt(vvv), IniPath);
        CFN.WriteIni(FString("SceneTools"), FString("PowV"), FString::FromInt(val), IniPath);
		if (vvv > 512)
		{
			SizeValue->SetForegroundColor(FLinearColor(0.93,0.02,0.1,1.0));
		}else
			SizeValue->SetForegroundColor(FLinearColor(0.0,0.92,0.1,1.0));
	}
}
void SSlateMain::ptValue_0(FPlatformTypes::int32 val)
{
    CFN.WriteIni(FString("SceneTools"), FString("PercentTriangles_0"), FString::FromInt(val), IniPath);
}
void SSlateMain::ptValue_1(FPlatformTypes::int32 val)
{
    CFN.WriteIni(FString("SceneTools"), FString("PercentTriangles_1"), FString::FromInt(val), IniPath);
}
void SSlateMain::ptValue_2(FPlatformTypes::int32 val)
{
    CFN.WriteIni(FString("SceneTools"), FString("PercentTriangles_2"), FString::FromInt(val), IniPath);
}
void SSlateMain::ptValue_3(FPlatformTypes::int32 val)
{
    CFN.WriteIni(FString("SceneTools"), FString("PercentTriangles_3"), FString::FromInt(val), IniPath);
}

void SSlateMain::ssValue_0(float val)
{
    CFN.WriteIni(FString("SceneTools"), FString("ScreenSize_0"), FString::SanitizeFloat(val), IniPath);
}
void SSlateMain::ssValue_1(float val)
{
    CFN.WriteIni(FString("SceneTools"), FString("ScreenSize_1"), FString::SanitizeFloat(val), IniPath);
}
void SSlateMain::ssValue_2(float val)
{
    CFN.WriteIni(FString("SceneTools"), FString("ScreenSize_2"), FString::SanitizeFloat(val), IniPath);
}
void SSlateMain::ssValue_3(float val)
{
    CFN.WriteIni(FString("SceneTools"), FString("ScreenSize_3"), FString::SanitizeFloat(val), IniPath);
}
void SSlateMain::comp_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	texComp->SetText(FText::FromString(*Item));
}
void SSlateMain::LODData_ComboChanged(const TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (Item)
	{
		DisplayLODTri->SetColorAndOpacity(FLinearColor(0.4,0.4,0.4,1.0));
		LODDataTxt->SetText(FText::FromString(*Item));
		LodDataGetVal(*Item);
		getLodBtn->SetToolTipText(FText::FromString(*Item));	//修改按钮ToolTip文本需要转换为FText类型
	}
}
void SSlateMain::LOD_ComboChanged(const TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	LODGroupTxt->SetText(FText::FromString(*Item));
	if(*Item == "SmallProp")
	{
        SS_2->SetVisibility(EVisibility::Hidden);	//显示::Visible
        PT_2->SetVisibility(EVisibility::Hidden);
		SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
		PT_3->SetVisibility(EVisibility::Hidden);
		SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
		PT_1->SetVisibility(EVisibility::Visible);
	}
	else if(*Item == "LargeProp")
	{
		SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
		PT_1->SetVisibility(EVisibility::Visible);
		SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
		PT_2->SetVisibility(EVisibility::Visible);
		SS_3->SetVisibility(EVisibility::Hidden);	//显示::Visible
		PT_3->SetVisibility(EVisibility::Hidden);
	}
	else
	{
		SS_1->SetVisibility(EVisibility::Visible);	//显示::Visible
		PT_1->SetVisibility(EVisibility::Visible);
		SS_2->SetVisibility(EVisibility::Visible);	//显示::Visible
		PT_2->SetVisibility(EVisibility::Visible);
		SS_3->SetVisibility(EVisibility::Visible);	//显示::Visible
		PT_3->SetVisibility(EVisibility::Visible);
	}
}
void SSlateMain::comp_equalText(const TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	if (*Item == TEXT("等于"))
	{
		equalText->SetText(FText::FromString(TEXT("等于")));
		CFN.WriteIni(FString("SceneTools"), FString("Equal"), TEXT("等于"), IniPath);
	}
	else
	{
		equalText->SetText(FText::FromString(TEXT("大于等于")));
		CFN.WriteIni(FString("SceneTools"), FString("Equal"), TEXT("大于等于"), IniPath);
	}
}
//用于显示下拉菜单内容,所有SComboBox的.OnGenerateWidget(...)共用该函数
TSharedRef<class SWidget> SSlateMain::comp_ComboItem(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}


void SSlateMain::HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	//SelectInfo = ESelectInfo::OnKeyPress;
	SaveNewPath();
	texPath->SetText(FText::FromString(*Item));
	FString aa = LexToString(*phComBox->GetSelectedItem());
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, aa);
}

void SSlateMain::SaveNewPath()
{
	FString pText = texPath->GetText().ToString();
	if (pText != "")
	{
		if (pText.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
		{
			FString newP = "";
			TArray<FString> SArr;
			pText.ParseIntoArray(SArr, TEXT("\\"), false);
			for (const FString sss : SArr)
			{
				newP += sss + "/";
			}
			pText = newP;
		}
		FString en = pText.Right(1);
		if (en == "/")
			pText = pText.LeftChop(1);
		if (FPaths::DirectoryExists(*(FPaths::ProjectContentDir() + pText)))
		{
			if (DiffPathText(pText))
			{
				phOpations.Add(MakeShareable(new FString(pText))); //單獨添加路徑
				phComBox->RefreshOptions(); //刷新下拉列表
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("新路徑已保存")));
				UE_LOG(LogTemp, Warning, TEXT("新路徑已保存"));
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("请输入content下的路径")));
	}
}
//读取记录
void SSlateMain::ReflashHist()
{
	FString aaa = ReadTxt("ST.txt");
	UE_LOG(LogTemp, Log, TEXT("%s"), *aaa);
	TArray<FString> arr;
	aaa.ParseIntoArray(arr, TEXT("\n"), false); //以换行符劈开文本字符
	if (arr.Num() > 0)
	{
		for (const FString path : arr)
		{
			//批量添加下拉列表
			if (path != "")
				if (FPaths::DirectoryExists(*(FPaths::ProjectContentDir() + path)))
				{
					phOpations.Add(MakeShareable(new FString(path)));
				}
		}
	}
}
//读取文件函数
FString SSlateMain::ReadTxt(FString PN)
{
	FString readString;
	//路徑ProjectPluginsDir() = "../../../PM/Plugins/"
	FFileHelper::LoadFileToString(readString, *(FPaths::ProjectPluginsDir() + "SceneTools_W_P/" + PN));
	return readString;
}
//写入文件函数
bool SSlateMain::WriteTxt(FString savestring, FString SavePath)
{
	bool result;
	result = FFileHelper::SaveStringToFile(savestring, *SavePath);
	return true;
}
FReply SSlateMain::LoadLODDataUI()	//读取目录中的LOD DataAsset 文件
{
	LoadLODData(*lodpppp);
	return FReply::Handled();
}
FReply SSlateMain::LoadLODData(FString lodp)	//读取目录中的LOD DataAsset 文件
{
	if(lodp != "")
	{
		LODDataOpations.Empty();	//先清空列表
		TArray<FAssetData> AssetDatas;
		const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
		FARFilter Filter;
		CFN.ReadIniValue(FString("SceneTools"), FString("LodDataPath"), lodp, *IniPath);
		FString pp = *lodp;
		//FString pp = "Mesh/Common/LOD_Setting";
		if (pp != "")
		{
			//查找路径是否是反斜杠，如果是切割并替换成正斜杠
			if (pp.Find(TEXT("\\"), ESearchCase::IgnoreCase, ESearchDir::FromStart, INDEX_NONE) != INDEX_NONE)
			{
				FString newP = "";
				TArray<FString> SArr;
				pp.ParseIntoArray(SArr, TEXT("\\"), false);
				for (const FString sss : SArr)
				{
					newP += sss + "/";
				}
				pp = newP;
			}
			const FString en = pp.Right(1);
			if (en == "/")
				pp = pp.LeftChop(1);
			//提取最后一个目录名 pName
			TArray<FString> SArr;
			pp.ParseIntoArray(SArr, TEXT("/"), false);
			Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //设置资源路径,需要FName類型字符 *FString 前面加星號解引出來使用
		}else
		{
			Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game")));
		}
		// Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp)); //需要FName類型字符 *FString 前面加星號解引出來使用
		Filter.ClassNames.Add(USkeletalMeshLODSettings::StaticClass()->GetFName());
		AssetRegistryModule.Get().GetAssets(Filter, AssetDatas);
		LDcount->SetText(FString::Printf(TEXT(": %i"),AssetDatas.Num()));
		for (const FAssetData& AssetData : AssetDatas)
		{
			const USkeletalMeshLODSettings* LODData = Cast<USkeletalMeshLODSettings>(StaticLoadObject(USkeletalMeshLODSettings::StaticClass(), nullptr,
			                                                                                          (TEXT("SkeletalMeshLODSettings'%s'"), *AssetData.ObjectPath.ToString())));
			if (LODData){
				GEngine->AddOnScreenDebugMessage(-1, 26.f, FColor::Yellow, FString::Printf(TEXT("%s  > %i 级LOD"), *LODData->GetName(), LODData->GetNumberOfSettings()));
				LODDataOpations.Add(MakeShareable(new FString(FString::Printf(TEXT("%s"), *LODData->GetName()))));
			}
		}
		LODdataComb->RefreshOptions();	//这里需要刷新
		GEngine->AddOnScreenDebugMessage(-1, 26.f, FColor::Green, FString::Printf(TEXT("路径：Content/%s/"), *lodp));
	}
	return FReply::Handled();
}
FReply SSlateMain::SaveButtom()
{
	SaveNewPath();
	
	return FReply::Handled();
}
void SSlateMain::OnSelTextChanged(const FText& Text)
{
	CFN.WriteIni(FString("SceneTools"), FString("SelText"), Text.ToString(), IniPath);
}
FReply SSlateMain::AddPerfix()
{	FText const Title = FText::FromString(TEXT("添加前缀命名"));
	FText const DialogText = FText::FromString(TEXT("确认选择的物体添加前缀命名吗?"));
	EAppReturnType::Type const ReturnType = FMessageDialog::Open(EAppMsgType::OkCancel, DialogText, &Title);
	if (ReturnType == EAppReturnType::Type::Ok)
	{
		USelection* SelectionSet = GEditor->GetSelectedActors();  //先从编辑器获取选择的Actor
		if (SelectionSet->Num() > 0)
		{
			TArray<AActor*> SelectedActors;  //定义AActor类型数组存放获取的选择物体
			SelectedActors.Reserve(SelectionSet->Num());  //储备所有选择的物体
			SelectionSet->GetSelectedObjects(SelectedActors); //将储备的物体提取到选择组
			for (AActor* Actor : SelectedActors)
			{
				Actor->SetActorLabel(FString::Printf(TEXT("%s_%s"), *selText->GetText().ToString(), *Actor->GetName()));
			}
		}
	}
    return FReply::Handled();
}
FReply SSlateMain::SelectFromText()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	TArray<AActor*> sel;
	sel.Reserve(SelectionSet->Num());
	SelectionSet->GetSelectedObjects(sel);
    FString boxname;
    UWorld* World = GEditor->GetEditorWorldContext().World();
    
    TArray<AActor*> ActorsToFind;
    if(World)
    {
    	UGameplayStatics::GetAllActorsOfClass(World, AStaticMeshActor::StaticClass(), ActorsToFind);
    }
    SelectionSet->DeselectAll();
    for (AActor* inActor: ActorsToFind){
    	// auto aaa = inActor->GetName().Find("STBox");
    	// GEngine->AddOnScreenDebugMessage(-1, 43.f, FColor::Black, FString::Printf(TEXT("< %i"),aaa));
    	if(inActor->GetName().Find(selText->GetText().ToString())>-1)
    		SelectionSet->Select(inActor);
    }
	SelectionSet->ReloadConfig();
	GEngine->AddOnScreenDebugMessage(-1, 16.f, FColor::Yellow, FString::Printf(TEXT("共选中 %i 个"), SelectionSet->Num()));
	return FReply::Handled();
}
FReply SSlateMain::CloneActor()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
 	
	if (SelectionSet->Num() == 1)
	{
		FVector Cscl;
		UWorld* World = GEditor->GetEditorWorldContext().World();
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[0];
		// auto* clas = Cast<UClass>(ppp);
		
		if (ppp->GetClass()->GetName()=="StaticMeshActor"){
			FVector Cpos=ppp->GetActorLocation();
			Cscl=ppp->GetActorScale();

			auto* selA = Cast<AStaticMeshActor>(ppp);	//通过Cast获取选择的对象指定<中>的类型,才能提取StaticMesh
			UStaticMesh* meshload = selA->GetStaticMeshComponent()->GetStaticMesh();
     	
			SelectionSet->DeselectAll();
			FString boxname;
			FString levN = ppp->GetName();
			FString STLevel = "";
			CFN.ReadIniValue(FString("SceneTools"), levN, STLevel, IniPath);
			int STcunt;
			STcunt = FCString::Atoi(*STLevel);
			if (STcunt > 0)
			{
				int CEO=0; //计算场景有多少组矩阵盒子
				TArray<AActor*> ActorsToFind;
				if(World)
				{ // GetAllActorsOfClass(World, 类型的::StaticClass(), 定义的存放数组);
					UGameplayStatics::GetAllActorsOfClass(World, AActor::StaticClass(), ActorsToFind);
				}
				for (int i = 1; i <= STcunt; i++)	//遍历场景中所有的StaticMeshActor物体,查找是否存在矩阵盒子,如果没有将记录归为1
					{
					for (AActor* inActor: ActorsToFind){
						//这里查找名字是否包含用Find,不能用GetName()==".." 否则在第二次创建物体时会误判为找不到名称
						if(inActor->GetName().Find(FString::Printf(TEXT("%s_%i"), *levN, i))>-1)
							CEO+=1;
					}
					}
				if (CEO > 0)
				{
					STcunt += 1;
					CFN.WriteIni(FString("SceneTools"), levN, FString::FromInt(STcunt), IniPath);
				}else
				{
					CFN.WriteIni(FString("SceneTools"), levN, "1", IniPath);
					STcunt = 1;
				}
			
			}else{
				CFN.WriteIni(FString("SceneTools"), levN, "1", IniPath);
				STcunt = 1;
			}
		// FActorSpawnParameters newcc = ppp->SpawnCollisionHandlingMethod;
			FActorSpawnParameters newcc = FActorSpawnParameters();
			for (int i = 1; i <= matrixNum->GetValue(); i++)
			{
				auto* MyActor = World->SpawnActor<AStaticMeshActor>(Cpos+FVector(0,100,0), ppp->GetActorRotation(), newcc);
				MyActor->SetFolderPath("Clone_Folder");
				MyActor->GetStaticMeshComponent()->SetStaticMesh(meshload);
				boxname = levN+"_" +FString::FromInt(STcunt)+"_" + FString::FromInt(i);
				MyActor->SetActorLabel(boxname);
				MyActor->SetActorScale3D(Cscl);
				SelectionSet->Select(MyActor);	//选中对象
			}
			SelectionSet->ReloadConfig();
			SSlateMain::XArray_slide(1.0);
		}else
		{
			GEngine->AddOnScreenDebugMessage(-1, 26.f, FColor::Blue, FString::Printf(TEXT("该类型是: %s"),*ppp->GetClass()->GetName()));
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red, TEXT("请选择StaticMeshActor静态网格模型对象!"));
		}
			
	}
	return FReply::Handled();
}
FReply SSlateMain::SelSameObj()
{
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num()>0)
	{
		TArray<AActor*> sel;
		sel.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(sel);
		FString boxname;
		UWorld* World = GEditor->GetEditorWorldContext().World();
    
		TArray<AActor*> ActorsToFind;
		if(World)
		{
			UGameplayStatics::GetAllActorsOfClass(World, AStaticMeshActor::StaticClass(), ActorsToFind);
		}
		const FString selname = sel[0]->GetName().LeftChop(log10(matrixNum->GetValue())+1); //提取第一个选择的对象名去掉最后几个字符,用矩阵数的位数+3
		SelectionSet->DeselectAll();
		for (AActor* inActor: ActorsToFind){
			if(inActor->GetName().Find(selname)>-1)
				SelectionSet->Select(inActor);
		}
		SelectionSet->ReloadConfig();
		GEngine->AddOnScreenDebugMessage(-1, 16.f, FColor::Yellow, FString::Printf(TEXT("%s 选中 %i 个"), *selname, SelectionSet->Num()));
	}
	return FReply::Handled();
}


#undef LOCTEXT_NAMESPACE
