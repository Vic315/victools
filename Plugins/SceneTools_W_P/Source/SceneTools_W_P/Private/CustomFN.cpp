#include "CustomFN.h"
#include "Misc/FileHelper.h"

void CustomFN::ReadIniValue(FString Section, FString inKey, FString& outValue, FString IniFile)
{
	if (!GConfig)
		return;
	GConfig->GetString(*Section, *inKey, outValue, IniFile);
}
bool CustomFN::WriteIni(FString newSection, FString newKey, FString newValue, FString IniFile)
{
	if(!GConfig)
		return false;
	GConfig->SetString(*newSection, *newKey, *newValue, IniFile);
	GConfig->Flush(true);	//即时刷新写入文件
	return true;
}
