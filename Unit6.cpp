//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit6.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm6 *Form6;
//---------------------------------------------------------------------------
__fastcall TForm6::TForm6(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormCreate(TObject *Sender)
{
  for(int i=1;i<=5;i++)
	 {((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseEnter=ImageMouseEnter;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseLeave=ImageMouseLeave;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnClick=ImageClick;}
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormShow(TObject *Sender)
{
  const char *smile[5] = { "happy","action","cry","horror","thoughtful"};
  for (int i=1;i<=5;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile("+AnsiString(smile[i-1])+").png");
  Image6->Picture->LoadFromFile("Soft/Backgrounds/Background 9.jpg");
  Form6->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm6::FormClose(TObject *Sender, TCloseAction &Action)
{
  for(int i=1;i<=6;i++)
	((TImage*)Form6->FindComponent("Image"+IntToStr(i)))->Picture->Assign(NULL);
}
//-------------------------------Определение выбранного настроения---------------

void __fastcall TForm6::ImageClick(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:Form6->Tag=1;Close();break;
   case 2:Form6->Tag=2;Close();break;
   case 3:Form6->Tag=3;Close();break;
   case 4:Form6->Tag=4;Close();break;
   case 5:Form6->Tag=5;Close();break;
  }
}
//-------------------------События MouseEnter - MouseLeave для картинок-----------

void __fastcall TForm6::ImageMouseEnter(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(happy_light).png");break;
   case 2:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(action_light).png");break;
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(cry_light).png");break;
   case 4:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(horror_light).png");break;
   case 5:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(thoughtful_light).png");break;
  }
}
void __fastcall TForm6::ImageMouseLeave(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(happy).png");break;
   case 2:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(action).png");break;
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(cry).png");break;
   case 4:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(horror).png");break;
   case 5:current->Picture->LoadFromFile("Soft/Buttons/Smiles/Smile(thoughtful).png");break;
  }
}
//---------------------------------------------------------------------------
