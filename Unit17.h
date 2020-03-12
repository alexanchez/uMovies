//---------------------------------------------------------------------------

#ifndef Unit17H
#define Unit17H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "TeCanvas.hpp"
#include <pngimage.hpp>
#include <jpeg.hpp>
#include "ZipForge.hpp"
#include <Buttons.hpp>
#include "TeeEdiGrad.hpp"
#include <CategoryButtons.hpp>
//---------------------------------------------------------------------------
class TForm17 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet3;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label15;
	TLabel *LabelStar5;
	TLabel *LabelStar4_5;
	TLabel *LabelStar4;
	TLabel *LabelStar3_5;
	TLabel *LabelStar3;
	TLabel *LabelStar2_5;
	TLabel *LabelStar2;
	TLabel *LabelStar1_5;
	TLabel *LabelStar1;
	TLabel *LabelStar0_5;
	TLabel *LabelStar0;
	TImage *Image1;
	TTabSheet *TabSheet2;
	TListBox *ListBox2;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TListBox *ListBox1;
	TListBox *ListBox3;
	TListBox *ListBox4;
	TListBox *ListBox5;
	TLabel *Label16;
	TZipForge *ZipForge1;
	TRadioButton *RadioButton4;
	TLabel *Label17;
	TLabel *Saving;
	TChart *Chart1;
	TRadioButton *RadioButton6;
	TRadioButton *RadioButton7;
	TComboBox *ComboBox1;
	THorizBarSeries *Series1;
	THorizBarSeries *Series2;
	TBarSeries *Series3;
	THorizBarSeries *Series4;
	TLabel *Label18;
	TLabel *Label9;
	TBarSeries *Series5;
	TRadioButton *RadioButton5;
	TCategoryButtons *CategoryButtons1;
	TComboBox *EventsBox;
	TLabel *Label19;
	TRadioButton *DatePicker1;
	TRadioButton *DatePicker2;
	TDateTimePicker *DateTimePicker1;
	TDateTimePicker *DateTimePicker2;
	TLabel *EventsQuantity;
	TImage *Image3;
	TEdit *Edit5;
	TImage *Image6;
	void __fastcall RadioButton1Click(TObject *Sender);
	void __fastcall RadioButton2Click(TObject *Sender);
	void __fastcall RadioButton3Click(TObject *Sender);
	void __fastcall Chart1Click(TObject *Sender);
	void __fastcall ListBox3Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall RadioButton6Click(TObject *Sender);
	void __fastcall RadioButton7Click(TObject *Sender);
	void __fastcall RadioButton4Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall SavingMouseEnter(TObject *Sender);
	void __fastcall SavingMouseLeave(TObject *Sender);
	void __fastcall SavingClick(TObject *Sender);
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall RadioButton5Click(TObject *Sender);
	void __fastcall EventsBoxChange(TObject *Sender);
	void __fastcall DatePicker1Click(TObject *Sender);
	void __fastcall DatePicker2Click(TObject *Sender);
	void __fastcall DateTimePicker1Click(TObject *Sender);
	void __fastcall Edit5Change(TObject *Sender);
	void __fastcall Edit5Enter(TObject *Sender);
	void __fastcall Edit5Exit(TObject *Sender);
	void __fastcall Image6Click(TObject *Sender);

private:	// User declarations
public:		AnsiString DateofCreation,QuantityFilms,Saved,EventNumbers,Search;
	__fastcall TForm17(TComponent* Owner);
	void __fastcall TForm17::SeriesMouseEnter(TObject *Sender);
	void __fastcall TForm17::SeriesMouseLeave(TObject *Sender);
	void __fastcall SetLang(AnsiString _DateofCreation,AnsiString _QuantityFilms,AnsiString _Saved,AnsiString _EventQuantity,
							AnsiString _Search)
		{
		   DateofCreation=_DateofCreation;Saved=_Saved;QuantityFilms=_QuantityFilms;EventNumbers=_EventQuantity;Search=_Search;
		};
};
//---------------------------------------------------------------------------
extern PACKAGE TForm17 *Form17;
//---------------------------------------------------------------------------
#endif
