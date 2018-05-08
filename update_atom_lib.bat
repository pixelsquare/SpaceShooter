@ECHO OFF
SETLOCAL
PUSHD %~dp0

SET ATOM_SRC_PATH=%~dp0..\atom-engine
SET ATOM_LIB_PATH=%ATOM_SRC_PATH%\proj.win32\Release.win32
SET ATOM_HEADER_PATH=%ATOM_SRC_PATH%\atomengine\core

SET TARGET_SRC_PATH=%CD%\src\atom
SET TARGET_LIB_PATH=%TARGET_SRC_PATH%\lib
SET TARGET_HEADER_PATH=%TARGET_SRC_PATH%\include


ECHO Copying libraries ...

FOR /R %ATOM_LIB_PATH% %%F IN (*.lib *.dll) DO (
	COPY %%F %TARGET_LIB_PATH% > NUL
	ECHO    %%~NXF
)

ECHO.
ECHO Copying header files ...

FOR /R %ATOM_HEADER_PATH% %%F IN (*.h) DO (
	COPY %%F %TARGET_HEADER_PATH% > NUL
	ECHO    %%~NXF
)

ECHO.
ECHO SUCCESS!
ECHO.

PAUSE

POPD
ENDLOCAL