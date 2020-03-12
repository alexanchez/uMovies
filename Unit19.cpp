//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit19.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm19 *Form19;
//---------------------------------------------------------------------------
__fastcall TForm19::TForm19(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm19::CharClick(TObject *Sender)
{
  TButton* current=static_cast<TButton*>(Sender);
  Char=current->Caption;
}
//---------------------------------------------------------------------------

void __fastcall TForm19::FormCreate(TObject *Sender)
{
   for(int i=1;i<=59;i++)
	 {((TButton*)FindComponent("Button"+IntToStr(i)))->OnClick=CharClick;
	  ((TButton*)FindComponent("Button"+IntToStr(i)))->Cursor=(TCursor)1;}

}
//---------------------------------------------------------------------------
void __fastcall TForm19::FormActivate(TObject *Sender)
{
  Form19->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm19::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==char(27))Close();
}
//---------------------------------------------------------------------------
