//---------------------------------------------------------------------------

#ifndef Unit13H
#define Unit13H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <pngimage.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TForm13 : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox1;
	TLabel *Label1;
	TImage *Image1;
	TEdit *Edit1;
	TImage *Image3;
	TButton *Button1;
	TButton *Button2;
	TImage *Image2;
	TEdit *Edit2;
	TImage *Image4;
	TPopupMenu *PopupMenu1;
	TPopupMenu *PopupMenu2;
	TMenuItem *MRemoveSelectionL1;
	TMenuItem *MRemoveSelectionL2;
	TBitBtn *MoveAllMovieRL;
	TBitBtn *MoveMovieRL;
	TBitBtn *MoveMovieLR;
	TBitBtn *MoveAllMovieLR;
	TLabel *Label2;
	TListBox *ListBox2;
	void __fastcall MRemoveSelectionL1Click(TObject *Sender);
	void __fastcall MRemoveSelectionL2Click(TObject *Sender);
	void __fastcall MoveMovieLRClick(TObject *Sender);
	void __fastcall MoveAllMovieLRClick(TObject *Sender);
	void __fastcall MoveMovieRLClick(TObject *Sender);
	void __fastcall MoveAllMovieRLClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit1Change(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Edit1Enter(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit2Change(TObject *Sender);
	void __fastcall Edit2Enter(TObject *Sender);
	void __fastcall Edit2Exit(TObject *Sender);
	void __fastcall ListBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ListBox1MouseLeave(TObject *Sender);
	void __fastcall ListBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall ListBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ListBox2MouseLeave(TObject *Sender);
	void __fastcall ListBox2MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall ListBox2MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ListBox2MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall PopupMenu2Popup(TObject *Sender);
	void __fastcall ListBox1DragOver(TObject *Sender, TObject *Source, int X, int Y,
          TDragState State, bool &Accept);
	void __fastcall ListBox2DragOver(TObject *Sender, TObject *Source, int X, int Y,
          TDragState State, bool &Accept);
	void __fastcall ListBox2DragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall ListBox1DragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall FormCreate(TObject *Sender);
private:	AnsiString search,exit;
public:		int lastindex;
	__fastcall TForm13(TComponent* Owner);
	void __fastcall TForm13::ImageMouseEnter(TObject *Sender);
	void __fastcall TForm13::ImageMouseLeave(TObject *Sender);
	void __fastcall SetLang(AnsiString _search,AnsiString _exit)
		 {
		  search=_search;exit=_exit;
		 };
};
//---------------------------------------------------------------------------
extern PACKAGE TForm13 *Form13;
//---------------------------------------------------------------------------
#endif
