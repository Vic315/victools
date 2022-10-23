@echo off
if not exist "%windir%\Fonts\consola.ttf" copy /y consola.ttf "%windir%\Fonts"
REM if not exist "%windir%\Fonts\MONACO.TTF" copy /y MONACO.TTF "%windir%\Fonts"
if not exist "%windir%\Fonts\MONACO.TTF" (
	start MONACO.TTF
	echo 在打开的字体预览窗左上方点击 安装 按钮
)
echo.
set mintty=%USERPROFILE%\.minttyrc

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Font=Monaco set /a num=num+1
)
if %num%==0 (
	echo Font=Monaco>%mintty%
)
set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==FontHeight=12 set /a num=num+1
)
if %num%==0 echo FontHeight=12>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Columns=120 set /a num=num+1
)
if %num%==0 echo Columns=120>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Rows=36 set /a num=num+1
)
if %num%==0 echo Rows=36>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Locale=zh_CN set /a num=num+1
)
if %num%==0 echo Locale=zh_CN>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Charset=UTF-8 set /a num=num+1
)
if %num%==0 echo Charset=UTF-8>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==BackgroundColour=0^,36^,36 set /a num=num+1
)
if %num%==0 echo BackgroundColour=0^,36^,36>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Transparency=40 set /a num=num+1
)
if %num%==0 echo Transparency=40>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==Scrollbar=left set /a num=num+1
)
if %num%==0 echo Scrollbar=left>>%mintty%

set /a num=0
for /f %%i in (%mintty%) do (
    if %%i==ThemeFile=rosipov set /a num=num+1
)
if %num%==0 echo ThemeFile=rosipov>>%mintty%


@echo 设置完成，按任意键退出。

pause>nul