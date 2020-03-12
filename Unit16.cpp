//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit16.h"
#include "Unit10.h"
#include "Unit1.h"
#include <clipbrd.hpp>
#include "SortingOptions.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm16 *Form16;
TStringList *ListOfFilters,*Filter;
AnsiString FilterMode,LastName;
bool Form16_CheckedCLB=true;
AnsiString Mode[4];
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TForm16::TForm16(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
/*
Words[0] - Все
Words[1] - Сохранить изменения?
Words[2] - Вы уверены?
Words[3] - Имя содержит недопустимые символы!(\\/*<>|?)")
Words[4] - Фильтр с таким именем уже есть!
Words[5] - Настройте все параметры!
Words[6] - Любимый фильтр
Words[7] - Фильтр помечен как любимый!
*/

//-------------------------События MouseEnter - MouseLeave для картинок--------------------------

void __fastcall TForm16::ImageMouseEnter(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:current->Picture->LoadFromFile("Soft/Buttons/Optionsort(light).png");break;
   case 2:if(Image2->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/Apply(light).png");break;
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Filter_Cancel(light).png");break;
   case 4:current->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter(light).png");break;
  }
}
void __fastcall TForm16::ImageMouseLeave(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 1:current->Picture->LoadFromFile("Soft/Buttons/Optionsort.png");break;
   case 2:if(Image2->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/Apply.png");break;
   case 3:current->Picture->LoadFromFile("Soft/Buttons/Filter_Cancel.png");break;
   case 4:current->Picture->LoadFromFile("Soft/Buttons/FavouriteFilter.png");break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm16::CheckListBoxMouseEnter(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  if(current->Hint=="0")
  {
	switch(current->Tag)
	{
	case 1:if(CheckListBox1->Height==26){CheckListBox1->Height=245;CheckListBox1->Width=339;CheckListBox1->Columns=2;}break;
	case 2:if(CheckListBox2->Height==26){CheckListBox2->Height=245;CheckListBox2->Width=339;CheckListBox2->Columns=2;}break;
	case 3:if(CheckListBox3->Height==26){CheckListBox3->Height=184;CheckListBox3->Width=339;CheckListBox3->Columns=5;}break;
	case 4:if(CheckListBox4->Height==26){CheckListBox4->Height=184;CheckListBox4->Width=339;CheckListBox4->Columns=4;}break;
	}
	if(current->Tag==2 || current->Tag==4)current->Left=16;
	current->BringToFront();
	current->SetFocus();
  }
  current->Hint=AnsiString(current->Hint.ToInt()+1);//++
}
//-----------------------------------------------------------------------------------------
void __fastcall TForm16::CheckListBoxMouseLeave(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  if(current->Hint=="3")
  {
	current->Height=26;current->Width=154;current->Columns=0;
	if(current->Tag==2 || current->Tag==4)current->Left=201;
	current->Hint="0";
	DefocusControl(current,false);
  }
  if(current->Hint=="1")current->Hint=AnsiString(current->Hint.ToInt()+1);//++
}
//-----------------------------------------------------------------------------------------

void __fastcall TForm16::CheckListBoxClick(TObject *Sender)
{
  TCheckListBox * current = static_cast<TCheckListBox*>(Sender);
  if(Form16_CheckedCLB==true)
  {
   for(int i=0;i<current->Count;i++)
	if(current->Selected[i])
	   {
	    if(current->Checked[i]==true)
		   current->Checked[i]=false;
		else
		   current->Checked[i]=true;
		break;
	   }
  }
  Form16_CheckedCLB=true;
}
//-----------------------------------------------------------------------------------------
void __fastcall TForm16::CheckListBoxClickCheck(TObject *Sender)
{
  Form16_CheckedCLB=false;
}
//-------------------------------------------------------------------------------------------

void __fastcall TForm16::FormCreate(TObject *Sender)
{
  for(int i=1;i<=4;i++)
	 {((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseEnter=ImageMouseEnter;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseLeave=ImageMouseLeave;}
  for(int i=1;i<=4;i++)
	 {
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClick=CheckListBoxClick;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClickCheck=CheckListBoxClick;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnMouseEnter=CheckListBoxMouseEnter;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnMouseLeave=CheckListBoxMouseLeave;
	 }
  Edit1->OnChange=VerifyEnteredData;
  ComboBox1->OnChange=VerifyEnteredData;ComboBox2->OnChange=VerifyEnteredData;
  ComboBox5->OnChange=VerifyEnteredData;ComboBox6->OnChange=VerifyEnteredData;
}
//---------------------------------------------------------------------------

void ShowFilters()
{
  AnsiString name;
  Form16->ListBox1->Items->Clear();
  TSearchRec sr;
   if (FindFirst("Filters\\*.dat", faAnyFile | faDirectory, sr) == 0)
     {
		do
		{   name=sr.Name;name=name.Delete(name.Length()-4+1, 4);
			for(int i=0; i<name.Length();i++)
			{
			  if(name.c_str()[i]=='_')
				 name.c_str()[i]=':';
			  if(name.c_str()[i]=='[')
				 name.c_str()[i]='«';
			  if(name.c_str()[i]==']')
				 name.c_str()[i]='»';
			}
			Form16->ListBox1->Items->Add(name);
		}
        while(FindNext(sr) == 0);
	 }
  ListOfFilters->Assign(Form16->ListBox1->Items);
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

void ApplyButtonEnabled()
{
  if(Form16->ListBox1->Items->Count>=1 && Form16->ListBox1->ItemIndex!=-1)Form16->Button1->Enabled=true;
  else Form16->Button1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm16::VerifyEnteredData(TObject *Sender)
{
   bool enabled=true;
   while(enabled)
   {
   if(Form16->Edit1->Text=="" || Form16->Edit1->Text=="-")enabled=false;

   if(Filter->Strings[0]=="1" && (Form16->ComboBox1->Text==""||Form16->ComboBox1->ItemIndex==-1))enabled=false;
   if(Filter->Strings[1]=="1" && (Form16->ComboBox2->Text==""||Form16->ComboBox2->ItemIndex==-1))enabled=false;
   if(Filter->Strings[2]=="1" && (Form16->ComboBox3->Text==""||Form16->ComboBox3->ItemIndex==-1))enabled=false;
   if(Filter->Strings[2]=="3" && (Form16->ComboBox3->Text==""||Form16->ComboBox3->ItemIndex==-1||
								  Form16->ComboBox7->Text==""||Form16->ComboBox7->ItemIndex==-1))enabled=false;
   if(Filter->Strings[3]=="1" && (Form16->ComboBox4->Text==""||Form16->ComboBox4->ItemIndex==-1))enabled=false;
   if(Filter->Strings[3]=="3" && (Form16->ComboBox4->Text==""||Form16->ComboBox4->ItemIndex==-1||
							      Form16->ComboBox8->Text==""||Form16->ComboBox8->ItemIndex==-1))enabled=false;
   if(Form16->ComboBox5->Text==""||Form16->ComboBox5->ItemIndex==-1||
	  Form16->ComboBox6->Text==""||Form16->ComboBox6->ItemIndex==-1)enabled=false;
   break;
   }
   if(enabled){Form16->Image2->Enabled=true;Form16->Image2->Picture->LoadFromFile("Soft/Buttons/Apply.png");}
   else {Form16->Image2->Enabled=false;Form16->Image2->Picture->LoadFromFile("Soft/Buttons/Apply(not color).png");}

}
//---------------------------------------------------------------------------

AnsiString CheckedElements(TCheckListBox *CheckLB)
{
  int n=0;AnsiString string="";
	for(int i=0;i<CheckLB->Count;i++)
	  if(CheckLB->Checked[i])
	  {
	  if(n>0)
	   {string=string+","+i;n++;}
	  if(n==0)
	   {string=string+i;n++;}
	  }
  if(string=="")string="-";
   return string;
}
//---------------------------------------------------------------------------

void CheckElements(TCheckListBox *CheckLB,AnsiString string)
{
 if(string=="-")return;
 if(!string.Pos(","))CheckLB->Checked[StrToInt(string)]=true;
 else
  {
   AnsiString temp="";
   for(int i=0;i<string.Length();i++)
   {
	 if(string.c_str()[i]!=',')
		temp=temp+string.c_str()[i];
	 else
		{CheckLB->Checked[StrToInt(temp)]=true;temp="";}
   }
   if(temp!="") CheckLB->Checked[StrToInt(temp)]=true;
  }
}
//---------------------------------------------------------------------------

void StringDivision(AnsiString string,TComboBox *CB1,TComboBox *CB2)
{
  AnsiString from="",till="";
  for(int i=0;i<string.Length();i++)
	 {if(string.c_str()[i]!='-')
		till+=string.c_str()[i];
	  else
	   {from=till;till="";}
	 }
  CB1->ItemIndex=StrToInt(from);CB2->ItemIndex=StrToInt(till);
}
//---------------------------------------------------------------------------

AnsiString ExpressionNumberFromString(TComboBox*combobox)
{
   AnsiString number,temp,string=combobox->Text;bool null=false;
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
	return number;
}
//---------------------------------------------------------------------------

void SetFilter(TForm *Form)
{
   TComboBox *CB1=((TComboBox*)Form->FindComponent("ComboBox1")),*CB2=((TComboBox*)Form->FindComponent("ComboBox2")),
			 *CB3=((TComboBox*)Form->FindComponent("ComboBox3")),*CB4=((TComboBox*)Form->FindComponent("ComboBox4")),
			 *CB5=((TComboBox*)Form->FindComponent("ComboBox5")),*CB6=((TComboBox*)Form->FindComponent("ComboBox6")),
			 *CB7=((TComboBox*)Form->FindComponent("ComboBox7")),*CB8=((TComboBox*)Form->FindComponent("ComboBox8"));
   TCheckListBox *CLB1=((TCheckListBox*)Form->FindComponent("CheckListBox1")),*CLB2=((TCheckListBox*)Form->FindComponent("CheckListBox2")),
				 *CLB3=((TCheckListBox*)Form->FindComponent("CheckListBox3")),*CLB4=((TCheckListBox*)Form->FindComponent("CheckListBox4"));
   TRadioButton *RB1=((TRadioButton*)Form->FindComponent("RadioButton1")),*RB2=((TRadioButton*)Form->FindComponent("RadioButton2")),
				*RB3=((TRadioButton*)Form->FindComponent("RadioButton3")),*RB4=((TRadioButton*)Form->FindComponent("RadioButton4"));

   if(Form10->RadioButton1->Checked==true)Filter->Strings[4]=CB1->ItemIndex;
   if(Form10->RadioButton2->Checked==true)Filter->Strings[4]=CheckedElements(CLB1);
   if(Form10->RadioButton3->Checked==true)Filter->Strings[4]=CheckedElements(CLB1);

   if(Form10->RadioButton4->Checked==true)Filter->Strings[5]=CB2->ItemIndex;
   if(Form10->RadioButton5->Checked==true)Filter->Strings[5]=CheckedElements(CLB2);
   if(Form10->RadioButton6->Checked==true)Filter->Strings[5]=CheckedElements(CLB2);

   if(Form10->RadioButton7->Checked==true)Filter->Strings[6]=CB3->ItemIndex;
   if(Form10->RadioButton8->Checked==true)Filter->Strings[6]=CheckedElements(CLB3);
   if(Form10->RadioButton9->Checked==true)Filter->Strings[6]=AnsiString(CB3->ItemIndex)+"-"+AnsiString(CB7->ItemIndex);

   if(Form10->RadioButton10->Checked==true)Filter->Strings[7]=CB4->ItemIndex;
   if(Form10->RadioButton11->Checked==true)Filter->Strings[7]=CheckedElements(CLB4);
   if(Form10->RadioButton12->Checked==true)Filter->Strings[7]=AnsiString(CB4->ItemIndex)+"-"+AnsiString(CB8->ItemIndex);
   Filter->Strings[8]=CB5->ItemIndex;Filter->Strings[9]=CB6->ItemIndex;
   if(RB1->Checked)Filter->Strings[10]="2";if(RB2->Checked)Filter->Strings[10]="3";//2-Фильмы;3-Сериалы
   if(RB3->Checked)Filter->Strings[10]="1";if(RB4->Checked)Filter->Strings[10]="4";//1-Все;4-Избранные
}
//---------------------------------------------------------------------------

void __fastcall TForm16:: ShowInformation(TForm *Form,TStringList *filter)
{
  TComboBox *CB1=((TComboBox*)Form->FindComponent("ComboBox1")),*CB2=((TComboBox*)Form->FindComponent("ComboBox2")),
			*CB3=((TComboBox*)Form->FindComponent("ComboBox3")),*CB4=((TComboBox*)Form->FindComponent("ComboBox4")),
			*CB5=((TComboBox*)Form->FindComponent("ComboBox5")),*CB6=((TComboBox*)Form->FindComponent("ComboBox6")),
			*CB7=((TComboBox*)Form->FindComponent("ComboBox7")),*CB8=((TComboBox*)Form->FindComponent("ComboBox8"));
  TCheckListBox *CLB1=((TCheckListBox*)Form->FindComponent("CheckListBox1")),*CLB2=((TCheckListBox*)Form->FindComponent("CheckListBox2")),
				*CLB3=((TCheckListBox*)Form->FindComponent("CheckListBox3")),*CLB4=((TCheckListBox*)Form->FindComponent("CheckListBox4"));
  TRadioButton *RB1=((TRadioButton*)Form->FindComponent("RadioButton1")),*RB2=((TRadioButton*)Form->FindComponent("RadioButton2")),
			   *RB3=((TRadioButton*)Form->FindComponent("RadioButton3")),*RB4=((TRadioButton*)Form->FindComponent("RadioButton4"));
  if(Form==Form16)
  {
  if(filter->Strings[10]=="1")RB3->Checked=true;if(filter->Strings[10]=="2")RB1->Checked=true;//1-Все;2-Фильмы
  if(filter->Strings[10]=="3")RB2->Checked=true;if(filter->Strings[10]=="4")RB4->Checked=true;//3-Сериалы;4-Избранные
  }
  else //RadioButton3Click-Чтобы переключило даже если уже стоит эта категория на форме
  {
  if(filter->Strings[10]=="1"){Form1->Label13Click(Form1);Form1->RadioButton3Click(Form1);}
  if(filter->Strings[10]=="2"){Form1->Label11Click(Form1);Form1->RadioButton1Click(Form1);}
  if(filter->Strings[10]=="3"){Form1->Label12Click(Form1);Form1->RadioButton2Click(Form1);}
  if(filter->Strings[10]=="4"){Form1->Label16Click(Form1);Form1->RadioButton4Click(Form1);}
  }
  if(filter->Strings[0]=="1")CB1->ItemIndex=StrToInt(filter->Strings[4]);
  if(filter->Strings[0]=="2")CheckElements(CLB1,filter->Strings[4]);
  if(filter->Strings[0]=="3")CheckElements(CLB1,filter->Strings[4]);
  if(filter->Strings[1]=="1")CB2->ItemIndex=StrToInt(filter->Strings[5]);
  if(filter->Strings[1]=="2")CheckElements(CLB2,filter->Strings[5]);
  if(filter->Strings[1]=="3")CheckElements(CLB2,filter->Strings[5]);
  if(filter->Strings[2]=="1")CB3->ItemIndex=StrToInt(filter->Strings[6]);
  if(filter->Strings[2]=="2")CheckElements(CLB3,filter->Strings[6]);
  if(filter->Strings[2]=="3")StringDivision(filter->Strings[6],CB3,CB7);
  if(filter->Strings[3]=="1")CB4->ItemIndex=StrToInt(filter->Strings[7]);
  if(filter->Strings[3]=="2")CheckElements(CLB4,filter->Strings[7]);
  if(filter->Strings[3]=="3")StringDivision(filter->Strings[7],CB4,CB8);
  CB5->ItemIndex=StrToInt(filter->Strings[8]);
  CB6->ItemIndex=StrToInt(filter->Strings[9]);
}
//---------------------------------------------------------------------------

void DefaultOptions()
{
  Filter->Clear();
  for(int i=0; i<4;i++)Filter->Add("1");
  for(int i=4; i<10;i++)Filter->Add("0");
  Filter->Add("1");//Категория
  SetRadioButtons(Filter);
  for(int i=0; i<4;i++)Filter->Strings[i]="0";
  SetOptions(Form16,Filter,Form16->Words[0]);
  for(int i=0; i<4;i++)Filter->Strings[i]="1";
  Form16->Edit1->Text="";
  Form16->ComboBox5->ItemIndex=0;Form16->ComboBox6->ItemIndex=0;
  Form16->RadioButton3->Checked=true;//Категория "Все"
  for(int i=1;i<=4;i++)((TCheckListBox*)Form16->FindComponent("CheckListBox"+IntToStr(i)))->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TForm16::FormShow(TObject *Sender)
{
  ListOfFilters=new TStringList();Filter=new TStringList();
  ShowFilters();
  ApplyButtonEnabled();
  if(Form16->Tag==0)DefaultOptions();
  FilterMode="";
  Image4->Hint=Words[6]+": "+FavoriteFilter;
  GroupBox2->Enabled=false;Image2->Visible=false;Image3->Visible=false;
  FiltersQuantity->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
  if(Form16->Tag==1)
  {
	for(int i=0; i<10;i++)Filter->Add("0");
	Filter->Add("1");//Категория
	SetOptions(Form16,Filter,Form16->Words[0]);//Установка размеров и Filter->Strings[0-3]
	SetFilter(Form1);//Запись параметров из Form1
	ShowInformation(Form16,Filter);//Показ параметров на Form16
	GroupBox2->Enabled=true;Image2->Visible=true;Image3->Visible=true;Button1->Enabled=false;
	Image2->Enabled=false;Image2->Picture->LoadFromFile("Soft/Buttons/Apply(not color).png");
	FilterMode="Adding";
	Edit1->Text="";Edit1->SetFocus();ListBox1->ItemIndex=-1;
  }
  Form16->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm16::FormClose(TObject *Sender, TCloseAction &Action)
{
  delete ListOfFilters,Filter;ListOfFilters=NULL;Filter=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm16::PopupMenu1Popup(TObject *Sender)
{
  if(ListBox1->Count==0 || ListBox1->ItemIndex==-1)
	  {EditFilter->Enabled=false;DeleteFilter->Enabled=false;FavouriteFilter->Enabled=false;}
  else
	  {EditFilter->Enabled=true;DeleteFilter->Enabled=true;
	   if(FilterMode!="Editing")FavouriteFilter->Enabled=true;
	   else FavouriteFilter->Enabled=false;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm16::AddFilterClick(TObject *Sender)
{
  GroupBox2->Enabled=true;Image2->Visible=true;Image3->Visible=true;Button1->Enabled=false;
  Image2->Enabled=false;Image2->Picture->LoadFromFile("Soft/Buttons/Apply(not color).png");
  DefaultOptions();
  Edit1->SetFocus();
  FilterMode="Adding";
  ListBox1->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TForm16::EditFilterClick(TObject *Sender)
{
  GroupBox2->Enabled=true;Image2->Visible=true;Image3->Visible=true;Button1->Enabled=false;
  FilterMode="Editing";
}
//---------------------------------------------------------------------------

void __fastcall TForm16::DeleteFilterClick(TObject *Sender)
{
  if(MessageDlg(Words[2],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
	 {
	   GroupBox2->Enabled=false;Image2->Visible=false;Image3->Visible=false;
	   FilterMode="";
	   FavoriteFilter="-";Image4->Hint=Words[6]+": -";
	   ListOfFilters->Delete(ListBox1->ItemIndex);
	   if(ListBox1->Items->Strings[ListBox1->ItemIndex]==Form1->MLastFilter->Hint)Form1->MLastFilter->Enabled=false;
	   AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];AccessToForbiddenChar(name);//Перевод : -> _,« -> [,» -> ]
	   DeleteFile("Filters/"+name+".dat");
	   ShowFilters();
	   ApplyButtonEnabled();
	   DefaultOptions();
	   FiltersQuantity->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm16::FavouriteFilterClick(TObject *Sender)
{
  FavoriteFilter=ListBox1->Items->Strings[ListBox1->ItemIndex];
  Image4->Hint=Words[6]+": "+FavoriteFilter;
  MessageDlg(Words[7],mtInformation,TMsgDlgButtons()<<mbOK,0);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Image4Click(TObject *Sender)
{
  if(ListBox1->Count!=0)
	 if(FavoriteFilter!="-")
	   {ListBox1->ItemIndex=ListBox1->Items->IndexOf(FavoriteFilter);ListBox1->SetFocus();ListBox1Click(Sender);}
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ListBox1Click(TObject *Sender)
{
  if(ListBox1->ItemIndex!=-1)
  {
	 if(FilterMode=="Adding" || FilterMode=="Editing")
	 {
	   AnsiString title=AddFilter->Caption+"?";
	   if(FilterMode=="Adding" && MessageDlg(title,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
		{
		 if(Image2->Enabled)
		   {
			if(ListOfFilters->IndexOf(Edit1->Text)>=0)
			   {ShowMessage(Words[4]);return;}//Words[4]="Фильтр с таким названием уже есть!"
			else
			   Image2Click(Sender);
		   }
		 else {ShowMessage(Words[5]);return;}//Words[5]="Настройте все параметры!"
		}
	 if(FilterMode=="Editing" && MessageDlg(Words[1],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
		{
		 if(Image2->Enabled)
		   {
			if(Edit1->Text!=LastName && ListOfFilters->IndexOf(Edit1->Text)>=0)
			   {ShowMessage(Words[4]);ListBox1->ItemIndex=ListBox1->Items->IndexOf(LastName);return;}//Words[4]="Фильтр с таким названием уже есть!"
			else
			  if(Edit1->Text==LastName || ListOfFilters->IndexOf(Edit1->Text)==-1)
				 Image2Click(Sender);
		   }
		 else {ShowMessage(Words[5]);ListBox1->ItemIndex=ListBox1->Items->IndexOf(LastName);return;}
		}
	 }
	 if(FilterMode!="Adding")LastName=ListBox1->Items->Strings[ListBox1->ItemIndex];
	 AnsiString name="Filters/"+ListBox1->Items->Strings[ListBox1->ItemIndex]+".dat";
	 AccessToForbiddenChar(name);//Перевод : -> _,« -> [,» -> ]
	 GroupBox2->Enabled=false;Image2->Visible=false;Image3->Visible=false;Button1->Enabled=true;
	 Edit1->Text=ListBox1->Items->Strings[ListBox1->ItemIndex];
	 //Для установки параметров фильтра(отключение в SetOptions условия &&Filter->Strings[0]!="1")
	 Filter->LoadFromFile(name);
	 SetRadioButtons(Filter);
	 for(int i=0; i<4;i++)Filter->Strings[i]="0";
	 SetOptions(Form16,Filter,Form16->Words[0]);
	 //-------------------------------------------
	 Filter->LoadFromFile(name);
	 FilterMode="";
	 ShowInformation(Form16,Filter);
	 FiltersQuantity->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect,
		  TOwnerDrawState State)
{
  TCanvas *pCanvas = ((TListBox *)Control)->Canvas;
  if(State.Contains(odSelected))
	 pCanvas->Brush->Color =(TColor)RGB(255,153,0);
  pCanvas->FillRect(Rect);
  pCanvas->TextOut(Rect.Left , Rect.Top, ((TListBox *)Control)->Items->Strings[Index]);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ListBox1DblClick(TObject *Sender)
{
  if(ListBox1->ItemIndex!=-1)Button1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==VK_RETURN && ListBox1->ItemIndex!=-1 && FilterMode=="") Button1->Click();
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Button1Click(TObject *Sender)
{
  Form1->MLastFilter->Enabled=true;Form1->MLastFilter->Hint=ListBox1->Items->Strings[ListBox1->ItemIndex];//Применить последний фильтр
  for(int i=0; i<4;i++)Mode[i]=Filter->Strings[i];//Для передачи режимов для Form1->sortmode
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];AccessToForbiddenChar(name);//Перевод : -> _,« -> [,» -> ]
  //Для установки параметров фильтра(отключение в SetOptions условия &&Filter->Strings[0]!="1")
  for(int i=0; i<4;i++)Filter->Strings[i]="0";
  SetOptions(Form1,Filter,Words[0]);
  Filter->LoadFromFile("Filters/"+name+".dat");
  //----
  SetOptions(Form1,Filter,Words[0]);
  ShowInformation(Form1,Filter);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::GetSortMode(TStringList *List)
{
  for(int i=0; i<4;i++)List->Strings[i]=Mode[i];
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Image1Click(TObject *Sender)
{
   SetRadioButtons(Filter);
   Form10->Position=poScreenCenter;
   if (Form10->ShowModal()==mrCancel)
	return;
   SetOptions(Form16,Filter,Form16->Words[0]);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Image2Click(TObject *Sender)
{
   if(FilterMode=="Adding" && Image2->Enabled)
   {
	  if(ListOfFilters->IndexOf(Edit1->Text)>=0)
	   {ShowMessage(Words[4]);return;}//Words[4]="Фильтр с таким названием уже есть!"
	  else
		{
		  ListOfFilters->Add(Edit1->Text);
		  SetFilter(Form16);
		  AnsiString name=Edit1->Text;AccessToForbiddenChar(name);//Перевод : -> _,« -> [,» -> ]
		  Filter->SaveToFile("Filters/"+name+".dat");
		  ShowFilters();
		  FilterMode="";
		  GroupBox2->Enabled=false;Image2->Visible=false;Image3->Visible=false;Button1->Enabled=true;
		  ListBox1->ItemIndex=ListBox1->Items->IndexOf(Edit1->Text);ListBox1->SetFocus();ListBox1Click(Sender);
		  for(int i=1;i<=4;i++)((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->ClearSelection();
		  FiltersQuantity->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
		}
   }
   if(FilterMode=="Editing" && Image2->Enabled)
   {
	  if(Edit1->Text!=LastName && ListOfFilters->IndexOf(Edit1->Text)>=0)//LastName-ListBox1->Items->Strings[ListBox1->ItemIndex]
		 {ShowMessage(Words[4]);return;}//Words[4]="Фильтр с таким названием уже есть!"
	  else
		 if(Edit1->Text==LastName || ListOfFilters->IndexOf(Edit1->Text)==-1)
		 {
		   ListOfFilters->Strings[ListBox1->Items->IndexOf(LastName)]=Edit1->Text;//ListBox1->ItemIndex
		   AnsiString OldName="Filters/"+LastName+".dat",NewName="Filters/"+Edit1->Text+".dat";
		   AccessToForbiddenChar(OldName);AccessToForbiddenChar(NewName);//Перевод : -> _,« -> [,» -> ]
		   RenameFile(OldName,NewName);
		   SetFilter(Form16);
		   Filter->SaveToFile(NewName);
		   ShowFilters();
		   FilterMode="";
		   if(LastName==FavoriteFilter && FavoriteFilter!=Edit1->Text)
			 {FavoriteFilter=Edit1->Text;Image4->Hint=Words[6]+": "+FavoriteFilter;}
		   GroupBox2->Enabled=false;Image2->Visible=false;Image3->Visible=false;Button1->Enabled=true;
		   if(LastName==Form1->MLastFilter->Hint)Form1->MLastFilter->Hint=Edit1->Text;
		   ListBox1->ItemIndex=ListBox1->Items->IndexOf(Edit1->Text);ListBox1->SetFocus();ListBox1Click(Sender);
		   for(int i=1;i<=4;i++)((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->ClearSelection();
		   FiltersQuantity->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
		 }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Image3Click(TObject *Sender)
{
  FilterMode="";
  GroupBox2->Enabled=false;Image2->Visible=false;Image3->Visible=false;
  ListBox1->SetFocus();ListBox1Click(Sender);
  for(int i=1;i<=4;i++)((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->ClearSelection();
}
//---------------------------------------------------------------------------

void __fastcall TForm16::Edit1KeyPress(TObject *Sender, wchar_t &Key)
{
  AnsiString ForbiddenChars = "\\/*<>|?",buffer=Clipboard()->AsText;
  if(ForbiddenChars.Pos(Key)||Key=='"')
	 {Key=0;Beep();}
  if (Key == 0x16)
	{
	 for(int i=0;i<buffer.Length();i++)
	   if(ForbiddenChars.Pos(buffer.c_str()[i])||buffer.c_str()[i]=='"')
		 {Key=0;Beep();ShowMessage(Words[3]);return;}//Words[3]-"Имя содержит недопустимые символы!(\\/*<>|?)"
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm16::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==char(89) && Shift.Contains(ssCtrl))Image2Click(Sender);
  if(Key==char(78) && Shift.Contains(ssCtrl))Image3Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox3Change(TObject *Sender)
{
  if(Filter->Strings[2]=="3"&&ComboBox3->Text!=""&&ComboBox7->Text!=""&&!ComboBox3->Text.Pos('~')&&!ComboBox7->Text.Pos('~'))
   if(StrToInt(ComboBox3->Text)>StrToInt(ComboBox7->Text))
	 if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0)
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox7Change(TObject *Sender)
{
  if(Filter->Strings[2]=="3"&&ComboBox3->Text!=""&&ComboBox7->Text!=""&&!ComboBox3->Text.Pos('~')&&!ComboBox7->Text.Pos('~'))
   if(StrToInt(ComboBox3->Text)>StrToInt(ComboBox7->Text))
	 if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0)
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox3Exit(TObject *Sender)
{
  if(ComboBox3->Items->IndexOf(ComboBox3->Text)<0&&Filter->Strings[2]=="3"
   &&ComboBox3->Text!=""&&!ComboBox3->Text.Pos('~'))
	 {if(ComboBox7->Items->IndexOf(ComboBox7->Text)>=0&&ComboBox7->Text!="")
		 ComboBox3->ItemIndex=ComboBox7->ItemIndex;
	  else
		 ComboBox3->ItemIndex=0;}
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox7Exit(TObject *Sender)
{
  if(ComboBox7->Items->IndexOf(ComboBox7->Text)<0&&Filter->Strings[2]=="3"
   &&ComboBox7->Text!=""&&!ComboBox7->Text.Pos('~'))
	 {if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0&&ComboBox3->Text!="")
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;
	  else
		 ComboBox7->ItemIndex=0;}
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox4Change(TObject *Sender)
{
  AnsiString numbercb4=ExpressionNumberFromString(ComboBox4);
   if(Filter->Strings[3]=="3"&&ComboBox4->Text!=""&&ComboBox8->Text!=""&&!ComboBox4->Text.Pos('~')&&!ComboBox8->Text.Pos('~'))
	   {int numbercb8=StrToInt(ExpressionNumberFromString(ComboBox8));
		if(StrToInt(numbercb4)>numbercb8)
		  if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0)
			 ComboBox8->ItemIndex=ComboBox4->ItemIndex;}
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox8Change(TObject *Sender)
{
  AnsiString numbercb8=ExpressionNumberFromString(ComboBox8);
   if(Filter->Strings[3]=="3"&&ComboBox4->Text!=""&&ComboBox8->Text!=""&&!ComboBox4->Text.Pos('~')&&!ComboBox8->Text.Pos('~'))
	   {int numbercb4=StrToInt(ExpressionNumberFromString(ComboBox4));
		if(StrToInt(numbercb4)>numbercb8)
		  if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0)
			 ComboBox8->ItemIndex=ComboBox4->ItemIndex;}
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox4Exit(TObject *Sender)
{
  if(ComboBox4->Items->IndexOf(ComboBox4->Text)<0&&Filter->Strings[3]=="3"
   &&ComboBox4->Text!=""&&!ComboBox4->Text.Pos('~'))
	 {if(ComboBox8->Items->IndexOf(ComboBox8->Text)>=0&&ComboBox8->Text!="")
		 ComboBox4->ItemIndex=ComboBox8->ItemIndex;
	  else
		 ComboBox4->ItemIndex=0;}
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox8Exit(TObject *Sender)
{
  if(ComboBox8->Items->IndexOf(ComboBox8->Text)<0&&Filter->Strings[3]=="3"
   &&ComboBox8->Text!=""&&!ComboBox8->Text.Pos('~'))
	 {if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0&&ComboBox4->Text!="")
		 ComboBox8->ItemIndex=ComboBox4->ItemIndex;
	  else
		 ComboBox8->ItemIndex=0;}
  VerifyEnteredData(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm16::ComboBox4KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key!=VK_BACK)
   {AnsiString numbercb4=ExpressionNumberFromString(ComboBox4);
   ComboBox4->Text=numbercb4+WordMinute;}
}
//---------------------------------------------------------------------------

void __fastcall TForm16::ComboBox8KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key!=VK_BACK)
   {AnsiString numbercb8=ExpressionNumberFromString(ComboBox8);
   ComboBox8->Text=numbercb8+WordMinute;}
}
//---------------------------------------------------------------------------


//Не нужно-------------------------------------------------------------------
/*bool ExistenceCheckedElements(TCheckListBox *CLB)
{
   bool null=true;
   for(int i=0;i<CLB->Count;i++)
		if(CLB->Checked[i]==true)
		   {null=false;return true;}
   return false;
}*/
//---------------------------------------------------------------------------

/*Shadow->BorderStyle = bsNone;
  Shadow->AlphaBlend=true;
  Shadow->AlphaBlendValue=20;
  Shadow->Color=clBlack;
  Shadow->Show();
  Shadow->BringToFront();
  Shadow->Left=Form16->Left+GroupBox2->Left+3;Shadow->Top=Form16->Top+GroupBox2->Top+25;//GroupBox2->Left=321;GroupBox2->Top=8;
  Shadow->Width=GroupBox2->Width;Shadow->Height=GroupBox2->Height;
*/



