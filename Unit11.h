//---------------------------------------------------------------------------

#ifndef Unit11H
#define Unit11H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ZipForge.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm11 : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *ProgressBar1;
	TTimer *Timer1;
	TZipForge *ZipForge1;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		AnsiString CatalogSaving,CatalogClosing;
	 void SetCaptions(AnsiString _CatalogSaving,AnsiString _CatalogClosing)
	 {
		CatalogSaving=_CatalogSaving;CatalogClosing=_CatalogClosing;
     }
	__fastcall TForm11(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm11 *Form11;
//---------------------------------------------------------------------------
#endif
