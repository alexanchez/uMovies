object Form11: TForm11
  Left = 0
  Top = 0
  BorderIcons = [biMinimize, biMaximize]
  BorderStyle = bsDialog
  Caption = #1042#1099#1087#1086#1083#1085#1103#1077#1090#1089#1103' '#1089#1086#1093#1088#1072#1085#1077#1085#1080#1077'...'
  ClientHeight = 25
  ClientWidth = 201
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 0
    Width = 201
    Height = 25
    TabOrder = 0
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 600
    OnTimer = Timer1Timer
    Left = 224
  end
  object ZipForge1: TZipForge
    ExtractCorruptedFiles = False
    CompressionLevel = clNone
    CompressionMode = 0
    CurrentVersion = '6.70 '
    SpanningMode = smNone
    SpanningOptions.AdvancedNaming = False
    SpanningOptions.VolumeSize = vsAutoDetect
    Options.FlushBuffers = True
    Options.OEMFileNames = True
    InMemory = False
    Zip64Mode = zmDisabled
    UnicodeFilenames = True
    EncryptionMethod = caPkzipClassic
    Left = 256
  end
end
