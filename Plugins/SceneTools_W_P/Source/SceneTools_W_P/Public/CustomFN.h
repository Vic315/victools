#pragma once

class CustomFN
{
public:
	void ReadIniValue(FString Section, FString inKey, FString& outValue, FString IniFile);
	bool WriteIni(FString newSection, FString newKey, FString newValue, FString IniFile);
};
