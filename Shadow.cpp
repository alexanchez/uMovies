//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Shadow.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

// ========================================================== CShadowClass ========================================================================

// public:
//---------------------------------------------------------------------------
CShadowClass::CShadowClass(TForm *Form) : image(NULL),timer(NULL)
{
		visible=false;
		Parent_Form=Form;
}

//---------------------------------------------------------------------------

CShadowClass::~CShadowClass()
{
   delete image,timer,image_form,shadow_form;timer=NULL;image=NULL;image_form=NULL;shadow_form=NULL;
}
//---------------------------------------------------------------------------

void CShadowClass::SetComponents(TImage *Pic)
{
   Screen->Cursors[3] = LoadCursorFromFile("Soft/Cursors/Cursor_select.cur");
   shadow_form=new TForm(Parent_Form);
   shadow_form->BorderStyle = bsNone;
   shadow_form->AlphaBlend=true;
   shadow_form->Color=clBlack;
   shadow_form->Cursor=(TCursor)3;
   shadow_form->OnClick=ShadowFormClick;
   shadow_form->OnMouseDown=ShadowFormMouseDown;
   shadow_form->OnShow=ShadowFormShow;

   timer = new TTimer(shadow_form);
   timer->Enabled = false;
   timer->Interval = 50;
   timer->OnTimer = OnTimer;

   image_form=new TForm(Parent_Form);
   image_form->BorderStyle = bsNone;
   image_form->AlphaBlend=true;
   image_form->Color=clBtnFace;
   image_form->TransparentColor=true;image_form->TransparentColorValue=clBtnFace;
   image_form->DoubleBuffered=true;

   image = new TImage(image_form);
   image->Parent=image_form;
   image->Center=true;image->Proportional=true;
   image->Stretch=true;
   image->Cursor=(TCursor)3;
   image->Picture=Pic->Picture;
   image->OnClick=ShadowFormClick;
}
//---------------------------------------------------------------------------

void CShadowClass::ShowPicture(TImage *Pic)
{
   SetComponents(Pic);
   shadow_form->Show();
   image_form->Show();
   Parent_Form->BringToFront();
   visible=true;
   SetSizes();
}
//---------------------------------------------------------------------------

void CShadowClass::SetSizes()
{
   shadow_form->Top=Parent_Form->Top+50;shadow_form->Left=Parent_Form->Left+8;//+50/+30 - с MainMenu/без MainMenu;
   shadow_form->ClientHeight=Parent_Form->ClientHeight;shadow_form->ClientWidth=Parent_Form->ClientWidth;
   image_form->Top=Parent_Form->Top+50;image_form->Left=Parent_Form->Left+8;
   image_form->ClientHeight=Parent_Form->ClientHeight;image_form->ClientWidth=Parent_Form->ClientWidth;
   image->Width=image_form->Width/1.26086;image->Height=image_form->Height/1.23728;
   image->Left=image_form->Width/9.66666;image->Top=image_form->Height/10.428571;
}
//---------------------------------------------------------------------------

bool CShadowClass::CheckVisible()
{
	if(visible)return true;
	else return false;
}
//---------------------------------------------------------------------------
void CShadowClass::ResetVisible()
{
	visible=false;
}
//---------------------------------------------------------------------------

// protected:
void __fastcall CShadowClass::OnTimer(TObject *Sender)
{
	if(timer->Tag==0)
	 {
	  shadow_form->AlphaBlendValue=shadow_form->AlphaBlendValue+23;
	  image_form->AlphaBlendValue=image_form->AlphaBlendValue+42;
	  if(shadow_form->AlphaBlendValue>=124){timer->Enabled=false;}
	 }
	if(timer->Tag==1)
	 {
	  shadow_form->AlphaBlendValue=shadow_form->AlphaBlendValue-23;
	  image_form->AlphaBlendValue=image_form->AlphaBlendValue-42;
	  if(shadow_form->AlphaBlendValue==0)
	  {
	   timer->Enabled=false;visible=false;
	   shadow_form->Close();image_form->Close();
	   delete image,timer,image_form,shadow_form;timer=NULL;image=NULL;image_form=NULL;shadow_form=NULL;
	  }
	 }
}
//---------------------------------------------------------------------------

void __fastcall CShadowClass::ShadowFormClick(TObject *Sender)
{
	if(timer!=NULL){timer->Tag=1;timer->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall CShadowClass::ShadowFormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	image_form->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall CShadowClass::ShadowFormShow(TObject *Sender)
{
	shadow_form->AlphaBlendValue=0;image_form->AlphaBlendValue=0;timer->Tag=0;timer->Enabled=true;
}
//---------------------------------------------------------------------------

