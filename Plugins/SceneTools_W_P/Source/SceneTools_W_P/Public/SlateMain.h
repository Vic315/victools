// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "UMyDatatable.h"
#include "Widgets/Input/SComboBox.h"
#include "Widgets/Input/SSpinBox.h"
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
		FReply OnGoButtonClicked();	//按鈕事件聲明
		FReply OnGoMapButtonClicked();	//按鈕事件聲明
		bool DiffPathText(FString path);	//檢查路徑是否存在
		void comp_ComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		//ComBox 事件聲明
		TSharedRef<class SWidget> comp_ComboItem(TSharedPtr<FString> InItem);
		TSharedRef<class SWidget> GenerateSourceComboItem(TSharedPtr<FString> InItem);
		void HandleSourceComboChanged(TSharedPtr<FString> Item, ESelectInfo::Type SelectInfo);
		void SaveNewPath();
		void ReflashHist();	//刷新路徑記錄
		FString ReadTxt(FString PN);
		bool WriteTxt(FString savestring, FString PN);
		
		FReply SaveButtom();
	public:
		TSharedPtr<class SExpandableArea> Expnv12;
		TSharedPtr<class SEditableTextBox> texPath;
		TSharedPtr<class SEditableTextBox> suffixSeach;
		TSharedPtr<class SEditableTextBox> texComp;//CompressionSettings text
		
	protected:
		TSharedPtr<SSpinBox<int>> randomAngle;//随机数
		TSharedPtr<SSpinBox<int>> arraySpace;//间距
		TSharedPtr<SSpinBox<int>> arrayRow;//每行数目
		TSharedPtr<SSpinBox<int>> arrayRowSp;//每行间距
		TArray<TSharedPtr<FString>> phOpations;//ComBox存放下拉列表成員
		TArray<TSharedPtr<FString>> compOpations;
		TSharedPtr<SComboBox<TSharedPtr<FString>>> phComBox;//路徑記錄下拉列表
		TSharedPtr<SComboBox<TSharedPtr<FString>>> compSettingComBox;
		TSharedPtr<SBox> compComBoxCont;
		TSharedPtr<SBox> phComBoxCont;
		TSharedPtr<class SCheckBox> RPath;//子目錄選項
};
