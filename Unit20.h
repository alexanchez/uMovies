//---------------------------------------------------------------------------

#ifndef Unit20H
#define Unit20H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TForm20 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Country;
	TImage *FrameImage;
	TLabel *Genre;
	TImage *Image1;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TMemo *Memo1;
	TLabel *OrigName;
	TPanel *Panel1;
	TImage *Image2;
	TImage *Star1;
	TImage *Star2;
	TImage *Star3;
	TImage *Star4;
	TImage *Star5;
	TLabel *Time;
	TLabel *Year;
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm20(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm20 *Form20;
//---------------------------------------------------------------------------
#endif
