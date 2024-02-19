#define MyAppName "TIP"
#define MyAppVersion "8.0"
#define MyAppPublisher "Pavel Remdenok"
#define MyAppURL "https://github.com/pavel-cpp"
#define MyAppExeName "TIP.exe"

[Setup]
AppId={{FEE4A6CD-D4BE-4A0C-A7C7-2E64173A3160}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
;PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=commandline
OutputDir=..\..\installer
OutputBaseFilename=tip_setup
SetupIconFile=..\..\source\resources\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\..\build\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{tmp}\vcredist_x86.exe"; Parameters: "/S"; StatusMsg: "Installing vcredist_x86..."; Flags: waituntilterminated
Filename: "{tmp}\vcredist_x64.exe"; Parameters: "/S"; StatusMsg: "Installing vcredist_x64..."; Flags: waituntilterminated
Filename: "{tmp}\Win64OpenSSL-1_1_1w.exe"; Parameters: "/S"; StatusMsg: "Installing OpenSSL..."; Flags: waituntilterminated
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[Code]
procedure InitializeWizard();
begin
    idpAddFile('https://aka.ms/vs/17/release/vc_redist.x86.exe', ExpandConstant('{tmp}\vcredist_x86.exe'));
    idpAddFile('https://aka.ms/vs/17/release/vc_redist.x64.exe', ExpandConstant('{tmp}\vcredist_x64.exe'));
    idpAddFile('https://slproweb.com/download/Win32OpenSSL-1_1_1w.exe', ExpandConstant('{tmp}\Win64OpenSSL-1_1_1w.exe'));
    idpDownloadAfter(wpReady);
end;
