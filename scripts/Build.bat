@echo off
setlocal

set EnginePath=H:\Github\UnrealEngine
set BuildToolPath=%EnginePath%\Engine\Build\BatchFiles\RunUAT.bat
set ProjectName=FlameControl
set ProjectPath=%cd%/..
set UProjectPath=%ProjectPath%\%ProjectName%.uproject
set Platform=Win64
set Configuration=Shipping

set FullCommand=%BuildToolPath% BuildCookRun -project=%UProjectPath% -platform=%Platform% -configuration=%Configuration%

call %FullCommand% -build

set SourceFile=%EnginePath%\Engine\Binaries\%Platform%\%ProjectName%-%Platform%-%Configuration%.target
set DestinationFile=%ProjectPath%\Binaries\%Platform%\%ProjectName%.target

move "%SourceFile%" "%DestinationFile%"
python ModifyTarget.py "%DestinationFile%" "%UProjectPath%"

call %FullCommand% -stage -package

endlocal