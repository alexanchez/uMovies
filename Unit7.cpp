//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
#include "Unit10.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;bool Form7_CheckedCLB=true,Stars_check;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
		: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm7::EditChange(TObject *Sender)
{
   TEdit* edit=dynamic_cast<TEdit*>(Sender);
   AnsiString a=edit->Hint;
   if(a=="1")
     {if(((TEdit*)FindComponent("Edit"+a))->Text!="")
       ((TCheckBox*)FindComponent("CheckBox"+a))->Checked=true;
     else
       ((TCheckBox*)FindComponent("CheckBox"+a))->Checked=false;}
   else
     {if(((TEdit*)FindComponent("Edit"+IntToStr(StrToInt(a)-6)))->Text!="")
       ((TCheckBox*)FindComponent("CheckBox"+a))->Checked=true;
      else
       ((TCheckBox*)FindComponent("CheckBox"+a))->Checked=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBoxChange(TObject *Sender)
{
   TComboBox* combobox=dynamic_cast<TComboBox*>(Sender);
   AnsiString a=combobox->Hint;
   if(((TComboBox*)FindComponent("ComboBox"+IntToStr(StrToInt(a)-1)))->Text!="")
	 ((TCheckBox*)FindComponent("CheckBox"+a))->Checked=true;
   else
	 ((TCheckBox*)FindComponent("CheckBox"+a))->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::CheckListBoxMouseEnter(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  if(current->Hint=="0")
  {
	switch(current->Tag)
	{
	case 1:if(CheckListBox1->Height==26){CheckListBox1->Height=169;CheckListBox1->Width=473;CheckListBox1->Columns=3;}break;
	case 2:if(CheckListBox2->Height==26){CheckListBox2->Height=186;CheckListBox2->Width=459;CheckListBox2->Columns=3;}break;
	case 3:if(CheckListBox3->Height==26){CheckListBox3->Height=90;CheckListBox3->Width=465;CheckListBox3->Columns=7;}break;
	case 4:if(CheckListBox4->Height==26){CheckListBox4->Height=90;CheckListBox4->Width=465;CheckListBox4->Columns=5;}break;
	}
	current->SetFocus();
  }
  current->Hint=AnsiString(current->Hint.ToInt()+1);//++
}
//-----------------------------------------------------------------------------------------

void __fastcall TForm7::CheckListBoxMouseLeave(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  if(current->Hint=="3")
  {
	current->Height=26;current->Width=146;current->Columns=0;
	current->Hint="0";
	DefocusControl(current,false);
  }
  if(current->Hint=="1")current->Hint=AnsiString(current->Hint.ToInt()+1);//++
}
//-----------------------------------------------------------------------------------------

void __fastcall TForm7::CheckListBoxClick(TObject *Sender)
{
  TCheckListBox * current = static_cast<TCheckListBox*>(Sender);
  if(Form7_CheckedCLB==true)
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
  Form7_CheckedCLB=true;

  bool k=false;
  for(int i=0;i<current->Count;i++)
	if(current->Checked[i])
	  {k=true;break;}
  if(k==true)((TCheckBox*)FindComponent("CheckBox"+IntToStr(current->Tag+1)))->Checked=true;
  else ((TCheckBox*)FindComponent("CheckBox"+IntToStr(current->Tag+1)))->Checked=false;
}
//-----------------------------------------------------------------------------------------
void __fastcall TForm7::CheckListBoxClickCheck(TObject *Sender)
{
  Form7_CheckedCLB=false;
}
//-------------------------------------------------------------------------------------------

void __fastcall TForm7::FormCreate(TObject *Sender)
{
   for(int i=1;i<=6;i++)
	 if(i!=3&&i!=4)
	   ((TComboBox*)FindComponent("ComboBox"+IntToStr(i)))->OnChange=ComboBoxChange;
   for(int i=1;i<=7;i++)
   ((TEdit*)FindComponent("Edit"+IntToStr(i)))->OnChange=EditChange;
   for(int i=1;i<=4;i++)
	 {
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClick=CheckListBoxClick;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClickCheck=CheckListBoxClick;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnMouseEnter=CheckListBoxMouseEnter;
	 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnMouseLeave=CheckListBoxMouseLeave;
	 }
   for (int i=1;i<=5;i++)
	{
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnMouseEnter=StarsMouseEnter;
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnMouseLeave=StarsMouseLeave;
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnMouseMove=StarsMouseMove;
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->OnClick=StarsClick;
	}
   DateTimePicker1->Date=TDateTime::CurrentDate()-366;
   DateTimePicker2->Date=TDateTime::CurrentDate();
   DateTimePicker1->MaxDate=Now().CurrentDate();
   DateTimePicker2->MaxDate=Now().CurrentDate();
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormShow(TObject *Sender)
{
   Image1->Picture->LoadFromFile("Soft/Backgrounds/Background 7.jpg");
   Image2->Picture->LoadFromFile("Soft/Buttons/Button Refresh.png");
   Image3->Picture->LoadFromFile("Soft/Buttons/Optionsort.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::FormClose(TObject *Sender, TCloseAction &Action)
{
  Image1->Picture->Assign(NULL);Image2->Picture->Assign(NULL);Image3->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

void EnabledSeasonsSeries(bool b)
{
  Form7->CheckBox12->Enabled=b;Form7->CheckBox13->Enabled=b;
  Form7->Edit6->Enabled=b;Form7->Edit7->Enabled=b;
}
//---------------------------------------------------------------------------

void UncheckFlags(TCheckListBox *CLB)
{
   for(int i=0;i<CLB->Count;i++)
		if(CLB->Checked[i]==true)
		   CLB->Checked[i]=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::RadioButton1Click(TObject *Sender)
{
  EnabledSeasonsSeries(true);        
}
//---------------------------------------------------------------------------

void __fastcall TForm7::RadioButton2Click(TObject *Sender)
{
  EnabledSeasonsSeries(false);
}
//---------------------------------------------------------------------------

void __fastcall TForm7::RadioButton3Click(TObject *Sender)
{
  EnabledSeasonsSeries(true);        
}
//---------------------------------------------------------------------------

void __fastcall TForm7::RadioButton4Click(TObject *Sender)
{
  EnabledSeasonsSeries(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image2MouseEnter(TObject *Sender)
{
  Image2->Picture->LoadFromFile("Soft/Buttons/Button Refresh(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image2MouseLeave(TObject *Sender)
{
  Image2->Picture->LoadFromFile("Soft/Buttons/Button Refresh.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image3MouseEnter(TObject *Sender)
{
  Image3->Picture->LoadFromFile("Soft/Buttons/Optionsort(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image3MouseLeave(TObject *Sender)
{
  Image3->Picture->LoadFromFile("Soft/Buttons/Optionsort.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image2Click(TObject *Sender)
{
   for(int i=1;i<=15;i++)
	  ((TCheckBox*)FindComponent("CheckBox"+IntToStr(i)))->Checked=false;
   for(int i=1;i<=7;i++)
	  ((TEdit*)FindComponent("Edit"+IntToStr(i)))->Text="";
   for(int i=1;i<=8;i++)
	  ((TComboBox*)FindComponent("ComboBox"+IntToStr(i)))->Text="";
   for(int i=1;i<=4;i++)
	for(int j=0;j<((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->Count;j++)
	 if(((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->Checked[j]==true)
		((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->Checked[j]=false;
   for (int i=1;i<=5;i++)
	((TImage*)FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
   Rating->Caption="0.0";
   RadioButton1->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image3Click(TObject *Sender)
{
   if(searchmode->Strings[0]=="1")Form10->RadioButton1->Checked=true;
   if(searchmode->Strings[0]=="2")Form10->RadioButton2->Checked=true;
   if(searchmode->Strings[0]=="3")Form10->RadioButton3->Checked=true;
   if(searchmode->Strings[1]=="1")Form10->RadioButton4->Checked=true;
   if(searchmode->Strings[1]=="2")Form10->RadioButton5->Checked=true;
   if(searchmode->Strings[1]=="3")Form10->RadioButton6->Checked=true;
   if(searchmode->Strings[2]=="1")Form10->RadioButton7->Checked=true;
   if(searchmode->Strings[2]=="2")Form10->RadioButton8->Checked=true;
   if(searchmode->Strings[2]=="3")Form10->RadioButton9->Checked=true;
   if(searchmode->Strings[3]=="1")Form10->RadioButton10->Checked=true;
   if(searchmode->Strings[3]=="2")Form10->RadioButton11->Checked=true;
   if(searchmode->Strings[3]=="3")Form10->RadioButton12->Checked=true;
   Form10->Position=poScreenCenter;
   if (Form10->ShowModal()==mrCancel)
	return;
   if(Form10->RadioButton1->Checked==true&&searchmode->Strings[0]!="1"){searchmode->Strings[0]="1";ComboBox1->Visible=true;CheckListBox1->Visible=false;}
   if(Form10->RadioButton2->Checked==true&&searchmode->Strings[0]!="2"){searchmode->Strings[0]="2";ComboBox1->Visible=false;CheckListBox1->Visible=true;
	  UncheckFlags(CheckListBox1);}
   if(Form10->RadioButton3->Checked==true&&searchmode->Strings[0]!="3"){searchmode->Strings[0]="3";ComboBox1->Visible=false;CheckListBox1->Visible=true;
	  UncheckFlags(CheckListBox1);}
   if(Form10->RadioButton4->Checked==true&&searchmode->Strings[1]!="1"){searchmode->Strings[1]="1";ComboBox2->Visible=true;CheckListBox2->Visible=false;}
   if(Form10->RadioButton5->Checked==true&&searchmode->Strings[1]!="2"){searchmode->Strings[1]="2";ComboBox2->Visible=false;CheckListBox2->Visible=true;
	  UncheckFlags(CheckListBox2);}
   if(Form10->RadioButton6->Checked==true&&searchmode->Strings[1]!="3"){searchmode->Strings[1]="3";ComboBox2->Visible=false;CheckListBox2->Visible=true;
	  UncheckFlags(CheckListBox2);}
   if(Form10->RadioButton7->Checked==true&&searchmode->Strings[2]!="1"){searchmode->Strings[2]="1";ComboBox3->Visible=true;ComboBox7->Visible=false;
	  CheckListBox3->Visible=false;ComboBox3->Width=146;if(ComboBox3->Items->Strings[0]=="~")ComboBox3->Items->Delete(0);}
   if(Form10->RadioButton8->Checked==true&&searchmode->Strings[2]!="2"){searchmode->Strings[2]="2";ComboBox3->Visible=false;ComboBox7->Visible=false;CheckListBox3->Visible=true;
	  UncheckFlags(CheckListBox3);}
   if(Form10->RadioButton9->Checked==true&&searchmode->Strings[2]!="3"){searchmode->Strings[2]="3";ComboBox3->Visible=true;ComboBox7->Visible=true;ComboBox7->Text="";
	  CheckListBox3->Visible=false;ComboBox3->Width=74;if(ComboBox3->Items->Strings[0]!="~")ComboBox3->Items->Insert(0,"~");}
   if(Form10->RadioButton10->Checked==true&&searchmode->Strings[3]!="1"){searchmode->Strings[3]="1";ComboBox4->Visible=true;ComboBox8->Visible=false;
	  CheckListBox4->Visible=false;ComboBox4->Width=146;if(ComboBox4->Items->Strings[0]=="~")ComboBox4->Items->Delete(0);}
   if(Form10->RadioButton11->Checked==true&&searchmode->Strings[3]!="2"){searchmode->Strings[3]="2";ComboBox4->Visible=false;ComboBox8->Visible=false;CheckListBox4->Visible=true;
	  UncheckFlags(CheckListBox4);}
   if(Form10->RadioButton12->Checked==true&&searchmode->Strings[3]!="3"){searchmode->Strings[3]="3";ComboBox4->Visible=true;ComboBox8->Visible=true;ComboBox8->Text="";
	  CheckListBox4->Visible=false;ComboBox4->Width=74;if(ComboBox4->Items->Strings[0]!="~")ComboBox4->Items->Insert(0,"~");}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox1KeyPress(TObject *Sender, char &Key)
{
  if (isdigit(Key))Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox3Change(TObject *Sender)
{
  if(searchmode->Strings[2]=="3"&&ComboBox3->Text!=""&&ComboBox7->Text!=""&&!ComboBox3->Text.Pos('~')&&!ComboBox7->Text.Pos('~'))
   if(StrToInt(ComboBox3->Text)>StrToInt(ComboBox7->Text))
	 if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0)
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;

  if(searchmode->Strings[2]!="3"){if(ComboBox3->Text!="") CheckBox4->Checked=true; else CheckBox4->Checked=false;}
  if(searchmode->Strings[2]=="3")
	{if(ComboBox3->Text!=""&&ComboBox7->Text!="")
	   CheckBox4->Checked=true;
	 else
	   CheckBox4->Checked=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox7Change(TObject *Sender)
{
  if(searchmode->Strings[2]=="3"&&ComboBox3->Text!=""&&ComboBox7->Text!=""&&!ComboBox3->Text.Pos('~')&&!ComboBox7->Text.Pos('~'))
   if(StrToInt(ComboBox3->Text)>StrToInt(ComboBox7->Text))
	 if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0)
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;

  if(ComboBox3->Text!=""&&ComboBox7->Text!="")
	 CheckBox4->Checked=true;
  else
	 CheckBox4->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox3Exit(TObject *Sender)
{
  if(ComboBox3->Items->IndexOf(ComboBox3->Text)<0&&searchmode->Strings[2]=="3"
   &&ComboBox3->Text!=""&&!ComboBox3->Text.Pos('~'))
	 {if(ComboBox7->Items->IndexOf(ComboBox7->Text)>=0&&ComboBox7->Text!="")
		 ComboBox3->ItemIndex=ComboBox7->ItemIndex;
	  else
		 ComboBox3->ItemIndex=0;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox7Exit(TObject *Sender)
{
  if(ComboBox7->Items->IndexOf(ComboBox7->Text)<0&&searchmode->Strings[2]=="3"
   &&ComboBox7->Text!=""&&!ComboBox7->Text.Pos('~'))
	 {if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0&&ComboBox3->Text!="")
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;
	  else
		 ComboBox7->ItemIndex=0;}
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

void __fastcall TForm7::ComboBox4KeyUp(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
  if(Key!=VK_BACK)
   {AnsiString numbercb4=ExpressionNumberFromString(ComboBox4);
   ComboBox4->Text=numbercb4+wordminute;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox8KeyUp(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key!=VK_BACK)
   {AnsiString numbercb8=ExpressionNumberFromString(ComboBox8);
   ComboBox8->Text=numbercb8+wordminute;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox4Change(TObject *Sender)
{
   AnsiString numbercb4=ExpressionNumberFromString(ComboBox4);
   if(searchmode->Strings[3]=="3"&&ComboBox4->Text!=""&&ComboBox8->Text!=""&&!ComboBox4->Text.Pos('~')&&!ComboBox8->Text.Pos('~'))
	   {int numbercb8=StrToInt(ExpressionNumberFromString(ComboBox8));
		if(StrToInt(numbercb4)>numbercb8)
		  if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0)
			 ComboBox8->ItemIndex=ComboBox4->ItemIndex;}

   if(searchmode->Strings[3]!="3"){if(ComboBox4->Text!="") CheckBox5->Checked=true; else CheckBox5->Checked=false;}
   if(searchmode->Strings[3]=="3")
	{if(ComboBox4->Text!=""&&ComboBox8->Text!="")
	   CheckBox5->Checked=true;
	 else
	   CheckBox5->Checked=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox8Change(TObject *Sender)
{
   AnsiString numbercb8=ExpressionNumberFromString(ComboBox8);
   if(searchmode->Strings[3]=="3"&&ComboBox4->Text!=""&&ComboBox8->Text!=""&&!ComboBox4->Text.Pos('~')&&!ComboBox8->Text.Pos('~'))
	   {int numbercb4=StrToInt(ExpressionNumberFromString(ComboBox4));
		if(StrToInt(numbercb4)>numbercb8)
		  if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0)
			 ComboBox8->ItemIndex=ComboBox4->ItemIndex;}

   if(ComboBox4->Text!=""&&ComboBox8->Text!="")
	 CheckBox5->Checked=true;
   else
	 CheckBox5->Checked=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox4Exit(TObject *Sender)
{
  if(ComboBox4->Items->IndexOf(ComboBox4->Text)<0&&searchmode->Strings[3]=="3"
   &&ComboBox4->Text!=""&&!ComboBox4->Text.Pos('~'))
	 {if(ComboBox8->Items->IndexOf(ComboBox8->Text)>=0&&ComboBox8->Text!="")
		 ComboBox4->ItemIndex=ComboBox8->ItemIndex;
	  else
		 ComboBox4->ItemIndex=0;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::ComboBox8Exit(TObject *Sender)
{
  if(ComboBox8->Items->IndexOf(ComboBox8->Text)<0&&searchmode->Strings[3]=="3"
   &&ComboBox8->Text!=""&&!ComboBox8->Text.Pos('~'))
	 {if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0&&ComboBox4->Text!="")
		 ComboBox8->ItemIndex=ComboBox4->ItemIndex;
	  else
		 ComboBox8->ItemIndex=0;}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::StarsClick(TObject *Sender)
{
	if(Stars_check==true)
	{Stars_check=false;CheckBox14->Checked=false;
	 for (int i=1;i<=5;i++)
	  {((TImage*)FindComponent("Star"+IntToStr(i)))->Cursor=(TCursor)1;
	   ((TImage*)Form7->FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");}
	}
	else
	{Stars_check=true;CheckBox14->Checked=true;
	 for (int i=1;i<=5;i++)
	  ((TImage*)FindComponent("Star"+IntToStr(i)))->Cursor=(TCursor)2;
	}
}

void __fastcall TForm7::StarsMouseEnter(TObject *Sender)
{
   if(Stars_check==false)
   {
	Stars_check=false;
	for (int i=1;i<=5;i++)
	((TImage*)Form7->FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm7::StarsMouseLeave(TObject *Sender)
{
  if(Stars_check==false)
   {for (int i=1;i<=5;i++)
	((TImage*)Form7->FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
	Rating->Caption="0.0";
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm7::StarsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
  if(Stars_check==false)
  {
	TImage* current=static_cast<TImage*>(Sender);
	if(current->Tag>1)
	 for (int i=1;i<current->Tag;i++)
	  ((TImage*)Form7->FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star.png");
	if(X>=12){current->Picture->LoadFromFile("Soft/Buttons/Star.png");Rating->Caption=IntToStr(current->Tag)+".0";}
	if(X<12 && X>=4) {current->Picture->LoadFromFile("Soft/Buttons/Star_half.png");Rating->Caption=IntToStr(current->Tag-1)+".5";}
	if(X<4) {current->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");Rating->Caption=IntToStr(current->Tag-1)+".0";}
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm7::DateTimePicker1Change(TObject *Sender)
{
   CheckBox15->Checked=true;
   DateTimePicker1->MaxDate=Now().CurrentDate();
   DateTimePicker2->MaxDate=Now().CurrentDate();
}
//---------------------------------------------------------------------------

void __fastcall TForm7::DateTimePicker2Change(TObject *Sender)
{
   CheckBox15->Checked=true;
   DateTimePicker1->MaxDate=Now().CurrentDate();
   DateTimePicker2->MaxDate=Now().CurrentDate();
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image4Click(TObject *Sender)
{
  if(Image4->Tag==1)
  {
	DateTimePicker1->Enabled=false;
	Image4->Picture->LoadFromFile("Soft/Buttons/Disable(light).png");Image4->Tag=0;
  }
  else
  {
	DateTimePicker1->Enabled=true;
	Image4->Picture->LoadFromFile("Soft/Buttons/Enable(light).png");Image4->Tag=1;
  }
  if(Image4->Tag==0 && Image5->Tag==0){Image5->Tag=0;Image5Click(Sender);}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image5Click(TObject *Sender)
{
  if(Image5->Tag==1)
  {
	DateTimePicker2->Enabled=false;
	Image5->Picture->LoadFromFile("Soft/Buttons/Disable(light).png");Image5->Tag=0;
  }
  else
  {
	DateTimePicker2->Enabled=true;
	Image5->Picture->LoadFromFile("Soft/Buttons/Enable(light).png");Image5->Tag=1;
  }
  if(Image4->Tag==0 && Image5->Tag==0){Image4->Tag=0;Image4Click(Sender);}
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image4MouseEnter(TObject *Sender)
{
   if(Image4->Tag==1)Image4->Picture->LoadFromFile("Soft/Buttons/Enable(light).png");
   if(Image4->Tag==0)Image4->Picture->LoadFromFile("Soft/Buttons/Disable(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image4MouseLeave(TObject *Sender)
{
   if(Image4->Tag==1)Image4->Picture->LoadFromFile("Soft/Buttons/Enable.png");
   if(Image4->Tag==0)Image4->Picture->LoadFromFile("Soft/Buttons/Disable.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image5MouseEnter(TObject *Sender)
{
   if(Image5->Tag==1)Image5->Picture->LoadFromFile("Soft/Buttons/Enable(light).png");
   if(Image5->Tag==0)Image5->Picture->LoadFromFile("Soft/Buttons/Disable(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image5MouseLeave(TObject *Sender)
{
   if(Image5->Tag==1)Image5->Picture->LoadFromFile("Soft/Buttons/Enable.png");
   if(Image5->Tag==0)Image5->Picture->LoadFromFile("Soft/Buttons/Disable.png");
}
//---------------------------------------------------------------------------


/*
long x_prev=0;
int ka=0;
void __fastcall TForm7::Timer1Timer(TObject *Sender)
{
  //if(k>=20)
  //{
	long x = Mouse->CursorPos.x-Form7->Left;
	if(x>=259 && Image4->Tag==0)Image4Click(Sender);
	else if(x<259 && Image4->Tag==1)Image4Click(Sender);
  //}
  ka++;
  Caption=ka;
  //Caption="X: "+FloatToStr(x);
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image4MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
  //Image4Click(Sender);Timer1->Enabled=true;
  long x = Mouse->CursorPos.x-Form7->Left;
  if(x>=259 && Image4->Tag==0)Image4Click(Sender);
  else if(x<259 && Image4->Tag==1)Image4Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm7::Image4MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
  Timer1->Enabled=false;
  //if(k>=20)
  //{
	long x = Mouse->CursorPos.x-Form7->Left;
	if(x>=259 && Image4->Tag==0)Image4Click(Sender);
	else if(x<259 && Image4->Tag==1)Image4Click(Sender);
  //}
  ka=0;
}
//---------------------------------------------------------------------------
*/
