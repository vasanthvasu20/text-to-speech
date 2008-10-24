; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVakDlg
LastTemplate=CDocument
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Vak.h"
ODLFile=Vak.odl

ClassCount=5
Class1=CVakApp
Class2=CVakDlg
Class3=CAboutDlg
Class4=CVakDlgAutoProxy

ResourceCount=7
Resource1=IDD_VAK_DIALOG (English (U.S.))
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_ABOUTBOX (English (U.S.))
Class5=CDoc
Resource5=IDD_VAK_DIALOG
Resource6=IDR_MENU1
Resource7=IDR_ACCELERATOR1

[CLS:CVakApp]
Type=0
HeaderFile=Vak.h
ImplementationFile=Vak.cpp
Filter=N
LastObject=CVakApp

[CLS:CVakDlg]
Type=0
HeaderFile=VakDlg.h
ImplementationFile=VakDlg.cpp
Filter=D
LastObject=ID_FILE_SPEAKFILE
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=VakDlg.h
ImplementationFile=VakDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_BUTTON1,button,1342242816

[CLS:CVakDlgAutoProxy]
Type=0
HeaderFile=DlgProxy.h
ImplementationFile=DlgProxy.cpp
BaseClass=CCmdTarget
Filter=N

[DLG:IDD_VAK_DIALOG]
Type=1
Class=CVakDlg
ControlCount=6
Control1=IDC_DATA,edit,1352732676
Control2=IDC_SPEAK,button,1342242816
Control3=IDC_OPTIONS2,button,1342242816
Control4=IDC_OPTIONS,button,1342242816
Control5=IDC_UPDATEDATA,edit,1352734724
Control6=IDB_BITMAP1,static,1342179854

[DLG:IDD_VAK_DIALOG (English (U.S.))]
Type=1
Class=CVakDlg
ControlCount=6
Control1=IDC_DATA,edit,1352732676
Control2=IDC_SPEAK,button,1342242816
Control3=IDC_OPTIONS2,button,1342242816
Control4=IDC_OPTIONS,button,1342242816
Control5=IDC_STATIC,static,1476466958
Control6=IDC_UPDATEDATA,edit,1352734724

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_BUTTON1,button,1342242816

[CLS:CDoc]
Type=0
HeaderFile=Doc.h
ImplementationFile=Doc.cpp
BaseClass=CDocument
Filter=N
LastObject=CDoc
VirtualFilter=DC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_SPEAK
Command2=ID_FILE_REPEAT
Command3=ID_FILE_SPEAKFILE
Command4=ID_FILE_SAVEFILE
Command5=ID_FILE_SAVETEXT
Command6=ID_FILE_EXIT
CommandCount=6

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=ID_FILE_SPEAK
Command2=ID_FILE_SPEAKFILE
Command3=ID_FILE_REPEAT
Command4=ID_FILE_EXIT
Command5=ID_FILE_SAVEFILE
CommandCount=5

