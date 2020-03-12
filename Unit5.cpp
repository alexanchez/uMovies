//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
#include "Unit12.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::Label1Click(TObject *Sender)
{
 AnsiString _url="https://vk.com/id48556641";
 ShellExecute (HWND(AboutBox), "open", _url.c_str(), NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Label1MouseEnter(TObject *Sender)
{
  Label1->Font->Color=clBlue;
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::Label1MouseLeave(TObject *Sender)
{
  Label1->Font->Color=clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::FormShow(TObject *Sender)
{
  const char *pictures[5] = {"Background 10","Background 7.2","Background 10","Background 7.2","Background 9"};
  for (int i=1;i<=5;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Backgrounds/"+AnsiString(pictures[i-1])+".jpg");
  Image6->Picture->LoadFromFile("Soft/Buttons/License_Activated.png");
  ProgramIcon->Picture->LoadFromFile("Soft/Buttons/ProgramIcon.png");

  if(AboutBox->Tag==0)//Лицензия есть, триал выкл
  {
	  Topic->Caption=lang->Strings[0];                      //"Лицензия успешно активирована"
	  LicenseInfo->Caption=lang->Strings[1];                //"Спасибо за покупку лицензии µMovies!"
	  License->Visible=false;TrialVersion->Visible=false;Image6->Visible=true;
  }
  if(AboutBox->Tag==1)//лицензия-, триал выкл)
  {
	  Topic->Caption=lang->Strings[5];                      //"Активация пробной версии программы"
	  LicenseInfo->Caption=lang->Strings[3];
	  //lang->Strings[3]-"Активация пробной версии программы позволит вам использовать uMovies в течение ознакомительного периода (24 часа)."
  }
  if(AboutBox->Tag==2)//лицензия-, триал вкл
  {
	  Topic->Caption=lang->Strings[2];                      //"Активация пробной версии программы"
	  //LicenseInfo->Caption - определяется перед открытием;
	  TrialVersion->Enabled=false;
  }
  if(AboutBox->Tag==3)//лицензия-, триал выкл
  {
	  Topic->Caption=lang->Strings[4];                      //"Активация лицензии программы"
	  LicenseInfo->Caption=lang->Strings[6];                //"Ваш ознакомительный период завершён. Активируйте лицензию!"
	  TrialVersion->Enabled=false;
  }
}
//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormClose(TObject *Sender, TCloseAction &Action)
{
  ProgramIcon->Picture->Assign(NULL);
  for(int i=1;i<=6;i++)
  ((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------


void __fastcall TAboutBox::LicenseClick(TObject *Sender)
{
   Form12->Position=poScreenCenter;Form12->ShowModal();
   if(Form12->Tag==1)
   {
	  AboutBox->Tag=0;
	  Topic->Caption=lang->Strings[0];                      //"Лицензия успешно активирована"
	  LicenseInfo->Caption=lang->Strings[1];                //"Спасибо за покупку лицензии µMovies!"
	  License->Visible=false;TrialVersion->Visible=false;Image6->Visible=true;
   }
}
//---------------------------------------------------------------------------


void __fastcall TAboutBox::TrialVersionClick(TObject *Sender)
{
   TrialVersion->Enabled=false;AboutBox->Tag=2;Close();
}
//---------------------------------------------------------------------------


