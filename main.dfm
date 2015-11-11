object FormMetrick: TFormMetrick
  Left = 199
  Top = 171
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1052#1057#1080#1057#1074#1048#1085#1092#1058' '#1051#1072#1073'. '#1056#1072#1073'. 1 - '#1041#1077#1075#1091#1085' '#1040#1083#1077#1082#1089#1072#1085#1076#1088' '#1075#1088'.451001'
  ClientHeight = 776
  ClientWidth = 913
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonOpenFile: TButton
    Left = 768
    Top = 24
    Width = 137
    Height = 81
    Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
    TabOrder = 0
    OnClick = ButtonOpenFileClick
  end
  object GroupBoxInputText: TGroupBox
    Left = 8
    Top = 8
    Width = 745
    Height = 321
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1090#1077#1082#1089#1090' '#1076#1083#1103' '#1072#1085#1072#1083#1080#1079#1072' :'
    TabOrder = 4
    object MemoInputText: TMemo
      Left = 16
      Top = 16
      Width = 713
      Height = 297
      ScrollBars = ssVertical
      TabOrder = 0
      WantTabs = True
      OnChange = MemoInputTextChange
    end
  end
  object GroupBoxResult: TGroupBox
    Left = 8
    Top = 336
    Width = 745
    Height = 433
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1072#1085#1072#1083#1080#1079#1072' :'
    TabOrder = 5
    object LabelMetric: TLabel
      Left = 24
      Top = 19
      Width = 159
      Height = 13
      Caption = #1044#1072#1085#1085#1099#1077' '#1087#1086' '#1084#1077#1090#1088#1080#1082#1077' '#1061#1086#1083#1089#1090#1077#1076#1072' :'
    end
    object LabelOperators: TLabel
      Left = 504
      Top = 43
      Width = 165
      Height = 13
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1085#1080#1082#1072#1083#1100#1085#1099#1093' '#1086#1087#1077#1088#1072#1090#1086#1088#1086#1074':'
    end
    object LabelOperands: TLabel
      Left = 504
      Top = 259
      Width = 183
      Height = 13
      Caption = #1057#1087#1080#1089#1086#1082' '#1091#1085#1080#1082#1072#1083#1100#1085#1099#1093' '#1086#1087#1077#1088#1072#1090#1086#1088#1072#1085#1076#1086#1074':'
    end
    object StringGridMetrick: TStringGrid
      Left = 8
      Top = 40
      Width = 465
      Height = 379
      ColCount = 3
      DefaultColWidth = 118
      FixedCols = 2
      RowCount = 15
      ScrollBars = ssNone
      TabOrder = 0
      RowHeights = (
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24
        24)
    end
    object StringGridOperators: TStringGrid
      Left = 488
      Top = 64
      Width = 243
      Height = 120
      ColCount = 2
      DefaultColWidth = 110
      FixedCols = 0
      RowCount = 2
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object StringGridOperands: TStringGrid
      Left = 488
      Top = 280
      Width = 243
      Height = 120
      ColCount = 2
      DefaultColWidth = 110
      FixedCols = 0
      RowCount = 2
      ScrollBars = ssVertical
      TabOrder = 2
    end
  end
  object ButtonClearAll: TButton
    Left = 768
    Top = 672
    Width = 137
    Height = 81
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1074#1089#1105
    TabOrder = 3
    OnClick = ButtonClearAllClick
  end
  object ButtonExecut: TButton
    Left = 768
    Top = 384
    Width = 137
    Height = 81
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 2
    WordWrap = True
    OnClick = ButtonExecutClick
  end
  object ButtonSaveInputText: TButton
    Left = 768
    Top = 120
    Width = 137
    Height = 81
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1080#1089#1093#1086#1076#1085#1099#1081' '#1090#1077#1082#1089#1090
    TabOrder = 1
    WordWrap = True
    OnClick = ButtonSaveInputTextClick
  end
  object OpenDialog: TOpenDialog
    DefaultExt = 'GetCurrentDir'
    Filter = 
      'Text file|*.txt|Word file|*.doc|Word file (2013)|*.docx|C cod|*.' +
      'c'
    Left = 784
    Top = 232
  end
  object SaveDialog: TSaveDialog
    DefaultExt = 'GetCurrentDir'
    Filter = 'Text file|*.txt|Word file|*.doc|Word file (2013)|*.docx'
    Left = 816
    Top = 232
  end
  object XPManifest: TXPManifest
    Left = 848
    Top = 232
  end
  object VistaAltFix1: TVistaAltFix
    Left = 784
    Top = 264
  end
end
