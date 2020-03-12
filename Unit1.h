//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Buttons.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <CheckLst.hpp>
#include "CSPIN.h"
#include "ZipForge.hpp"
#include <Dialogs.hpp>
#include <pngimage.hpp>
#include <Graphics.hpp>
#include <GestureCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TImage *Image1;
        TMemo *Memo1;
        TImage *Image2;
        TLabel *Label2;
        TComboBox *ComboBox1;
        TLabel *Label3;
        TLabel *Label4;
        TComboBox *ComboBox4;
        TLabel *Label1;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TEdit *Edit4;
        TRadioButton *RadioButton1;
        TLabel *Label11;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TLabel *Label12;
        TLabel *Label13;
        TComboBox *ComboBox3;
        TComboBox *ComboBox6;
        TLabel *Label14;
        TComboBox *ComboBox5;
        TLabel *Label15;
        TRadioButton *RadioButton4;
        TLabel *Label16;
        TPopupMenu *PopupMenu;
        TMenuItem *MElect;
        TMenuItem *MDelete;
        TMenuItem *MEdit;
        TMainMenu *MainMenu1;
	TMenuItem *MCatalogMenu;
	TMenuItem *MOptions;
        TMenuItem *MAbout;
        TMenuItem *MAdd;
        TMenuItem *MSave;
        TMenuItem *MSort;
        TMenuItem *N4_3;
        TMenuItem *MQuit;
        TMenuItem *MReset;
        TMenuItem *N4_6;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *BG1;
        TMenuItem *BG2;
        TMenuItem *BG3;
        TMenuItem *Font1;
        TMenuItem *Font2;
        TMenuItem *Font3;
        TMenuItem *Font4;
        TMenuItem *MWebSite;
        TMenuItem *BG4;
        TMenuItem *BG5;
        TMenuItem *Font5;
        TEdit *Edit5;
        TImage *Image3;
        TImage *Image4;
        TImage *Image5;
        TLabel *Label18;
        TMenuItem *MHelpNote;
        TMenuItem *N2;
        TMenuItem *UA;
        TMenuItem *RU;
        TMenuItem *English;
        TMenuItem *MQFilter;
        TMenuItem *MQView;
        TMenuItem *MQRls;
        TMenuItem *MQYear;
        TMenuItem *MQAll;
        TMenuItem *MSearch;
        TImage *Image6;
        TMenuItem *MCatalog;
        TZipForge *ZipForge1;
	TMenuItem *PAddToDesired;
        TMenuItem *MFilms;
        TPopupMenu *PopupMenu1;
        TListBox *ListBox2;
        TImage *Image7;
	TMenuItem *PAddToMyCatalog;
        TMenuItem *PDeleteFilm;
        TImage *Image8;
        TLabel *Label17;
        TTimer *Timer1;
        TLabel *Label19;
        TEdit *Edit6;
        TComboBox *ComboBox2;
        TLabel *Label20;
        TImage *Image9;
        TImage *Image10;
        TImage *Image11;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TEdit *Edit7;
        TEdit *Edit8;
        TLabel *Label24;
        TMemo *Memo2;
        TMenuItem *N1;
        TMenuItem *MTurnOn;
        TMenuItem *MTurnOff;
        TMenuItem *AllGroups;
        TMenuItem *MainGroup;
        TMenuItem *N7;
        TMenuItem *MAddGroup;
        TMenuItem *Groups;
        TMenuItem *FilmDel;
        TMenuItem *Groups1;
        TMenuItem *Groups2;
        TImage *Image12;
	TMenuItem *N3;
        TCheckListBox *CheckListBox1;
        TCheckListBox *CheckListBox3;
        TCheckListBox *CheckListBox4;
        TCheckListBox *CheckListBox2;
        TComboBox *ComboBox7;
        TComboBox *ComboBox8;
        TImage *Image13;
	TMenuItem *MRandomFilm;
	TMenuItem *MFilmsUnderMood;
	TTimer *Timer2;
	TTimer *Timer3;
	TImage *Image14;
	TTimer *Timer4;
	TLabel *Line6;
	TLabel *Line4;
	TLabel *Line5;
	TLabel *Line3;
	TLabel *Line2;
	TLabel *Line1;
	TLabel *Line7;
	TImage *Pointer;
	TImage *Star1;
	TImage *Star2;
	TImage *Star3;
	TImage *Star4;
	TImage *Star5;
	TMenuItem *MSeveralDeleting;
	TTimer *Timer5;
	TImage *Image15;
	TMenuItem *MFilter;
	TImage *Image16;
	TMenuItem *N4;
	TMenuItem *MLastFilter;
	TMenuItem *MStatistic;
	TMenuItem *MFavouriteFilter;
	TMenuItem *MSerialExpected;
	TMenuItem *MAlphabetFilm;
	TPanel *Panel2;
	TImage *PanelImage;
	TPanel *Panel1;
	TImage *ExpandCollapseButton;
	TCategoryPanelGroup *CategoryPanelGroup1;
	TCategoryPanel *CategoryPanel59;
	TCategoryPanel *CategoryPanel58;
	TCategoryPanel *CategoryPanel57;
	TCategoryPanel *CategoryPanel56;
	TCategoryPanel *CategoryPanel55;
	TCategoryPanel *CategoryPanel54;
	TCategoryPanel *CategoryPanel53;
	TCategoryPanel *CategoryPanel52;
	TCategoryPanel *CategoryPanel51;
	TCategoryPanel *CategoryPanel50;
	TCategoryPanel *CategoryPanel49;
	TCategoryPanel *CategoryPanel48;
	TCategoryPanel *CategoryPanel47;
	TCategoryPanel *CategoryPanel46;
	TCategoryPanel *CategoryPanel45;
	TCategoryPanel *CategoryPanel44;
	TCategoryPanel *CategoryPanel43;
	TCategoryPanel *CategoryPanel42;
	TCategoryPanel *CategoryPanel41;
	TCategoryPanel *CategoryPanel40;
	TCategoryPanel *CategoryPanel39;
	TCategoryPanel *CategoryPanel38;
	TCategoryPanel *CategoryPanel37;
	TCategoryPanel *CategoryPanel36;
	TCategoryPanel *CategoryPanel35;
	TCategoryPanel *CategoryPanel34;
	TCategoryPanel *CategoryPanel33;
	TCategoryPanel *CategoryPanel32;
	TCategoryPanel *CategoryPanel31;
	TCategoryPanel *CategoryPanel30;
	TCategoryPanel *CategoryPanel29;
	TCategoryPanel *CategoryPanel28;
	TCategoryPanel *CategoryPanel27;
	TCategoryPanel *CategoryPanel26;
	TCategoryPanel *CategoryPanel25;
	TCategoryPanel *CategoryPanel24;
	TCategoryPanel *CategoryPanel23;
	TCategoryPanel *CategoryPanel22;
	TCategoryPanel *CategoryPanel21;
	TCategoryPanel *CategoryPanel20;
	TCategoryPanel *CategoryPanel19;
	TCategoryPanel *CategoryPanel18;
	TCategoryPanel *CategoryPanel17;
	TCategoryPanel *CategoryPanel16;
	TCategoryPanel *CategoryPanel15;
	TCategoryPanel *CategoryPanel14;
	TCategoryPanel *CategoryPanel13;
	TCategoryPanel *CategoryPanel12;
	TCategoryPanel *CategoryPanel11;
	TCategoryPanel *CategoryPanel10;
	TCategoryPanel *CategoryPanel9;
	TCategoryPanel *CategoryPanel8;
	TCategoryPanel *CategoryPanel7;
	TCategoryPanel *CategoryPanel6;
	TCategoryPanel *CategoryPanel5;
	TCategoryPanel *CategoryPanel4;
	TCategoryPanel *CategoryPanel3;
	TCategoryPanel *CategoryPanel2;
	TCategoryPanel *CategoryPanel1;
	TLabel *Label25;
	TPanel *Panel3;
	TImage *Image17;
	TLabel *ExpandAllAlphabetPanel;
	TImage *Image18;
	TLabel *CollapseAllAlphabetPanel;
	TTimer *Timer6;
	TMenuItem *AlphabetPanelOptions;
	TMenuItem *MTemplateCommands;
	TLabel *Label26;
	TMenuItem *MNewMovies;
	TMenuItem *MCinemaAffiche;
	TMenuItem *MMoviesAnalysis;
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Label11Click(TObject *Sender);
        void __fastcall Label12Click(TObject *Sender);
        void __fastcall Label13Click(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall ComboBox6Change(TObject *Sender);
        void __fastcall ComboBox5Change(TObject *Sender);
        void __fastcall ComboBox3Change(TObject *Sender);
        void __fastcall ComboBox4Change(TObject *Sender);
        void __fastcall PopupMenuPopup(TObject *Sender);
        void __fastcall MElectClick(TObject *Sender);
        void __fastcall Label16Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall MDeleteClick(TObject *Sender);
        void __fastcall MEditClick(TObject *Sender);
        void __fastcall MQuitClick(TObject *Sender);
        void __fastcall MSaveClick(TObject *Sender);
        void __fastcall MAddClick(TObject *Sender);
        void __fastcall MSortClick(TObject *Sender);
        void __fastcall MResetClick(TObject *Sender);
        void __fastcall Memo1Change(TObject *Sender);
        void __fastcall BG1Click(TObject *Sender);
        void __fastcall BG2Click(TObject *Sender);
        void __fastcall BG3Click(TObject *Sender);
        void __fastcall Font1Click(TObject *Sender);
        void __fastcall Font2Click(TObject *Sender);
        void __fastcall Font3Click(TObject *Sender);
        void __fastcall Font4Click(TObject *Sender);
        void __fastcall MWebSiteClick(TObject *Sender);
        void __fastcall MAboutClick(TObject *Sender);
        void __fastcall BG4Click(TObject *Sender);
        void __fastcall BG5Click(TObject *Sender);
        void __fastcall Font5Click(TObject *Sender);
        void __fastcall Edit5Change(TObject *Sender);
        void __fastcall Image5Click(TObject *Sender);
        void __fastcall Image4Click(TObject *Sender);
        void __fastcall MHelpNoteClick(TObject *Sender);
        void __fastcall UAClick(TObject *Sender);
        void __fastcall RUClick(TObject *Sender);
        void __fastcall EnglishClick(TObject *Sender);
        void __fastcall Edit5KeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall MQViewClick(TObject *Sender);
        void __fastcall MQRlsClick(TObject *Sender);
        void __fastcall MQYearClick(TObject *Sender);
        void __fastcall MQAllClick(TObject *Sender);
        void __fastcall MSearchClick(TObject *Sender);
        void __fastcall Image6Click(TObject *Sender);
        void __fastcall MCatalogClick(TObject *Sender);
        void __fastcall PAddToDesiredClick(TObject *Sender);
        void __fastcall MFilmsClick(TObject *Sender);
        void __fastcall ListBox2Click(TObject *Sender);
        void __fastcall Image7Click(TObject *Sender);
        void __fastcall PAddToMyCatalogClick(TObject *Sender);
        void __fastcall PDeleteFilmClick(TObject *Sender);
        void __fastcall PopupMenu1Popup(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Image9Click(TObject *Sender);
        void __fastcall Image11Click(TObject *Sender);
        void __fastcall Image10Click(TObject *Sender);
        void __fastcall Memo2Change(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall MTurnOnClick(TObject *Sender);
        void __fastcall MTurnOffClick(TObject *Sender);
        void __fastcall Edit5Enter(TObject *Sender);
        void __fastcall Edit5Exit(TObject *Sender);
        void __fastcall MainGroupClick(TObject *Sender);
        void __fastcall MAddGroupClick(TObject *Sender);
        void __fastcall GroupsClick(TObject *Sender);
        void __fastcall FilmDelClick(TObject *Sender);
        void __fastcall ComboBox7Change(TObject *Sender);
        void __fastcall ComboBox8Change(TObject *Sender);
        void __fastcall Image13Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
	void __fastcall MFilmsUnderMoodClick(TObject *Sender);
	void __fastcall MRandomFilmClick(TObject *Sender);
	void __fastcall Timer2Timer(TObject *Sender);
	void __fastcall ComboBox3Exit(TObject *Sender);
	void __fastcall ComboBox7Exit(TObject *Sender);
	void __fastcall ComboBox4Exit(TObject *Sender);
	void __fastcall ComboBox8Exit(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall Timer4Timer(TObject *Sender);
	void __fastcall MSeveralDeletingClick(TObject *Sender);
	void __fastcall Label17Click(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image1MouseEnter(TObject *Sender);
	void __fastcall Timer5Timer(TObject *Sender);
	void __fastcall Image15Click(TObject *Sender);
	void __fastcall MFilterClick(TObject *Sender);
	void __fastcall ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall Image16Click(TObject *Sender);
	void __fastcall ListBox2DrawItem(TWinControl *Control, int Index, TRect &Rect, TOwnerDrawState State);
	void __fastcall MLastFilterClick(TObject *Sender);
	void __fastcall MStatisticClick(TObject *Sender);
	void __fastcall MFavouriteFilterClick(TObject *Sender);
	void __fastcall MSerialExpectedClick(TObject *Sender);
	void __fastcall MAlphabetFilmClick(TObject *Sender);
	void __fastcall Timer6Timer(TObject *Sender);
	void __fastcall ExpandCollapseButtonClick(TObject *Sender);
	void __fastcall AlphabetPanelOptionsClick(TObject *Sender);
	void __fastcall CategoryPanelGroup1MouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
	void __fastcall CategoryPanelGroup1MouseWheelUp(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled);
	void __fastcall ExpandCollapseButtonMouseEnter(TObject *Sender);
	void __fastcall ExpandCollapseButtonMouseLeave(TObject *Sender);
	void __fastcall ExpandAllAlphabetPanelMouseEnter(TObject *Sender);
	void __fastcall ExpandAllAlphabetPanelMouseLeave(TObject *Sender);
	void __fastcall CollapseAllAlphabetPanelMouseEnter(TObject *Sender);
	void __fastcall CollapseAllAlphabetPanelMouseLeave(TObject *Sender);
	void __fastcall Image17Click(TObject *Sender);
	void __fastcall Image18Click(TObject *Sender);
	void __fastcall ExpandAllAlphabetPanelClick(TObject *Sender);
	void __fastcall CollapseAllAlphabetPanelClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall MTemplateCommandsClick(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall PanelImageMouseEnter(TObject *Sender);
	void __fastcall MNewMoviesClick(TObject *Sender);
	void __fastcall MCinemaAfficheClick(TObject *Sender);
	void __fastcall MMoviesAnalysisClick(TObject *Sender);



private:	// User declarations
public:
		void __fastcall TForm1::ComboBoxPress(TObject *Sender, wchar_t &Key)
          {
            TComboBox *Current=static_cast<TComboBox *>(Sender);
            if(Current->Tag==0)
              if (isdigit(Key))Key = 0;
            if(Current->Tag==1)
              if((Key!=VK_BACK)&&(Key<'0'||Key>'9'))Key=0;
            Current=NULL;delete Current;
		  }
		void __fastcall TForm1::ComboBoxKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
          {
			TComboBox *Current=static_cast<TComboBox *>(Sender);
			if(Key==VK_RETURN && Current->ItemIndex!=-1)
			   Current->Text=Current->Items->Strings[Current->ItemIndex];
			Current=NULL;delete Current;
		  }
		void __fastcall TForm1::EditPress(TObject *Sender, wchar_t &Key)
          {
            TEdit *Current=static_cast<TEdit *>(Sender);
            if(Current->Tag==0)
              if (isdigit(Key))Key = 0;
            if(Current->Tag==1)
              if((Key!=VK_BACK)&&(Key<'0'||Key>'9'))Key=0;
            Current=NULL;delete Current;
          }
        void __fastcall TForm1::ImageDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
          {
            TImage *Current=static_cast<TImage *>(Sender);
            Current->Height+=2;Current->Width+=2;
            Current=NULL;delete Current;
          }
        void __fastcall TForm1::ImageUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
          {
            TImage *Current=static_cast<TImage *>(Sender);
            Current->Height-=2;Current->Width-=2;
			Current=NULL;delete Current;
          }

		__fastcall TForm1(TComponent* Owner);
		void __fastcall TForm1::SizeOfIndicatorViewed();
		void __fastcall TForm1::MOpenGroupClick(TObject *Sender);
        void __fastcall TForm1::MRenameGroupClick(TObject *Sender);
        void __fastcall TForm1::MDeleteGroupClick(TObject *Sender);
        void __fastcall TForm1::MAddFilmToGroupClick(TObject *Sender);
		void __fastcall TForm1::MRemoveFilmFromGroupClick(TObject *Sender);
        void __fastcall TForm1::CheckListBoxClick(TObject *Sender);
		void __fastcall TForm1::CheckListBoxClickCheck(TObject *Sender);
		void __fastcall TForm1::ImageMouseEnter(TObject *Sender);
		void __fastcall TForm1::ImageMouseLeave(TObject *Sender);
		void __fastcall TForm1::CheckListBoxMouseEnter(TObject *Sender);
		void __fastcall TForm1::CheckListBoxMouseLeave(TObject *Sender);
		void __fastcall TForm1::ComboBoxDropDown(TObject *Sender);
		//Боковая панель
		void __fastcall TForm1::CategoryPanelExpand(TObject *Sender);
		void __fastcall TForm1::CategoryPanelCollapse(TObject *Sender);
		void __fastcall TForm1::LabelMouseEnter(TObject *Sender);
		void __fastcall TForm1::LabelMouseLeave(TObject *Sender);
		void __fastcall TForm1::LabelClick(TObject *Sender);
		void __fastcall TForm1::CategoryPanelMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y);
		void __fastcall TForm1::CategoryPanelMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y);
		void __fastcall TForm1::CategoryPanelMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);

		void __fastcall CatchDrag(TMessage &Msg);
		  BEGIN_MESSAGE_MAP
			 MESSAGE_HANDLER(WM_MOVING, TMessage, CatchDrag);
		  END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
