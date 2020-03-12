//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit18.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm18 *Form18;
bool MiddlePressed;int YPos;//Для прокрутки скролла с помощью движения мыши вверх-вниз
//---------------------------------------------------------------------------
__fastcall TForm18::TForm18(TComponent* Owner)
	: TForm(Owner)
{
  SeasonsCount=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm18::FormCreate(TObject *Sender)
{
  AddSeason->OnMouseEnter=ImageMouseEnter;AddSeason->OnMouseLeave=ImageMouseLeave;
  DeleteSeason->OnMouseEnter=ImageMouseEnter;DeleteSeason->OnMouseLeave=ImageMouseLeave;
  ImageInfo->OnMouseEnter=ImageMouseEnter;ImageInfo->OnMouseLeave=ImageMouseLeave;
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ImageMouseEnter(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:current->Picture->LoadFromFile("Soft/Buttons/AddSeason(light).png");break;
   case 2:current->Picture->LoadFromFile("Soft/Buttons/DeleteSeason(light).png");break;
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Info(light).png");break;
  }
}
void __fastcall TForm18::ImageMouseLeave(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:current->Picture->LoadFromFile("Soft/Buttons/AddSeason.png");break;
   case 2:current->Picture->LoadFromFile("Soft/Buttons/DeleteSeason.png");break;
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Info.png");break;
  }
}
//---------------------------------------------------------------------------

void VerifyInputInformation()
{
  bool enabled=true;
  for(int i=1;i<=Form18->SeasonsCount;i++)
	 if(((TEdit*)Form18->ScrollBox1->FindComponent("Edit"+AnsiString(i)))->Text==""||
		((TEdit*)Form18->ScrollBox1->FindComponent("Edit"+AnsiString(i)))->Text=="0")
	   {enabled=false;break;}
  if(enabled){Form18->ApplyButton->Enabled=true;Form18->ImageInfo->Visible=false;}
  else {Form18->ApplyButton->Enabled=false;Form18->ImageInfo->Visible=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm18::SeriesChange(TObject *Sender)
{
  TEdit* current=static_cast<TEdit*>(Sender);
  if(current->Text!="0" && current->Text.c_str()[0]=='0')
	 current->Text=current->Text.Delete(1,1);
  if(current->Text.Length()>=4)current->Text=current->Text.Delete(current->Text.Length(),1);
  VerifyInputInformation();
}
//---------------------------------------------------------------------------

void __fastcall TForm18::EditMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
  MiddlePressed=false;ScrollBox1->Cursor=crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TForm18::SeasonsChange(TObject *Sender)
{
  if(Seasons->Text!="0" && Seasons->Text.c_str()[0]=='0')
	 Seasons->Text=Seasons->Text.Delete(1,1);
  if(Seasons->Text.Length()>=4)Seasons->Text=Seasons->Text.Delete(Seasons->Text.Length(),1);
}
//---------------------------------------------------------------------------

void __fastcall TForm18::AddingSeason(TObject *Sender)
{
  TImage *Image=new TImage(ScrollBox1);
  Image->Parent=ScrollBox1;
  Image->Name="Image"+AnsiString(SeasonsCount+1);                                 //Image->Top=41*list->Count+3+2*list->Count;
  if(SeasonsCount==0)Image->Top=3;//3 - отступ до, 2*list->Count - отступ после
  else Image->Top=((TImage*)ScrollBox1->FindComponent("Image"+AnsiString(SeasonsCount)))->Top+2+41;//2-отступ после,41-высота Image
  Image->Left=3;
  Image->Width=41;Image->Height=41;
  Image->Picture->LoadFromFile("Soft/Buttons/Indicator.bmp");
  Image->Enabled=false;//Для прокрутки с помощью движения мышки (чтобы не мешал двигать)

  TEdit *Edit=new TEdit(ScrollBox1);
  Edit->Parent=ScrollBox1;
  Edit->Name="Edit"+AnsiString(SeasonsCount+1);
  if(SeasonsCount==0)Edit->Top=9;//Edit->Top=31*list->Count+9+12*list->Count;
  else Edit->Top=((TEdit*)ScrollBox1->FindComponent("Edit"+AnsiString(SeasonsCount)))->Top+12+31;//12-отступ после,31-высота Edit
  Edit->Left=50;
  Edit->Alignment=taCenter;Edit->Font->Name="Times New Roman";Edit->Font->Size=15;
  Edit->Width=41;Edit->Height=31;
  Edit->Text="";Edit->NumbersOnly=true;
  Edit->OnChange=SeriesChange;
  Edit->OnMouseUp=EditMouseUp;

  SeasonsCount++;
  AnsiString k=IntToStr(SeasonsCount);
  Image->Canvas->Font->Name="Monotype Corsiva";
  Image->Canvas->Font->Color=clCream;
  Image->Canvas->Font->Size=18;
  Image->Canvas->Brush->Style=bsClear;//Прозрачность
  if(k.Length()>=2)Image->Canvas->TextOut(7,4,k);
  else Image->Canvas->TextOut(13,4,k);
}
//---------------------------------------------------------------------------

void __fastcall TForm18::DeletingSeason(TObject *Sender)
{
  if(SeasonsCount!=0)
   {
	delete ((TImage*)ScrollBox1->FindComponent("Image"+AnsiString(SeasonsCount)));
	delete ((TEdit*)ScrollBox1->FindComponent("Edit"+AnsiString(SeasonsCount)));
	SeasonsCount--;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm18::SetSeasons(TStringList *_seasons)
{
  Seasons->Text=_seasons->Count;
  wchar_t Key=VK_RETURN;
  SeasonsKeyPress(Form18,Key);
  for(int i=1;i<=SeasonsCount;i++)
	 ((TEdit*)ScrollBox1->FindComponent("Edit"+AnsiString(i)))->Text=_seasons->Strings[i-1];
}
//---------------------------------------------------------------------------

void __fastcall TForm18::GetSeasons(TStringList *_seasons)
{
  _seasons->Clear();
  for(int i=1;i<=SeasonsCount;i++)
	 _seasons->Add(((TEdit*)ScrollBox1->FindComponent("Edit"+AnsiString(i)))->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ImageInfoClick(TObject *Sender)
{
  for(int i=1;i<=SeasonsCount;i++)
	 if(((TEdit*)Form18->ScrollBox1->FindComponent("Edit"+AnsiString(i)))->Text=="")
	   {((TEdit*)Form18->ScrollBox1->FindComponent("Edit"+AnsiString(i)))->SetFocus();break;}
}
//---------------------------------------------------------------------------

void __fastcall TForm18::SeasonsKeyPress(TObject *Sender, wchar_t &Key)
{
 if (Key == VK_RETURN)
 {
   if(Seasons->Text!=""&&Seasons->Text!="0")
   {
	if(Seasons->Text.ToInt()>SeasonsCount)
	 {
	  int q=Seasons->Text.ToInt()-SeasonsCount;
	  for(int i=0;i<q;i++)
	   AddingSeason(Sender);
	  VerifyInputInformation();return;
	 }
	if(Seasons->Text.ToInt()<SeasonsCount)
	 {
	  int q=SeasonsCount-Seasons->Text.ToInt();
	  for(int i=0;i<q;i++)
	   DeletingSeason(Sender);
	  VerifyInputInformation();return;
	 }
	if(Seasons->Text.ToInt()==SeasonsCount);
   }
  else Beep(300,500);
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm18::AddSeasonClick(TObject *Sender)
{
  AddingSeason(Sender);
  Seasons->Text=SeasonsCount;VerifyInputInformation();
}
//---------------------------------------------------------------------------

void __fastcall TForm18::DeleteSeasonClick(TObject *Sender)
{
  if(SeasonsCount>1){DeletingSeason(Sender);Seasons->Text=SeasonsCount;VerifyInputInformation();}
}
//---------------------------------------------------------------------------

void __fastcall TForm18::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==char(65) && Shift.Contains(ssCtrl))AddSeasonClick(Sender);
  if(Key==char(68) && Shift.Contains(ssCtrl))DeleteSeasonClick(Sender);
  if(Key==char(27))Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ScrollBox1Click(TObject *Sender)
{
  ScrollBox1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ScrollBox1MouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
  ScrollBox1->VertScrollBar->Position += 15;
  Handled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ScrollBox1MouseWheelUp(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
  ScrollBox1->VertScrollBar->Position -= 15;
  Handled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ScrollBox1MouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
  if(Button==mbMiddle){MiddlePressed=true;ScrollBox1->Cursor=crSizeAll;}
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ScrollBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
  MiddlePressed=false;ScrollBox1->Cursor=(TCursor)1;
}
//---------------------------------------------------------------------------

void __fastcall TForm18::ScrollBox1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
  if(MiddlePressed)
  {
	if(Y>YPos)ScrollBox1->VertScrollBar->Position += 10;
	if(Y<YPos)ScrollBox1->VertScrollBar->Position -= 10;
	YPos=Y;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm18::FormMouseEnter(TObject *Sender)
{
  MiddlePressed=false;ScrollBox1->Cursor=(TCursor)1;
}
//---------------------------------------------------------------------------

