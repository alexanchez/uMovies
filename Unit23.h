//---------------------------------------------------------------------------

#ifndef Unit23H
#define Unit23H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Chart.hpp"
#include "Series.hpp"
#include "TeEngine.hpp"
#include "TeeProcs.hpp"
#include <CategoryButtons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <pngimage.hpp>
#include <Graphics.hpp>
#include <vector>
//---------------------------------------------------------------------------
class TForm23 : public TForm
{
__published:	// IDE-managed Components
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TLabel *CurrentLocation;
	TComboBox *CityBox;
	TLabel *Label1;
	TImage *Image1;
	TLabel *DateLabel1;
	TComboBox *CinemaBox;
	TScrollBox *ScrollBox1;
	TImage *TestStar;
	TImage *PosterImage;
	TLabel *RatingLabel;
	TLabel *VotesLabel;
	TLabel *IMDBLabel;
	TLabel *CountryYearGenreLabel;
	TLabel *TestDirectorLabel;
	TLabel *TestActorsLabel;
	TLabel *NameLabel;
	TLabel *TestPremiereLabel;
	TImage *CircleImage;
	TLabel *DirectorLabel;
	TLabel *AgeLabel;
	TLabel *ActorsLabel;
	TLabel *Label11;
	TComboBox *CityBox1;
	TLabel *Label12;
	TLabel *PremiereLabel;
	TLabel *Label2;
	TLabel *Label3;
	TImage *Image2;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TImage *Image3;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label13;
	TLabel *Label14;
	TImage *Image4;
	TLabel *Label15;
	TImage *Image5;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label20;
	TLabel *Label21;
	TLabel *Label22;
	TLabel *Label23;
	TLabel *Label24;
	TLabel *Label25;
	TLabel *Label26;
	TLabel *Label27;
	TImage *Image6;
	TImage *Image7;
	TScrollBox *ScrollBox2;
	TImage *Image9;
	TImage *Image10;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TLabel *Label32;
	TLabel *Label33;
	TLabel *Label34;
	TLabel *Label36;
	TLabel *Label37;
	TScrollBox *ScrollBox3;
	TImage *Image8;
	TLabel *Label31;
	TLabel *Label35;
	TLabel *Label38;
	TLabel *Label40;
	TLabel *Label39;
	TLabel *Label41;
	TPanel *Panel1;
	TLabel *Label44;
	TLabel *Label45;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TTabSheet *TabSheet4;
	TTabSheet *TabSheet5;
	TLabel *CityLabel2;
	TLabel *CityLabel1;
	TScrollBox *ScrollBox4;
	TLabel *MovieGenre;
	TLabel *MovieScreenwriterLabel;
	TLabel *MovieScreenwriter;
	TLabel *MovieCY;
	TLabel *MovieIMDB;
	TLabel *MovieCYLabel;
	TLabel *MovieGenreLabel;
	TLabel *MovieDurationLabel;
	TLabel *MovieDuration;
	TPageControl *PageControl2;
	TTabSheet *TabSheet6;
	TMemo *MoviePlot;
	TTabSheet *TabSheet7;
	TLabel *Label43;
	TLabel *CityLabel3;
	TLabel *DateLabel2;
	TScrollBox *ScrollBox5;
	TImage *MovieSessions;
	TLabel *MovieWorldPremiere;
	TLabel *MovieProducerLabel;
	TLabel *MovieProducer;
	TLabel *MovieWorldPremiereLabel;
	TLabel *MoviePremiere;
	TLabel *MovieDirector;
	TImage *MovieStar;
	TLabel *MovieName;
	TLabel *MovieAge;
	TImage *MoviePoster;
	TImage *MovieCircle;
	TLabel *MovieActorsLabel;
	TLabel *MovieActors;
	TLabel *MoviePremiereLabel;
	TLabel *MovieDirectorLabel;
	TLabel *MovieRating;
	TLabel *MovieVotes;
	TLabel *MovieOriginalName;
	TScrollBox *ScrollBox6;
	TImage *CinemaPoster;
	TLabel *CinemaName;
	TLabel *CinemaTelephone;
	TLabel *CinemaAddress;
	TLabel *CinemaTelephoneLabel;
	TLabel *CinemaAddressLabel;
	TLabel *CinemaPopularity;
	TImage *CinemaStar;
	TLabel *CinemaVotes;
	TPageControl *PageControl3;
	TTabSheet *TabSheet8;
	TMemo *CinemaPlot;
	TTabSheet *TabSheet9;
	TLabel *Label42;
	TLabel *CityLabel4;
	TLabel *DateLabel3;
	TScrollBox *ScrollBox7;
	TImage *CinemaSessions;
	TLabel *CinemaRating;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall PageControl1Change(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall MoviePlotChange(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
			void __fastcall TForm23::MovieClick(TObject *Sender);
			void __fastcall TForm23::MovieMouseEnter(TObject *Sender);
			void __fastcall TForm23::MovieMouseLeave(TObject *Sender);

			void __fastcall TForm23::CinemaClick(TObject *Sender);
			void __fastcall TForm23::MovieSoonClick(TObject *Sender);

			//----------MoviesInHire----------------
			void clearMoviesVector();
			void addMovies();
			struct Movie
			{
				TImage *Poster;
				TImage *Circle;
				TImage *Star;
				TLabel *Age;
				TLabel *Name;
				TLabel *CYG; //CountryYearGenre
				TLabel *DirectorLabel;
				TLabel *Director;
				TLabel *ActorsLabel;
				TLabel *Actors;
				TLabel *PremiereLabel;
				TLabel *Premiere;
				TLabel *Rating;
				TLabel *Votes;
				TLabel *IMDB;
				int number;
			};
			std::vector<Movie> movies;
			//----------Cinemas-------------
			void clearCinemasVector();
			void addCinemas();
			struct Cinema
			{
				TImage *Poster;
				TImage *Star;
				TLabel *Name;
				TLabel *AddressLabel;
				TLabel *Address;
				TLabel *TelephoneLabel;
				TLabel *Telephone;
				TLabel *Popularity;
				TLabel *Rating;
				TLabel *Votes;
				int number;
			};
			std::vector<Cinema> cinemas;
			//----------MoviesComingSoon----------------
			void clearMoviesComingSoonVector();
			void addMoviesComingSoon();
			struct MovieComingSoon
			{
				TImage *Poster;
				TPanel *Panel;
				TLabel *Name;
				TLabel *CYG; 		    //CountryYearGenre
				TLabel *DirectorLabel;
				TLabel *Director;
				TLabel *ActorsLabel;
				TLabel *Actors;
				TLabel *PremiereDate;
				TLabel *LeftDays;		//ToPremiere
				int number;
			};
			std::vector<MovieComingSoon> moviesComingSoon;
			//--------ScrollBox---------------
			void __fastcall TForm23::ScrollBoxClick(TObject *Sender);
			void __fastcall TForm23::ScrollBoxExit(TObject *Sender);
			void __fastcall TForm23::ScrollBoxMouseWheelDown(TObject *Sender, TShiftState Shift,
			const TPoint &MousePos, bool &Handled);
			void __fastcall TForm23::ScrollBoxMouseWheelUp(TObject *Sender, TShiftState Shift,
			const TPoint &MousePos, bool &Handled);
			void __fastcall TForm23::ScrollBoxMouseDown(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
			void __fastcall TForm23::ScrollBoxMouseUp(TObject *Sender, TMouseButton Button,
			TShiftState Shift, int X, int Y);
			void __fastcall TForm23::ScrollBoxMouseMove(TObject *Sender, TShiftState Shift, int X,
            int Y);
			void __fastcall TForm23::ScrollBoxMouseEnter(TObject *Sender);
			__fastcall TForm23(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm23 *Form23;
//---------------------------------------------------------------------------
#endif
