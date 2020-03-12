//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit15.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm15 *Form15;
//---------------------------------------------------------------------------
__fastcall TForm15::TForm15(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TForm15::FormActivate(TObject *Sender)
{
  Button1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm15::FormCreate(TObject *Sender)
{
  SerialSeasons=new TStringList();
}
//---------------------------------------------------------------------------

void __fastcall TForm15::FormDestroy(TObject *Sender)
{
  delete SerialSeasons;SerialSeasons=NULL;
}
//---------------------------------------------------------------------------
/*
ItemHeight 16, Tahoma 10, 100x22
*/
void __fastcall TForm15::ComboBox1Change(TObject *Sender)
{
   ComboBox2->Items->Clear();
   for(int i=1;i<=StrToInt(SerialSeasons->Strings[ComboBox1->ItemIndex]);i++)
	 ComboBox2->Items->Add(ComboBox2->Hint+IntToStr(i));
   ComboBox2->ItemIndex=0;
   Button1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm15::ComboBox2Change(TObject *Sender)
{
   Button1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm15::ComboBox1CloseUp(TObject *Sender)
{
   Button1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm15::ComboBox2CloseUp(TObject *Sender)
{
   Button1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm15::CheckBox1Click(TObject *Sender)
{
  if(CheckBox1->Checked)
   {ComboBox1->Enabled=false;ComboBox2->Enabled=false;ComboBox1->Color=(TColor)RGB(245,245,245);ComboBox2->Color=(TColor)RGB(245,245,245);}
  else
   {ComboBox1->Enabled=true;ComboBox2->Enabled=true;ComboBox1->Color=clWindow;ComboBox2->Color=clWindow;}
}
//---------------------------------------------------------------------------

void __fastcall TForm15::Label1Click(TObject *Sender)
{
  if(CheckBox1->Checked)CheckBox1->Checked=false;
  else CheckBox1->Checked=true;
}
//---------------------------------------------------------------------------


