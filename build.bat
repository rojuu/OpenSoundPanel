@echo off
SETLOCAL
set TARGET=x64

set CommonCompilerFlags=/Zi /Od /EHsc /nologo /FC 

set CommonLinkerFlags=/DEBUG user32.lib

if not exist bin (
    mkdir bin
)
pushd bin
cl %CommonCompilerFlags% ..\src\main.cpp /link /subsystem:console %CommonLinkerFlags% /out:OpenSoundPanel.exe
popd
echo Done