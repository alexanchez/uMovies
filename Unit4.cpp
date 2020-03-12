//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
TStringList *website;
AnsiString mode="";bool Save=false;int selected=0;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
		: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormShow(TObject *Sender)
{
    Image1->Picture->LoadFromFile("Soft/Backgrounds/Background 8.jpg");
	website= new TStringList();website->LoadFromFile("Soft/Websites.txt");
	ListBox1->Items->Assign(website);
	mode="";
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(Save==true)
	  if(MessageDlg(savechange,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)//savechange="Сохранить изменения?"
        website->SaveToFile("Soft/Websites.txt");
	Edit1->Visible=false;Save=false;
	Image1->Picture->Assign(NULL);
	delete website;website=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::PopupMenu1Popup(TObject *Sender)
{
	if(ListBox1->Count==0 || ListBox1->ItemIndex==-1)
	  {PDelete->Enabled=false;PEdit->Enabled=false;}
	else
	  {PDelete->Enabled=true;PEdit->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Button1Click(TObject *Sender)
{
  if(ListBox1->Count!=0 && ListBox1->ItemIndex!=-1)
	{
	  AnsiString _url=ListBox1->Items->Strings[ListBox1->ItemIndex];
	  ShellExecute (HWND(Form4), "open", _url.c_str(), NULL, NULL, SW_SHOW );
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ListBox1Click(TObject *Sender)
{
	if(mode=="Adding" || mode=="Editing")
	{
	  AnsiString title_add=PAdd->Caption+"?",title_edit=PEdit->Caption+"?";
	  if(mode=="Adding" && Edit1->Text!="" && MessageDlg(title_add,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
		 {website->Add(Edit1->Text);ListBox1->Items->Assign(website);Save=true;}
	  if(mode=="Editing"&& Edit1->Text!="" && MessageDlg(title_edit,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
		 {website->Strings[selected]=Edit1->Text;ListBox1->Items->Assign(website);Save=true;}
	}
	Edit1->Visible=false;mode="";
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ListBox1DblClick(TObject *Sender)
{
   Button1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==VK_RETURN) Button1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::PAddClick(TObject *Sender)
{
  Edit1->Visible=true;mode="Adding";Edit1->Hint=enterforadd;//enterforadd="Нажмите Enter для добавления"
  Edit1->Text="http://";Edit1->SetFocus();Edit1->SelStart=Edit1->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::PEditClick(TObject *Sender)
{
  Edit1->Visible=true;mode="Editing";Edit1->Hint=enterforchange;//enterforchange="Нажмите Enter для изменения"
  Edit1->Text=ListBox1->Items->Strings[ListBox1->ItemIndex];selected=ListBox1->ItemIndex;
  Edit1->SetFocus();Edit1->SelStart=Edit1->Text.Length();
}
//---------------------------------------------------------------------------

void __fastcall TForm4::PDeleteClick(TObject *Sender)
{
  if(ListBox1->Count!=0 && ListBox1->ItemIndex!=-1)
   if(MessageDlg(youresure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes) //youresure="Вы уверены?"
	 {
	 website->Delete(ListBox1->ItemIndex);
	 ListBox1->Items->Assign(website);
	 ListBox1->SetFocus();
	 Save=true;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm4::PCancelClick(TObject *Sender)
{
  Edit1->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Edit1KeyDown(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
   if(mode=="Adding")
	   if (Key == VK_RETURN && Edit1->Text!="")
		  {website->Add(Edit1->Text);ListBox1->Items->Assign(website);
		   Edit1->Visible=false;Save=true;mode="";}
   if(mode=="Editing")
	   if (Key == VK_RETURN && Edit1->Text!="")
		  {website->Strings[selected]=Edit1->Text;ListBox1->Items->Assign(website);
		   Edit1->Visible=false;Save=true;mode="";}
}
//---------------------------------------------------------------------------

