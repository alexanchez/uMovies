#include <vcl.h>
#include <CheckLst.hpp>

#include "Unit10.h"
//---------------------------------------------------------------------------

void UncheckFlags(TCheckListBox *CLB)
{
   for(int i=0;i<CLB->Count;i++)
		if(CLB->Checked[i]==true)
		   CLB->Checked[i]=false;
}
//---------------------------------------------------------------------------

void SetRadioButtons(TStringList *List)
{
  if(List->Strings[0]=="1")Form10->RadioButton1->Checked=true;
  if(List->Strings[0]=="2")Form10->RadioButton2->Checked=true;
  if(List->Strings[0]=="3")Form10->RadioButton3->Checked=true;
  if(List->Strings[1]=="1")Form10->RadioButton4->Checked=true;
  if(List->Strings[1]=="2")Form10->RadioButton5->Checked=true;
  if(List->Strings[1]=="3")Form10->RadioButton6->Checked=true;
  if(List->Strings[2]=="1")Form10->RadioButton7->Checked=true;
  if(List->Strings[2]=="2")Form10->RadioButton8->Checked=true;
  if(List->Strings[2]=="3")Form10->RadioButton9->Checked=true;
  if(List->Strings[3]=="1")Form10->RadioButton10->Checked=true;
  if(List->Strings[3]=="2")Form10->RadioButton11->Checked=true;
  if(List->Strings[3]=="3")Form10->RadioButton12->Checked=true;
}
//---------------------------------------------------------------------------

void SetOptions(TForm *Form,TStringList *List,AnsiString All)
{
   TComboBox *CB1=((TComboBox*)Form->FindComponent("ComboBox1")),*CB2=((TComboBox*)Form->FindComponent("ComboBox2")),
			 *CB3=((TComboBox*)Form->FindComponent("ComboBox3")),*CB4=((TComboBox*)Form->FindComponent("ComboBox4")),
			 *CB7=((TComboBox*)Form->FindComponent("ComboBox7")),*CB8=((TComboBox*)Form->FindComponent("ComboBox8"));
   TCheckListBox *CLB1=((TCheckListBox*)Form->FindComponent("CheckListBox1")),*CLB2=((TCheckListBox*)Form->FindComponent("CheckListBox2")),
				 *CLB3=((TCheckListBox*)Form->FindComponent("CheckListBox3")),*CLB4=((TCheckListBox*)Form->FindComponent("CheckListBox4"));

   if(Form10->RadioButton1->Checked==true && List->Strings[0]!="1"){List->Strings[0]="1";CB1->Visible=true;CLB1->Visible=false;CB1->ItemIndex=0;}
   if(Form10->RadioButton2->Checked==true && List->Strings[0]!="2"){List->Strings[0]="2";CB1->Visible=false;CLB1->Visible=true;
	  UncheckFlags(CLB1);}
   if(Form10->RadioButton3->Checked==true && List->Strings[0]!="3"){List->Strings[0]="3";CB1->Visible=false;CLB1->Visible=true;
	  UncheckFlags(CLB1);}
   if(Form10->RadioButton4->Checked==true && List->Strings[1]!="1"){List->Strings[1]="1";CB2->Visible=true;CLB2->Visible=false;CB2->ItemIndex=0;}
   if(Form10->RadioButton5->Checked==true && List->Strings[1]!="2"){List->Strings[1]="2";CB2->Visible=false;CLB2->Visible=true;
	  UncheckFlags(CLB2);}
   if(Form10->RadioButton6->Checked==true && List->Strings[1]!="3"){List->Strings[1]="3";CB2->Visible=false;CLB2->Visible=true;
	  UncheckFlags(CLB2);}

   if(Form10->RadioButton7->Checked==true && List->Strings[2]!="1"){List->Strings[2]="1";CB3->Visible=true;CB7->Visible=false;
	  CLB3->Visible=false;CB3->Width=154;CB3->Items->Strings[0]=All;CB3->ItemIndex=0;}
   if(Form10->RadioButton8->Checked==true && List->Strings[2]!="2"){List->Strings[2]="2";CB3->Visible=false;CB7->Visible=false;
	  CLB3->Visible=true;UncheckFlags(CLB3);}
   if(Form10->RadioButton9->Checked==true && List->Strings[2]!="3"){List->Strings[2]="3";CB3->Visible=true;CB7->Visible=true;
	  CLB3->Visible=false;CB3->Width=77;CB3->Items->Strings[0]="~";CB3->ItemIndex=0;CB7->ItemIndex=0;}

   if(Form10->RadioButton10->Checked==true && List->Strings[3]!="1"){List->Strings[3]="1";CB4->Visible=true;CB8->Visible=false;
	  CLB4->Visible=false;CB4->Width=154;CB4->Items->Strings[0]=All;CB4->ItemIndex=0;}
   if(Form10->RadioButton11->Checked==true && List->Strings[3]!="2"){List->Strings[3]="2";CB4->Visible=false;CB8->Visible=false;
	  CLB4->Visible=true;UncheckFlags(CLB4);}
   if(Form10->RadioButton12->Checked==true && List->Strings[3]!="3"){List->Strings[3]="3";CB4->Visible=true;CB8->Visible=true;
	  CLB4->Visible=false;CB4->Width=77;CB4->Items->Strings[0]="~";CB4->ItemIndex=0;CB8->ItemIndex=0;}
}
