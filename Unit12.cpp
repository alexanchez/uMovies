//---------------------------------------------------------------------------

#include <vcl.h>
#include <time.h>
#pragma hdrstop

#include "Unit12.h"
#include "Registry.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm12 *Form12;
AnsiString key,code,key_temp;char tmp;
//---------------------------------------------------------------------------
__fastcall TForm12::TForm12(TComponent* Owner)
	: TForm(Owner)
{
   srand(time(NULL));
}
//---------------------------------------------------------------------------

void __fastcall TForm12::Button1Click(TObject *Sender)
{
  AnsiString userkey=Edit2->Text;
  if(key_temp==userkey)
   {
	MessageBeep(MB_ICONASTERISK);
	ShowMessage(key_correct);//"Congratulations! You have successfully registered."
	TRegistry *reg=new TRegistry();
	reg->RootKey=HKEY_CLASSES_ROOT;
	reg->OpenKey("\System.IndexOfOperation\\CLSD",true);
	reg->WriteString("","{6CA9671B-2DC3-5BF8-567A-5E6D15CSB16E}");
	reg->CloseKey();
	delete reg;
	Form12->Tag=1;
	Close();
   }
  else
   {MessageBeep(MB_ICONEXCLAMATION);ShowMessage(key_incorrect);}//"The key is incorrect. Program not registered!"
}
//---------------------------------------------------------------------------


void __fastcall TForm12::FormShow(TObject *Sender)
{
   Image1->Picture->LoadFromFile("Soft/Buttons/License_Activation.png");
   Edit1->Text="";Edit2->Text="";key="";
   for(int i=0;i<6;i++)
	   key+=char(rand()%150-150);
   code=key;
   char *temp1=code.c_str();key_temp=temp1;
   code.c_str()[0]-=20;code.c_str()[1]+=10;code.c_str()[2]-=31;code.c_str()[3]+=4;code.c_str()[4]-=11;code.c_str()[5]+=23;
   tmp=code.c_str()[1];
   code.c_str()[1]=code.c_str()[3];
   code.c_str()[3]=tmp;
   tmp=code.c_str()[2];
   code.c_str()[2]=code.c_str()[5];
   code.c_str()[5]=tmp;

   code.c_str()[0]=code.c_str()[0]+code.c_str()[4];
   code.c_str()[2]=code.c_str()[2]-code.c_str()[5];
   code.c_str()[3]=code.c_str()[3]+code.c_str()[1];
   code.c_str()[4]=code.c_str()[4]-code.c_str()[5];
   Edit1->Text=code;
}
//---------------------------------------------------------------------------


void __fastcall TForm12::FormClose(TObject *Sender, TCloseAction &Action)
{
  Image1->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

