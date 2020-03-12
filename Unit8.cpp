//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit8.h"
#include "Unit9.h"

#include "SystemsFunctions.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZipForge"
#pragma resource "*.dfm"
TForm8 *Form8;
TStringList *catalog,*listcatalogs,*logs8;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void Showcatalogs()
{
  AnsiString name;
  Form8->ListBox1->Items->Clear();
  TSearchRec sr;
   if (FindFirst("Catalogs\\*.cof", faAnyFile | faDirectory, sr) == 0)
     {
		do
		{   name=sr.Name;name=name.Delete(name.Length()-4+1, 4);
			Form8->ListBox1->Items->Add(name);
        }
        while(FindNext(sr) == 0);
     }
  listcatalogs->Assign(Form8->ListBox1->Items);
  Form8->CatalogsQuantity->Caption=FloatToStr(Form8->ListBox1->ItemIndex+1)+'-'+FloatToStr(Form8->ListBox1->Count);
}
//---------------------------------------------------------------------------

void OpenModePasswordDialog(int w,int h,int okl,int cancell,int top,bool t,bool f)
{
 PasswordDlg->Width=w;PasswordDlg->Height=h;PasswordDlg->Label1->Visible=f;PasswordDlg->Label2->Visible=t;
 PasswordDlg->Label3->Visible=t;PasswordDlg->NewPassword->Visible=t;
 PasswordDlg->OKBtn->Left=okl;PasswordDlg->OKBtn->Top=top;
 PasswordDlg->CancelBtn->Left=cancell;PasswordDlg->CancelBtn->Top=top;
}
//---------------------------------------------------------------------------

void CreateZip(AnsiString name_save)
{
  catalog->SaveToFile("Data/Backup/Data/Options.ini");
  Form8->ZipForge1->FileName="Catalogs\\"+name_save+".cof";
  Form8->ZipForge1->OpenArchive();
  Form8->ZipForge1->BaseDir = "Data/Backup/";
  Form8->ZipForge1->AddFiles("\\Data\\Options.ini");
  Form8->ZipForge1->CloseArchive();
}
//--------------------------------------------------------------------------- 

void Logs(AnsiString Text,AnsiString Name)
  {
   TDateTime CurrentDateTime=Now();
   logs8->LoadFromFile("Data/Logs.txt");logs8->Add("["+CurrentDateTime+"] ("+Text+"): "+Name);//Основной лог
   logs8->SaveToFile("Data/Logs.txt");
   logs8->LoadFromFile("Data/Logs.temp");logs8->Add("["+CurrentDateTime+"] ("+Text+"): "+Name);//Буферный лог
   logs8->SaveToFile("Data/Logs.temp");
   logs8->Clear();
  }
//---------------------------------------------------------------------------

void __fastcall TForm8::FormShow(TObject *Sender)
{
  catalog=new TStringList();listcatalogs=new TStringList();logs8=new TStringList();
  Form8->Tag=0;Image1->Picture->LoadFromFile("Soft/Backgrounds/Background 7.1.jpg");
  Showcatalogs();
}
//---------------------------------------------------------------------------

void __fastcall TForm8::FormClose(TObject *Sender, TCloseAction &Action)
{
 Image1->Picture->Assign(NULL);
 if(ListBox1->Count!=0)
   DeleteFiles("Data/Backup/Data");
 delete catalog,listcatalogs,logs8;catalog=NULL;listcatalogs=NULL;logs8=NULL;
 DeleteFiles("Data/Backup/NewCatalog");
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PopupMenu1Popup(TObject *Sender)
{
  if(ListBox1->Count==0 || ListBox1->ItemIndex==-1)
	  {PDeleteCatalog->Enabled=false;POpenCatalog->Enabled=false;PRenameCatalog->Enabled=false;
	   PPassword->Enabled=false;PCreateDublicateSelected->Enabled=false;}
  else
	  {PDeleteCatalog->Enabled=true;POpenCatalog->Enabled=true;PPassword->Enabled=true;
	   if(ListBox1->Items->Strings[ListBox1->ItemIndex]=="My")
         PRenameCatalog->Enabled=false;
       else
		 PRenameCatalog->Enabled=true;
	   if(ListBox1->Items->Strings[ListBox1->ItemIndex]==namecatalog)
		 PCreateDublicateSelected->Enabled=false;
	   else
	     PCreateDublicateSelected->Enabled=true;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::ListBox1Click(TObject *Sender)
{
  if(ListBox1->ItemIndex!=-1)
	 {
	  catalog->Clear();Image2->Visible=true;
	  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
	  ZipForge1->FileName ="Catalogs\\"+name+".cof";
	  ZipForge1->OpenArchive(fmOpenRead);
	  ZipForge1->BaseDir = "Data/Backup";
	  ZipForge1->ExtractFiles("*Options.ini*");
	  ZipForge1->ExtractFiles("*Names.dat*");
	  ZipForge1->CloseArchive();
	  catalog->LoadFromFile("Data/Backup/Data/Names.dat");
	  Label2->Caption=lang->Strings[11]+AnsiString(catalog->Count); //lang->Strings[11]="Количество фильмов: "
	  catalog->LoadFromFile("Data/Backup/Data/Options.ini");
	  if(catalog->Strings[8]=="0")
		Image2->Picture->LoadFromFile("Soft/Buttons/Filter_Cancel.png");
	  else
		Image2->Picture->LoadFromFile("Soft/Buttons/Apply.png");
	  CatalogsQuantity->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::ListBox1DblClick(TObject *Sender)
{
  POpenCatalogClick(Form8);
}
//---------------------------------------------------------------------------

void __fastcall TForm8::ListBox1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  if(Key==VK_RETURN) POpenCatalogClick(Form8);
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PAddCatalogClick(TObject *Sender)
{
  AnsiString nFileName;
  if(OpenDialog1->Execute())
	{
	 nFileName=ExtractFileName(OpenDialog1->FileName);
	 nFileName=nFileName.Delete(nFileName.Length()-4+1, 4);//обрезание .cof
	 if(listcatalogs->IndexOf(nFileName)>=0)
		{ShowMessage(lang->Strings[10]);return;}           //lang->Strings[10]="Каталог с таким именем уже есть"
	 Logs("Added catalog",nFileName);nFileName="Catalogs/"+ExtractFileName(OpenDialog1->FileName);
	 UnicodeString ws = OpenDialog1->FileName;
	 char * x = AnsiString(ws).c_str();
	 CopyFile( x, nFileName.c_str(), true );
	}
  Showcatalogs();
}
//---------------------------------------------------------------------------

void __fastcall TForm8::POpenCatalogClick(TObject *Sender)
{
   if(ListBox1->ItemIndex>=0)
   {
   AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
   ListBox1->Items->Clear();ListBox1->Items->Add(name);
   Form8->Tag=1;ShowMessage(lang->Strings[3]);Close();//lang->Strings[3]=Нужен перезапуск программы
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PRenameCatalogClick(TObject *Sender)
{
   AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
   AnsiString ForbiddenChars = "\\/*:<>«»|?";
   String NameCatalog;
   if(InputQuery(lang->Strings[5],lang->Strings[6],NameCatalog)==False)   //InputQuery("Внимание!","Введите имя каталога","")
     return;
   if(NameCatalog.Length()==0)
      {ShowMessage(lang->Strings[7]);Form8->Tag=0;return;}              //lang->Strings[7]- "Имя каталога не введено!"
   else
     {
       for(int i=0;i<NameCatalog.Length();i++)
         if(ForbiddenChars.Pos(NameCatalog.c_str()[i])||NameCatalog.c_str()[i]=='"')
		   {ShowMessage(forbiddenchars);Form8->Tag=0;return;}           //forbiddenchars-"Имя содержит недопустимые символы!(\\/*:<>|?)"
	   if(listcatalogs->IndexOf(NameCatalog)>=0)
		  {ShowMessage(lang->Strings[10]);Form8->Tag=0;return;}         //lang->Strings[10]="Каталог с таким именем уже есть"
	   catalog->Clear();
	   catalog->LoadFromFile("Data/Backup/Data/Options.ini");
       catalog->Strings[7]=NameCatalog;
       if(name==namecatalog)
          {namecatalog=NameCatalog;Label1->Caption=lang->Strings[1]+NameCatalog;}
       RenameFile("Catalogs/"+name+".cof","Catalogs/"+NameCatalog+".cof");
	   CreateZip(NameCatalog);
       Logs("Renamed catalog",name+" -> "+NameCatalog);
       Showcatalogs();
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PDeleteCatalogClick(TObject *Sender)
{
       for(int i=0;i<ListBox1->Count;i++)
         if(ListBox1->Selected[i])
		   {
			if(ListBox1->Items->Strings[i]!="My")
			{
				AnsiString name=ListBox1->Items->Strings[i];
				catalog->Clear();catalog->LoadFromFile("Data/Backup/Data/Options.ini");
				//Если стоит пароль, то для удаления нужно ввести пароль выделенного каталога
				if(catalog->Strings[8]!="0")
				{
					PasswordDlg->Image1->Visible=false;PasswordDlg->Caption="Password of the deleting catalog";PasswordDlg->Position=poScreenCenter;
					AnsiString password=catalog->Strings[8];PasswordDlg->SetPassword(password);
					OpenModePasswordDialog(249,130,70,150,59,false,true);
					PasswordDlg->Tag=3;PasswordDlg->ShowModal();
					if(PasswordDlg->Tag==0) //Если не правильный пароль, не давать разрешения на удаление каталога
						return;
					if(PasswordDlg->Tag==1);//Дать разрешение на удаление каталога
				}
				//--------
				if(MessageDlg(lang->Strings[0],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes) //lang->Strings[0]="Вы уверены?"
				{
					DeleteFile("Catalogs/"+ListBox1->Items->Strings[i]+".cof");
					Logs("Removed catalog",ListBox1->Items->Strings[i]);
					if(Label1->Caption.Pos(ListBox1->Items->Strings[i]))
					   {Label1->Caption=lang->Strings[1]+ListBox1->Items->Strings[i]+lang->Strings[2];//lang->Strings[1]=Открытый каталог:
						namedeletedcatalog=ListBox1->Items->Strings[i]+lang->Strings[2];}                //lang->Strings[2]=(каталог удален)
				}
			}
			if(ListBox1->Items->Strings[i]=="My")
              {ShowMessage(lang->Strings[4]);break;}                            //lang->Strings[4]=Свой каталог нельзя удалить!
		   }
      Showcatalogs();
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PCreateDublicateSelectedClick(TObject *Sender)
{
  String NameCatalog;AnsiString ForbiddenChars = "\\/*:<>«»|?";
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
   if(InputQuery(lang->Strings[5],lang->Strings[6],NameCatalog)==False)   //InputQuery("Внимание!","Введите имя каталога","")
	 return;
   if(NameCatalog.Length()==0)
	  {ShowMessage(lang->Strings[7]);Form8->Tag=0;return;}              //lang->Strings[7]- "Имя каталога не введено!"
   else
	 {
	   for(int i=0;i<NameCatalog.Length();i++)
		 if(ForbiddenChars.Pos(NameCatalog.c_str()[i])||NameCatalog.c_str()[i]=='"')
		   {ShowMessage(forbiddenchars);Form8->Tag=0;return;}           //forbiddenchars-"Имя содержит недопустимые символы!(\\/*:<>|?)"
	   if(listcatalogs->IndexOf(NameCatalog)>=0)
		  {ShowMessage(lang->Strings[10]);Form8->Tag=0;return;}         //lang->Strings[10]="Каталог с таким именем уже есть"
	   catalog->Clear();catalog->LoadFromFile("Data/Backup/Data/Options.ini");
	   //Если стоит пароль, то для создания копии нужно ввести пароль выделенного каталога
	   if(catalog->Strings[8]!="0")
	   {
		 PasswordDlg->Image1->Visible=false;PasswordDlg->Caption="Password";PasswordDlg->Position=poScreenCenter;
		 AnsiString password=catalog->Strings[8];PasswordDlg->SetPassword(password);
		 OpenModePasswordDialog(249,130,70,150,59,false,true);
		 PasswordDlg->Tag=3;PasswordDlg->ShowModal();
		 if(PasswordDlg->Tag==1)
			catalog->Strings[8]="0";
		 if(PasswordDlg->Tag==0)
			return;
	   }
	   //--------
	   AnsiString CatalogToCopy="Catalogs/"+name+".cof",CatalogToCreate="Catalogs/"+NameCatalog+".cof";
	   CopyFile(CatalogToCopy.c_str(),CatalogToCreate.c_str(),true);
	   //catalog->Clear();catalog->LoadFromFile("Data/Backup/Data/Options.ini");
	   catalog->Strings[7]=NameCatalog;
	   catalog->Strings[10]="[DateOfCreation]="+Now();
	   CreateZip(NameCatalog);
	   //Очистка лога и запись даты создания нового каталога
	   catalog->Clear();catalog->Add("["+Now()+"] (Created catalog): "+NameCatalog);catalog->SaveToFile("Data/Backup/Data/Logs.txt");
	   ZipForge1->FileName="Catalogs\\"+NameCatalog+".cof";
	   ZipForge1->OpenArchive();
	   ZipForge1->BaseDir = "Data/Backup/";
	   ZipForge1->AddFiles("\\Data\\Logs.txt");
	   ZipForge1->CloseArchive();
	   //---
	   Logs("Created catalog",NameCatalog);
	   Showcatalogs();
	 }
}
//---------------------------------------------------------------------------


void __fastcall TForm8::PCreateDublicateClick(TObject *Sender)
{
  String NameCatalog;AnsiString ForbiddenChars = "\\/*:<>«»|?";
   if(InputQuery(lang->Strings[5],lang->Strings[6],NameCatalog)==False)   //InputQuery("Внимание!","Введите имя каталога","")
	 return;
   if(NameCatalog.Length()==0)
	  {ShowMessage(lang->Strings[7]);Form8->Tag=0;return;}              //lang->Strings[7]- "Имя каталога не введено!"
   else
	 {
	   for(int i=0;i<NameCatalog.Length();i++)
		 if(ForbiddenChars.Pos(NameCatalog.c_str()[i])||NameCatalog.c_str()[i]=='"')
		   {ShowMessage(forbiddenchars);Form8->Tag=0;return;}           //forbiddenchars-"Имя содержит недопустимые символы!(\\/*:<>|?)"
	   if(listcatalogs->IndexOf(NameCatalog)>=0)
		  {ShowMessage(lang->Strings[10]);Form8->Tag=0;return;}         //lang->Strings[10]="Каталог с таким именем уже есть"
	   //Если стоит пароль, то для создания копии нужно ввести пароль открытого каталога
	   if(paswrd!="0")
	   {
		 PasswordDlg->Image1->Visible=false;PasswordDlg->Caption="Password";PasswordDlg->Position=poScreenCenter;
		 char *temp=paswrd.c_str();AnsiString password=temp;//AnsiString password=paswrd;
		 PasswordDlg->SetPassword(password);
		 OpenModePasswordDialog(249,130,70,150,59,false,true);
		 PasswordDlg->Tag=3;PasswordDlg->ShowModal();
		 if(PasswordDlg->Tag==1);//Дать разрешение на создание копии
		 if(PasswordDlg->Tag==0)
			return;
	   }
	   //--------
	   ListBox1->Items->Clear();ListBox1->Items->Add(NameCatalog);
	   Logs("Created catalog",NameCatalog);
	   Form8->Tag=2;ShowMessage(lang->Strings[3]);Close();              //lang->Strings[3]=Нужен перезапуск программы
	 }
}
//---------------------------------------------------------------------------lang->Strings[10]="Каталог с таким именем уже есть"

void __fastcall TForm8::PCreateEmptyClick(TObject *Sender)
{
  String NameCatalog;AnsiString ForbiddenChars = "\\/*:<>«»|?";
   if(InputQuery(lang->Strings[5],lang->Strings[6],NameCatalog)==False)   //InputQuery("Внимание!","Введите имя каталога","")
     return;
   if(NameCatalog.Length()==0)
      {ShowMessage(lang->Strings[7]);Form8->Tag=0;return;}              //lang->Strings[7]- "Имя каталога не введено!"
   else
     {
        for(int i=0;i<NameCatalog.Length();i++)
          if(ForbiddenChars.Pos(NameCatalog.c_str()[i])||NameCatalog.c_str()[i]=='"')
            {ShowMessage(forbiddenchars);Form8->Tag=0;return;}
        if(listcatalogs->IndexOf(NameCatalog)>=0)
		   {ShowMessage(lang->Strings[10]);Form8->Tag=0;return;}        //lang->Strings[10]="Каталог с таким именем уже есть"
		CopyFiles("Catalogs/NewCatalog/","Data/Backup/");
		TStringList *temp=new TStringList();
		temp->LoadFromFile("Data/Backup/NewCatalog/Data/Options.ini");
		temp->Strings[7]=NameCatalog;temp->Strings[10]="[DateOfCreation]="+Now();//Имя нового каталога и дата создания каталога
		temp->SaveToFile("Data/Backup/NewCatalog/Data/Options.ini");
		temp->LoadFromFile("Data/Backup/NewCatalog/Data/Logs.txt");temp->Add("["+Now()+"] (Created catalog): "+NameCatalog);
		temp->SaveToFile("Data/Backup/NewCatalog/Data/Logs.txt");                 //Дата создания нового каталога(запись в Logs)
		delete temp;temp=NULL;
		ZipForge1->FileName="Catalogs\\"+NameCatalog+".cof";
		ZipForge1->OpenArchive(fmCreate);
		ZipForge1->BaseDir = "Data/Backup/NewCatalog/";
		ZipForge1->AddFiles("\\Data\\*.*");
		ZipForge1->CloseArchive();
		Logs("Created catalog",NameCatalog);
		Showcatalogs();
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PPasswordCreateClick(TObject *Sender)
{
  PasswordDlg->Image1->Visible=false;PasswordDlg->Caption="Password";PasswordDlg->Position=poScreenCenter;
  catalog->Clear();catalog->LoadFromFile("Data/Backup/Data/Options.ini");
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
  if(catalog->Strings[8]=="0")
       {
		OpenModePasswordDialog(249,130,70,150,59,false,true);
		PasswordDlg->Tag=0;PasswordDlg->ShowModal();
        if(PasswordDlg->Tag==1)
		  {catalog->Strings[8]=PasswordDlg->GetPassword();AnsiString a=catalog->Strings[8];
		   for (int i=0;i<a.Length();i++)
			 a.c_str()[i]=a.c_str()[i]+50;
		   catalog->Strings[8]=a;
		   if(name==namecatalog)
			 paswrd=catalog->Strings[8];
		   CreateZip(name);}
		if(PasswordDlg->Tag==0)
          return;
       }
  else
	if(MessageDlg(lang->Strings[8],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)//lang->Strings[8]="Пароль уже cтоит! Желаете поменять?"
	  {
	   AnsiString a=catalog->Strings[8];PasswordDlg->SetPassword(a);
	   OpenModePasswordDialog(249,170,70,150,99,true,false);
	   PasswordDlg->Tag=2;PasswordDlg->ShowModal();
       if(PasswordDlg->Tag==1)
		  {catalog->Strings[8]=PasswordDlg->GetPassword();AnsiString a=catalog->Strings[8];
		   for (int i=0;i<a.Length();i++)
			 a.c_str()[i]=a.c_str()[i]+50;
		   catalog->Strings[8]=a;
           if(name==namecatalog)
			 paswrd=catalog->Strings[8];
           CreateZip(name);}
       if(PasswordDlg->Tag==0)
          return;
      }
  Image2->Picture->LoadFromFile("Soft/Buttons/Apply.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm8::PPasswordDeleteClick(TObject *Sender)
{
  PasswordDlg->Image1->Visible=false;PasswordDlg->Caption="Password";PasswordDlg->Position=poScreenCenter;
  catalog->Clear();catalog->LoadFromFile("Data/Backup/Data/Options.ini");
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
  if(catalog->Strings[8]=="0")
      ShowMessage(lang->Strings[9]);//lang->Strings[9]="Пароля нету!"
  else
	  {
	   AnsiString a=catalog->Strings[8];PasswordDlg->SetPassword(a);
	   OpenModePasswordDialog(249,130,70,150,59,false,true);
	   PasswordDlg->Tag=3;PasswordDlg->ShowModal();
	   if(PasswordDlg->Tag==1)
		  {catalog->Strings[8]="0";
		   if(name==namecatalog)
			 paswrd=catalog->Strings[8];
		   CreateZip(name);}
	   if(PasswordDlg->Tag==0)
		  return;
       }
  Image2->Picture->LoadFromFile("Soft/Buttons/Filter_Cancel.png");
}
//---------------------------------------------------------------------------




