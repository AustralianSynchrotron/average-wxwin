[Setup]
OutputBaseFilename=Average-setup
Compression=bzip
AppCopyright=ASRP 1995-2006
AppName=Average
AppVerName=Average 2.0.5
InfoAfterFile=C:\Documents and Settings\jrh\My Documents\Program Development\average-wxwin\Packaging\Post-install-readme.txt
LicenseFile=C:\Documents and Settings\jrh\My Documents\Program Development\average-wxwin\Packaging\asrp_copyright_final.rtf
AllowCancelDuringInstall=false
DefaultDirName={pf}\ASRP\Average-2.0
DefaultGroupName=XFIT
ShowLanguageDialog=auto
[Types]
Name: Full; Description: Full installation
Name: DLLs; Description: Update facility files only
[Components]
Name: Main; Description: Essential files; Types: Full
Name: DLLs; Description: Facility data description files; Types: DLLs Full
[Files]
Source: ..\wxpaverage.exe; DestDir: {app}\bin; DestName: Average-2.0.exe; Components: Main
Source: ..\..\unixclibrary-average-wxwin\libaverage14.dll; DestDir: {sys}; Components: Main
Source: ..\..\unixclibrary-average-wxwin\anbf.dll; DestDir: {app}\lib; Components: Main DLLs
Source: ..\..\unixclibrary-average-wxwin\anbf-dxp.dll; DestDir: {app}\lib
Source: Post-install-readme.txt; DestDir: {app}\doc; Flags: isreadme
Source: D:\msys\1.0\mingw\bin\mingwm10.dll; DestDir: {sys}
Source: ..\average.ico; DestDir: {app}\bin
Source: ..\..\unixclibrary-average-wxwin\nw10a.dll; DestDir: {app}\lib; Components: " DLLs Main"
[INI]
Filename: {%USERPROFILE}\XFIT.INI; Section: data modules; Key: module1; String: {app}\lib\anbf.dll; Components: Main DLLs; Flags: uninsdeleteentry
Filename: {%USERPROFILE}\XFIT.INI; Section: data modules; Key: module2; String: {app}\lib\anbf-dxp.dll; Components: Main DLLs; Flags: uninsdeleteentry
Filename: {%USERPROFILE}\XFIT.INI; Section: data modules; Key: module3; String: {app}\lib\nw10a.dll; Components: " DLLs Main"; Flags: uninsdeleteentry
[Icons]
Name: {userprograms}\EXAFS\Average-2.0; Filename: {app}\bin\Average-2.0.exe; WorkingDir: {userdesktop}; Comment: Average for Windows version 2.0; Flags: createonlyiffileexists; Components: Main; IconFilename: {app}\bin\average.ico; IconIndex: 0
