// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "UMyDatatable.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Layout/SExpandableArea.h"

class SSlateMain :public SCompoundWidget {
	
	public:
		SLATE_BEGIN_ARGS(SSlateMain) {}
		SLATE_END_ARGS()
		void Construct(const FArguments& InArgs);
		FReply testClicked();
		FReply SaveRedo();
		FReply ParentHelpClicked();
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
		FReply OnGoButtonClicked();	//按鈕事件聲明
		FReply OnGoMapButtonClicked();	//按鈕事件聲明
		bool DiffPathText(FString path);	//檢查路徑是否存在
		void OnPathText(const FText& Text);
		void OnSubfixText(const FText& Text);
		void SearchSizeValueSet(FPlatformTypes::int32 val);
		void SetSizeValue(FPlatformTypes::int32 val); //设置尺寸值次方计算，val是传入的本控件整数值
		void comp_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void comp_equalText(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		//ComBox 事件聲明
		TSharedRef<class SWidget> comp_ComboItem(TSharedPtr<FString> InItem);
		void HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void SaveNewPath();
		void ReflashHist();	//刷新路徑記錄
		FString ReadTxt(FString PN);
		bool WriteTxt(FString savestring, FString PN);
		FReply SaveButtom();
		FReply TTTButtom();
	public:
		TSharedPtr<class SExpandableArea> Expnv12;
		TSharedPtr<class SExpandableArea> Expnv1;
		TSharedPtr<class SEditableTextBox> texPath;
		TSharedPtr<class SEditableTextBox> suffixSeach;
		TSharedPtr<class SEditableTextBox> equalText;
		TSharedPtr<class SEditableTextBox> texComp;//CompressionSettings text
		
	protected:
		TSharedPtr<class SEditableTextBox> SizeValue;//贴图大小次方计算
		TSharedPtr<SSpinBox<int>> searchSize;//重置贴图大小查找尺寸
		TSharedPtr<SSpinBox<int>> randomAngle;//随机数
		TSharedPtr<SSpinBox<int>> arraySpace;//间距
		TSharedPtr<SSpinBox<int>> arrayRow;//每行数目
		TSharedPtr<SSpinBox<int>> arrayRowSp;//每行间距
		TArray<TSharedPtr<FString>> equalSel;//贴图大小查找条件选项
		TArray<TSharedPtr<FString>> compOpations;//ComBox存放下拉列表成員
		TSharedPtr<SBox> phComBoxCont;
		TArray<TSharedPtr<FString>> phOpations;
		TSharedPtr<SComboBox<TSharedPtr<FString>>> phComBox;//路徑記錄下拉列表,调用->RefreshOptions()可用于刷新列表
		TSharedPtr<class SCheckBox> RPath;//子目錄選項
};
