//---------------------------------------------------------------------------

#ifndef Unit8H
#define Unit8H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ZipForge.hpp"
#include <Menus.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
//---------------------------------------------------------------------------
class TForm8 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TLabel *Label1;
        TPopupMenu *PopupMenu1;
        TMenuItem *PCreateCatalog;
        TMenuItem *POpenCatalog;
        TMenuItem *PDeleteCatalog;
        TZipForge *ZipForge1;
        TOpenDialog *OpenDialog1;
        TMenuItem *PAddCatalog;
        TImage *Image1;
        TMenuItem *PPassword;
        TMenuItem *PPasswordCreate;
        TMenuItem *PPasswordDelete;
        TLabel *Label3;
        TImage *Image2;
	TMenuItem *PCreateDublicate;
        TMenuItem *PCreateEmpty;
        TMenuItem *PRenameCatalog;
	TMenuItem *PCreateDublicateSelected;
	TLabel *CatalogsQuantity;
	TLabel *Label2;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall PDeleteCatalogClick(TObject *Sender);
        void __fastcall POpenCatalogClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall PAddCatalogClick(TObject *Sender);
        void __fastcall ListBox1DblClick(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall PPasswordCreateClick(TObject *Sender);
        void __fastcall PPasswordDeleteClick(TObject *Sender);
        void __fastcall PCreateDublicateClick(TObject *Sender);
        void __fastcall PCreateEmptyClick(TObject *Sender);
        void __fastcall PRenameCatalogClick(TObject *Sender);
	void __fastcall ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall PCreateDublicateSelectedClick(TObject *Sender);

private:	// User declarations
       TStringList*lang;AnsiString paswrd,namecatalog,namedeletedcatalog,forbiddenchars;bool agreement;
public:		// User declarations
      void __fastcall ForbiddenChars(AnsiString AChars)
       {
          forbiddenchars=AChars;
       };
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
      void __fastcall SetPas_NameCatalog(AnsiString ACatalog,AnsiString APassword)
       {
         namecatalog=ACatalog;paswrd = APassword;
       };
      AnsiString __fastcall GetPas()
       {
          return paswrd;
       };
      AnsiString __fastcall GetNamecatalog()
       {
          return namecatalog;
       };
      void __fastcall SetNameDeletedCatalog(AnsiString ANameDeletedCatalog)
       {
         namedeletedcatalog = ANameDeletedCatalog;
       };
      AnsiString __fastcall GetNameDeletedCatalog()
       {
          return namedeletedcatalog;
       };
      void __fastcall SetAgreement(bool AAgreement)
       {
         agreement=AAgreement;
       };
      bool __fastcall GetAgreement()
       {
          return agreement;
       };
        __fastcall TForm8(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm8 *Form8;
//---------------------------------------------------------------------------

#endif
