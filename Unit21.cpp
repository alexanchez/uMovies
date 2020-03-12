//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit21.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm21 *Form21;
//---------------------------------------------------------------------------
__fastcall TForm21::TForm21(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

int GetTextLength(TWinControl *AControl)
{
  TComboBox *pComboBox = dynamic_cast <TComboBox *> (AControl);
  int Length = 0;
  TCanvas *pCanvas = new TCanvas();
  pCanvas->Handle = GetDC(pComboBox->Handle);
  for(int i = 0; i < pComboBox->Items->Count; i++)
	{
	 AnsiString Text = pComboBox->Items->Strings[i];
	 int TempLength = pCanvas->TextWidth(Text);
	 if(TempLength > Length)
		Length = TempLength;
	}
  delete pCanvas;
  return Length;
}
//---------------------------------------------------------------------------

void __fastcall TForm21::ComboBoxDropDown(TObject *Sender)
{
 TComboBox *current = static_cast <TComboBox *> (Sender);
 SendMessage(current->Handle, CB_SETDROPPEDWIDTH, GetTextLength(current) + 30, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm21::ComboBoxChange(TObject *Sender)
{
  TComboBox* current=static_cast<TComboBox*>(Sender);
  if(current->ItemIndex==0)
  {
   ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(current->Tag)))->Enabled=false;
   ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(current->Tag)))->ItemIndex=0;
  }
  else
  {
   if(Form21->ComboBox7->Items->Count!=0)
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(current->Tag)))->Enabled=true;
   else
     ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(current->Tag)))->Enabled=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm21::FormCreate(TObject *Sender)
{
  for(int i=1;i<=6;i++)
   {
	((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->OnChange=ComboBoxChange;
	((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->OnDropDown=ComboBoxDropDown;
   }
}
//---------------------------------------------------------------------------


void __fastcall TForm21::FormShow(TObject *Sender)
{
  for(int i=1;i<=12;i++)
   {
	if(i<=6)((TImage*)Form21->FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/HotKey.png");
	if(i>=7)((TImage*)Form21->FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Arrow(group).png");
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm21::FormClose(TObject *Sender, TCloseAction &Action)
{
  for(int i=1;i<=12;i++)
	  ((TImage*)Form21->FindComponent("Image"+IntToStr(i)))->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

