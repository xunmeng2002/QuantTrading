@echo off
call "D:\Program Files\Microsoft Visual Studio\2022\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
if errorlevel 1 exit /b 1
set "PATH=C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja;%PATH%"
if "%1"=="configure" (
  cmake --preset x64-Debug
  exit /b %errorlevel%
)
cmake --build out/build/x64-Debug --target MdbStatic MdOffer SimExchange BackTest -j 4
exit /b %errorlevel%
