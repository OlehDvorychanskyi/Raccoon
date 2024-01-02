!define APPNAME "Raccoon"
Name "${APPNAME}"
Outfile "${APPNAME}Setup.exe"

!include "MUI2.nsh"

!define MUI_ABORTWARNING

!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

!define MUI_HEADER_TEXT "Welcome to the ${APPNAME} Installer"
!define MUI_HEADER_SUBTEXT "Follow the steps to complete the installation."
!define MUI_PAGE_HEADER_TEXT "Installing ${APPNAME}"
!define MUI_PAGE_HEADER_SUBTEXT "Please choose the installation directory."

!insertmacro MUI_LANGUAGE English

Section "Install Files"
    SetOutPath $INSTDIR\${APPNAME}
    File "C:\Code\GitHub\Raccoon\build\MinGW_Release\bin\RaccoonEditor.exe"

    SetOutPath "$APPDATA\Raccoon\export\templates"
    File "C:\Code\GitHub\Raccoon\build\Templates\Windows\bin\WindowsRelease.exe"
    
    SetOutPath "$APPDATA\Raccoon"
    File "C:\Users\dos05\AppData\Roaming\Raccoon\editor.ini"

    SetOutPath "$APPDATA\Raccoon\resources"
    File "C:\Code\GitHub\Raccoon\RaccoonEditor\assets\textures\Project.png"
    File "C:\Code\GitHub\Raccoon\Logos\logo.png"

    WriteUninstaller "$INSTDIR\${APPNAME}\Uninstall.exe"
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\RaccoonEditor.exe"
    
    Delete "$APPDATA\Raccoon\export\templates\WindowsRelease.exe"
    ; RMDir /r "$APPDATA\Raccoon\export\templates"
    RMDir /r "$APPDATA\Raccoon\export"

    Delete "$APPDATA\Raccoon\editor.ini"

    Delete "$APPDATA\Raccoon\resources\logo.png"
    Delete "$APPDATA\Raccoon\resources\Project.png"

    RMDir /r "$APPDATA\Raccoon\resources"

    RMDir /r "$APPDATA\Raccoon"

    Delete "$INSTDIR\Uninstall.exe"
    RMDir "$INSTDIR"
SectionEnd
