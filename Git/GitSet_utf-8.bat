@echo off
::set gitcon=%USERPROFILE%\.gitconfig

git config --global alias.st ^"status^"
git config --global alias.dec ^"log --oneline --decorate --graph^"
git config --global alias.lsf ^"show --name-only --oneline^"
git config --global alias.cus ^"log --pretty=format:^'%%h %%ar ^| %%s ^| %%cn^'^"
git config --global alias.lsff ^"show --stat^"
echo 快捷命令设置完成。可以使用：st、dec:历史、lsf:列出文件、cus

echo.
git config --global core.quotepath false
git config --global gui.encoding utf-8
git config --global i18n.commitencoding utf-8
git config --global i18n.logoutputencoding utf-8
::export LESSCHARSET=utf-8

echo 中文设置完成
pause>nul