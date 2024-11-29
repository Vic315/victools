md D:\Mouse
copy /y peza* D:\Mouse
copy /y cakecur*.cur D:\Mouse

reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v Arrow /t REG_EXPAND_SZ /d "D:\Mouse\peza2.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v Crosshair /t REG_EXPAND_SZ /d "D:\Mouse\peza+.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v Hand /t REG_EXPAND_SZ /d "D:\Mouse\cakecur_s.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v IBeam /t REG_EXPAND_SZ /d "D:\Mouse\pezaIB_kuai.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v Help /t REG_SZ /d "D:\Mouse\peza2h.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v AppStarting /t REG_EXPAND_SZ /d "D:\Mouse\peza3.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v Wait /t REG_EXPAND_SZ /d "D:\Mouse\peza3.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v SizeAll /t REG_EXPAND_SZ /d "D:\Mouse\peza_SC.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v SizeNESW /t REG_EXPAND_SZ /d "D:\Mouse\peza_SL.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v SizeNS /t REG_EXPAND_SZ /d "D:\Mouse\peza_SV.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v SizeNWSE /t REG_EXPAND_SZ /d "D:\Mouse\peza_SR.cur" /f
reg add "HKEY_CURRENT_USER\Control Panel\Cursors" /v SizeWE /t REG_EXPAND_SZ /d "D:\Mouse\peza_SH.cur" /f

start control main.cpl
pause