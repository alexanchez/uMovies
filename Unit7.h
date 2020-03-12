//---------------------------------------------------------------------------

#ifndef Unit7H
#define Unit7H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <pngimage.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm7 : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TImage *Image1;
        TCheckBox *CheckBox2;
	TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TEdit *Edit1;
        TComboBox *ComboBox1;
        TComboBox *ComboBox4;
	TComboBox *ComboBox3;
        TComboBox *ComboBox6;
        TComboBox *ComboBox5;
        TButton *Button1;
        TButton *Button2;
        TImage *Image2;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
	TCheckBox *CheckBox3;
	TComboBox *ComboBox2;
        TCheckBox *CheckBox8;
        TEdit *Edit2;
        TCheckBox *CheckBox9;
        TEdit *Edit3;
        TCheckBox *CheckBox10;
        TEdit *Edit4;
        TCheckBox *CheckBox11;
        TEdit *Edit5;
        TCheckBox *CheckBox12;
        TEdit *Edit6;
        TCheckBox *CheckBox13;
        TEdit *Edit7;
	TImage *Image3;
	TCheckListBox *CheckListBox1;
	TCheckListBox *CheckListBox2;
	TCheckListBox *CheckListBox4;
	TCheckListBox *CheckListBox3;
	TComboBox *ComboBox8;
	TComboBox *ComboBox7;
	TImage *Star1;
	TImage *Star2;
	TImage *Star3;
	TImage *Star4;
	TImage *Star5;
	TLabel *Rating;
	TCheckBox *CheckBox14;
	TCheckBox *CheckBox15;
	TImage *Image4;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TImage *Image5;
	TTimer *Timer1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Image2Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ComboBox4KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall ComboBox1KeyPress(TObject *Sender, char &Key);
	void __fastcall Image2MouseEnter(TObject *Sender);
	void __fastcall Image2MouseLeave(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image3MouseEnter(TObject *Sender);
	void __fastcall Image3MouseLeave(TObject *Sender);
	void __fastcall ComboBox3Change(TObject *Sender);
	void __fastcall ComboBox4Change(TObject *Sender);
	void __fastcall ComboBox7Change(TObject *Sender);
	void __fastcall ComboBox8KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ComboBox3Exit(TObject *Sender);
	void __fastcall ComboBox7Exit(TObject *Sender);
	void __fastcall ComboBox8Change(TObject *Sender);
	void __fastcall ComboBox4Exit(TObject *Sender);
	void __fastcall ComboBox8Exit(TObject *Sender);
	void __fastcall DateTimePicker1Change(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Image5Click(TObject *Sender);
	void __fastcall DateTimePicker2Change(TObject *Sender);
	void __fastcall Image4MouseEnter(TObject *Sender);
	void __fastcall Image4MouseLeave(TObject *Sender);
	void __fastcall Image5MouseEnter(TObject *Sender);
	void __fastcall Image5MouseLeave(TObject *Sender);


private:	// User declarations
	   AnsiString wordminute;TStringList *searchmode;
public:		// User declarations
	   void __fastcall SetLang(AnsiString AMin)
         {
		  wordminute=AMin;
		 };
	   void __fastcall CreateList()
		 {
          searchmode=new TStringList();for(int i=0; i<4;i++)searchmode->Add("1");
		 };
	   void __fastcall DeleteList()
         {
		  delete searchmode;searchmode=NULL;
		 };
	   AnsiString __fastcall GetSearchMode()
	   {
		  return searchmode->Text;
	   };
		__fastcall TForm7(TComponent* Owner);
		void __fastcall TForm7::EditChange(TObject *Sender);
		void __fastcall TForm7::ComboBoxChange(TObject *Sender);
		void __fastcall TForm7::CheckListBoxClick(TObject *Sender);
		void __fastcall TForm7::CheckListBoxClickCheck(TObject *Sender);
		void __fastcall TForm7::CheckListBoxMouseEnter(TObject *Sender);
		void __fastcall TForm7::CheckListBoxMouseLeave(TObject *Sender);
		void __fastcall TForm7::StarsMouseEnter(TObject *Sender);
		void __fastcall TForm7::StarsMouseLeave(TObject *Sender);
		void __fastcall TForm7::StarsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y);
		void __fastcall TForm7::StarsClick(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm7 *Form7;
//---------------------------------------------------------------------------
#endif
