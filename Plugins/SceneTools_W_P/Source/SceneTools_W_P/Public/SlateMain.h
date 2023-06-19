// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "Containers/UnrealString.h"
#include "Engine/Blueprint.h"
#include "Templates/SubclassOf.h"

class SSlateMain :public SCompoundWidget {

	public:
		SLATE_BEGIN_ARGS(SSlateMain) {}
		SLATE_END_ARGS()
		void Construct(const FArguments& InArgs);
		FReply testClicked();
		FReply ParentHelpClicked();
		FReply LoadLODData(FString lodp);
		void maixSave(FPlatformTypes::int32 val);
		void RowNumSave(FPlatformTypes::int32 val);
		void XArray_slide(float val);
		FReply CreateBoxs();
		FReply OutPutActorPos();
		FReply XArray_Clicked();
		FReply YArray_Clicked();
		FReply XoAlignX_Clicked();
		FReply oXAlignX_Clicked();
		FReply oXoAlignX_Clicked();
		FReply YoAlignY_Clicked();
		FReply oYAlignY_Clicked();
		FReply oYoAlignY_Clicked();
		FReply ZoAlignZ_Clicked();
		FReply oZAlignZ_Clicked();
		FReply oZoAlignZ_Clicked();
		FReply cAlignX_Clicked();
		FReply cAlignNX_Clicked();
		FReply cAlignY_Clicked();
		FReply cAlignNY_Clicked();
		FReply cAlignZ_Clicked();
		FReply cAlignNZ_Clicked();
		FReply AlignPosClicked();
		FReply AlignRotClicked();
		FReply AlignSclClicked();
		FReply SeachAdjustmentTexture(); //搜索Adjustment修改过的贴图
		FReply SetTextureMax(); //设置贴图尺寸
		FReply ResetTextureLODBias(); //重置LOD Bias
		FReply GetLODsets_Sel();
		FReply largePropLODsets_Sel();
		FReply removeM_Sel();
		FReply largePropLODsets();
		FReply listLODdetails();
		FString RemoveTrailingZeros(float value);
		FReply miniLODset_removeM();
		FReply LODset();
		FReply OnGoButtonClicked();	//按鈕事件聲明
		FReply SetUITextureClicked();
		FReply OnGoMapButtonClicked();	//按鈕事件聲明
		bool DiffPathText(FString path);	//檢查路徑是否存在
		void OnPathText(const FText& Text);
		void LodDataGetVal(FString LODtt);
		FReply Createlodset();
		FReply LodlodsetVal();
		void LodDataOnPathText(const FText& Text);
		void OnSubfixText(const FText& Text);
		void SearchSizeValueSet(FPlatformTypes::int32 val);
		void btn360(FPlatformTypes::int32 val);
		void SetSizeValue(FPlatformTypes::int32 val); //设置尺寸值次方计算，val是传入的本控件整数值
		void ptValue_0(FPlatformTypes::int32 val);
		void ptValue_1(FPlatformTypes::int32 val);
		void ptValue_2(FPlatformTypes::int32 val);
		void ptValue_3(FPlatformTypes::int32 val);
		void ssValue_0(float val);
		void ssValue_1(float val);
		void ssValue_2(float val);
		void ssValue_3(float val);
		void comp_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void LOD_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void LODData_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void comp_equalText(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		//ComBox 事件聲明
		TSharedRef<class SWidget> comp_ComboItem(TSharedPtr<FString> InItem);
		void HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void SaveNewPath();
		void ReflashHist();	//刷新路徑記錄
		FString ReadTxt(FString PN);
		bool WriteTxt(FString savestring, FString SavePath);
		FReply  LoadLODDataUI();
		FReply SaveButtom();
		void OnSelTextChanged(const FText& Text);
		FReply AddPerfix();
		FReply SelectFromText();
		// FReply TTTButtom();
		FReply CloneActor();
		FReply SelSameObj();

		// TSharedPtr<SBox> MyBox;
		// TSharedPtr<class SWindow> MyWin;
		TSharedPtr<class SEditableTextBox> selText;
		TSharedPtr<class SExpandableArea> Expnv12;
		TSharedPtr<class SExpandableArea> Expnv1;
		TSharedPtr<class SEditableTextBox> texPath;
		TSharedPtr<class SEditableTextBox> loddataPath;
		TSharedPtr<class SEditableTextBox> suffixSeach;
		TSharedPtr<class SEditableTextBox> equalText;
		TSharedPtr<class STextBlock> DisplayLODTri;
		TSharedPtr<class SEditableTextBox> texComp;//CompressionSettings text
		TSharedPtr<class SEditableTextBox> LODGroupTxt;//LOD组列表
		TSharedPtr<class SEditableTextBox> LODDataTxt;//LODData
		TSharedPtr<class STextBlock> LDcount;//LODDataCount
		
	protected:
		TSharedPtr<class SEditableTextBox> SizeValue;//贴图大小次方计算
		TSharedPtr<SSpinBox<int>> searchSize;//重置贴图大小查找尺寸
		TSharedPtr<SSpinBox<int>> randomAngle;//随机数
		TSharedPtr<SSpinBox<float>> arraySpace;//间距
		TSharedPtr<SSpinBox<int>> arrayRow;//每行数目
		TSharedPtr<SSpinBox<float>> arrayRowSp;//每行间距
		TSharedPtr<SSpinBox<int>> matrixNum;//矩阵数
		TSharedPtr<SSpinBox<int>> spn360;
		TSharedPtr<SSpinBox<int>> PT_0;
		TSharedPtr<SSpinBox<int>> PT_1;
		TSharedPtr<SSpinBox<int>> PT_2;
		TSharedPtr<SSpinBox<int>> PT_3;
		TSharedPtr<SSpinBox<float>> SS_0;
		TSharedPtr<SSpinBox<float>> SS_1;
		TSharedPtr<SSpinBox<float>> SS_2;
		TSharedPtr<SSpinBox<float>> SS_3;
		TSharedPtr<SButton> getLodBtn;
		TArray<TSharedPtr<FString>> equalSel;//贴图大小查找条件选项
		TArray<TSharedPtr<FString>> compOpations;//ComBox存放下拉列表成員
		TArray<TSharedPtr<FString>> LODGrpOpations;//LOD组存放下拉列表成員
		TArray<TSharedPtr<FString>> LODDataOpations;//LODData列表
		TSharedPtr<SComboBox<TSharedPtr<FString>>> LODdataComb; //调用->RefreshOptions()可用于刷新列表
		TSharedPtr<SBox> phComBoxCont;
		TArray<TSharedPtr<FString>> phOpations;
		TSharedPtr<SComboBox<TSharedPtr<FString>>> phComBox;//路徑記錄下拉列表,调用->RefreshOptions()可用于刷新列表
		TSharedPtr<class SCheckBox> RPath;//子目錄選項
		TSharedPtr<class SCheckBox> autoCompute;//Auto Compute LOD Distances
		TSharedPtr<class SCheckBox> openTxt;//打开处理文件记录文本
		TSharedPtr<class SCheckBox> useLODData;//载入LOD预设选项
	private:
	//注意:指定bp_Box文件必须存在,否则会出错*(FPaths::ProjectPluginsDir() + "
		// UBlueprint* bp_Matrix = Cast<UBlueprint>(StaticLoadObject(UObject::StaticClass(), nullptr, TEXT("Blueprint'/Game/Developers/Vic/STcontent/bp_Box.bp_Box'")));
		// TSubclassOf<class UObject> bpZMaitrexClass = (bp_Matrix)->GeneratedClass;

};
