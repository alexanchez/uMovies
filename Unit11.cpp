//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit11.h"

#include "SystemsFunctions.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZipForge"
#pragma resource "*.dfm"
TForm11 *Form11;
//---------------------------------------------------------------------------
__fastcall TForm11::TForm11(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm11::FormActivate(TObject *Sender)
{
  ProgressBar1->Position=0;
  if(Form11->Tag==1)//Открытие
	{ProgressBar1->Position=25;
	 CopyFiles("Data/Image","Data/Backup/");ProgressBar1->Position=50;
	 CopyFiles("Data/Plot/","Data/Backup/");ProgressBar1->Position=75;
	 CopyFiles("Data/Seasons/","Data/Backup/");ProgressBar1->Position=85;
	 CopyFiles("Data/Groups/","Data/Backup/");ProgressBar1->Position=100;}
  if(Form11->Tag==2)//Сохранение
	{DeleteDir("Data/Backup");ProgressBar1->Position=20;
	 MkDir("Data/Backup");ProgressBar1->Position=40;
	 CopyFiles("Data/Image","Data/Backup/");ProgressBar1->Position=60;
	 CopyFiles("Data/Plot","Data/Backup/");ProgressBar1->Position=80;
	 CopyFiles("Data/Seasons","Data/Backup/");ProgressBar1->Position=90;
	 CopyFiles("Data/Groups/","Data/Backup/");ProgressBar1->Position=100;}
  if(Form11->Tag==3)//Закрытие
	{ProgressBar1->Position=35;//Чтобы появилась полоса
	 Form11->Caption=CatalogSaving;
	 ZipForge1->FileName="Catalogs\\"+Form11->Hint+".cof";ProgressBar1->Position=25;
	 ZipForge1->OpenArchive(fmCreate);ProgressBar1->Position=50;
	 ZipForge1->AddFiles("\\Data\\*.*");ProgressBar1->Position=75;
	 ZipForge1->CloseArchive();
	 Form11->Caption=CatalogClosing;
	 ProgressBar1->Position=100;}
  Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm11::Timer1Timer(TObject *Sender)
{
  Close();Timer1->Enabled=false;
}
//---------------------------------------------------------------------------


