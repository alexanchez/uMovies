//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TPasswordDlg *PasswordDlg;
//---------------------------------------------------------------------
__fastcall TPasswordDlg::TPasswordDlg(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TPasswordDlg::FormShow(TObject *Sender)
{
   Password->Text="";NewPassword->Text="";//Label1->Caption=password;
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::OKBtnClick(TObject *Sender)
{
  if(PasswordDlg->Tag==0)                                       //Создать пароль
	 {password=Password->Text;PasswordDlg->Tag=1;Close();}
  if(PasswordDlg->Tag==2)                                       //Смена пароля
     {
	 if(password!=Password->Text)
       ShowMessage(name);//"Неправильный пароль!"
     else
       {password=NewPassword->Text;PasswordDlg->Tag=1;Close();}
     }
  if(PasswordDlg->Tag==3)                                       //Удаление/проверка пароля
     {
	 if(password!=Password->Text)
       ShowMessage(name);//"Неправильный пароль!"
     else
       {PasswordDlg->Tag=1;Close();}
     }
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::CancelBtnClick(TObject *Sender)
{
   PasswordDlg->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::Image1Click(TObject *Sender)
{
  PasswordDlg->Tag=2;Close();
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::PasswordChange(TObject *Sender)
{
  if(PasswordDlg->Tag==0||PasswordDlg->Tag==3)
    {if(Password->Text=="")
      OKBtn->Enabled=false;
    else
      OKBtn->Enabled=true;}
  else
    {if(Password->Text==""||NewPassword->Text=="")
      OKBtn->Enabled=false;
    else
      OKBtn->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::NewPasswordChange(TObject *Sender)
{
  if(Password->Text==""||NewPassword->Text=="")
    OKBtn->Enabled=false;
  else
    OKBtn->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::FormCreate(TObject *Sender)
{
  Image1->Picture->LoadFromFile("Soft/Buttons/ChangeCatalog.png");
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   Image1->Picture->Assign(NULL);
   if (PasswordDlg->Tag==3) PasswordDlg->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::Image1MouseEnter(TObject *Sender)
{
  Image1->Picture->LoadFromFile("Soft/Buttons/ChangeCatalog(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TPasswordDlg::Image1MouseLeave(TObject *Sender)
{
  Image1->Picture->LoadFromFile("Soft/Buttons/ChangeCatalog.png");
}
//---------------------------------------------------------------------------

