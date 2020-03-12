//--------------------------------------------------------------------------- Label 8,9,10 свободны

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "Unit1.h"
#include "Unit4.h"  – Сайты с фильмами
#include "Unit18.h" – Настройка сезонов в сериале
#include <clipbrd.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;AnsiString selname;
bool button1leave=false,button2leave=false;
bool expand1pressed=false,expand2pressed=false,expand3pressed=false,emptyedit1=false,emptyclb1=false,emptyclb2=false;
bool Form2_CheckedCLB=true,stars_check;
bool Favourite=false;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//-------------------------События MouseEnter - MouseLeave для картинок--------------------------

void __fastcall TForm2::ImageMouseEnter(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Emblem-download(light).png");break;
   case 4:current->Picture->LoadFromFile("Soft/Buttons/Emblem-download(light).png");break;
   case 5:current->Picture->LoadFromFile("Soft/Buttons/Web-internet(light).png");break;
   case 6:current->Picture->LoadFromFile("Soft/Buttons/Youtube-play-button(light).png");break;
   case 9:if(expand1pressed==false)current->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");break;
   case 10:if(expand2pressed==false)current->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");break;
   case 11:if(expand3pressed==false)current->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");break;
   case 12:current->Picture->LoadFromFile("Soft/Buttons/SerialSetting(light).png");break;
   case 13:
	{
		if(!Favourite)current->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(inactive_light).png");
		else current->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(light).png");
		break;
	}
  }
}
void __fastcall TForm2::ImageMouseLeave(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Emblem-download.png");break;
   case 4:current->Picture->LoadFromFile("Soft/Buttons/Emblem-download.png");break;
   case 5:current->Picture->LoadFromFile("Soft/Buttons/Web-internet.png");break;
   case 6:current->Picture->LoadFromFile("Soft/Buttons/Youtube-play-button.png");break;
   case 9:if(expand1pressed==false)current->Picture->LoadFromFile("Soft/Buttons/Expand.png");break;
   case 10:if(expand2pressed==false)current->Picture->LoadFromFile("Soft/Buttons/Expand.png");break;
   case 11:if(expand3pressed==false)current->Picture->LoadFromFile("Soft/Buttons/Expand.png");break;
   case 12:current->Picture->LoadFromFile("Soft/Buttons/SerialSetting.png");break;
   case 13:
	{
		if(!Favourite)current->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(inactive).png");
		else current->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter.png");
		break;
	}
  }
}
void __fastcall TForm2::LabelMouseEnter(TObject *Sender)
{
  TLabel* current=static_cast<TLabel*>(Sender);
  int index=current->Tag;
  switch(index)
  {
	  case 1:Image7->Picture->LoadFromFile("Soft/Buttons/Button(light).png");break;
	  case 2:Image8->Picture->LoadFromFile("Soft/Buttons/Button(light).png");break;
  }
}
void __fastcall TForm2::LabelMouseLeave(TObject *Sender)
{
  TLabel* current=static_cast<TLabel*>(Sender);
  int index=current->Tag;
  switch(index)
  {
	  case 1:Image7->Picture->LoadFromFile("Soft/Buttons/Button.png");break;
	  case 2:Image8->Picture->LoadFromFile("Soft/Buttons/Button.png");break;
  }
}
//---------------------------------------------------------------------------

void selectimage(TImage *Image,TLabel *Label,int h,int w)
{
 Image->Height=h;Image->Width=w;Label->Height=h;Label->Width=w;
}
//---------------------------------------------------------------------------s

void CheckListBoxChecked(TCheckListBox*CLB)
{
 if(Form2_CheckedCLB==true)
  {
   for(int i=0;i<CLB->Count;i++)
	if(CLB->Selected[i])
	   {if(CLB->Checked[i]==true)
		   CLB->Checked[i]=false;
		else
		   CLB->Checked[i]=true;
		break;}
  }
 Form2_CheckedCLB=true;
}
//---------------------------------------------------------------------------

bool CheckListBox_Click_Check(TCheckListBox*CheckLB,bool kindclb1,bool kindclb2)
{
 int k=0;CheckListBoxChecked(CheckLB);
 for(int i=0;i<CheckLB->Count;i++)
	   if(CheckLB->Checked[i])
		  k++;
 if(k==0)
   {Form2->Label12->Enabled=false;Form2->Label12->ShowHint=true;kindclb1=true;}
 else
   {kindclb1=false;
	if(emptyedit1==false&&kindclb2==false)
	   {Form2->Label12->Enabled=true;Form2->Label12->ShowHint=false;}
	else
	   {Form2->Label12->Enabled=false;Form2->Label12->ShowHint=true;}
	}
 return kindclb1;
}
//---------------------------------------------------------------------------TCheckListBox*CheckListBox=CheckListBox1;

void __fastcall TForm2::CheckListBoxClick(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  switch(current->Tag)
  {
   case 1:emptyclb1=CheckListBox_Click_Check(CheckListBox1,emptyclb1,emptyclb2);break;
   case 2:emptyclb2=CheckListBox_Click_Check(CheckListBox2,emptyclb2,emptyclb1);break;
   case 3:CheckListBoxChecked(CheckListBox3);break;
  }
}
void __fastcall TForm2::CheckListBoxClickCheck(TObject *Sender)
{
  Form2_CheckedCLB=false;
}
//--------------------------------------Избранные----------------------------

void __fastcall TForm2::SetFavourite(bool _Favourite)
{
	Favourite = _Favourite;
}

bool __fastcall TForm2::GetFavourite()
{
	return Favourite;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
  seasons=new TStringList();

  Edit5->OnKeyPress=EditClipboardPress;Edit6->OnKeyPress=EditClipboardPress;Edit7->OnKeyPress=EditClipboardPress;
  Memo2->OnKeyPress=EditClipboardPress;
  Form2->Cursor=(TCursor)1;RadioButton1->Cursor=(TCursor)1;RadioButton2->Cursor=(TCursor)1;
  CheckBox1->Cursor=(TCursor)1;CheckBox2->Cursor=(TCursor)1;
  ComboBox1->Cursor=(TCursor)1;ComboBox2->Cursor=(TCursor)1;
  CheckListBox1->Cursor=(TCursor)1;CheckListBox2->Cursor=(TCursor)1;CheckListBox3->Cursor=(TCursor)1;
  for(int i=1;i<=13;i++)
   if(i!=2&&i!=7&&i!=8)
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->Cursor=(TCursor)2;
  for(int i=3;i<=13;i++)
   if(i!=7&&i!=8)
	 {((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseEnter=ImageMouseEnter;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseLeave=ImageMouseLeave;}
  Label12->OnMouseEnter=LabelMouseEnter;Label12->OnMouseLeave=LabelMouseLeave;
  Label13->OnMouseEnter=LabelMouseEnter;Label13->OnMouseLeave=LabelMouseLeave;
  for(int i=1;i<=3;i++)
	{((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClick=CheckListBoxClick;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClickCheck=CheckListBoxClickCheck;}
  for (int i=1;i<=5;i++)
	{
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnMouseEnter=StarsMouseEnter;
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnMouseLeave=StarsMouseLeave;
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnMouseMove=StarsMouseMove;
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnClick=StarsClick;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormDestroy(TObject *Sender)
{
  delete seasons;seasons=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormShow(TObject *Sender)
{
 Form2->Tag=0;emptyedit1=false;emptyclb1=false;emptyclb2=false;
 selname=Edit1->Text;Label12->Enabled=true;Form2->Label12->ShowHint=false;
 Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 2.jpg");
 if(Screen->Height<900)
	Form2->Height=694;
 const char *pictures[11] = {"Emblem-download","Emblem-download","Web-internet","Youtube-play-button","Button","Button",
							"Expand","Expand","Expand","SerialSetting","FavouriteFilter(inactive)"};
 for (int i=3;i<=13;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/"+AnsiString(pictures[i-3])+".png");

 //Избранные
 if(Favourite){Image13->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter.png");Image13->Hint=DeleteFromFavourite;}
 else {Image13->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(inactive).png");Image13->Hint=AddToFavourite;}

 if(openmode=="openadd")
	 {stars_check=false;for (int i=1;i<=5;i++)((TImage*)FindComponent("Star"+IntToStr(i)))->Cursor=(TCursor)1;
	  Edit1->SelLength=Edit1->Text.Length();} //Выделить полностью название
 if(openmode=="openedit")
	 {stars_check=true;for (int i=1;i<=5;i++)((TImage*)FindComponent("Star"+IntToStr(i)))->Cursor=(TCursor)2;
	  Edit1->SelStart=Edit1->Text.Length();}  //Поставить фокус в конец названия
}
//---------------------------------------------------------------------------


void __fastcall TForm2::FormClose(TObject *Sender, TCloseAction &Action)
{
  CheckListBox1->ClearSelection();CheckListBox2->ClearSelection();
  expand1pressed=true;Image9Click(Form2);Edit1->SetFocus();
  Label12->Enabled=true;Form2->Label12->ShowHint=false;
  Image2->Picture->Assign(NULL);
  for (int i=3;i<=13;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->Assign(NULL);
  int q=Form18->SeasonsCount;
  for(int i=0;i<q;i++)
	 Form18->DeletingSeason(Form18);
  //Удаление enter в списке актёров
  AnsiString memo=Memo2->Text;
  for(int i=0;i<memo.Length();i++)
	if(memo.c_str()[i]==char(13))memo.Delete(i+1,1);
  Memo2->Text=memo;
}
//--------------------------Событие кнопки Добавить/Редактировать---------------

void __fastcall TForm2::Label12Click(TObject *Sender)
{
  //if(Edit1->Text.c_str()[Edit1->Text.Length()-1]==' '){Edit1Exit(Sender);return;}//Для очистки пробелов после названия
  Edit1Exit(Sender);                                //Для очистки пробелов после названия
  if(openmode=="openadd")                           //openmode-режим открытия
	 {
       if(films->IndexOf(Edit1->Text)>=0)
          {ShowMessage(filmwithnameis);return;}     //filmwithnameis-Фильм с таким именем уже есть
       else
          {Form2->Tag=1;Close();}
     }
  if(openmode=="openedit")
	 {
       if(Edit1->Text==selname)
         {Form2->Tag=1;Close();}
       else
         {
          if(films->IndexOf(Edit1->Text)>=0)
			{ShowMessage(filmwithnameis);return;}
          else
            {Form2->Tag=1;Close();}
         }
     }
}
//-------------------------Событие кнопки Закрыть-------------------------------

void __fastcall TForm2::Label13Click(TObject *Sender)
{
  Form2->Tag=0;Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton1Click(TObject *Sender)
{
  Label14->Visible=false;Edit4->Visible=false;Label21->Visible=false;Edit8->Visible=false;Image12->Visible=false;
  ComboBox3->Visible=false;Label20->Visible=false;ComboBox1->Left=754;ComboBox1->Width=97;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::RadioButton2Click(TObject *Sender)
{
  Label14->Visible=true;Edit4->Visible=true;Label21->Visible=true;Edit8->Visible=true;Image12->Visible=true;
  ComboBox3->Visible=true;Label20->Visible=true;ComboBox1->Left=715;ComboBox1->Width=81;
  ComboBox3->ItemIndex=ComboBox1->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox1Change(TObject *Sender)
{
 if(RadioButton2->Checked==true&&ComboBox1->Text!=""&&ComboBox3->Text!="")
   if(StrToInt(ComboBox1->Text)>StrToInt(ComboBox3->Text))
      ComboBox3->ItemIndex=ComboBox1->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox2Change(TObject *Sender)
{
 AnsiString number,temp,string=ComboBox2->Text;bool null=false;
   for (int i=0;i<string.Length();i++)
     if ((string.c_str()[i]>=48) && (string.c_str()[i]<=57))
       temp = temp+string.c_str()[i];
   if(temp==""||temp=="0")number="1";
   else
     for (int i=0;i<temp.Length();i++)
        {
         if(temp.c_str()[i]!='0')
           null=true;
         if(null==true)
           number+=temp.c_str()[i];
        }
   ComboBox2->Text=number+wordminute;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox2Exit(TObject *Sender)
{
   ComboBox2Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox3Change(TObject *Sender)
{
  if(RadioButton2->Checked==true&&ComboBox1->Text!=""&&ComboBox3->Text!="")
   if(StrToInt(ComboBox1->Text)>StrToInt(ComboBox3->Text))
      ComboBox3->ItemIndex=ComboBox1->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox1KeyPress(TObject *Sender, wchar_t &Key)
{
  if(Key==VK_BACK)Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ComboBox3KeyPress(TObject *Sender, wchar_t &Key)
{
  if(Key==VK_BACK)Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1Change(TObject *Sender)
{
 if(Edit1->Text=="")
	{Label12->Enabled=false;Label12->ShowHint=true;emptyedit1=true;}
 else
	{emptyedit1=false;
	 if(emptyclb1==false&&emptyclb2==false)
       {Label12->Enabled=true;Label12->ShowHint=false;}
     else
       {Label12->Enabled=false;Label12->ShowHint=true;}
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1KeyPress(TObject *Sender, wchar_t &Key)
{
  EditClipboardPress(Sender,Key);
  AnsiString ForbiddenChars = "\\/*<>|?",buffer=Clipboard()->AsText;
  if(ForbiddenChars.Pos(Key)||Key=='"')
	 {Key=0;Beep();}
  if (Key == 0x16)
	{
	 for(int i=0;i<buffer.Length();i++)
	   if(ForbiddenChars.Pos(buffer.c_str()[i])||buffer.c_str()[i]=='"')
		 {Key=0;Beep();ShowMessage(forbiddenChars);return;}//forbiddenChars-"Имя содержит недопустимые символы!(\\/*<>|?)"
	}    //Application->MessageBox("Запрет на ввод недопустимых символов!(\\/*<>|?)","Ошибка!",MB_OK | MB_ICONERROR);

  if(Key==' ' && Edit1->Text=="")Key=0;                                    //Для очистки пробелов после названия
  else if(Key==' ' && Edit1->SelStart==0 && Edit1->Text.Length()!=0)Key=0; //Для очистки пробелов перед названием
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
  //if(Key==' ' && Edit1->Text==" ")Edit1->Text="";//Для очистки пробелов после названия
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Edit1Exit(TObject *Sender)//Для очистки пробелов после названия
{
  AnsiString name="";int index=0;
  if(Edit1->Text.c_str()[Edit1->Text.Length()-1]==' ')
	{
	 for(int i=Edit1->Text.Length()-1;i>=0;i--)
	  {
	   if(Edit1->Text.c_str()[i]!=' ')
		{index=i;break;}
	  }
	 for(int i=0;i<=index;i++)
		name+=Edit1->Text.c_str()[i];
	 Edit1->Text=name;
	 //Edit1Change(Form2);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image1Click(TObject *Sender)
{
 if(OpenPictureDialog1->Execute())
 {
   Image1->Picture->LoadFromFile(OpenPictureDialog1->FileName);
   AnsiString FileName = OpenPictureDialog1->FileName;
   if(ExtractFileExt(FileName)==".bmp")
   {
	  TJPEGImage *Jpg=new TJPEGImage;
	  Jpg->Assign(Image1->Picture->Graphic);
	  Jpg->CompressionQuality = 95;			//Степень сжатия (качество) 1..100
	  Jpg->Compress();						//Упаковать графику
	  Image1->Picture->Assign(Jpg);
	  delete Jpg;
   }
   if(ExtractFileExt(FileName)==".png")
   {
      TJPEGImage *Jpg=new TJPEGImage;
	  Graphics::TBitmap *Bmp = new Graphics::TBitmap();
	  Bmp->Assign(Image1->Picture->Graphic);//PNG->BMP
	  Jpg->Assign(Bmp);                     //BMP->JPG
	  Jpg->CompressionQuality = 95;			//Степень сжатия (качество) 1..100
	  Jpg->Compress();						//Упаковать графику
	  Image1->Picture->Assign(Jpg);
	  delete Jpg,Bmp;
   }
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image3Click(TObject *Sender)
{
 UnicodeString text = "The clipboard does not contain text.";
 const wchar_t * wtext = text.c_str();
 if (Clipboard()->HasFormat(CF_TEXT))
   Edit2->Text = Clipboard()->AsText;
else
   Application->MessageBox(wtext, NULL, MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image4Click(TObject *Sender)
{
 UnicodeString text = "The clipboard does not contain text.";
 const wchar_t * wtext = text.c_str();
 if (Clipboard()->HasFormat(CF_TEXT))
   Edit3->Text = Clipboard()->AsText;
else
   Application->MessageBox(wtext, NULL, MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image5Click(TObject *Sender)
{
  Form4->Position=poScreenCenter;Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image6Click(TObject *Sender)
{
  AnsiString _url="https://www.youtube.com/?hl=ru";
	   ShellExecute (HWND(Form2), "open", _url.c_str(), NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image9Click(TObject *Sender)
{
  Image10->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");expand2pressed=false;
  CheckListBox2->Height=64;CheckListBox2->Width=140;CheckListBox2->Columns=0;
  Image11->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");expand3pressed=false;
  CheckListBox3->Height=64;CheckListBox3->Width=140;CheckListBox3->ScrollWidth = 0;
  if(expand1pressed==false)
     {Image9->Picture->LoadFromFile("Soft/Buttons/Expand(pressed).png");expand1pressed=true;
	  CheckListBox1->Height=169;CheckListBox1->Width=473;CheckListBox1->Columns=3;CheckListBox2->SendToBack();return;}
  if(expand1pressed==true)
     {Image9->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");expand1pressed=false;
      CheckListBox1->Height=64;CheckListBox1->Width=140;CheckListBox1->Columns=0;CheckListBox2->BringToFront();return;}
}
//------------------------------------------------------------------------------

void __fastcall TForm2::Image10Click(TObject *Sender)
{
  Image11->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");expand3pressed=false;
  CheckListBox3->Height=64;CheckListBox3->Width=140;CheckListBox3->ScrollWidth = 0;
  if(expand2pressed==false)
	 {Image10->Picture->LoadFromFile("Soft/Buttons/Expand(pressed).png");expand2pressed=true;
	  CheckListBox2->Height=224;CheckListBox2->Width=459;CheckListBox2->Columns=3;return;}
  if(expand2pressed==true)
	 {Image10->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");expand2pressed=false;
      CheckListBox2->Height=64;CheckListBox2->Width=140;CheckListBox2->Columns=0;return;}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image11Click(TObject *Sender)
{
  if(expand3pressed==false)
	 {Image11->Picture->LoadFromFile("Soft/Buttons/Expand(pressed).png");expand3pressed=true;
	  int scrollWidth = 0;
	  for(int i=0;i<CheckListBox3->Count;i++)
		 scrollWidth=Max(scrollWidth,CheckListBox3->Canvas->TextWidth(CheckListBox3->Items->Strings[i])+20);
	  CheckListBox3->ScrollWidth=scrollWidth;
	  if(CheckListBox3->Items->Count>3)
		 CheckListBox3->Height=CheckListBox3->Items->Count*21+7;
	  CheckListBox3->Width=290;
	  return;}
  if(expand3pressed==true)
	 {Image11->Picture->LoadFromFile("Soft/Buttons/Expand(light).png");expand3pressed=false;
	  CheckListBox3->Height=64;CheckListBox3->Width=140;CheckListBox3->ScrollWidth = 0;return;}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image12Click(TObject *Sender)
{
  Form18->SetSeasons(seasons);
  Form18->Position=poScreenCenter;
  if(Form18->ShowModal()==mrCancel)
	 return;
  Form18->GetSeasons(seasons);
  int sum=0;
  for(int i=0;i<seasons->Count;i++)
	sum+=StrToInt(seasons->Strings[i]);
  Edit4->Text=seasons->Count;Edit8->Text=sum;
}
//--------------------------MouseMove-Leave для кнопки "фото фильма(Download)"------------------

void __fastcall TForm2::Image1MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  Image1->Width=604;Image1->Height=238;
}
void __fastcall TForm2::Image1MouseLeave(TObject *Sender)
{
  Image1->Width=599;Image1->Height=233;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label12MouseDown(TObject *Sender,
	  TMouseButton Button, TShiftState Shift, int X, int Y)
{
  selectimage(Image7,Label12,74,155);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label12MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  selectimage(Image7,Label12,72,153);
}
//------------------------------------------------------------------------------


void __fastcall TForm2::Label13MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  selectimage(Image8,Label13,74,155);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label13MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
  selectimage(Image8,Label13,72,153);
}
//---------------------------------------------------------------------------
//-------------------------------РЕЙТИНГ-------------------------------------

void __fastcall TForm2::StarsClick(TObject *Sender)
{
	if(stars_check==true)
	{stars_check=false;
	 for (int i=1;i<=5;i++)
	  {((TImage*)FindComponent("Star"+IntToStr(i)))->Cursor=(TCursor)1;
	   ((TImage*)FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");}
	}
	else
	{stars_check=true;
	 for (int i=1;i<=5;i++)
	  ((TImage*)FindComponent("Star"+IntToStr(i)))->Cursor=(TCursor)2;
	}
}

void __fastcall TForm2::StarsMouseEnter(TObject *Sender)
{
   if(stars_check==false)
   {
	stars_check=false;
	for (int i=1;i<=5;i++)
	((TImage*)FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::StarsMouseLeave(TObject *Sender)
{
  if(stars_check==false)
   {for (int i=1;i<=5;i++)
	((TImage*)FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
	Rating->Caption="0.0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::StarsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
  if(stars_check==false)
  {
	TImage* current=static_cast<TImage*>(Sender);
	if(current->Tag>1)
	 for (int i=1;i<current->Tag;i++)
	  ((TImage*)FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star.png");
	if(X>=12){current->Picture->LoadFromFile("Soft/Buttons/Star.png");Rating->Caption=IntToStr(current->Tag)+".0";}
	if(X<12 && X>=4) {current->Picture->LoadFromFile("Soft/Buttons/Star_half.png");Rating->Caption=IntToStr(current->Tag-1)+".5";}
	if(X<4) {current->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");Rating->Caption=IntToStr(current->Tag-1)+".0";}
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image13Click(TObject *Sender)
{
  if(!Favourite){Favourite=true;Image13->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(light).png");Image13->Hint=DeleteFromFavourite;}
  else {Favourite=false;Image13->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(inactive_light).png");Image13->Hint=AddToFavourite;}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label5Click(TObject *Sender)
{
  if(Favourite)ShowMessage("true");
  else ShowMessage("false");
}
//---------------------------------------------------------------------------

