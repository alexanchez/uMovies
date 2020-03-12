//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "LoadingSavingComponent.cpp" - загрузка/сохранение параметров компонентов
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TeCanvas"
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void SetInfoSizes()
{
  Form3->Label1->Left=Form3->OrigName->Left+Form3->OrigName->Width+3;Form3->Label2->Left=Form3->Genre->Left+Form3->Genre->Width+3;
  Form3->Label3->Left=Form3->Country->Left+Form3->Country->Width+3;Form3->Label4->Left=Form3->Year->Left+Form3->Year->Width+3;
  Form3->Label5->Left=Form3->Time->Left+Form3->Time->Width+3;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::PanelStyleClick(TObject *Sender)
{
	TImage* current=static_cast<TImage*>(Sender);
	((TRadioButton*)FindComponent("RBPanel"+IntToStr(current->Tag)))->Checked=true;
	GroupBox1->Tag=current->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
  for(int i=1;i<=5;i++)
	 ((TImage*)FindComponent("Style"+IntToStr(i)))->OnClick=PanelStyleClick;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormShow(TObject *Sender)
{
  Image1->Picture->LoadFromFile("Soft/AlphabetPanel/Template.jpg");
  Style4->Picture->LoadFromFile("Soft/AlphabetPanel/Style4.png");
  Style5->Picture->LoadFromFile("Soft/AlphabetPanel/Style5.png");
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormClose(TObject *Sender, TCloseAction &Action)
{
  Button1->SetFocus();
  Image1->Picture->Assign(NULL);
  Style4->Picture->Assign(NULL);
  Style5->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RBFrameNoneClick(TObject *Sender)
{
  FrameImage->Visible=false;ComboBox1->Enabled=false;ButtonColor1->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RBFrameStyleClick(TObject *Sender)
{
  FrameImage->Visible=true;ComboBox1->Enabled=true;ButtonColor1->Enabled=false;
  ComboBox1Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RBFrameOwnClick(TObject *Sender)
{
  FrameImage->Visible=true;ComboBox1->Enabled=false;ButtonColor1->Enabled=true;
  FrameProperties::LoadComponent(FrameImage,"Soft/AlphabetPanel/FrameImageOwn.dat");
  ButtonColor1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ComboBox1Change(TObject *Sender)
{
  switch(ComboBox1->ItemIndex)
  {
	 case 0:FrameProperties::LoadComponent(FrameImage,"Soft/AlphabetPanel/FrameImage1.dat");break;
	 case 1:FrameProperties::LoadComponent(FrameImage,"Soft/AlphabetPanel/FrameImage2.dat");break;
	 case 2:FrameProperties::LoadComponent(FrameImage,"Soft/AlphabetPanel/FrameImage3.dat");break;
	 case 3:FrameProperties::LoadComponent(FrameImage,"Soft/AlphabetPanel/FrameImage4.dat");break;
	 case 4:FrameProperties::LoadComponent(FrameImage,"Soft/AlphabetPanel/FrameImage5.dat");break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ButtonColor1Click(TObject *Sender)
{
  FrameImage->Canvas->Brush->Color=ButtonColor1->SymbolColor;
  FrameImage->Canvas->Rectangle(-1,-1,FrameImage->Width+1,FrameImage->Height+1);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::InfoFontClick(TObject *Sender)
{
  FontDialog1->Tag=0;
  TColor color=Panel1->Font->Color;
  if(FontDialog1->Execute())
   {Panel1->Font->Assign(FontDialog1->Font);Panel1->Font->Color=color;}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::InfoTextColorClick(TObject *Sender)
{
  Panel1->Font->Color=InfoTextColor->SymbolColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::InfoBackGroundColorClick(TObject *Sender)
{
  Panel1->Color=InfoBackGroundColor->SymbolColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::LabelsFontClick(TObject *Sender)
{
  FontDialog1->Tag=1;
  TColor color=OrigName->Font->Color;
  if(FontDialog1->Execute())
  {
	  OrigName->Font->Assign(FontDialog1->Font);
	  Genre->Font->Assign(FontDialog1->Font);
	  Country->Font->Assign(FontDialog1->Font);
	  Year->Font->Assign(FontDialog1->Font);
	  Time->Font->Assign(FontDialog1->Font);

	  OrigName->Font->Color=color;
	  Genre->Font->Color=color;
	  Country->Font->Color=color;
	  Year->Font->Color=color;
	  Time->Font->Color=color;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::LabelsColorClick(TObject *Sender)
{
  OrigName->Font->Color=LabelsColor->SymbolColor;
  Genre->Font->Color=LabelsColor->SymbolColor;
  Country->Font->Color=LabelsColor->SymbolColor;
  Year->Font->Color=LabelsColor->SymbolColor;
  Time->Font->Color=LabelsColor->SymbolColor;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FontDialog1Apply(TObject *Sender, HWND Wnd)
{
  if(FontDialog1->Tag==0)Panel1->Font->Assign(FontDialog1->Font);
  if(FontDialog1->Tag==1)
  {
	OrigName->Font->Assign(FontDialog1->Font);
	Genre->Font->Assign(FontDialog1->Font);
	Country->Font->Assign(FontDialog1->Font);
	Year->Font->Assign(FontDialog1->Font);
	Time->Font->Assign(FontDialog1->Font);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RBWindowStylesClick(TObject *Sender)
{
  ComboBox2->Enabled=true;GroupBox4->Enabled=false;GroupBox4->Color=(TColor)RGB(244,244,244);
  ComboBox2Change(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::RBWindowOwnClick(TObject *Sender)
{
  ComboBox2->Enabled=false;GroupBox4->Enabled=true;GroupBox4->Color=clWhite;
  FrameProperties::LoadComponent(Panel1,"Soft/AlphabetPanel/WindowStyleOwn.dat");
  SetLabelsFont(Form3,"WindowStyleOwn");
  SetInfoSizes();
  InfoTextColor->SymbolColor=Panel1->Font->Color;InfoTextColor->Repaint();
  InfoBackGroundColor->SymbolColor=Panel1->Color;InfoBackGroundColor->Repaint();
  LabelsColor->SymbolColor=OrigName->Font->Color;LabelsColor->Repaint();
  //Установка текущей рамки
  if(RBFrameNone->Checked) RBFrameNoneClick(Sender);
  if(RBFrameStyle->Checked)RBFrameStyleClick(Sender);
  if(RBFrameOwn->Checked)RBFrameOwnClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::ComboBox2Change(TObject *Sender)
{
  if(ComboBox2->ItemIndex==0){FrameProperties::LoadComponent(Panel1,"Soft/AlphabetPanel/WindowStyle1.dat");SetLabelsFont(Form3,"WindowStyle1");}
  if(ComboBox2->ItemIndex==1){FrameProperties::LoadComponent(Panel1,"Soft/AlphabetPanel/WindowStyle2.dat");SetLabelsFont(Form3,"WindowStyle2");}
  SetInfoSizes();
  InfoTextColor->SymbolColor=Panel1->Font->Color;InfoTextColor->Repaint();
  InfoBackGroundColor->SymbolColor=Panel1->Color;InfoBackGroundColor->Repaint();
  LabelsColor->SymbolColor=OrigName->Font->Color;LabelsColor->Repaint();
  //Установка текущей рамки
  if(RBFrameNone->Checked) RBFrameNoneClick(Sender);
  if(RBFrameStyle->Checked)RBFrameStyleClick(Sender);
  if(RBFrameOwn->Checked)RBFrameOwnClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::InfoFontMouseEnter(TObject *Sender)
{
  InfoFont->Picture->LoadFromFile("Soft/Buttons/Font(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::InfoFontMouseLeave(TObject *Sender)
{
  InfoFont->Picture->LoadFromFile("Soft/Buttons/Font.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::LabelsFontMouseEnter(TObject *Sender)
{
  LabelsFont->Picture->LoadFromFile("Soft/Buttons/Font(light).png");
}
//---------------------------------------------------------------------------

void __fastcall TForm3::LabelsFontMouseLeave(TObject *Sender)
{
  LabelsFont->Picture->LoadFromFile("Soft/Buttons/Font.png");
}
//---------------------------------------------------------------------------


