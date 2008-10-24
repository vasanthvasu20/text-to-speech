; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVaachakaDlg
LastTemplate=CDocument
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Vaachaka.h"

ClassCount=4
Class1=CVaachakaApp
Class2=CVaachakaDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDoc
Resource3=IDD_VAACHAKA_DIALOG
Resource4=IDR_MENU1

[CLS:CVaachakaApp]
Type=0
HeaderFile=Vaachaka.h
ImplementationFile=Vaachaka.cpp
Filter=N

[CLS:CVaachakaDlg]
Type=0
HeaderFile=VaachakaDlg.h
ImplementationFile=VaachakaDlg.cpp
Filter=D
LastObject=ID_FILE_EXIT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=VaachakaDlg.h
ImplementationFile=VaachakaDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VAACHAKA_DIALOG]
Type=1
Class=CVaachakaDlg
ControlCount=4
Control1=IDC_EDIT1,edit,1352728580
Control2=IDC_SPEAK,button,1342242816
Control3=IDC_REPEAT,button,1342242816
Control4=IDCANCEL,button,1342242816

[CLS:CDoc]
Type=0
HeaderFile=Doc.h
ImplementationFile=Doc.cpp
BaseClass=CDocument
Filter=N

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_SPEAK
Command2=ID_FILE_REPEAT
Command3=ID_FILE_EXIT
CommandCount=3

