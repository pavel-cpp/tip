;     "Text Insertion Program (TIP)" is a software
;     for client management and generating unique images for each client.
;     Copyright (C) 2024  Pavel Remdenok
;
;     This program is free software: you can redistribute it and/or modify
;     it under the terms of the GNU General Public License as published by
;     the Free Software Foundation, either version 3 of the License, or
;     (at your option) any later version.
;
;     This program is distributed in the hope that it will be useful,
;     but WITHOUT ANY WARRANTY; without even the implied warranty of
;     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;     GNU General Public License for more details.
;
;     You should have received a copy of the GNU General Public License
;     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#define MyAppName "TIP"
#define MyAppVersion "8.1"
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
OutputBaseFilename=tip_setup_offline
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
; Filename: "{tmp}\vcredist_x86.exe"; Parameters: "/S"; StatusMsg: "Installing vcredist_x86..."; Flags: waituntilterminated
; Filename: "{tmp}\vcredist_x64.exe"; Parameters: "/S"; StatusMsg: "Installing vcredist_x64..."; Flags: waituntilterminated
; Filename: "{tmp}\Win64OpenSSL-1_1_1w.exe"; Parameters: "/S"; StatusMsg: "Installing OpenSSL..."; Flags: waituntilterminated
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

; [Code]
; procedure InitializeWizard();
; begin
;     idpAddFile('https://aka.ms/vs/17/release/vc_redist.x86.exe', ExpandConstant('{tmp}\vcredist_x86.exe'));
;     idpAddFile('https://aka.ms/vs/17/release/vc_redist.x64.exe', ExpandConstant('{tmp}\vcredist_x64.exe'));
;     idpAddFile('https://slproweb.com/download/Win64OpenSSL-1_1_1w.exe', ExpandConstant('{tmp}\Win64OpenSSL-1_1_1w.exe'));
;     idpDownloadAfter(wpReady);
; end;
