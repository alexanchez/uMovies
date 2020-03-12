//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Unit10.cpp", Form10);
USEFORM("Unit7.cpp", Form7);
USEFORM("Unit16.cpp", Form16);
USEFORM("Unit15.cpp", Form15);
USEFORM("Unit8.cpp", Form8);
USEFORM("Unit20.cpp", Form20);
USEFORM("Unit23.cpp", Form23);
USEFORM("Unit18.cpp", Form18);
USEFORM("Unit3.cpp", Form3);
USEFORM("Unit13.cpp", Form13);
USEFORM("Unit6.cpp", Form6);
USEFORM("Unit5.cpp", AboutBox);
USEFORM("Unit4.cpp", Form4);
USEFORM("Unit2.cpp", Form2);
USEFORM("Unit9.cpp", PasswordDlg);
USEFORM("Unit12.cpp", Form12);
USEFORM("Unit17.cpp", Form17);
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit14.cpp", Form14);
USEFORM("Unit11.cpp", Form11);
USEFORM("Unit19.cpp", Form19);
USEFORM("Unit21.cpp", Form21);
USEFORM("Unit22.cpp", Form22);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->Title = "µMovies";
		Application->CreateForm(__classid(TForm1), &Form1);
		Application->CreateForm(__classid(TForm2), &Form2);
		Application->CreateForm(__classid(TForm3), &Form3);
		Application->CreateForm(__classid(TForm4), &Form4);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TForm6), &Form6);
		Application->CreateForm(__classid(TForm7), &Form7);
		Application->CreateForm(__classid(TForm8), &Form8);
		Application->CreateForm(__classid(TPasswordDlg), &PasswordDlg);
		Application->CreateForm(__classid(TForm10), &Form10);
		Application->CreateForm(__classid(TForm11), &Form11);
		Application->CreateForm(__classid(TForm12), &Form12);
		Application->CreateForm(__classid(TForm13), &Form13);
		Application->CreateForm(__classid(TForm14), &Form14);
		Application->CreateForm(__classid(TForm15), &Form15);
		Application->CreateForm(__classid(TForm16), &Form16);
		Application->CreateForm(__classid(TForm17), &Form17);
		Application->CreateForm(__classid(TForm18), &Form18);
		Application->CreateForm(__classid(TForm19), &Form19);
		Application->CreateForm(__classid(TForm20), &Form20);
		Application->CreateForm(__classid(TForm21), &Form21);
		Application->CreateForm(__classid(TForm22), &Form22);
		Application->CreateForm(__classid(TForm23), &Form23);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
