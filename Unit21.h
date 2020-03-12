//---------------------------------------------------------------------------

#ifndef Unit21H
#define Unit21H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm21 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TLabel *Label1;
	TImage *Image2;
	TComboBox *ComboBox1;
	TComboBox *ComboBox2;
	TImage *Image3;
	TComboBox *ComboBox3;
	TImage *Image4;
	TComboBox *ComboBox4;
	TImage *Image5;
	TComboBox *ComboBox5;
	TImage *Image6;
	TComboBox *ComboBox6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TImage *Image12;
	TComboBox *ComboBox7;
	TComboBox *ComboBox8;
	TComboBox *ComboBox9;
	TComboBox *ComboBox10;
	TComboBox *ComboBox11;
	TComboBox *ComboBox12;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *Button1;
	TButton *Button2;
	TImage *ImageInfo;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
	__fastcall TForm21(TComponent* Owner);
	void __fastcall TForm21::ComboBoxChange(TObject *Sender);
	void __fastcall TForm21::ComboBoxDropDown(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm21 *Form21;
//---------------------------------------------------------------------------
#endif
