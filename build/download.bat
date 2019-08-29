@echo off

cd %~dp0%/..

mkdir include
call :dircls "include"
set src=D:/Depends/__CSC__
for /f "tokens=*" %%i in ('dir /b "%src%"') do (
	mklink /H "include/%%i" "%src%/%%i")

cls
exit

rem ######################################################## rem

goto :EOF
:dircls
set rax=%1
set rax=%rax:~1,-1%
for /f "delims=" %%i in ('dir /a-d /w /b "%rax%"') do (
	call :delf "%rax%\%%i")
for /f "delims=" %%i in ('dir /a /w /b "%rax%"') do (
	call :deld "%rax%\%%i")
goto :EOF

goto :EOF
:delf
rem takeown /f "%~1" /a
rem icacls "%~1" /grant administrators:F
rem attrib "%~1" -S -H
del /f /s /q "%~1"
goto :EOF

goto :EOF
:deld
call :dircls "%~1"
rem takeown /f "%~1" /a /r /d Y
rem icacls "%~1" /grant administrators:F
rem attrib "%~1" -S -H
rd /s /q "%~1"
goto :EOF