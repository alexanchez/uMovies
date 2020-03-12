object Form15: TForm15
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = #1058#1077#1082#1091#1097#1072#1103' '#1089#1077#1088#1080#1103
  ClientHeight = 87
  ClientWidth = 221
  Color = clBlack
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 6
    Width = 158
    Height = 19
    Caption = #1054#1078#1080#1076#1072#1077#1090#1089#1103' '#1089#1077#1088#1080#1103'/'#1089#1077#1079#1086#1085
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindow
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    OnClick = Label1Click
  end
  object CheckBox1: TCheckBox
    Left = 9
    Top = 7
    Width = 16
    Height = 17
    TabOrder = 4
    OnClick = CheckBox1Click
  end
  object ComboBox1: TComboBox
    Tag = 1
    Left = 8
    Top = 27
    Width = 102
    Height = 25
    Style = csOwnerDrawFixed
    Color = 16250871
    Ctl3D = True
    DoubleBuffered = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 19
    ParentCtl3D = False
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 0
    OnChange = ComboBox1Change
    OnCloseUp = ComboBox1CloseUp
  end
  object Button1: TButton
    Left = 8
    Top = 56
    Width = 102
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = []
    ModalResult = 1
    ParentFont = False
    TabOrder = 1
  end
  object Button2: TButton
    Left = 112
    Top = 56
    Width = 102
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = []
    ModalResult = 2
    ParentFont = False
    TabOrder = 2
  end
  object ComboBox2: TComboBox
    Tag = 1
    Left = 112
    Top = 27
    Width = 102
    Height = 25
    Style = csOwnerDrawFixed
    Ctl3D = True
    DoubleBuffered = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 19
    ParentCtl3D = False
    ParentDoubleBuffered = False
    ParentFont = False
    TabOrder = 3
    OnChange = ComboBox2Change
    OnCloseUp = ComboBox2CloseUp
  end
end
