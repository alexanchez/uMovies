//---------------------------------------------------------------------------

#ifndef Unit22H
#define Unit22H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TForm22 : public TForm
{
__published:	// IDE-managed Components
	TImage *MovieImage1;
	TImage *MovieImage2;
	TImage *MovieImage3;
	TLabel *MovieLabel1;
	TLabel *MovieLabel2;
	TLabel *MovieLabel3;
	TButton *Button1;
	TButton *Button2;
	TImage *BackgroundImage;
	TImage *MovieExistsImage1;
	TImage *SelectedMovieImage;
	TImage *MovieExistsImage2;
	TImage *MovieExistsImage3;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:
			AnsiString currentLanguage,minutes_word;
			TStringList *lang;
public:
			void __fastcall CreateList()
			{
				lang=new TStringList();
			};
			void __fastcall FillList(TStringList *currentLang)
			{
				lang->Text=currentLang->Text;
			};
			void __fastcall DeleteList()
			{
				delete lang;lang=NULL;
			};
			void __fastcall SetCurrentLanguage(AnsiString curLang,AnsiString min_word)
			{
				currentLanguage = curLang;
				minutes_word = min_word;
			};
			void __fastcall TForm22::MovieClick(TObject *Sender);
			void __fastcall TForm22::MovieMouseEnter(TObject *Sender);
			void __fastcall TForm22::MovieMouseLeave(TObject *Sender);
	__fastcall TForm22(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm22 *Form22;
//---------------------------------------------------------------------------
#endif
