//----------------------------------------------------------------------------
#ifndef Unit9H
#define Unit9H
//----------------------------------------------------------------------------
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <pngimage.hpp>
//----------------------------------------------------------------------------
class TPasswordDlg : public TForm
{
__published:
	TEdit *Password;
	TButton *OKBtn;
	TButton *CancelBtn;
        TEdit *NewPassword;
	TLabel *Label2;
	TLabel *Label3;
        TImage *Image1;
	TLabel *Label1;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall OKBtnClick(TObject *Sender);
        void __fastcall CancelBtnClick(TObject *Sender);
        void __fastcall PasswordChange(TObject *Sender);
        void __fastcall NewPasswordChange(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image1MouseEnter(TObject *Sender);
	void __fastcall Image1MouseLeave(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:AnsiString name,password;
public:
      void __fastcall Setname(AnsiString AName)
       {
         name = AName;
       };
	  AnsiString __fastcall GetPassword()
       {
          return password;
       };
      void __fastcall SetPassword(AnsiString APas)
       {
		 for(int i=0;i<APas.Length();i++)
			APas.c_str()[i]=APas.c_str()[i]-50;
		 password = APas;
       };
	virtual __fastcall TPasswordDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TPasswordDlg *PasswordDlg;
//----------------------------------------------------------------------------
#endif
