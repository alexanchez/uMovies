//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit13.h"
#include "Unit14.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm13 *Form13;
bool mousedown=false;//Для массового выделения строк ListBoxa зажатой ЛКМ
//---------------------------------------------------------------------------
__fastcall TForm13::TForm13(TComponent* Owner)
	: TForm(Owner)
{
   lastindex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ImageMouseEnter(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  current->Picture->LoadFromFile("Soft/Buttons/Delete(light).png");
}
void __fastcall TForm13::ImageMouseLeave(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  current->Picture->LoadFromFile("Soft/Buttons/Delete.png");
}
//---------------------------------------------------------------------------

void AccessToForbiddenChar(AnsiString changename)
{
	  for(int i=0;i<changename.Length();i++)
		{if(changename.c_str()[i]==':')
		   changename.c_str()[i]='_';
		 if(changename.c_str()[i]=='«')
		   changename.c_str()[i]='[';
		 if(changename.c_str()[i]=='»')
		   changename.c_str()[i]=']';}
}
//---------------------------------------------------------------------------

void __fastcall TForm13::FormCreate(TObject *Sender)
{
  Image3->OnMouseEnter=ImageMouseEnter;Image3->OnMouseLeave=ImageMouseLeave;
  Image4->OnMouseEnter=ImageMouseEnter;Image4->OnMouseLeave=ImageMouseLeave;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::FormShow(TObject *Sender)
{
   Form14->Left=Form13->Left+ListBox2->Left-40;
   const char *pictures[4] = {"Search","Search","Delete","Delete"};
   for (int i=1;i<=4;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/"+AnsiString(pictures[i-1])+".png");
}
//---------------------------------------------------------------------------

void __fastcall TForm13::FormClose(TObject *Sender, TCloseAction &Action)
{
   Form14->Close();
   Form14->Image1->Picture->Assign(NULL);
   for (int i=1;i<=4;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm13::MRemoveSelectionL1Click(TObject *Sender)
{
  ListBox1->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TForm13::MRemoveSelectionL2Click(TObject *Sender)
{
  ListBox2->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TForm13::MoveMovieLRClick(TObject *Sender)
{
  for(int i=0;i<ListBox1->Items->Count;i++)
   if(ListBox1->Selected[i])
	  {ListBox2->Items->Add(ListBox1->Items->Strings[i]);ListBox1->Items->Delete(i);i--;}
  if(ListBox2->Items->Count==0)Button1->Enabled=false;
  else Button1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::MoveMovieRLClick(TObject *Sender)
{
  for(int i=0;i<ListBox2->Items->Count;i++)
   if(ListBox2->Selected[i])
	  {ListBox1->Items->Add(ListBox2->Items->Strings[i]);ListBox2->Items->Delete(i);i--;}
  if(ListBox2->Items->Count==0)Button1->Enabled=false;
  else Button1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::MoveAllMovieLRClick(TObject *Sender)
{
  for(int i=0;i<ListBox1->Items->Count;i++)
	  {ListBox2->Items->Add(ListBox1->Items->Strings[i]);ListBox1->Items->Delete(i);i--;}
  if(ListBox2->Items->Count==0)Button1->Enabled=false;
  else Button1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::MoveAllMovieRLClick(TObject *Sender)
{
  for(int i=0;i<ListBox2->Items->Count;i++)
	  {ListBox1->Items->Add(ListBox2->Items->Strings[i]);ListBox2->Items->Delete(i);i--;}
  if(ListBox2->Items->Count==0)Button1->Enabled=false;
  else Button1->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm13::Button1Click(TObject *Sender)
{
  if(MessageDlg(exit,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)//exit-Are you sure?
	 Form13->ModalResult=mrOk;
  else
	 Form13->ModalResult=mrCancel;
}
//---------------------------------------------------------------------------


void __fastcall TForm13::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==char(65) && Shift.Contains(ssCtrl))MoveMovieRLClick(Sender);
  if(Key==char(68) && Shift.Contains(ssCtrl))MoveMovieLRClick(Sender);
  if(Key==char(65) && Shift.Contains(ssAlt))MoveAllMovieRLClick(Sender);
  if(Key==char(68) && Shift.Contains(ssAlt))MoveAllMovieLRClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm13::Edit1Change(TObject *Sender)
{
	 if(Edit1->Text=="")
		{ListBox1->ClearSelection();Image3->Visible=false;}
	 if(Edit1->Text!=""&&Edit1->Text!=search)//
		{Image3->Visible=true;
		 if(ListBox1->Items->Count > 0)
		  for(int i=0;i<ListBox1->Items->Count;i++)
			{
			  if(ListBox1->Items->Strings[i].LowerCase().Pos(Edit1->Text.LowerCase())>0)
				  ListBox1->Selected[i] = true;
			  else
				  ListBox1->Selected[i] = false;
			}
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm13::Edit2Change(TObject *Sender)
{
	 if(Edit2->Text=="")
		{ListBox2->ClearSelection();Image4->Visible=false;}
	 if(Edit2->Text!=""&&Edit2->Text!=search)//
		{Image4->Visible=true;
		 if(ListBox2->Items->Count > 0)
		  for(int i=0;i<ListBox2->Items->Count;i++)
			{
			  if(ListBox2->Items->Strings[i].LowerCase().Pos(Edit2->Text.LowerCase())>0)
				  ListBox2->Selected[i] = true;
			  else
				  ListBox2->Selected[i] = false;
			}
		}
}
//---------------------------------------------------------------------------


void __fastcall TForm13::Edit1Enter(TObject *Sender)
{
  if(Edit1->Text==search)
	 Edit1->Text="";
   Edit1->Font->Color=clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::Edit2Enter(TObject *Sender)
{
  if(Edit2->Text==search)
	 Edit2->Text="";
   Edit2->Font->Color=clBlack;
}
//---------------------------------------------------------------------------


void __fastcall TForm13::Edit1Exit(TObject *Sender)
{
  if(Edit1->Text=="")
	{Edit1->Text=search;Edit1->Font->Color=clBtnShadow;Image3->Visible=false;}
}
//---------------------------------------------------------------------------


void __fastcall TForm13::Edit2Exit(TObject *Sender)
{
  if(Edit2->Text=="")
	{Edit2->Text=search;Edit2->Font->Color=clBtnShadow;Image4->Visible=false;}
}
//---------------------------------------------------------------------------


void __fastcall TForm13::Image3Click(TObject *Sender)
{
  if(Edit1->Focused()) Edit1->Clear();
  else {Edit1->Text=search;Edit1->Font->Color=clBtnShadow;}
  Image3->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::Image4Click(TObject *Sender)
{
  if(Edit2->Focused()) Edit2->Clear();
  else {Edit2->Text=search;Edit2->Font->Color=clBtnShadow;}
  Image4->Visible=false;
}
//---------------------------------------------------------------------------
//int _X = Mouse->CursorPos.x-Form13->Left-ListBox1->Left-4;
//int _y = Mouse->CursorPos.y-Form13->Top-ListBox1->Top-26;

void __fastcall TForm13::ListBox1MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
 if(mousedown==false)
 {
  int index;AnsiString namefilm;
  index=ListBox1->ItemAtPos(TPoint(X,Y),true);
  if(index>=0 && index!=lastindex)
	  {
	   lastindex=index;
	   namefilm=ListBox1->Items->Strings[index];
	   AccessToForbiddenChar(namefilm);
	   Form14->Image1->Picture->LoadFromFile("Data/Image/"+namefilm+".jpg");
	   long _Y = Mouse->CursorPos.y;
	   Form14->Top=_Y;//Form14->Left=Form13->Left+ListBox2->Left-40;
	   if((Form14->Top+Form14->Height)>Screen->Height)Form14->Top=Screen->Height-Form14->Height-45;//Если вылазит за высоту экрана
	   //if((Form14->Left+Form14->Width)>Screen->Width) Form14->Left=Form13->Left-Form14->Width;   //Если вылазит за ширину экрана
	   Form14->Show();
	  }
  long _X = Mouse->CursorPos.x;
  if((_X+15+Form14->Width)<=Screen->Width) Form14->Left=_X+15;
  else Form14->Left=_X-15-Form14->Width;                                                           //Если вылазит за ширину экрана
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox1MouseLeave(TObject *Sender)
{
   Form14->Close();
   Form14->Image1->Picture->Assign(NULL);
   lastindex=-1;
}
//---------------------------------------------------------------------------


void __fastcall TForm13::ListBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
   Form14->Close();
   mousedown=true;
   lastindex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
   mousedown=false;
}
//---------------------------------------------------------------------------


void __fastcall TForm13::PopupMenu1Popup(TObject *Sender)
{
   Form14->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox2MouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
 if(mousedown==false)
 {
  int index;AnsiString namefilm;
  index=ListBox2->ItemAtPos(TPoint(X,Y),true);
  if(index>=0 && index!=lastindex)
	  {
	   lastindex=index;
	   namefilm=ListBox2->Items->Strings[index];
	   AccessToForbiddenChar(namefilm);
	   Form14->Image1->Picture->LoadFromFile("Data/Image/"+namefilm+".jpg");
	   long _Y = Mouse->CursorPos.y;
	   Form14->Top=_Y;//Form14->Left=Form13->Left+ListBox2->Left-Form14->Width;
	   if((Form14->Top+Form14->Height)>Screen->Height)Form14->Top=Screen->Height-Form14->Height-45;//Если вылазит за высоту экрана
	   //if(Form14->Left<0) Form14->Left=Form13->Left+Form13->Width;                               //Если вылазит за ширину экрана
	   Form14->Show();
	  }
  long _X = Mouse->CursorPos.x;
  if((_X+15+Form14->Width)<=Screen->Width) Form14->Left=_X+15;
  else Form14->Left=_X-15-Form14->Width;                                                           //Если вылазит за ширину экрана
 }
}
//---------------------------------------------------------------------------


void __fastcall TForm13::ListBox2MouseLeave(TObject *Sender)
{
   Form14->Close();
   Form14->Image1->Picture->Assign(NULL);
   lastindex=-1;
}
//---------------------------------------------------------------------------


void __fastcall TForm13::ListBox2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   Form14->Close();
   mousedown=true;
   lastindex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
   mousedown=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::PopupMenu2Popup(TObject *Sender)
{
   Form14->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox1DragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
   Accept=true;
   int k=0;
   for(int i=0;i<ListBox1->Items->Count;i++)
	if(ListBox1->Selected[i]==true)
	  {k++;if(k==2)break;}

   if(k<=1)ListBox1->DragCursor=crDrag;
   else    ListBox1->DragCursor=crMultiDrag;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox2DragOver(TObject *Sender, TObject *Source, int X,
          int Y, TDragState State, bool &Accept)
{
   Accept=true;
   int k=0;
   for(int i=0;i<ListBox2->Items->Count;i++)
	if(ListBox2->Selected[i]==true)
	  {k++;if(k==2)break;}

   if(k<=1)ListBox2->DragCursor=crDrag;
   else    ListBox2->DragCursor=crMultiDrag;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox2DragDrop(TObject *Sender, TObject *Source, int X,
          int Y)
{
  TListBox *pList1 = (TListBox*)Source;
  TListBox *pList2 = (TListBox*)Sender;
  if(pList1==pList2)return;
  for (int i = pList1->Items->Count - 1; i >= 0; --i)
	 if (pList1->Selected[i])
        {
			pList2->Items->Insert(0, pList1->Items->Strings[i]);
            pList1->Items->Delete(i);
		}
  if(ListBox2->Items->Count==0)Button1->Enabled=false;
  else Button1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm13::ListBox1DragDrop(TObject *Sender, TObject *Source, int X,
          int Y)
{
  TListBox *pList1 = (TListBox*)Sender;
  TListBox *pList2 = (TListBox*)Source;
  if(pList1==pList2)return;
  for (int i = pList2->Items->Count - 1; i >= 0; --i)
		if (pList2->Selected[i])
		{
			pList1->Items->Insert(0, pList2->Items->Strings[i]);
			pList2->Items->Delete(i);
		}
  if(ListBox2->Items->Count==0)Button1->Enabled=false;
  else Button1->Enabled=true;
}
//---------------------------------------------------------------------------

