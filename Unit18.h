//---------------------------------------------------------------------------

#ifndef Unit18H
#define Unit18H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ButtonGroup.hpp>
#include <DockTabSet.hpp>
#include <Tabs.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <pngimage.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm18 : public TForm
{
__published:	// IDE-managed Components
	TEdit *Seasons;
	TLabel *Label1;
	TScrollBox *ScrollBox1;
	TImage *TestImage;
	TEdit *TestEdit;
	TButton *ApplyButton;
	TImage *ImageInfo;
	TImage *AddSeason;
	TImage *DeleteSeason;
	void __fastcall ScrollBox1Click(TObject *Sender);
	void __fastcall ScrollBox1MouseWheelDown(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall ScrollBox1MouseWheelUp(TObject *Sender, TShiftState Shift, TPoint &MousePos,
          bool &Handled);
	void __fastcall SeasonsKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall ImageInfoClick(TObject *Sender);
	void __fastcall ScrollBox1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ScrollBox1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ScrollBox1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseEnter(TObject *Sender);
	void __fastcall AddSeasonClick(TObject *Sender);
	void __fastcall DeleteSeasonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall SeasonsChange(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		int SeasonsCount;
	__fastcall TForm18(TComponent* Owner);
	void __fastcall TForm18::ImageMouseEnter(TObject *Sender);
	void __fastcall TForm18::ImageMouseLeave(TObject *Sender);
	void __fastcall SeriesChange(TObject *Sender);
	void __fastcall AddingSeason(TObject *Sender);
	void __fastcall DeletingSeason(TObject *Sender);
	void __fastcall SetSeasons(TStringList *_seasons);
	void __fastcall GetSeasons(TStringList *_seasons);
	void __fastcall EditMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm18 *Form18;
//---------------------------------------------------------------------------
#endif
