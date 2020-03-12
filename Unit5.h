//----------------------------------------------------------------------------
#ifndef Unit5H
#define Unit5H
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <ComCtrls.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TImage *Image3;
	TButton *OKButton1;
	TPanel *Panel2;
	TImage *Image4;
	TLabel *LicenseInfo;
	TLabel *Topic;
	TButton *TrialVersion;
	TButton *License;
	TImage *Image1;
	TButton *OKButton;
	TPanel *Panel1;
	TImage *Image2;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
	TLabel *Label1;
	TImage *Image5;
	TImage *Image6;
        void __fastcall Label1Click(TObject *Sender);
	void __fastcall Label1MouseEnter(TObject *Sender);
	void __fastcall Label1MouseLeave(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LicenseClick(TObject *Sender);
	void __fastcall TrialVersionClick(TObject *Sender);
private:
		 TStringList*lang;
public:
         void __fastcall CreateList()
		 {
		   lang=new TStringList();
		 };
		 void __fastcall ClearList()
		 {
		   lang->Clear();
		 };
		 void __fastcall FillList(String temp)
		 {
		   lang->Add(temp);
		 };
		 void __fastcall DeleteList()
		 {
		   delete lang;lang=NULL;
		 };

	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
