//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Buttons.hpp>
#include <jpeg.hpp>
#include <CheckLst.hpp>
#include <ImgList.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <StdActns.hpp>
#include <clipbrd.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TComboBox *ComboBox1;
        TLabel *Label4;
        TLabel *Label5;
        TComboBox *ComboBox2;
        TMemo *Memo1;
        TImage *Image1;
        TCheckBox *CheckBox1;
        TEdit *Edit2;
        TLabel *Label6;
        TImage *Image2;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TCheckBox *CheckBox2;
        TEdit *Edit3;
        TLabel *Label11;
        TImage *Image3;
        TImage *Image4;
        TCheckListBox *CheckListBox1;
        TImage *Image5;
        TImage *Image6;
        TImage *Image7;
        TLabel *Label12;
        TImage *Image8;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *Edit4;
        TCheckListBox *CheckListBox2;
        TLabel *Label15;
        TLabel *Label17;
        TLabel *Label16;
        TLabel *Label18;
        TLabel *Label19;
        TMemo *Memo2;
        TEdit *Edit5;
        TEdit *Edit6;
        TEdit *Edit7;
        TImage *Image9;
        TImage *Image10;
        TComboBox *ComboBox3;
        TLabel *Label20;
        TEdit *Edit8;
        TLabel *Label21;
	TCheckListBox *CheckListBox3;
	TLabel *Label7;
	TImage *Image11;
	TImage *Star1;
	TImage *Star2;
	TImage *Star3;
	TImage *Star4;
	TImage *Star5;
	TLabel *Rating;
	TImage *Image12;
	TOpenPictureDialog *OpenPictureDialog1;
	TImage *Image13;
        void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall ComboBox2Change(TObject *Sender);
        void __fastcall Image3Click(TObject *Sender);
        void __fastcall Image4Click(TObject *Sender);
        void __fastcall Image5Click(TObject *Sender);
        void __fastcall Image6Click(TObject *Sender);
        void __fastcall Label12Click(TObject *Sender);
        void __fastcall Label12MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label12MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label13Click(TObject *Sender);
        void __fastcall Label13MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Label13MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall Image9Click(TObject *Sender);
        void __fastcall Image10Click(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall ComboBox2Exit(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ComboBox1KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ComboBox3KeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall Image1MouseLeave(TObject *Sender);
	void __fastcall Image11Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Image12Click(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Image13Click(TObject *Sender);
	void __fastcall Label5Click(TObject *Sender);

private:	// User declarations
		AnsiString filmwithnameis,openmode,forbiddenChars,wordminute,AddToFavourite,DeleteFromFavourite;TStringList *films;
public:	   TStringList *seasons;
		__fastcall TForm2(TComponent* Owner);
        void __fastcall SetOpenMode(AnsiString AMode)
         {
		  openmode=AMode;
         };
		void __fastcall SetLang(AnsiString _Film,AnsiString _Chars,AnsiString _Min,AnsiString _AddToFavourite,AnsiString _DeleteFromFavourite)
		 {
		  filmwithnameis=_Film;forbiddenChars=_Chars;wordminute=_Min;
		  AddToFavourite=_AddToFavourite;DeleteFromFavourite=_DeleteFromFavourite;
         };
        void __fastcall CreateList()
         {
          films=new TStringList();
         };
        void __fastcall FillList(TStringList *temp)
         {
          films->Clear();
          films->Text=temp->Text;
         };
        void __fastcall DeleteList()
         {
          delete films;films=NULL;
		 };
		void __fastcall TForm2::EditClipboardPress(TObject *Sender, wchar_t &Key)
		  {
            AnsiString buffer=Clipboard()->AsText,temp;bool a=false;
			if (Key == 0x16)
			  {
			   for(int i=0;i<buffer.Length();i++)
				 {if(buffer.c_str()[i]!=char(32)&&buffer.c_str()[i]!=char(9))
                     a=true;
                  if(a==true)
					 temp+=buffer.c_str()[i];}
			   Clipboard()->AsText=temp;
			  }
		  }
		void __fastcall SetFavourite(bool _Favourite);
		bool __fastcall GetFavourite();
		void __fastcall TForm2::ImageMouseEnter(TObject *Sender);
		void __fastcall TForm2::ImageMouseLeave(TObject *Sender);
		void __fastcall TForm2::LabelMouseEnter(TObject *Sender);
		void __fastcall TForm2::LabelMouseLeave(TObject *Sender);
		void __fastcall TForm2::CheckListBoxClickCheck(TObject *Sender);
		void __fastcall TForm2::CheckListBoxClick(TObject *Sender);
		void __fastcall TForm2::StarsMouseEnter(TObject *Sender);
		void __fastcall TForm2::StarsMouseLeave(TObject *Sender);
		void __fastcall TForm2::StarsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y);
		void __fastcall TForm2::StarsClick(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
