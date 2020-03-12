//---------------------------------------------------------------------------

#ifndef Unit4H
#define Unit4H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit1;
        TPopupMenu *PopupMenu1;
        TMenuItem *PAdd;
        TMenuItem *PDelete;
        TMenuItem *PEdit;
        TImage *Image1;
        TPopupMenu *PopupMenu2;
        TMenuItem *PCancel;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListBox1DblClick(TObject *Sender);
        void __fastcall PAddClick(TObject *Sender);
        void __fastcall Edit1KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PDeleteClick(TObject *Sender);
        void __fastcall PEditClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PCancelClick(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ListBox1Click(TObject *Sender);

private:	// User declarations
     AnsiString savechange,youresure,enterforadd,enterforchange;
public:		// User declarations
      void __fastcall SetLang(AnsiString AAdd,AnsiString AChange,AnsiString ASave,AnsiString ASure)
       {
         enterforadd=AAdd;enterforchange=AChange;savechange=ASave;youresure=ASure;
       };
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
