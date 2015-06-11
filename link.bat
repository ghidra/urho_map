@echo OFF
setlocal EnableDelayedExpansion

Echo ***********************************

if NOT "%1"=="" (

  if 1==0 (
    Echo Launch dir: "%~dp0"
    Echo Current dir: "%CD%"
    Echo Passed in dir: "%1"
  )

  SET URHOBUILD=%1

    if exist "!URHOBUILD!" (
      echo begin linking process

      if 1==0 (
        echo valid path "!URHOBUILD!"
      )

      if "%2"=="clean" (
        echo      -clean old links
        call:removeLinkedFolder "CMake" "%~dp0%\CMake"
        call:removeLinkedFolder "CoreData" "%~dp0%\bin\CoreData"
        call:removeLinkedFolder "Data" "%~dp0%\bin\Data"
      )


      echo      -link CoreData and Data folders
      call:makeAlias "CoreData" "!URHOBUILD!\CMake" "%~dp0%\CMake"
      call:makeAlias "CoreData" "!URHOBUILD!\bin\CoreData" "%~dp0%\bin\CoreData"
      call:makeAlias "Data" "!URHOBUILD!\bin\Data" "%~dp0%\bin\Data"

  ) else (
    echo invalid source path given: "!URHOBUILD!"
  )

) else (

  Echo no arguments given, please provide:
  Echo      -urho build path

)

Echo ***********************************

GOTO:EOF

:makeAlias
if exist %~3 (
  echo           -%~1 already exists
) else (
  mklink /J %~3 %~2
)
GOTO:EOF

:removeLinkedFolder
if exist %~2 (
  rmdir %~2
  echo           -%~2 removed
) else (
  echo           -%~1 does not exist
)
GOTO:EOF
