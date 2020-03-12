//---------------------------------------------------------------------------

#ifndef Unit16H
#define Unit16H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <pngimage.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm16 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TListBox *ListBox1;
	TGroupBox *GroupBox2;
	TCheckListBox *CheckListBox1;
	TCheckListBox *CheckListBox2;
	TCheckListBox *CheckListBox3;
	TCheckListBox *CheckListBox4;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TComboBox *ComboBox3;
	TComboBox *ComboBox4;
	TComboBox *ComboBox5;
	TComboBox *ComboBox6;
	TComboBox *ComboBox7;
	TComboBox *ComboBox8;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TImage *Image1;
	TPopupMenu *PopupMenu1;
	TMenuItem *AddFilter;
	TMenuItem *EditFilter;
	TMenuItem *DeleteFilter;
	TButton *Button1;
	TButton *Button2;
	TPanel *Panel1;
	TEdit *Edit1;
	TImage *Image2;
	TImage *Image3;
	TLabel *FiltersQuantity;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton4;
	TImage *Image4;
	TMenuItem *FavouriteFilter;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall AddFilterClick(TObject *Sender);
	void __fastcall EditFilterClick(TObject *Sender);
	void __fastcall DeleteFilterClick(TObject *Sender);
	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall ListBox1DblClick(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBox3Change(TObject *Sender);
	void __fastcall ComboBox7Change(TObject *Sender);
	void __fastcall ComboBox8Change(TObject *Sender);
	void __fastcall ComboBox4Change(TObject *Sender);
	void __fastcall ComboBox4Exit(TObject *Sender);
	void __fastcall ComboBox8Exit(TObject *Sender);
	void __fastcall ComboBox3Exit(TObject *Sender);
	void __fastcall ComboBox7Exit(TObject *Sender);
	void __fastcall ComboBox4KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ComboBox8KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FavouriteFilterClick(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);

private:	// User declarations
public:		AnsiString Words[8],WordMinute,FavoriteFilter;
	__fastcall TForm16(TComponent* Owner);
	void __fastcall SetLang(AnsiString _Words[8],AnsiString _WordMinute)
		{
		   for(int i=0;i<8;i++)Words[i]=_Words[i];
		   WordMinute=_WordMinute;
		};
	void __fastcall TForm16::ImageMouseEnter(TObject *Sender);
	void __fastcall TForm16::ImageMouseLeave(TObject *Sender);
	void __fastcall TForm16::CheckListBoxClick(TObject *Sender);
	void __fastcall TForm16::CheckListBoxClickCheck(TObject *Sender);
	void __fastcall TForm16::CheckListBoxMouseEnter(TObject *Sender);
	void __fastcall TForm16::CheckListBoxMouseLeave(TObject *Sender);
	void __fastcall TForm16::VerifyEnteredData(TObject *Sender);
	void __fastcall TForm16::ShowInformation(TForm *Form,TStringList *List);
	void __fastcall GetSortMode(TStringList *List);
	void __fastcall SetFavouriteFilter(AnsiString FavFilter)
	   {
		 FavoriteFilter = FavFilter;
	   };
	AnsiString __fastcall GetFavouriteFilter()
	   {
		 return FavoriteFilter;
	   };
};

//---------------------------------------------------------------------------
extern PACKAGE TForm16 *Form16;
//---------------------------------------------------------------------------
#endif
