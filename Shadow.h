//---------------------------------------------------------------------------

#ifndef ShadowH
#define ShadowH

#include <vcl.h>

  class CShadowClass
  {
  public:
	 CShadowClass(TForm *Form);//TForm form
	 ~CShadowClass();
	 void SetComponents(TImage *Pic);
	 void ShowPicture(TImage *Pic);
	 void SetSizes();
	 bool CheckVisible();
	 void ResetVisible();

  protected:
	 void ResetControls();
	 void __fastcall ShadowFormShow(TObject *Sender);
	 void __fastcall ShadowFormClick(TObject *Sender);
	 void __fastcall ShadowFormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	 void __fastcall OnTimer(TObject *Sender);

	 TImage *image;
	 TTimer *timer;
	 TForm *Parent_Form;
	 TForm *shadow_form,*image_form;
	 bool visible;
  };
//---------------------------------------------------------------------------
#endif
