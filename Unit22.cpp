//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit22.h"
#include "Unit2.h"  - Для доступа к форме добавления
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm22 *Form22;
int previousLabelNumber=0;
//---------------------------------------------------------------------------
__fastcall TForm22::TForm22(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm22::MovieClick(TObject *Sender)
{
	TComponent* current = dynamic_cast<TComponent*>(Sender);       //Если фильма нету ещё и текущий фокус не лежит на нем же
	if(((TImage*)Form22->FindComponent("MovieExistsImage"+IntToStr(current->Tag)))->Tag==0 && SelectedMovieImage->Tag!=current->Tag)
	{
		SelectedMovieImage->Visible=true;
		SelectedMovieImage->Left=((TImage*)Form22->FindComponent("MovieImage"+IntToStr(current->Tag)))->Left-3;
		SelectedMovieImage->Tag=current->Tag;
		SelectedMovieImage->Hint=((TImage*)Form22->FindComponent("MovieImage"+IntToStr(current->Tag)))->Hint;
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Cursor=(TCursor)1;
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Font->Color=(TColor)RGB(200,7,80);
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Font->Style= TFontStyles()<<fsUnderline<<fsBold;
		Button1->Enabled=true;
		if(previousLabelNumber!=0)
		{
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(previousLabelNumber)))->Cursor=(TCursor)2;
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(previousLabelNumber)))->Font->Color=clBlack;
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(previousLabelNumber)))->Font->Style= TFontStyles()>>fsUnderline<<fsBold;
		}
		previousLabelNumber=current->Tag;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm22::MovieMouseEnter(TObject *Sender)
{
	TComponent* current = dynamic_cast<TComponent*>(Sender);
	if(SelectedMovieImage->Tag!=current->Tag &&((TLabel*)Form22->FindComponent("MovieExistsImage"+IntToStr(current->Tag)))->Tag==0)//Если фокус не на текущем выбранном фильме и фильм ещё не добавлен
	{
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Font->Color=(TColor)RGB(200,7,80);
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Font->Style= TFontStyles()<<fsUnderline<<fsBold;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm22::MovieMouseLeave(TObject *Sender)
{
	TComponent* current = dynamic_cast<TComponent*>(Sender);
	if(SelectedMovieImage->Tag!=current->Tag &&((TLabel*)Form22->FindComponent("MovieExistsImage"+IntToStr(current->Tag)))->Tag==0)
	{
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Font->Color=clBlack;
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(current->Tag)))->Font->Style= TFontStyles()>>fsUnderline<<fsBold;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm22::FormClose(TObject *Sender, TCloseAction &Action)
{
	MovieImage1->Picture->Assign(NULL);
	MovieImage2->Picture->Assign(NULL);
	MovieImage3->Picture->Assign(NULL);
	BackgroundImage->Picture->Assign(NULL);
	if(SelectedMovieImage->Tag!=0)
	{
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(SelectedMovieImage->Tag)))->Cursor=(TCursor)2;
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(SelectedMovieImage->Tag)))->Font->Color=clBlack;
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(SelectedMovieImage->Tag)))->Font->Style= TFontStyles()>>fsUnderline<<fsBold;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm22::FormCreate(TObject *Sender)
{
	MovieImage1->OnClick=MovieClick;MovieLabel1->OnClick=MovieClick;
	MovieImage2->OnClick=MovieClick;MovieLabel2->OnClick=MovieClick;
	MovieImage3->OnClick=MovieClick;MovieLabel3->OnClick=MovieClick;
	MovieLabel1->OnMouseEnter=MovieMouseEnter;MovieLabel1->OnMouseLeave=MovieMouseLeave;
	MovieLabel2->OnMouseEnter=MovieMouseEnter;MovieLabel2->OnMouseLeave=MovieMouseLeave;
	MovieLabel3->OnMouseEnter=MovieMouseEnter;MovieLabel3->OnMouseLeave=MovieMouseLeave;
	MovieImage1->OnMouseEnter=MovieMouseEnter;MovieImage1->OnMouseLeave=MovieMouseLeave;
	MovieImage2->OnMouseEnter=MovieMouseEnter;MovieImage2->OnMouseLeave=MovieMouseLeave;
	MovieImage3->OnMouseEnter=MovieMouseEnter;MovieImage3->OnMouseLeave=MovieMouseLeave;
}
//---------------------------------------------------------------------------

void __fastcall TForm22::FormShow(TObject *Sender)
{
	previousLabelNumber=0;
	BackgroundImage->Picture->LoadFromFile("Soft/Backgrounds/Background 7.2.jpg");
}
//---------------------------------------------------------------------------

void __fastcall TForm22::Button1Click(TObject *Sender)
{
	if(Button1->ModalResult==mrNone)
	{
		//Loading the movie's info------------------------------------------
		int selectedMovie = Form22->SelectedMovieImage->Tag;
		TStringList *movie=new TStringList();
		movie->LoadFromFile("Soft/Parser/Movies/Movie"+AnsiString(selectedMovie-1)+"/Movie"+AnsiString(selectedMovie-1)+".dat");
		//Checking and changing the language if necessary-------------------
		TStringList *movieLanguage=new TStringList();
		movieLanguage->LoadFromFile("Soft/Language/Language.ru");
		if(currentLanguage=="Ukrainian"||currentLanguage=="English")
		{
			for(int i=31;i<=54;i++)  //Genre
				movie->Strings[6]=StringReplace(movie->Strings[6],movieLanguage->Strings[i],lang->Strings[i],TReplaceFlags()<<rfReplaceAll);
			for(int i=138;i<=168;i++)//Country
				movie->Strings[3]=StringReplace(movie->Strings[3],movieLanguage->Strings[i],lang->Strings[i],TReplaceFlags()<<rfReplaceAll);
		}
		delete movieLanguage;movieLanguage=NULL;
		//Adding the film--------------------------------------------------- 2330 - edit
		int genresCount=0,countryCount=0;
		AnsiString ForbiddenChars = "\\/*<>|?";
		Form2->Caption=lang->Strings[75];Form2->Label12->Caption=lang->Strings[61];
		for(int i=0;i<Form2->CheckListBox1->Count;i++)//Genres
		{
			if(movie->Strings[6].Pos(Form2->CheckListBox1->Items->Strings[i]))
				{Form2->CheckListBox1->Checked[i]=true;genresCount++;}
			else
				Form2->CheckListBox1->Checked[i]=false;
		}
		for(int i=0;i<Form2->CheckListBox2->Count;i++)//Countries
		{
			if(movie->Strings[3].Pos(Form2->CheckListBox2->Items->Strings[i]))
				{Form2->CheckListBox2->Checked[i]=true;countryCount++;}
			else
				Form2->CheckListBox2->Checked[i]=false;
		}
		if(genresCount==0)Form2->CheckListBox1->Checked[0]=true;
		if(countryCount==0)Form2->CheckListBox2->Checked[0]=true;
		Form2->CheckBox1->Checked=false;Form2->CheckBox2->Checked=false;
		Form2->Memo1->Text=movie->Strings[9];Form2->Memo2->Text=movie->Strings[8];
		for(int i=0;i<movie->Strings[0].Length();i++)//Удаление запрещенных символов в название
		   if(ForbiddenChars.Pos(movie->Strings[0].c_str()[i])||movie->Strings[0].c_str()[i]=='"')
				{movie->Strings[0]=movie->Strings[0].Delete(i+1,1);i--;}
		Form2->Edit1->Text=movie->Strings[0];Form2->Edit2->Text=movie->Strings[10];
		Form2->Edit3->Text="";Form2->Edit4->Text="1";Form2->Edit5->Text=movie->Strings[5];
		Form2->Edit6->Text=movie->Strings[4];Form2->Edit7->Text=movie->Strings[1];Form2->Edit8->Text="1";
		for(int i=0;i<44;i++)
			if(Form2->ComboBox1->Items->Strings[i]==movie->Strings[2])
				{Form2->ComboBox1->ItemIndex=i;break;}
		if(Form2->ComboBox1->ItemIndex==-1)Form2->ComboBox1->ItemIndex=25;
		if(movie->Strings[6].Pos("Сериал"))
		{
			Form2->RadioButton2->Checked=true;
			Form2->ComboBox3->ItemIndex=Form2->ComboBox1->ItemIndex;
		}
		else
		{
			Form2->RadioButton1->Checked=true;
			Form2->ComboBox3->ItemIndex=25;
		}
		if(movie->Strings[7]=="-")Form2->ComboBox2->ItemIndex=70;   //не было указано
		else
		{
			AnsiString time;
			if(movie->Strings[7].c_str()[0]=='0')                   //больше часа (01:30)
			{
				int hour = movie->Strings[7].SubString(1,2).ToInt(),
					minutes = movie->Strings[7].SubString(4,2).ToInt();
				time = IntToStr(hour*60 + minutes);
			}                                                       //до часа (30:00)
			else time = movie->Strings[7].SubString(1,2);
			if(Form2->ComboBox2->Items->IndexOf(time+minutes_word)>=0)
				Form2->ComboBox2->ItemIndex=Form2->ComboBox2->Items->IndexOf(time+minutes_word);
			else
				Form2->ComboBox2->ItemIndex=70;
		}
		Form2->Image1->Picture->LoadFromFile("Soft/Parser/Movies/Movie"+AnsiString(selectedMovie-1)+"/Image.jpg");
		for (int i=1;i<=5;i++)
		((TImage*)Form2->FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
		Form2->SetFavourite(false);
		Form2->Rating->Caption="0.0";
		Form2->SetOpenMode("openedit");//Form2->FillList(list);
		Form2->seasons->Clear();Form2->seasons->Add("1");//Сезоны для сериала
		delete movie;movie=NULL;
		Form2->Position=poScreenCenter;
		Form2->ShowModal();
		if(Form2->Tag==0)
			{Button1->ModalResult=mrNone;return;}
		if(Form2->Tag==1)
		{
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(selectedMovie)))->Font->Color=clBlack;
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(selectedMovie)))->Font->Style= TFontStyles()>>fsUnderline<<fsBold;
			Button1->ModalResult=mrOk;Close(); //В Unit1.cpp начинается добавление
		}
	}
}
//---------------------------------------------------------------------------



