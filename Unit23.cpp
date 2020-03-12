//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit23.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma resource "*.dfm"
TForm23 *Form23;
bool MiddleMousePressed;int YMousePos;//Для прокрутки скролла с помощью движения мыши вверх-вниз
int currentLevel = 0;
//---------------------------------------------------------------------------               Высота между лейбл = 6
__fastcall TForm23::TForm23(TComponent* Owner)                                             //Высота между компонентами =36
	: TForm(Owner)
{
	//ScrollBox->BevelOuter=bvRaised  граница есть
	//ScrollBox->BevelOuter=bvNone    границы нету
}
//---------------------------------------------------------------------------

void __fastcall TForm23::PageControl1Change(TObject *Sender)
{
	MiddleMousePressed = false;
	if(PageControl1->Pages[3]->TabVisible==true)PageControl1->Pages[3]->TabVisible=false;
	if(PageControl1->Pages[4]->TabVisible==true)PageControl1->Pages[4]->TabVisible=false;
}
//---------------------------------------------------------------------------
                                                                                //!!Перенести Описание фильма в отдельный файл
void __fastcall TForm23::MovieClick(TObject *Sender)                            //!!Смещение компонентов после заполнения
{
	TComponent* current = dynamic_cast<TComponent*>(Sender);
	TStringList *movieInfo=new TStringList();
	movieInfo->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(current->Tag)+"/Movie.dat");
	MoviePoster->Picture->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(current->Tag)+"/Image.jpg");
	MovieName->Caption=			movieInfo->Strings[0];
	MovieOriginalName->Caption=	movieInfo->Strings[1];
	MovieAge->Caption=			movieInfo->Strings[2];
	MovieRating->Caption=		movieInfo->Strings[3];
	MovieVotes->Caption=		movieInfo->Strings[4];
	MovieIMDB->Caption=			movieInfo->Strings[5];
	MovieCY->Caption=			movieInfo->Strings[6];
	MovieGenre->Caption=		movieInfo->Strings[7];
	MovieDirector->Caption=		movieInfo->Strings[8];
	MovieScreenwriter->Caption=	movieInfo->Strings[9];
	MovieProducer->Caption=		movieInfo->Strings[10];
	MovieActors->Caption=		movieInfo->Strings[12];//12 - полный список актеров
	MoviePremiere->Caption=		movieInfo->Strings[13];
	MovieWorldPremiere->Caption=movieInfo->Strings[14];
	MovieDuration->Caption=		movieInfo->Strings[15];
	//MoviePlot->Text = 			movieInfo->Strings[16];
	MoviePlot->Lines->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(current->Tag)+"/Plot.dat");
	MovieSessions->Picture->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(current->Tag)+"/Session.png");//Delete LATER

	MovieOriginalName->Top = MovieName->Top+MovieName->Height+8;
	MoviePoster->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieCircle->Top = MovieOriginalName->Top+MovieOriginalName->Height+12;
	MovieAge->Top = MovieOriginalName->Top+MovieOriginalName->Height+16;
	MovieStar->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieRating->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieVotes->Top = MovieStar->Top+MovieStar->Height+6;
	MovieIMDB->Top = MovieStar->Top+MovieStar->Height+22;
	MovieCYLabel->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieCY->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieGenreLabel->Top = MovieCY->Top+MovieCY->Height+6;
	MovieGenre->Top = MovieCY->Top+MovieCY->Height+6;
	MovieDirectorLabel->Top = MovieGenre->Top+MovieGenre->Height+6;
	MovieDirector->Top = MovieGenre->Top+MovieGenre->Height+6;
	MovieScreenwriterLabel->Top = MovieDirector->Top+MovieDirector->Height+6;
    MovieScreenwriter->Top = MovieDirector->Top+MovieDirector->Height+6;
	MovieProducerLabel->Top = MovieScreenwriter->Top+MovieScreenwriter->Height+6;
	MovieProducer->Top = MovieScreenwriter->Top+MovieScreenwriter->Height+6;
	MovieActorsLabel->Top = MovieProducer->Top+MovieProducer->Height+6;
	MovieActors->Top = MovieProducer->Top+MovieProducer->Height+6;
	MoviePremiereLabel->Top = MovieActors->Top+MovieActors->Height+6;
	MoviePremiere->Top = MovieActors->Top+MovieActors->Height+6;
	MovieWorldPremiereLabel->Top = MoviePremiere->Top+MoviePremiere->Height+6;
	MovieWorldPremiere->Top = MoviePremiere->Top+MoviePremiere->Height+6;
	MovieDurationLabel->Top = MovieWorldPremiere->Top+MovieWorldPremiere->Height+6;
	MovieDuration->Top = MovieWorldPremiere->Top+MovieWorldPremiere->Height+6;

	if((MoviePoster->Top+MoviePoster->Height) > (MovieDuration->Top+MovieDuration->Height))
		PageControl2->Top=MoviePoster->Top+MoviePoster->Height+38;
	else
		PageControl2->Top=MovieDuration->Top+MovieDuration->Height+38;

	MovieAge->Visible=true;MovieCircle->Visible=true;

	PageControl1->Pages[3]->TabVisible=true;
	PageControl2->Pages[1]->TabVisible=true;
	PageControl1->ActivePageIndex=3;

	ScrollBox4->VertScrollBar->Position=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::MovieSoonClick(TObject *Sender)                            //!!Смещение компонентов после заполнения
{
	TComponent* current = dynamic_cast<TComponent*>(Sender);
	TStringList *movieInfo=new TStringList();
	movieInfo->LoadFromFile("Soft/CinemaAffiche/MoviesComingSoon/Movie"+AnsiString(current->Tag)+"/Movie.dat");
	MoviePoster->Picture->LoadFromFile("Soft/CinemaAffiche/MoviesComingSoon/Movie"+AnsiString(current->Tag)+"/Image.jpg");
	MovieName->Caption=			movieInfo->Strings[0];
	MovieOriginalName->Caption=	movieInfo->Strings[1];
	MovieRating->Caption=		movieInfo->Strings[2];
	MovieVotes->Caption=		movieInfo->Strings[3];
	MovieIMDB->Caption=			movieInfo->Strings[4];
	MovieCY->Caption=			movieInfo->Strings[5];
	MovieGenre->Caption=		movieInfo->Strings[6];
	MovieDirector->Caption=		movieInfo->Strings[7];
	MovieScreenwriter->Caption=	movieInfo->Strings[8];
	MovieProducer->Caption=		movieInfo->Strings[9];
	MovieActors->Caption=		movieInfo->Strings[11];//12 - полный список актеров
	MoviePremiere->Caption=		movieInfo->Strings[12];
	MovieWorldPremiere->Caption=movieInfo->Strings[13];
	MovieDuration->Caption=		movieInfo->Strings[14];
	//MoviePlot->Text = 			movieInfo->Strings[15];
	MoviePlot->Lines->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(current->Tag)+"/Plot.dat");

	MovieOriginalName->Top = MovieName->Top+MovieName->Height+8;
	MoviePoster->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieCircle->Top = MovieOriginalName->Top+MovieOriginalName->Height+12;
	MovieAge->Top = MovieOriginalName->Top+MovieOriginalName->Height+16;
	MovieStar->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieRating->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieVotes->Top = MovieStar->Top+MovieStar->Height+6;
	MovieIMDB->Top = MovieStar->Top+MovieStar->Height+22;
	MovieCYLabel->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieCY->Top = MovieOriginalName->Top+MovieOriginalName->Height+20;
	MovieGenreLabel->Top = MovieCY->Top+MovieCY->Height+6;
	MovieGenre->Top = MovieCY->Top+MovieCY->Height+6;
	MovieDirectorLabel->Top = MovieGenre->Top+MovieGenre->Height+6;
	MovieDirector->Top = MovieGenre->Top+MovieGenre->Height+6;
	MovieScreenwriterLabel->Top = MovieDirector->Top+MovieDirector->Height+6;
    MovieScreenwriter->Top = MovieDirector->Top+MovieDirector->Height+6;
	MovieProducerLabel->Top = MovieScreenwriter->Top+MovieScreenwriter->Height+6;
	MovieProducer->Top = MovieScreenwriter->Top+MovieScreenwriter->Height+6;
	MovieActorsLabel->Top = MovieProducer->Top+MovieProducer->Height+6;
	MovieActors->Top = MovieProducer->Top+MovieProducer->Height+6;
	MoviePremiereLabel->Top = MovieActors->Top+MovieActors->Height+6;
	MoviePremiere->Top = MovieActors->Top+MovieActors->Height+6;
	MovieWorldPremiereLabel->Top = MoviePremiere->Top+MoviePremiere->Height+6;
	MovieWorldPremiere->Top = MoviePremiere->Top+MoviePremiere->Height+6;
	MovieDurationLabel->Top = MovieWorldPremiere->Top+MovieWorldPremiere->Height+6;
	MovieDuration->Top = MovieWorldPremiere->Top+MovieWorldPremiere->Height+6;

	if((MoviePoster->Top+MoviePoster->Height) > (MovieDuration->Top+MovieDuration->Height))
		PageControl2->Top=MoviePoster->Top+MoviePoster->Height+38;
	else
		PageControl2->Top=MovieDuration->Top+MovieDuration->Height+38;

	MovieAge->Visible=false;MovieCircle->Visible=false;

	PageControl1->Pages[3]->TabVisible=true;
	PageControl2->Pages[1]->TabVisible=false;
	PageControl1->ActivePageIndex=3;

	ScrollBox4->VertScrollBar->Position=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::CinemaClick(TObject *Sender)
{
	TComponent* current = dynamic_cast<TComponent*>(Sender);
	TStringList *cinemaInfo=new TStringList();
	cinemaInfo->LoadFromFile("Soft/CinemaAffiche/Cinemas/Cinema"+AnsiString(current->Tag)+"/Cinema.dat");
	CinemaPoster->Picture->LoadFromFile("Soft/CinemaAffiche/Cinemas/Cinema"+AnsiString(current->Tag)+"/Image.jpg");
	CinemaName->Caption=		cinemaInfo->Strings[0];
	CinemaRating->Caption=		cinemaInfo->Strings[1];
	CinemaVotes->Caption=		cinemaInfo->Strings[2];
	CinemaAddress->Caption=		cinemaInfo->Strings[3];
	CinemaTelephone->Caption=	cinemaInfo->Strings[4];
	CinemaPlot->Text = 			cinemaInfo->Strings[5];
	CinemaSessions->Picture->LoadFromFile("Soft/CinemaAffiche/Cinemas/Cinema"+AnsiString(current->Tag)+"/Session.png");//Delete LATER

	CinemaTelephoneLabel->Top = CinemaAddress->Top+CinemaAddress->Height+6;
	CinemaTelephone->Top = CinemaAddress->Top+CinemaAddress->Height+6;

	PageControl1->Pages[4]->TabVisible=true;
	PageControl1->ActivePageIndex=4;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::MovieMouseEnter(TObject *Sender)
{
	TLabel* current=static_cast<TLabel*>(Sender);
	current->Font->Style= TFontStyles()<<fsUnderline<<fsBold;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::MovieMouseLeave(TObject *Sender)
{
	TLabel* current=static_cast<TLabel*>(Sender);
	current->Font->Style= TFontStyles()>>fsUnderline<<fsBold;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::FormCreate(TObject *Sender)
{
	for(int i=1;i<=7;i++)
	{
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->Cursor=(TCursor)1;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnClick=ScrollBoxClick;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnExit=ScrollBoxExit;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnMouseWheelDown=ScrollBoxMouseWheelDown;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnMouseWheelUp=ScrollBoxMouseWheelUp;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnMouseDown=ScrollBoxMouseDown;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnMouseUp=ScrollBoxMouseUp;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnMouseMove=ScrollBoxMouseMove;
		((TScrollBox*)Form23->FindComponent("ScrollBox"+AnsiString(i)))->OnMouseEnter=ScrollBoxMouseEnter;
	}
	PageControl1->Cursor=(TCursor)1;
	PageControl1->Pages[0]->Cursor=(TCursor)1;
	PageControl1->Pages[1]->Cursor=(TCursor)1;
	PageControl1->Pages[2]->Cursor=(TCursor)1;
	PageControl1->Pages[3]->Cursor=(TCursor)1;
	PageControl1->Pages[4]->Cursor=(TCursor)1;

	PageControl2->Cursor=(TCursor)1;
	PageControl2->Pages[0]->Cursor=(TCursor)1;
	PageControl2->Pages[1]->Cursor=(TCursor)1;

	PageControl3->Cursor=(TCursor)1;
	PageControl3->Pages[0]->Cursor=(TCursor)1;
	PageControl3->Pages[1]->Cursor=(TCursor)1;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::FormShow(TObject *Sender)
{
	DateLabel1->Caption = "на "+Now().CurrentDate();
	DateLabel2->Caption = "на "+Now().CurrentDate();
	DateLabel3->Caption = "на "+Now().CurrentDate();

	clearMoviesVector();
	addMovies();
	clearCinemasVector();
	addCinemas();
	clearMoviesComingSoonVector();
	addMoviesComingSoon();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
	if(Key==char(27))Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxClick(TObject *Sender)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	current->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxExit(TObject *Sender)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	MiddleMousePressed=false;current->Cursor=(TCursor)1;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxMouseWheelDown(TObject *Sender, TShiftState Shift,
			const TPoint &MousePos, bool &Handled)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	current->VertScrollBar->Position += 15;
	Handled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxMouseWheelUp(TObject *Sender, TShiftState Shift,
			const TPoint &MousePos, bool &Handled)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	current->VertScrollBar->Position -= 15;
	Handled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	if(Button==mbMiddle){MiddleMousePressed=true;current->Cursor=crSizeAll;}
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxMouseUp(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	MiddleMousePressed=false;current->Cursor=(TCursor)1;
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxMouseMove(TObject *Sender, TShiftState Shift, int X,
			int Y)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	if(MiddleMousePressed)
	{
		if(Y>YMousePos)current->VertScrollBar->Position += 10;
		if(Y<YMousePos)current->VertScrollBar->Position -= 10;
		YMousePos=Y;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm23::ScrollBoxMouseEnter(TObject *Sender)
{
	TScrollBox* current=static_cast<TScrollBox*>(Sender);
	current->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::Button1Click(TObject *Sender)
{
	clearMoviesVector();
	addMovies();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::Button2Click(TObject *Sender)
{
	clearCinemasVector();
	addCinemas();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::Button3Click(TObject *Sender)
{
	clearMoviesComingSoonVector();
	addMoviesComingSoon();
}
//---------------------------------------------------------------------------

	/*TSearchRec sr;
	if (FindFirst("Films from other catalogs\\*.*", faDirectory, sr) == 0)
	{
		do
		{
			if( faDirectory  == sr.Attr )
				if( sr.Name != "." && sr.Name != "..")
				{
					name=sr.Name;
				}
		}
		while (FindNext(sr) == 0);
		FindClose(sr);
	}*/

void TForm23::addMovies()
{
	TStringList *movieInfo=new TStringList();
	movieInfo->LoadFromFile("Soft/CinemaAffiche/Movies/Movies_links.dat");
	int moviesNumber = movieInfo->Count;
	//moviesNumber = 5;
	currentLevel=0;
	for (int i = 0; i < moviesNumber; i++)
	{
		movieInfo->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(i)+"/Movie.dat");

		Movie movie;

		movie.number = i;

		movie.Poster=new TImage(ScrollBox1);
		movie.Poster->Parent=ScrollBox1;
		movie.Poster->Name="Poster"+AnsiString(i);
		movie.Poster->Top=currentLevel+18;//+188*i
		movie.Poster->Left=20;
		movie.Poster->Width=118;
		movie.Poster->Height=152;
		movie.Poster->Stretch=true;
		movie.Poster->Cursor=(TCursor)2;
		movie.Poster->Tag=i;
		movie.Poster->OnClick=MovieClick;
		movie.Poster->Picture->LoadFromFile("Soft/CinemaAffiche/Movies/Movie"+AnsiString(i)+"/Image.jpg");//0 -> i

		movie.Circle=new TImage(ScrollBox1);
		movie.Circle->Parent=ScrollBox1;
		movie.Circle->Name="Circle"+AnsiString(i);
		movie.Circle->Top=currentLevel+10;//+188*i
		movie.Circle->Left=13;
		movie.Circle->Width=30;
		movie.Circle->Height=30;
		movie.Circle->Cursor=(TCursor)2;
		movie.Circle->Tag=i;
		movie.Circle->OnClick=MovieClick;
		movie.Circle->Picture->LoadFromFile("Soft/Buttons/Agerate.png");

		movie.Star=new TImage(ScrollBox1);
		movie.Star->Parent=ScrollBox1;
		movie.Star->Name="Star"+AnsiString(i);
		movie.Star->Top=currentLevel+18;//+188*i
		movie.Star->Left=615;
		movie.Star->Width=30;
		movie.Star->Height=30;
		movie.Star->Picture->LoadFromFile("Soft/Buttons/Star(rating).png");

		movie.Age=new TLabel(ScrollBox1);
		movie.Age->Parent=ScrollBox1;
		movie.Age->Name="Age"+AnsiString(i);
		movie.Age->Top=currentLevel+14;//+188*i
		movie.Age->Left=13;
		movie.Age->Width=30;
		movie.Age->Height=17;
		movie.Age->Alignment=taCenter;
		movie.Age->AutoSize=false;
		movie.Age->ParentFont=false;
		movie.Age->Font->Name="Century Gothic";
		movie.Age->Font->Size=11;
		movie.Age->Font->Color=clWhite;
		movie.Age->Font->Style=TFontStyles()>>fsBold;
		movie.Age->Cursor=(TCursor)2;
		movie.Age->Caption = movieInfo->Strings[2];
		movie.Age->Tag=i;
		movie.Age->OnClick=MovieClick;

		movie.Rating=new TLabel(ScrollBox1);
		movie.Rating->Parent=ScrollBox1;
		movie.Rating->Name="Rating"+AnsiString(i);
		movie.Rating->Top=currentLevel+18;//+188*i
		movie.Rating->Left=651;
		movie.Rating->ParentFont=false;
		movie.Rating->Font->Name="Century Gothic";
		movie.Rating->Font->Size=18;
		movie.Rating->Font->Color=clBlack;
		movie.Rating->Font->Style=TFontStyles()<<fsBold;
		movie.Rating->Caption = movieInfo->Strings[3];

		movie.Votes=new TLabel(ScrollBox1);
		movie.Votes->Parent=ScrollBox1;
		movie.Votes->Name="Votes"+AnsiString(i);
		movie.Votes->Top=currentLevel+54;//+188*i
		movie.Votes->Left=615;
		movie.Votes->Caption = movieInfo->Strings[4];

		movie.IMDB=new TLabel(ScrollBox1);
		movie.IMDB->Parent=ScrollBox1;
		movie.IMDB->Name="IMDB"+AnsiString(i);
		movie.IMDB->Top=currentLevel+70;//+188*i
		movie.IMDB->Left=615;
		movie.IMDB->Caption = movieInfo->Strings[5];

		movie.Name=new TLabel(ScrollBox1);
		movie.Name->Parent=ScrollBox1;
		movie.Name->Name="Name"+AnsiString(i);
		movie.Name->Top=currentLevel+18;//+188*i
		movie.Name->Left=160;
		movie.Name->Constraints->MinWidth=400;
		movie.Name->Constraints->MaxWidth=400;
		movie.Name->ParentFont=false;
		movie.Name->Font->Name="Tahoma";
		movie.Name->Font->Size=14;
		movie.Name->Font->Color=clHotLight;
		movie.Name->Font->Style=TFontStyles()<<fsBold;
		movie.Name->WordWrap=true;
		movie.Name->Caption = movieInfo->Strings[0];
		movie.Name->OnClick=MovieClick;
		movie.Name->OnMouseEnter=MovieMouseEnter;
		movie.Name->OnMouseLeave=MovieMouseLeave;
		movie.Name->Cursor=(TCursor)2;
		movie.Name->Tag=i;
		//Caption=movie.Name->Caption;//Если текст в 3 ряда - 3 ряд не показывает

		movie.CYG=new TLabel(ScrollBox1);
		movie.CYG->Parent=ScrollBox1;
		movie.CYG->Name="CYG"+AnsiString(i);
		movie.CYG->Top=movie.Name->Top+movie.Name->Height+8;//+188*i
		movie.CYG->Left=160;
		movie.CYG->Constraints->MinWidth=400;
		movie.CYG->Constraints->MaxWidth=400;
		movie.CYG->ParentFont=false;
		movie.CYG->Font->Name="Century Gothic";
		movie.CYG->Font->Size=10;
		movie.CYG->Font->Color=clGrayText;
		movie.CYG->Font->Style=TFontStyles()<<fsBold;
		movie.CYG->WordWrap=true;
		movie.CYG->Caption = movieInfo->Strings[6]+" ("+movieInfo->Strings[7]+")";//"Великобританія, 2019 (драма)";

		movie.DirectorLabel=new TLabel(ScrollBox1);
		movie.DirectorLabel->Parent=ScrollBox1;
		movie.DirectorLabel->Name="DirectorLabel"+AnsiString(i);
		movie.DirectorLabel->Top=movie.CYG->Top+movie.CYG->Height+8;//+188*i
		movie.DirectorLabel->Left=160;
		movie.DirectorLabel->Caption = "Режисер:";

		movie.Director=new TLabel(ScrollBox1);
		movie.Director->Parent=ScrollBox1;
		movie.Director->Name="Director"+AnsiString(i);
		movie.Director->Top=movie.CYG->Top+movie.CYG->Height+8;//+188*i
		movie.Director->Left=228;
		movie.Director->Constraints->MinWidth=332;
		movie.Director->Constraints->MaxWidth=332;
		movie.Director->ParentFont=false;
		movie.Director->Font->Name="Century Gothic";
		movie.Director->Font->Size=10;
		movie.Director->Font->Color=clBlack;
		movie.Director->Font->Style=TFontStyles()<<fsBold;
		movie.Director->WordWrap=true;
		movie.Director->Caption = movieInfo->Strings[8];

		movie.ActorsLabel=new TLabel(ScrollBox1);
		movie.ActorsLabel->Parent=ScrollBox1;
		movie.ActorsLabel->Name="ActorsLabel"+AnsiString(i);
		movie.ActorsLabel->Top=movie.Director->Top+movie.Director->Height+8;
		movie.ActorsLabel->Left=160;
		movie.ActorsLabel->Caption = "Актори:";

		movie.Actors=new TLabel(ScrollBox1);
		movie.Actors->Parent=ScrollBox1;
		movie.Actors->Name="Actors"+AnsiString(i);
		movie.Actors->Top=movie.Director->Top+movie.Director->Height+8;
		movie.Actors->Left=217;
		movie.Actors->Constraints->MinWidth=343;
		movie.Actors->Constraints->MaxWidth=343;
		movie.Actors->ParentFont=false;
		movie.Actors->Font->Name="Century Gothic";
		movie.Actors->Font->Size=10;
		movie.Actors->Font->Color=clBlack;
		movie.Actors->Font->Style=TFontStyles()<<fsBold;
		movie.Actors->WordWrap=true;
		movie.Actors->Caption = movieInfo->Strings[11];

		movie.PremiereLabel=new TLabel(ScrollBox1);
		movie.PremiereLabel->Parent=ScrollBox1;
		movie.PremiereLabel->Name="PremiereLabel"+AnsiString(i);
		movie.PremiereLabel->Top=movie.Actors->Top+movie.Actors->Height+8;
		movie.PremiereLabel->Left=160;
		movie.PremiereLabel->Caption = "Прем'єра в Україні:";

		movie.Premiere=new TLabel(ScrollBox1);
		movie.Premiere->Parent=ScrollBox1;
		movie.Premiere->Name="Premiere"+AnsiString(i);
		movie.Premiere->Top=movie.Actors->Top+movie.Actors->Height+8;
		movie.Premiere->Left=297;
		movie.Premiere->ParentFont=false;
		movie.Premiere->Font->Name="Century Gothic";
		movie.Premiere->Font->Size=10;
		movie.Premiere->Font->Color=clBlack;
		movie.Premiere->Font->Style=TFontStyles()<<fsBold;
		movie.Premiere->Caption = movieInfo->Strings[13];

		if((movie.Poster->Top+movie.Poster->Height) > (movie.Premiere->Top+movie.Premiere->Height))
		{                                                                        //Если высота информации < высоты постера ->
			currentLevel = movie.Poster->Top+movie.Poster->Height+18;            //перейти на шаг высоты постера
			if(i==moviesNumber-1) //Увеличить отступ после последнего фильма
				movie.Premiere->Height+=movie.Poster->Top+movie.Poster->Height-(movie.Premiere->Top+movie.Premiere->Height)+20;
		}
		else
		{
			currentLevel = movie.Premiere->Top+movie.Premiere->Height+18;        // || перейти на шаг высоты информации
			if(i==moviesNumber-1) //Увеличить отступ после последнего фильма
				movie.Premiere->Height+=movie.Premiere->Top+movie.Premiere->Height-(movie.Poster->Top+movie.Poster->Height)+20;
		}

		movies.push_back(movie);
	}
	delete movieInfo;movieInfo = NULL;
}
//---------------------------------------------------------------------------

void TForm23::clearMoviesVector()
{
	for (int i = 0; i < movies.size(); i++)//while(movies.size()!=0)
	{
		delete movies[i].Poster;movies[i].Poster=NULL;
		delete movies[i].Circle;movies[i].Circle=NULL;
		delete movies[i].Star;movies[i].Star=NULL;
		delete movies[i].Age;movies[i].Age=NULL;
		delete movies[i].Name;movies[i].Name=NULL;
		delete movies[i].CYG;movies[i].CYG=NULL;
		delete movies[i].DirectorLabel;movies[i].DirectorLabel=NULL;
		delete movies[i].Director;movies[i].Director=NULL;
		delete movies[i].ActorsLabel;movies[i].ActorsLabel=NULL;
		delete movies[i].Actors;movies[i].Actors=NULL;
		delete movies[i].PremiereLabel;movies[i].PremiereLabel=NULL;
		delete movies[i].Premiere;movies[i].Premiere=NULL;
		delete movies[i].Rating;movies[i].Rating=NULL;
		delete movies[i].Votes;movies[i].Votes=NULL;
		delete movies[i].IMDB;movies[i].IMDB=NULL;
	}
	movies.clear();
}
//---------------------------------------------------------------------------

void TForm23::addCinemas()
{
	TStringList *cinemaInfo=new TStringList();
	cinemaInfo->LoadFromFile("Soft/CinemaAffiche/Cinemas/Cinemas_links.dat");
	int cinemaNumber = cinemaInfo->Count;
	currentLevel=0;
	for (int i = 0; i < cinemaNumber; i++)
	{
		cinemaInfo->LoadFromFile("Soft/CinemaAffiche/Cinemas/Cinema"+AnsiString(i)+"/Cinema.dat");

		Cinema cinema;

		cinema.number = i;

		cinema.Poster=new TImage(ScrollBox2);
		cinema.Poster->Parent=ScrollBox2;
		cinema.Poster->Name="CinemaPoster"+AnsiString(i);
		cinema.Poster->Top=currentLevel+18;
		cinema.Poster->Left=20;
		cinema.Poster->Width=158;
		cinema.Poster->Height=88;
		cinema.Poster->Cursor=(TCursor)2;
		cinema.Poster->Stretch=true;
		cinema.Poster->OnClick=CinemaClick;
		cinema.Poster->Tag=i;
		cinema.Poster->Picture->LoadFromFile("Soft/CinemaAffiche/Cinemas/Cinema"+AnsiString(i)+"/Image.jpg");//0 -> i

		cinema.Star=new TImage(ScrollBox2);
		cinema.Star->Parent=ScrollBox2;
		cinema.Star->Name="CinemaStar"+AnsiString(i);
		cinema.Star->Top=currentLevel+38;
		cinema.Star->Left=614;
		cinema.Star->Width=30;
		cinema.Star->Height=30;
		cinema.Star->Picture->LoadFromFile("Soft/Buttons/Star(rating).png");

		cinema.Popularity=new TLabel(ScrollBox2);
		cinema.Popularity->Parent=ScrollBox2;
		cinema.Popularity->Name="CinemaPopularity"+AnsiString(i);
		cinema.Popularity->Top=currentLevel+18;
		cinema.Popularity->Left=614;
		cinema.Popularity->ParentFont=false;
		cinema.Popularity->Font->Name="Century Gothic";
		cinema.Popularity->Font->Size=10;
		cinema.Popularity->Font->Color=clGrayText;
		cinema.Popularity->Font->Style=TFontStyles()<<fsBold;
		cinema.Popularity->Caption = "популярність";

		cinema.Rating=new TLabel(ScrollBox2);
		cinema.Rating->Parent=ScrollBox2;
		cinema.Rating->Name="CinemaRating"+AnsiString(i);
		cinema.Rating->Top=currentLevel+38;
		cinema.Rating->Left=650;
		cinema.Rating->ParentFont=false;
		cinema.Rating->Font->Name="Century Gothic";
		cinema.Rating->Font->Size=18;
		cinema.Rating->Font->Color=clBlack;
		cinema.Rating->Font->Style=TFontStyles()<<fsBold;
		cinema.Rating->Caption = cinemaInfo->Strings[1];

		cinema.Votes=new TLabel(ScrollBox2);
		cinema.Votes->Parent=ScrollBox2;
		cinema.Votes->Name="CinemaVotes"+AnsiString(i);
		cinema.Votes->Top=currentLevel+74;
		cinema.Votes->Left=614;
		cinema.Votes->Caption = cinemaInfo->Strings[2];

		cinema.Name=new TLabel(ScrollBox2);
		cinema.Name->Parent=ScrollBox2;
		cinema.Name->Name="CinemaName"+AnsiString(i);
		cinema.Name->Top=currentLevel+18;//+188*i
		cinema.Name->Left=190;
		cinema.Name->Constraints->MinWidth=400;
		cinema.Name->Constraints->MaxWidth=400;
		cinema.Name->ParentFont=false;
		cinema.Name->Font->Name="Tahoma";
		cinema.Name->Font->Size=14;
		cinema.Name->Font->Color=clHotLight;
		cinema.Name->Font->Style=TFontStyles()<<fsBold;
		cinema.Name->WordWrap=true;
		cinema.Name->Caption = cinemaInfo->Strings[0];
		cinema.Name->OnClick=CinemaClick;
		cinema.Name->OnMouseEnter=MovieMouseEnter;
		cinema.Name->OnMouseLeave=MovieMouseLeave;
		cinema.Name->Cursor=(TCursor)2;
		cinema.Name->Tag=i;
		//Caption=movie.Name->Caption;//>>

		cinema.AddressLabel=new TLabel(ScrollBox2);
		cinema.AddressLabel->Parent=ScrollBox2;
		cinema.AddressLabel->Name="CinemaAddressLabel"+AnsiString(i);
		cinema.AddressLabel->Top=cinema.Name->Top+cinema.Name->Height+8;
		cinema.AddressLabel->Left=190;
		cinema.AddressLabel->Caption = "Адреса:";

		cinema.Address=new TLabel(ScrollBox2);
		cinema.Address->Parent=ScrollBox2;
		cinema.Address->Name="CinemaAddress"+AnsiString(i);
		cinema.Address->Top=cinema.Name->Top+cinema.Name->Height+8;
		cinema.Address->Left=258;
		cinema.Address->Constraints->MinWidth=343;
		cinema.Address->Constraints->MaxWidth=343;
		cinema.Address->ParentFont=false;
		cinema.Address->Font->Name="Century Gothic";
		cinema.Address->Font->Size=10;
		cinema.Address->Font->Color=clBlack;
		cinema.Address->Font->Style=TFontStyles()<<fsBold;
		cinema.Address->WordWrap=true;
		cinema.Address->Caption = cinemaInfo->Strings[3];

		cinema.TelephoneLabel=new TLabel(ScrollBox2);
		cinema.TelephoneLabel->Parent=ScrollBox2;
		cinema.TelephoneLabel->Name="CinemaTelephoneLabel"+AnsiString(i);
		cinema.TelephoneLabel->Top=cinema.Address->Top+cinema.Address->Height+8;
		cinema.TelephoneLabel->Left=190;
		cinema.TelephoneLabel->Caption = "Телефон:";

		cinema.Telephone=new TLabel(ScrollBox2);
		cinema.Telephone->Parent=ScrollBox2;
		cinema.Telephone->Name="CinemaTelephone"+AnsiString(i);
		cinema.Telephone->Top=cinema.Address->Top+cinema.Address->Height+8;
		cinema.Telephone->Left=258;
		cinema.Telephone->Constraints->MinWidth=343;
		cinema.Telephone->Constraints->MaxWidth=343;
		cinema.Telephone->ParentFont=false;
		cinema.Telephone->Font->Name="Century Gothic";
		cinema.Telephone->Font->Size=10;
		cinema.Telephone->Font->Color=clBlack;
		cinema.Telephone->Font->Style=TFontStyles()<<fsBold;
		cinema.Telephone->WordWrap=true;
		cinema.Telephone->Caption = cinemaInfo->Strings[4];

		if((cinema.Poster->Top+cinema.Poster->Height) > (cinema.Telephone->Top+cinema.Telephone->Height))
		{                                                                       //Если высота информации < высоты постера ->
			currentLevel = cinema.Poster->Top+cinema.Poster->Height+18;         //перейти на шаг высоты постера
			if(i==cinemaNumber-1) //Увеличить отступ после последнего фильма
				cinema.Telephone->Height+=cinema.Poster->Top+cinema.Poster->Height-(cinema.Telephone->Top+cinema.Telephone->Height)+20;
		}
		else
		{
			currentLevel = cinema.Telephone->Top+cinema.Telephone->Height+18;    //перейти на шаг высоты информации
			if(i==cinemaNumber-1) //Увеличить отступ после последнего фильма
				cinema.Telephone->Height+=cinema.Telephone->Top+cinema.Telephone->Height-(cinema.Poster->Top+cinema.Poster->Height)+20;
		}

		cinemas.push_back(cinema);
	}
	delete cinemaInfo;cinemaInfo = NULL;
}
//---------------------------------------------------------------------------

void TForm23::clearCinemasVector()
{
	for (int i = 0; i < cinemas.size(); i++)//while(movies.size()!=0)
	{
		delete cinemas[i].Poster;cinemas[i].Poster=NULL;
		delete cinemas[i].Star;cinemas[i].Star=NULL;
		delete cinemas[i].Name;cinemas[i].Name=NULL;
		delete cinemas[i].AddressLabel;cinemas[i].AddressLabel=NULL;
		delete cinemas[i].Address;cinemas[i].Address=NULL;
		delete cinemas[i].TelephoneLabel;cinemas[i].TelephoneLabel=NULL;
		delete cinemas[i].Telephone;cinemas[i].Telephone=NULL;
		delete cinemas[i].Popularity;cinemas[i].Popularity=NULL;
		delete cinemas[i].Rating;cinemas[i].Rating=NULL;
		delete cinemas[i].Votes;cinemas[i].Votes=NULL;
	}
	cinemas.clear();
}
//---------------------------------------------------------------------------

void TForm23::addMoviesComingSoon()
{
	TStringList *movieInfo=new TStringList();
	movieInfo->LoadFromFile("Soft/CinemaAffiche/MoviesComingSoon/Movies_links.dat");
	int moviesNumber = movieInfo->Count;
	currentLevel=0;
	for (int i = 0; i < moviesNumber; i++)
	{
		movieInfo->LoadFromFile("Soft/CinemaAffiche/MoviesComingSoon/Movie"+AnsiString(i)+"/Movie.dat");

		MovieComingSoon movie;

		movie.number = i;

		movie.Poster=new TImage(ScrollBox3);
		movie.Poster->Parent=ScrollBox3;
		movie.Poster->Name="MovieSoonPoster"+AnsiString(i);
		movie.Poster->Top=currentLevel+18;//+188*i
		movie.Poster->Left=20;
		movie.Poster->Width=118;
		movie.Poster->Height=152;
		movie.Poster->Stretch=true;
		movie.Poster->Cursor=(TCursor)2;
		movie.Poster->OnClick=MovieSoonClick;
		movie.Poster->Tag=i;
		movie.Poster->Picture->LoadFromFile("Soft/CinemaAffiche/MoviesComingSoon/Movie"+AnsiString(i)+"/Image.jpg");//0 -> i

		movie.Panel=new TPanel(ScrollBox3);
		movie.Panel->Parent=ScrollBox3;
		movie.Panel->Name="MovieSoonPanel"+AnsiString(i);
		movie.Panel->Caption="";
		movie.Panel->Top=currentLevel+18;
		movie.Panel->Left=555;
		movie.Panel->Width=148;
		movie.Panel->Height=60;
		movie.Panel->ParentFont=false;
		movie.Panel->BevelInner=bvRaised;
		movie.Panel->BorderStyle=bsSingle;
		movie.Panel->Color=clBlack;
		movie.Panel->Cursor=(TCursor)1;

		movie.PremiereDate=new TLabel(movie.Panel);
		movie.PremiereDate->Parent=movie.Panel;
		movie.PremiereDate->Name="MoviePremiereDate"+AnsiString(i);
		movie.PremiereDate->Top=3;
		movie.PremiereDate->Left=6;
		movie.PremiereDate->ParentFont=false;
		movie.PremiereDate->Font->Name="Century Gothic";
		movie.PremiereDate->Font->Size=14;
		movie.PremiereDate->Font->Color=clBlack;
		movie.PremiereDate->Font->Style=TFontStyles()<<fsBold;
		movie.PremiereDate->Caption = movieInfo->Strings[15];

		movie.LeftDays=new TLabel(movie.Panel);
		movie.LeftDays->Parent=movie.Panel;
		movie.LeftDays->Name="MovieLeftDays"+AnsiString(i);
		movie.LeftDays->Top=34;
		movie.LeftDays->Left=6;
		movie.LeftDays->Font->Size=10;
		movie.LeftDays->Font->Style=TFontStyles()>>fsBold;
		movie.LeftDays->Caption = movieInfo->Strings[16];

		movie.Name=new TLabel(ScrollBox3);
		movie.Name->Parent=ScrollBox3;
		movie.Name->Name="MovieSoonName"+AnsiString(i);
		movie.Name->Top=currentLevel+18;
		movie.Name->Left=160;
		movie.Name->Constraints->MinWidth=377;
		movie.Name->Constraints->MaxWidth=377;
		movie.Name->ParentFont=false;
		movie.Name->Font->Name="Tahoma";
		movie.Name->Font->Size=14;
		movie.Name->Font->Color=clHotLight;
		movie.Name->Font->Style=TFontStyles()<<fsBold;
		movie.Name->WordWrap=true;
		movie.Name->Caption = movieInfo->Strings[0];
		movie.Name->OnClick=MovieSoonClick;
		movie.Name->OnMouseEnter=MovieMouseEnter;
		movie.Name->OnMouseLeave=MovieMouseLeave;
		movie.Name->Cursor=(TCursor)2;
		movie.Name->Tag=i;
		//Caption=movie.Name->Caption;//Если текст в 3 ряда - 3 ряд не показывает

		movie.CYG=new TLabel(ScrollBox3);
		movie.CYG->Parent=ScrollBox3;
		movie.CYG->Name="MovieSoonCYG"+AnsiString(i);
		movie.CYG->Top=movie.Name->Top+movie.Name->Height+8;
		movie.CYG->Left=160;
		movie.CYG->Constraints->MinWidth=377;
		movie.CYG->Constraints->MaxWidth=377;
		movie.CYG->ParentFont=false;
		movie.CYG->Font->Name="Century Gothic";
		movie.CYG->Font->Size=10;
		movie.CYG->Font->Color=clGrayText;
		movie.CYG->Font->Style=TFontStyles()<<fsBold;
		movie.CYG->WordWrap=true;
		movie.CYG->Caption = movieInfo->Strings[5]+" ("+movieInfo->Strings[6]+")";

		movie.DirectorLabel=new TLabel(ScrollBox3);
		movie.DirectorLabel->Parent=ScrollBox3;
		movie.DirectorLabel->Name="MovieSoonDirectorLabel"+AnsiString(i);
		movie.DirectorLabel->Top=movie.CYG->Top+movie.CYG->Height+8;
		movie.DirectorLabel->Left=160;
		movie.DirectorLabel->Caption = "Режисер:";

		movie.Director=new TLabel(ScrollBox3);
		movie.Director->Parent=ScrollBox3;
		movie.Director->Name="MovieSoonDirector"+AnsiString(i);
		movie.Director->Top=movie.CYG->Top+movie.CYG->Height+8;//+188*i
		movie.Director->Left=228;
		movie.Director->Constraints->MinWidth=320;
		movie.Director->Constraints->MaxWidth=320;
		movie.Director->ParentFont=false;
		movie.Director->Font->Name="Century Gothic";
		movie.Director->Font->Size=10;
		movie.Director->Font->Color=clBlack;
		movie.Director->Font->Style=TFontStyles()<<fsBold;
		movie.Director->WordWrap=true;
		movie.Director->Caption = movieInfo->Strings[7];

		movie.ActorsLabel=new TLabel(ScrollBox3);
		movie.ActorsLabel->Parent=ScrollBox3;
		movie.ActorsLabel->Name="MovieSoonActorsLabel"+AnsiString(i);
		movie.ActorsLabel->Top=movie.Director->Top+movie.Director->Height+8;
		movie.ActorsLabel->Left=160;
		movie.ActorsLabel->Caption = "Актори:";

		movie.Actors=new TLabel(ScrollBox3);
		movie.Actors->Parent=ScrollBox3;
		movie.Actors->Name="MovieSoonActors"+AnsiString(i);
		movie.Actors->Top=movie.Director->Top+movie.Director->Height+8;
		movie.Actors->Left=217;
		movie.Actors->Constraints->MinWidth=320;
		movie.Actors->Constraints->MaxWidth=320;
		movie.Actors->ParentFont=false;
		movie.Actors->Font->Name="Century Gothic";
		movie.Actors->Font->Size=10;
		movie.Actors->Font->Color=clBlack;
		movie.Actors->Font->Style=TFontStyles()<<fsBold;
		movie.Actors->WordWrap=true;
		movie.Actors->Caption = movieInfo->Strings[10];

		if((movie.Poster->Top+movie.Poster->Height) > (movie.Actors->Top+movie.Actors->Height))
		{                                                                       //Если высота информации < высоты постера ->
			currentLevel = movie.Poster->Top+movie.Poster->Height+18;           //перейти на шаг высоты постера
			if(i==moviesNumber-1) //Увеличить отступ после последнего фильма
				movie.Actors->Height+=movie.Poster->Top+movie.Poster->Height-(movie.Actors->Top+movie.Actors->Height)+20;
		}
		else
		{
			currentLevel = movie.Actors->Top+movie.Actors->Height+18;            // || перейти на шаг высоты информации
			if(i==moviesNumber-1) //Увеличить отступ после последнего фильма
				movie.Actors->Height+=movie.Actors->Top+movie.Actors->Height-(movie.Poster->Top+movie.Poster->Height)+20;
		}

		moviesComingSoon.push_back(movie);
	}
	delete movieInfo;movieInfo = NULL;
}
//---------------------------------------------------------------------------

void TForm23::clearMoviesComingSoonVector()
{
	for (int i = 0; i < moviesComingSoon.size(); i++)//while(movies.size()!=0)
	{
		delete moviesComingSoon[i].Poster;moviesComingSoon[i].Poster=NULL;
		delete moviesComingSoon[i].PremiereDate;moviesComingSoon[i].PremiereDate=NULL;
		delete moviesComingSoon[i].LeftDays;moviesComingSoon[i].LeftDays=NULL;
		delete moviesComingSoon[i].Panel;moviesComingSoon[i].Panel=NULL;
		delete moviesComingSoon[i].Name;moviesComingSoon[i].Name=NULL;
		delete moviesComingSoon[i].CYG;moviesComingSoon[i].CYG=NULL;
		delete moviesComingSoon[i].DirectorLabel;moviesComingSoon[i].DirectorLabel=NULL;
		delete moviesComingSoon[i].Director;moviesComingSoon[i].Director=NULL;
		delete moviesComingSoon[i].ActorsLabel;moviesComingSoon[i].ActorsLabel=NULL;
		delete moviesComingSoon[i].Actors;moviesComingSoon[i].Actors=NULL;
	}
	moviesComingSoon.clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm23::MoviePlotChange(TObject *Sender)
{
	if(MoviePlot->Lines->Count<9)
		MoviePlot->ScrollBars=ssNone;
	else
		MoviePlot->ScrollBars=ssVertical;
}
//---------------------------------------------------------------------------



void __fastcall TForm23::Button4Click(TObject *Sender)
{
	ScrollBox4->VertScrollBar->Position=0;
}
//---------------------------------------------------------------------------

