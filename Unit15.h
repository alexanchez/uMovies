//---------------------------------------------------------------------------

#ifndef Unit15H
#define Unit15H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TForm15 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox1;
	TButton *Button1;
	TButton *Button2;
	TComboBox *ComboBox2;
	TCheckBox *CheckBox1;
	TLabel *Label1;
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ComboBox2Change(TObject *Sender);
	void __fastcall ComboBox2CloseUp(TObject *Sender);
	void __fastcall ComboBox1CloseUp(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
private:	// User declarations
public:		TStringList *SerialSeasons;
	void SetEpisode(int season,int episode)
	{
      ComboBox1->Items->Clear();
	  for(int i=1;i<=SerialSeasons->Count;i++)
		ComboBox1->Items->Add(ComboBox1->Hint+IntToStr(i));
	  ComboBox1->ItemIndex=StrToInt(season)-1;
	  ComboBox2->Items->Clear();
	  for(int i=1;i<=StrToInt(SerialSeasons->Strings[StrToInt(season)-1]);i++)
		ComboBox2->Items->Add(ComboBox2->Hint+IntToStr(i));
	  ComboBox2->ItemIndex=StrToInt(episode)-1;
	}
	__fastcall TForm15(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm15 *Form15;
//---------------------------------------------------------------------------
#endif
