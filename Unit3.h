//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include "TeCanvas.hpp"
#include <Dialogs.hpp>
#include <Graphics.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TImage *Image2;
	TPanel *Panel1;
	TImage *FrameImage;
	TImage *Image1;
	TLabel *OrigName;
	TLabel *Genre;
	TLabel *Country;
	TImage *Star1;
	TImage *Star2;
	TImage *Star3;
	TImage *Star4;
	TImage *Star5;
	TLabel *Year;
	TLabel *Time;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	TGroupBox *GroupBox1;
	TImage *Style1;
	TImage *Style2;
	TImage *Style3;
	TImage *Style4;
	TImage *Style5;
	TRadioButton *RBPanel1;
	TRadioButton *RBPanel2;
	TRadioButton *RBPanel3;
	TRadioButton *RBPanel4;
	TRadioButton *RBPanel5;
	TRadioButton *RBPanelNone;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TRadioButton *RBFrameNone;
	TComboBox *ComboBox1;
	TRadioButton *RBFrameStyle;
	TRadioButton *RBFrameOwn;
	TButtonColor *ButtonColor1;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox5;
	TImage *InfoFont;
	TButtonColor *InfoTextColor;
	TButtonColor *InfoBackGroundColor;
	TGroupBox *GroupBox6;
	TImage *LabelsFont;
	TButtonColor *LabelsColor;
	TComboBox *ComboBox2;
	TRadioButton *RBWindowStyles;
	TRadioButton *RBWindowOwn;
	TColorDialog *ColorDialog1;
	TFontDialog *FontDialog1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall RBFrameNoneClick(TObject *Sender);
	void __fastcall RBFrameStyleClick(TObject *Sender);
	void __fastcall RBFrameOwnClick(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall ButtonColor1Click(TObject *Sender);
	void __fastcall InfoFontClick(TObject *Sender);
	void __fastcall InfoTextColorClick(TObject *Sender);
	void __fastcall InfoBackGroundColorClick(TObject *Sender);
	void __fastcall LabelsFontClick(TObject *Sender);
	void __fastcall LabelsColorClick(TObject *Sender);
	void __fastcall FontDialog1Apply(TObject *Sender, HWND Wnd);
	void __fastcall RBWindowStylesClick(TObject *Sender);
	void __fastcall RBWindowOwnClick(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall InfoFontMouseEnter(TObject *Sender);
	void __fastcall InfoFontMouseLeave(TObject *Sender);
	void __fastcall LabelsFontMouseEnter(TObject *Sender);
	void __fastcall LabelsFontMouseLeave(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
		__fastcall TForm3(TComponent* Owner);
		void __fastcall TForm3::PanelStyleClick(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
