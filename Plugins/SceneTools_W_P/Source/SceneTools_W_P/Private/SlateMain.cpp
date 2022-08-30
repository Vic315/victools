#include "SlateMain.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SButton.h"
#include "AssetRegistryModule.h"
#include "Engine/UserDefinedStruct.h"
#include "Logging/LogMacros.h"
#include "Misc/FileHelper.h"

#include "Editor.h"
#include "Engine/Engine.h"
#include "Engine/Selection.h"
#include "Engine/Texture.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "UObject/UObjectGlobals.h"
#include "Widgets/Input/SCheckBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SBox.h"

//#include "Widgets/SWidget.h"
//#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "SlateMain"

FString pppp;//全局变量

void SSlateMain::Construct(const FArguments& InArgs)
{
	//FString vers = FString::Printf(TEXT("%s %s"), *na, *ST_Ver);
	const FString vers = FString::Printf(TEXT("SceneTools  %s"), *ST_Ver);
	
	//IPlatformFile& fileManager = FPlatformFileManager::Get().GetPlatformFile();

	if (FPaths::FileExists(*(FPaths::ProjectPluginsDir() + "SceneTools_W_P/ST.txt"))) {
		ReflashHist();
	} else {
		WriteTxt("","ST.txt");
		//phOpations.Add(MakeShareable(new FString("")));
	}
	compOpations.Add(MakeShareable(new FString("Default")));
	compOpations.Add(MakeShareable(new FString("NormalMap")));
	compOpations.Add(MakeShareable(new FString("BC7")));
	
	ChildSlot
	[
		SNew(SVerticalBox)//創建垂直面板
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Center).AutoHeight()
		.Padding(2.0f)
		[
			SNew(STextBlock).Text(FText::FromString(*vers))
		]
		+ SVerticalBox::Slot().AutoHeight()
		.Padding(2.0f)	//间距
		[
			SNew(SExpandableArea)	//可折疊面板
			.AreaTitle(LOCTEXT("MyExpandable", "Scene Tools"))
			.InitiallyCollapsed(true)
			.Padding(2.0f)
			.HeaderContent()
			[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot().AutoWidth()
			.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(5.0f)
			[SNew(STextBlock).Text(LOCTEXT("batch", "批处理:"))
			]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left).AutoWidth()
			.Padding(2.0f)[
				SAssignNew(phComBox, SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&phOpations)
					.OnGenerateWidget(this, &SSlateMain::GenerateSourceComboItem)
					.OnSelectionChanged(this, &SSlateMain::HandleSourceComboChanged)
					.IsFocusable(true)[
						SAssignNew(phComBoxCont, SBox)
					]
				]
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.AutoWidth()
			.MaxWidth(280)
			.Padding(2.0f)
				[
					SAssignNew(texPath, SEditableTextBox).Text(FText::FromString(*pppp))
					//.OnTextCommitted(this, &SSlateMain::OnPathText)
				]
				+ SHorizontalBox::Slot()
					.HAlign(HAlign_Left)
					.Padding(4.f)
					[
						SNew(SButton).Text(LOCTEXT("savePath", "Save"))
						.ToolTipText(LOCTEXT("save", "保存當前路徑"))
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
			]
		.BodyContent()[
			SNew(SHorizontalBox)

				+ SHorizontalBox::Slot().AutoWidth()
				.HAlign(HAlign_Left).VAlign(VAlign_Center).Padding(2.0f)
				[SNew(STextBlock).Text(LOCTEXT("batchN", "压缩格式批处理: "))
				]
				+ SHorizontalBox::Slot().Padding(8.0f)
				.HAlign(HAlign_Fill).AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("go", "设置法线图_N"))
					.ToolTipText(LOCTEXT("goTooltip", "只设置法线贴图压缩格式"))
					.OnClicked(this, &SSlateMain::OnGoButtonClicked)
				]
				+ SHorizontalBox::Slot().Padding(8.0f)
				.HAlign(HAlign_Fill).AutoWidth()
				[
					SNew(SButton)
					.Text(LOCTEXT("goMap", "设置贴图"))
					.ToolTipText(LOCTEXT("goMapTooltip", "批量设置所有贴图压缩格式"))
					.OnClicked(this, &SSlateMain::OnGoMapButtonClicked)
				]
				+ SHorizontalBox::Slot().Padding(3.0f)
				.HAlign(HAlign_Left).VAlign(VAlign_Center).AutoWidth()
				[
					SAssignNew(compSettingComBox, SComboBox<TSharedPtr<FString>>)
					.OptionsSource(&compOpations)
					.OnGenerateWidget(this, &SSlateMain::comp_ComboItem)
					.OnSelectionChanged(this,&SSlateMain::comp_ComboChanged)
					.IsFocusable(true)[
						SAssignNew(compComBoxCont, SBox)
					]
				]
				+ SHorizontalBox::Slot().Padding(3.0f)
					.HAlign(HAlign_Left).VAlign(VAlign_Center)
					[
						SAssignNew(texComp, SEditableTextBox).Text(FText::FromString("Default"))
					]
			]
		]
		+ SVerticalBox::Slot().AutoHeight()
				.Padding(2.0f)	//间距
				[
					SAssignNew(Expnv12,SExpandableArea)	//可折疊面板
					.AreaTitle(LOCTEXT("v12expn", "AlignParent"))
				.InitiallyCollapsed(true)
				.Padding(2.0f)
				.HeaderContent()
			[
				SNew(SHorizontalBox)

				+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left).VAlign(VAlign_Center).FillWidth(30.0f)
			.Padding(2.0f)[
					SNew(STextBlock).Text(LOCTEXT("v12", "层级与对齐："))
			]
				+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center).VAlign(VAlign_Center).FillWidth(40.0f)
			.Padding(2.0f)[
					//SNew(STextBlock).Text(FText::FromString("Parent and Align:"))

				SNew(SButton)
					.Text(LOCTEXT("ttttt", "  - collapse -  "))
					.OnClicked(this, &SSlateMain::testClicked)
			]
				].BodyContent()[
					SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight()
		.Padding(2.0f)	//间距
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
				.Text(LOCTEXT("alignPos", "Location")).VAlign(VAlign_Center)
				.ToolTipText(LOCTEXT("alignPosTT", "对齐物体（位移）到最后选择的物体"))
				.OnClicked(this, &SSlateMain::AlignPosClicked)
			]
			+ SHorizontalBox::Slot().VAlign(VAlign_Center).AutoWidth()
				.HAlign(HAlign_Right).Padding(2.0f)
				[
					SNew(SButton)
					.Text(LOCTEXT("alignRot", "Rotation"))
				.ToolTipText(LOCTEXT("alignRotTT", "对齐物体（旋转）到最后选择的物体，右边值大于‘0’将取随机角度"))
				.OnClicked(this, &SSlateMain::AlignRotClicked)
				]
			+ SHorizontalBox::Slot().VAlign(VAlign_Center)
				.HAlign(HAlign_Left).AutoWidth().Padding(2.0f)
				[
					SAssignNew(randomAngle, SSpinBox<int>).MaxValue(360).MinValue(0).Value(0).ToolTipText(LOCTEXT("randval", "值大于‘0’将按该值随机角度旋转"))
				]
			+ SHorizontalBox::Slot().VAlign(VAlign_Center).AutoWidth()
				.HAlign(HAlign_Right).Padding(2.0f)
				[
					SNew(SButton)
					.Text(LOCTEXT("alignSel", "Scale"))
				.ToolTipText(LOCTEXT("alignSclTT", "对齐物体（缩放）到最后选择的物体"))
				.OnClicked(this, &SSlateMain::AlignSclClicked)
				]
		]
		+ SVerticalBox::Slot().AutoHeight()
			.Padding(2.0f)
			[
				SNew (SUniformGridPanel).SlotPadding(3.0f)

				+ SUniformGridPanel::Slot(0,0)
				.HAlign(HAlign_Center).VAlign(VAlign_Center)
				[SNew(STextBlock).Text(LOCTEXT("spacing","物体间距"))
				]
				+ SUniformGridPanel::Slot(1,0)
				.HAlign(HAlign_Center).VAlign(VAlign_Center)
				[SNew(STextBlock).Text(LOCTEXT("mo","行数"))
				]
				+ SUniformGridPanel::Slot(2,0)
				.HAlign(HAlign_Center).VAlign(VAlign_Center)
				[SNew(STextBlock).Text(LOCTEXT("moSp","行间距"))
				]
				+ SUniformGridPanel::Slot(0,2)
				.HAlign(HAlign_Center).VAlign(VAlign_Center)
				[SNew(STextBlock).Text(LOCTEXT("arrTT","排列对齐:"))
				]
				+ SUniformGridPanel::Slot(0,1)
				.HAlign(HAlign_Fill).VAlign(VAlign_Center)
				[
					SAssignNew(arraySpace, SSpinBox<int>).MaxValue(900).MinValue(-600).Value(0)
					
				]
				+ SUniformGridPanel::Slot(1,1)
				.HAlign(HAlign_Fill).VAlign(VAlign_Center)
				[
					SAssignNew(arrayRow, SSpinBox<int>).MaxValue(10).MinValue(1).Value(1)
				]
				+ SUniformGridPanel::Slot(2, 1)
					.HAlign(HAlign_Fill).VAlign(VAlign_Center)
					[
						SAssignNew(arrayRowSp, SSpinBox<int>).MaxValue(2000).MinValue(-2000).Value(0)
					]
				+ SUniformGridPanel::Slot(1,2)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("aX", "[X]■■■"))
					.ToolTipText(LOCTEXT("aXtt", "按 X 轴排列"))
					.OnClicked(this, &SSlateMain::XArray_Clicked)
				]
				+ SUniformGridPanel::Slot(2,2)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("aY", "[Y]■■■"))
					.ToolTipText(LOCTEXT("aYtt", "按 Y 轴排列"))
					.OnClicked(this, &SSlateMain::YArray_Clicked)
				]
				//----------------------------
				+ SUniformGridPanel::Slot(3,0)
				.HAlign(HAlign_Center).VAlign(VAlign_Center)
				[SNew(STextBlock).Text(LOCTEXT("bound","边界对齐:"))
				]
				+ SUniformGridPanel::Slot(4,0)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("Xadd", "X←"))
					.ToolTipText(LOCTEXT("Xo", "对齐至X轴边界"))
					.OnClicked(this, &SSlateMain::XoAlignX_Clicked)
				]
				+ SUniformGridPanel::Slot(6,0)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("-Xadd", "→X"))
					.ToolTipText(LOCTEXT("oX", "对齐至-X轴边界"))
				.OnClicked(this, &SSlateMain::oXAlignX_Clicked)
				]
				+ SUniformGridPanel::Slot(5, 0)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("cXadd", "→X←"))
					.ToolTipText(LOCTEXT("oXo", "对齐至X轴中间"))
				.OnClicked(this, &SSlateMain::oXoAlignX_Clicked)
				]

				+ SUniformGridPanel::Slot(4,1)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("Yadd", "Y←"))
					.ToolTipText(LOCTEXT("Yo", "对齐至Y轴边界"))
				.OnClicked(this, &SSlateMain::YoAlignY_Clicked)
				]
				+ SUniformGridPanel::Slot(6,1)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("-Yadd", "→Y"))
					.ToolTipText(LOCTEXT("oY", "对齐至-Y轴边界"))
				.OnClicked(this, &SSlateMain::oYAlignY_Clicked)
				]
				+ SUniformGridPanel::Slot(5,1)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("cYadd", "→Y←"))
					.ToolTipText(LOCTEXT("oYo", "对齐至Y轴中间"))
				.OnClicked(this, &SSlateMain::oYoAlignY_Clicked)
				]

				+ SUniformGridPanel::Slot(4,2)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("Zadd", "Z←"))
					.ToolTipText(LOCTEXT("Zo", "对齐至Z轴边界"))
				.OnClicked(this, &SSlateMain::ZoAlignZ_Clicked)
				]
				+ SUniformGridPanel::Slot(6,2)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("-Zadd", "→Z"))
					.ToolTipText(LOCTEXT("oZ", "对齐至-Z轴边界"))
				.OnClicked(this, &SSlateMain::oZAlignZ_Clicked)
				]
				+ SUniformGridPanel::Slot(5, 2)
				.HAlign(HAlign_Fill)
				[
					SNew(SButton)
					.Text(LOCTEXT("cZadd", "→Z←"))
					.ToolTipText(LOCTEXT("oZo", "对齐至Z轴中间"))
				.OnClicked(this, &SSlateMain::oZoAlignZ_Clicked)
				]
			]
		]
	]];
}
FReply SSlateMain::testClicked() {

	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 0) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[0];
		
		//UWorld* World = GEditor->GetWorld();
		//TSubclassOf<class AActor> bpClass = (ppp)->GetClass();
		//AActor* newA = World->SpawnActor<AActor>(bpClass,ppp->GetActorLocation()+FVector(50.0f,0.0f,0.0f), FRotator::ZeroRotator);
		TArray<AActor*>aa;
		ppp->GetAttachedActors(aa);
		for (int32 b = 0; b < aa.Num(); b++)
		{
			AActor* a = aa[b];
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(a->GetName()));
		}
	}
	if(Expnv12->IsExpanded())
	{
		Expnv12->SetExpanded(false);
	}
	else 
	{
		Expnv12->SetExpanded(true);
		
	}
	//UE_LOG(LogTemp, Error, TEXT("test %i"), arrayRow);
	return FReply::Handled();
}
FReply SSlateMain::SaveRedo() {

	return FReply::Handled();
}
FReply SSlateMain::ParentHelpClicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 0) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
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
FReply SSlateMain::XArray_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		float SpAdd=pO.Y;
		float RowSpAdd=0.f;
		float RowSp=pO.X;
		int CN = 0;
		int Rows = arrayRow->GetValue();
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				CN++;
				SpAdd += pE.X + Extent.X + float(arrayRowSp->GetValue());
				if (CN % Rows==0) {
					SpAdd = pO.Y;
					RowSp += float(arraySpace->GetValue())+pE.Y*2;
				}
				FVector newp = FVector(RowSp, SpAdd, pO.Z-(pE.Z-Extent.Z));
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::YArray_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		float SpAdd=pO.X;
		float RowSpAdd=0.f;
		float RowSp=pO.Y;
		int CN = 0;
		int Rows = arrayRow->GetValue();
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				CN++;
				SpAdd += pE.X + Extent.X + float(arrayRowSp->GetValue());
				if (CN % Rows==0) {
					SpAdd = pO.X;
					RowSp += float(arraySpace->GetValue())+pE.X*2;
				}
				FVector newp = FVector(SpAdd, RowSp, pO.Z-(pE.Z-Extent.Z));
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}

//===================[Align]==============================
FReply SSlateMain::XoAlignX_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X + pE.X + Extent.X, Origin.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::oXAlignX_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X - pE.X - Extent.X, Origin.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::oXoAlignX_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, Origin.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::YoAlignY_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, pO.Y + pE.Y + Extent.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::oYAlignY_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, pO.Y - pE.Y - Extent.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::oYoAlignY_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, pO.Y, Origin.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::ZoAlignZ_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, Origin.Y, pO.Z + pE.Z + Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::oZAlignZ_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, Origin.Y, pO.Z - pE.Z - Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::oZoAlignZ_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(Origin.X, Origin.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
//----------------------------------------------

FReply SSlateMain::cAlignX_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X + pE.X + Extent.X, pO.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::cAlignNX_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X - pE.X - Extent.X, pO.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::cAlignY_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y + pE.Y + Extent.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::cAlignNY_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y - pE.Y - Extent.Y, pO.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::cAlignZ_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y, pO.Z + pE.Z + Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::cAlignNZ_Clicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		FVector pO, pE;
		ppp->GetActorBounds(true, pO, pE);
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				FVector Origin, Extent;
				Actor->GetActorBounds(true, Origin, Extent);
				FVector newp = FVector(pO.X, pO.Y, pO.Z - pE.Z - Extent.Z);
				Actor->SetActorLocation(newp);
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
//==============================================
FReply SSlateMain::AlignPosClicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				Actor->SetActorLocation(ppp->GetActorLocation());
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::AlignRotClicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 0) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (randomAngle->GetValue() == 0) {
				if (Actor->GetFName() != ppp->GetFName()) {
					Actor->SetActorRotation(ppp->GetActorRotation());
					GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
				}
			}
			else
			{
				Actor->SetActorRotation(FRotator(0.f, float(FMath::RandRange(0, int(randomAngle->GetValue()))), 0.f));
			}
		}
	}
	return FReply::Handled();
}
FReply SSlateMain::AlignSclClicked() {
	USelection* SelectionSet = GEditor->GetSelectedActors();
	if (SelectionSet->Num() > 1) {
		TArray<AActor*> SelectedActors;
		SelectedActors.Reserve(SelectionSet->Num());
		SelectionSet->GetSelectedObjects(SelectedActors);
		AActor* ppp = SelectedActors[SelectedActors.Num() - 1];
		for (AActor* Actor : SelectedActors)
		{
			if (Actor->GetFName() != ppp->GetFName()) {
				Actor->SetActorScale3D(ppp->GetActorScale3D());
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Actor->GetFName().ToString());
			}
		}
	}
	else {
		GEditor->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("选择两个以上物体"));
	}
	return FReply::Handled();
}
FReply SSlateMain::OnGoButtonClicked() {
	//UE_LOG(LogTemp, Warning, TEXT("AssetName:%s"), *MatObj->GetName());
	TArray<FAssetData> AssetDatas;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FARFilter Filter;
	FString pp = texPath->GetText().ToString();
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
	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp));//需要FName類型字符 *FString 前面加星號解引出來使用
	Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());
	if (RPath->IsChecked())
	{	//遞歸搜尋路徑，查找子目錄
		Filter.bRecursivePaths = true;
	}else{
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
		UTexture* MatObj = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), nullptr, (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::FromInt(MatObj->CompressionSettings.GetValue()));
		if (texComp->GetText().ToString() == "Default") {
			if (MatObj->CompressionSettings.GetValue() == 1) {
				MatObj->CompressionSettings = TC_Default;
				//標記未保存星號
				MatObj->AddToRoot();
				MatObj->UpdateResource();
				MatObj->MarkPackageDirty();
				cou += 1;
				UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
			}
		}
			
		if (texComp->GetText().ToString() == "NormalMap") {
			if (MatObj->GetFName().ToString().Right(2) == "_N") {
				if (MatObj->CompressionSettings.GetValue() != 1) {
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
	if (cou > 0) {
		UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个法线贴图文件"), cou);
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个法线贴图文件"), cou));
	}
	return FReply::Handled();
}
FReply SSlateMain::OnGoMapButtonClicked() {
	//UE_LOG(LogTemp, Warning, TEXT("AssetName:%s"), *MatObj->GetName());
	TArray<FAssetData> AssetDatas;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FARFilter Filter;
	FString pp = texPath->GetText().ToString();
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
	Filter.PackagePaths.Add(*FString::Printf(TEXT("/Game/%s"), *pp));//需要FName類型字符 *FString 前面加星號解引出來使用
	Filter.ClassNames.Add(UTexture::StaticClass()->GetFName());
	if (RPath->IsChecked())
	{	//遞歸搜尋路徑，查找子目錄
		Filter.bRecursivePaths = true;
	}else{
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
		UTexture* MatObj = Cast<UTexture>(StaticLoadObject(UTexture::StaticClass(), nullptr, (TEXT("Texture'%s'"), *AssetData.ObjectPath.ToString())));
		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, FString::FromInt(MatObj->CompressionSettings.GetValue()));
		if (texComp->GetText().ToString() == "Default") {
			MatObj->CompressionSettings = TC_Default;
			//標記未保存星號
			MatObj->AddToRoot();
			MatObj->UpdateResource();
			MatObj->MarkPackageDirty();
			cou += 1;
			UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
		}
		
		if (texComp->GetText().ToString() == "BC7") {
			MatObj->CompressionSettings = TC_BC7;
			//標記未保存星號
			MatObj->AddToRoot();
			MatObj->UpdateResource();
			MatObj->MarkPackageDirty();
			cou += 1;
			UE_LOG(LogTemp, Log, TEXT("%s 【已处理】"), *AssetData.AssetName.ToString());
		}
	}
	if (cou > 0) {
		UE_LOG(LogTemp, Warning, TEXT("共处理 %i 个贴图文件"), cou);
		GEngine->AddOnScreenDebugMessage(-1, 6.f, FColor::Green, FString::Printf(TEXT("共处理 %i 个贴图文件"), cou));
	}
	return FReply::Handled();
}

bool SSlateMain::DiffPathText(FString path)
{
	int con = 0;
	FString aaa = ReadTxt("ST.txt");
	TArray<FString> arr;
	aaa.ParseIntoArray(arr, TEXT("\n"), false);
	for (const FString hist : arr) {
		if (hist == path)
			con += 1;
	}
	if (con == 0) {
		aaa += (path+"\n");
		WriteTxt(aaa, "ST.txt");
		return true;
	}
	else
	{
		return false;
	}
}
void SSlateMain::comp_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	texComp->SetText(FText::FromString(*Item));
}
TSharedRef<class SWidget> SSlateMain::comp_ComboItem(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}
TSharedRef<class SWidget> SSlateMain::GenerateSourceComboItem(TSharedPtr<FString> InItem)
{
	return SNew(STextBlock).Text(FText::FromString(*InItem));
}
void SSlateMain::HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo)
{
	SelectInfo = ESelectInfo::OnKeyPress;
	SaveNewPath();
	texPath->SetText(FText::FromString(*Item));
}
void SSlateMain::SaveNewPath() {
	FString pText = texPath->GetText().ToString();
	if (pText != "") {
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
		if (FPaths::DirectoryExists(*(FPaths::ProjectContentDir() + pText))) {
			if (DiffPathText(pText)) {
				phOpations.Add(MakeShareable(new FString(pText)));//單獨添加路徑
				phComBox->RefreshOptions();//刷新下拉列表
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

void SSlateMain::ReflashHist() {
	FString aaa = ReadTxt("ST.txt");
	UE_LOG(LogTemp, Log, TEXT("%s"), *aaa);
	TArray<FString> arr;
	aaa.ParseIntoArray(arr, TEXT("\n"), false);	//以换行符劈开文本字符
	if (arr.Num() > 0) {
		for (const FString path : arr) {	//批量添加下拉列表
			if (path != "")
				if (FPaths::DirectoryExists(*(FPaths::ProjectContentDir()+path)))
				{
					phOpations.Add(MakeShareable(new FString(path)));
					pppp = path;
				}
		}
	}
}
FString SSlateMain::ReadTxt(FString PN)
{
	FString readString;
	//路徑ProjectPluginsDir() = "../../../PM/Plugins/"
	FFileHelper::LoadFileToString(readString, *(FPaths::ProjectPluginsDir() + "SceneTools_W_P/"+PN));
	return readString;
}

bool SSlateMain::WriteTxt(FString savestring, FString PN)
{
	bool result;
	result = FFileHelper::SaveStringToFile(savestring, *(FPaths::ProjectPluginsDir() + "SceneTools_W_P/"+PN));
	return true;
}
FReply SSlateMain::SaveButtom(){
	SaveNewPath();
	return FReply::Handled();
}


#undef LOCTEXT_NAMESPACE
