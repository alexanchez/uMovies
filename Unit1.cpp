//--------------------------------------------------------------------------- 4121 строк кода(Form1-10),ОЗУ 19.262 мб, exe 3.5Мб
//Form1:2729,Form2:516,Form4:139,AboutBox:32,Form6:87,Form7:185,Form8:338,PasswordDlg:95
//2140 - Добавление фильма, 3587-Группы, 3800-размеры, 3408 - Смена каталога
/* Релиз
CategoryPanelGroup->Width=232
Очистить все рисунки на всех формах
Очистить логи
В MSearch в строках с ShellExecute(0,"open","Project1.exe",NULL,NULL,SW_NORMAL); вместо "Project1.exe" - "µMovies.exe"
*/
/* Дебаг/Релиз
Form1->Width=1160;
Form1->Height=780;
*/
#include <vcl.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h" - Добавление/редактирование фильма
#include "Unit3.h" - Настройка боковой панели
#include "Unit4.h" - Сайты с фильмами
#include "Unit5.h" - О программе/Лицензия
#include "Unit6.h" - Фильмы под настроение
#include "Unit7.h" - Глобальный поиск
#include "Unit8.h" - Каталоги
#include "Unit9.h" - Пароль
#include "Unit10.h" - Настройка сортировки
#include "Unit11.h" - Полоса состояния (загрузка-сохранение-закрытие)
#include "Unit12.h" - Активация лицензии
#include "Unit13.h" - Множественное удаление
#include "Unit15.h" - Текущая серия
#include "Unit16.h" - Собственные фильтры
#include "Unit17.h" - Статистика
#include "Unit18.h" - Настройка сериала
#include "Unit19.h" - Выбрать фильмы по первой букве
#include "Unit20.h" - Информация про фильм(боковая панель)
#include "Unit21.h" - Шаблонные команды
#include "Unit22.h" - Новинки кино
#include "Unit23.h" - Киноафиша
#include "Shadow.h" - Затемнение формы при увеличение фото фильма
#include "jpeg.hpp"
#include <IdGlobal.hpp>
#include "Registry.hpp"
#include "SystemsFunctions.cpp" - системные функции (копирование-перемещение-удаление файлов и папок)
#include "LoadingSavingComponent.cpp" - загрузка/сохранение параметров компонентов
#include "SortingOptions.cpp"

#include "stdio.h"
#include "stdlib.h"
#include <vector>
#include "TemperamentDeterminant.h" - Определения темперамента

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma link "ZipForge"
#pragma resource "*.dfm"
TForm1 *Form1;
TStringList *list  = new TStringList();TStringList *genre=new TStringList();
TStringList *year=new TStringList();TStringList *duration=new TStringList();TStringList *country=new TStringList();
TStringList *link=new TStringList();TStringList *view=new TStringList();
TStringList *type=new TStringList();TStringList *type1=new TStringList();TStringList *release=new TStringList();
TStringList *elect=new TStringList();TStringList *trailer=new TStringList();TStringList *season=new TStringList();
TStringList *tagline=new TStringList();TStringList *originalname=new TStringList();TStringList *director=new TStringList();
TStringList *cast=new TStringList();TStringList *rating=new TStringList();TStringList *episode=new TStringList();
TStringList *date=new TStringList();
TStringList *options=new TStringList();TStringList *lang=new TStringList();TStringList *logs=new TStringList();
TStringList *genreb=new TStringList();TStringList *countryb=new TStringList();TStringList *releaseb=new TStringList();TStringList *viewb=new TStringList();
bool s=false,electmode=0,pasagreement=false,openmode=false,openpassworddlg=false;       //pasagreement-режим открытия Form8(список каталогов)
bool FirstExecute=false;
int SelectedFilm=0,search=0,pas=0;                                                      //false:обычный; true:при запросе пароля;
AnsiString save,sure,yes,not,notfound,TypeFilm,watchtrailer,min,seasonfilm="0",seriesfilm,InitialLang;
AnsiString currentseason,currentepisode;
AnsiString dir = GetCurrentDir();
TStringList *sortmode=new TStringList();bool checkedclb=true;
TStringList *duration_activated=new TStringList();
TStringList *favouritefilter=new TStringList();
//-------------------------------------Groups--------------------------------
TStringList *namegroups=new TStringList();TStringList *listcurrentgroup=new TStringList();TStringList *listgroupsmovie=new TStringList();
TMenuItem* groups[20],*opengroup[20],*renamegroup[20],*deletegroup[20],*addtogroups[20],*deletefromgroups[20];
int quantity,quantityadd,quantitydelete;AnsiString currentgroup;
AnsiString OpenGroup,RenameGroup,DeleteGroup;
bool ExitMsgDlg=true;//Для показа окна с сообщением на разрешение выйти
//Лицензия---------------------------------------
int trial=0,trial_temp;//trial_temp: сравнения в OnClose для сохранения trial в реестр
bool trialtimer=false;//При Timer4->Enabled=true, запускает в конце OnShow для устранения ошибок
bool blinking;//Для предупреждения окончания пробной версии
bool close_access=true;//Определяет,активная ли главная форма(незанятая) для разрешения выхода при окончание пробной версии
//Увеличение изображения
CShadowClass *shadow;// = new CShadowClass(Form1);
//Алфавитная панель
TStringList *AlphabetOptions=new TStringList();
TLabel***Alphabet;
//Шаблонные команды
TStringList *TemplateCommands=new TStringList();
//---------------------------------------------------------------------------
AnsiString CutTemplateCommand(AnsiString command);

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
	ListBox2->Top=56;ListBox2->Left=16;
	CategoryPanelGroup1->Width=0;Panel3->Width=0;
	Panel1->Left=CategoryPanelGroup1->Left+CategoryPanelGroup1->Width;
	Panel2->Left=CategoryPanelGroup1->Left+CategoryPanelGroup1->Width;
	Alphabet=new TLabel**[59];
	srand(time(NULL));
}
//---------------------------------------------------------------------------

BOOL WeAreAlone(LPSTR  szName)
{
HANDLE hMutex=CreateMutex(NULL,TRUE,szName);
if  (GetLastError()==ERROR_ALREADY_EXISTS)
  {
  CloseHandle(hMutex);
  return  false;
  }
return true;
}

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  if(WeAreAlone("µMovies"));                              //Если нету копий - запустить
  else                                                    //Если есть копия
  {
	  if(FileExists("Soft/WaitingForClosingProgram.dat"))       //и происходит открытие после смены каталога - подождать 2 сек
	  {
		  int count = 0;
		  while(count<20)
		  {
			Sleep(100);
			if(WeAreAlone("µMovies")){DeleteFile("Soft/WaitingForClosingProgram.dat");break;}
			else count++;
		  }
		  if(count==20)
		  {
			ShowMessage("The program is already running!");
			DeleteFile("Soft/WaitingForClosingProgram.dat");
			exit(0);
		  }
	  }
	  else                                                      //иначе выйти из программы
	  {
		  ShowMessage("The program is already running!");
		  exit(0);
	  }
  }
  if(FileExists("Soft/WaitingForClosingProgram.dat"))DeleteFile("Soft/WaitingForClosingProgram.dat");//Удалить файл после смены каталога, если не понадобился (программа перезапустилась быстро)
  //Проверка прав администратора
  /*
  TRegistry *reg;
  bool openResult;
  reg = new TRegistry(KEY_READ);
  reg->RootKey = HKEY_LOCAL_MACHINE;
  reg->Access = KEY_WRITE;
  openResult = reg->OpenKey("Software\\MyCompanyName\\MyApplication\\" , true);
  if(openResult != true)
	 {MessageDlg("Запустите программу от имени администратора!", TMsgDlgType::mtError, mbOKCancel, 0);exit(0);}
  reg->CloseKey();
  reg->Free();
  */
  try {logs->SaveToFile("Soft/Verify.dat");}/*FileCreate("Soft/Verify.dat");*/
  catch (...) {MessageDlg("Запустите программу от имени администратора!", TMsgDlgType::mtError, mbOKCancel, 0);exit(0);}
  if(FileExists("Soft/Verify.dat"))DeleteFile("Soft/Verify.dat");
  for(int i=1;i<=59;i++)
	 {
	  ((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i)))->OnExpand=CategoryPanelExpand;
	  ((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i)))->OnCollapse=CategoryPanelCollapse;
	  ((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i)))->Hint="0";
	 }
 /*
  TStringList *CurrentLang=new TStringList();
  CurrentLang->LoadFromFile("Soft/Language/Language.txt");
  AnsiString currentlang=CurrentLang->Strings[1],admin;
  if(currentlang=="Ukrainian")
	{CurrentLang->LoadFromFile("Soft/Language/Language.ua");admin=lang->Strings[289];}
  if(currentlang=="Russian")
	{CurrentLang->LoadFromFile("Soft/Language/Language.ru");admin=lang->Strings[289];}
  if(currentlang=="English")
	{CurrentLang->LoadFromFile("Soft/Language/Language.en");admin=lang->Strings[289];}
  */
}
//-------------------------------MouseMove-Leave для всех рисунков и CheckListBox---------------------------

void __fastcall TForm1::ImageMouseEnter(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 4:current->Picture->LoadFromFile("Soft/Buttons/Youtube-play-button(light).png");break;
   case 5:current->Picture->LoadFromFile("Soft/Buttons/Arrow-Button(light).png");break;
   case 6:current->Picture->LoadFromFile("Soft/Buttons/Delete(light).png");break;
   case 7:current->Picture->LoadFromFile("Soft/Buttons/Cancel(light).png");break;
   case 9:current->Picture->LoadFromFile("Soft/Buttons/Wikipedia(light).png");break;
   case 10:if(current->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/Arrow(left_active_select).png");break;
   case 11:if(current->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/Arrow(right_active_select).png");break;
   case 13:current->Picture->LoadFromFile("Soft/Buttons/Optionsort(light).png");break;
   case 16:if(current->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/AddFilter(light).png");break;
   case 17:{current->Picture->LoadFromFile("Soft/Buttons/ExpandAll(light).png");Form1->ExpandAllAlphabetPanel->Font->Color=clBlue;break;}
   case 18:{current->Picture->LoadFromFile("Soft/Buttons/CollapseAll(light).png");Form1->CollapseAllAlphabetPanel->Font->Color=clBlue;break;}
  }
}
//----------------
void __fastcall TForm1::ImageMouseLeave(TObject *Sender)
{
  TImage* current=static_cast<TImage*>(Sender);
  int index=current->Tag;
  switch(index)
  {
   case 4:current->Picture->LoadFromFile("Soft/Buttons/Youtube-play-button.png");break;
   case 5:current->Picture->LoadFromFile("Soft/Buttons/Arrow-Button.png");break;
   case 6:current->Picture->LoadFromFile("Soft/Buttons/Delete.png");break;
   case 7:current->Picture->LoadFromFile("Soft/Buttons/Cancel.png");break;
   case 9:current->Picture->LoadFromFile("Soft/Buttons/Wikipedia.png");break;
   case 10:if(current->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/Arrow(left_active).png");break;
   case 11:if(current->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/Arrow(right_active).png");break;
   case 13:current->Picture->LoadFromFile("Soft/Buttons/Optionsort.png");break;
   case 16:if(current->Enabled==true)current->Picture->LoadFromFile("Soft/Buttons/AddFilter.png");break;
   case 17:{current->Picture->LoadFromFile("Soft/Buttons/ExpandAll.png");Form1->ExpandAllAlphabetPanel->Font->Color=clBlack;break;}
   case 18:{current->Picture->LoadFromFile("Soft/Buttons/CollapseAll.png");Form1->CollapseAllAlphabetPanel->Font->Color=clBlack;break;}
  }
}
//----------------
void __fastcall TForm1::CheckListBoxMouseEnter(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  if(current->Hint=="0")
  {
	switch(current->Tag)
	{
	case 1:CheckListBox1->Height=169;CheckListBox1->Width=473;CheckListBox1->Columns=3;break;
	case 2:CheckListBox2->Height=164;CheckListBox2->Width=608;CheckListBox2->Columns=4;break;
	case 3:CheckListBox3->Height=90;CheckListBox3->Width=480;CheckListBox3->Columns=7;break;
	case 4:CheckListBox4->Height=90;CheckListBox4->Width=465;CheckListBox4->Columns=5;break;
	}
	current->SetFocus();
  }
  current->Hint=AnsiString(current->Hint.ToInt()+1);//++
}
//----------------
void __fastcall TForm1::CheckListBoxMouseLeave(TObject *Sender)
{
  TCheckListBox *current=static_cast<TCheckListBox *>(Sender);
  if(current->Hint=="3")
  {
	switch(current->Tag)
	{
	case 1:CheckListBox1->Height=26;CheckListBox1->Width=146;CheckListBox1->Columns=0;break;
	case 2:CheckListBox2->Height=26;CheckListBox2->Width=148;CheckListBox2->Columns=0;break;
	case 3:CheckListBox3->Height=26;CheckListBox3->Width=146;CheckListBox3->Columns=0;break;
	case 4:CheckListBox4->Height=26;CheckListBox4->Width=148;CheckListBox4->Columns=0;break;
	}
	current->Hint="0";
	DefocusControl(current,false);
  }
  if(current->Hint=="1")current->Hint=AnsiString(current->Hint.ToInt()+1);//++
}
//-----------------------------------Создание групп-------------------------

void CreateGroup(int indexgroup,AnsiString name)
{
  int i=indexgroup;
  groups[i]=new TMenuItem(Form1->AllGroups);
   groups[i]->Caption=name;
   groups[i]->Hint=name;
   groups[i]->Tag=i;
  Form1->AllGroups->Add(groups[i]);
  opengroup[i]=new TMenuItem(groups[i]);
   opengroup[i]->Caption=OpenGroup; // "Открыть группу"
   opengroup[i]->Tag=i;
   opengroup[i]->OnClick=Form1->MOpenGroupClick;
  groups[i]->Add(opengroup[i]);
   renamegroup[i]=new TMenuItem(groups[i]);
   renamegroup[i]->Caption=RenameGroup;//"Изменить название"
   renamegroup[i]->Tag=i;
   renamegroup[i]->OnClick=Form1->MRenameGroupClick;
  groups[i]->Add(renamegroup[i]);
   deletegroup[i]=new TMenuItem(groups[i]);
   deletegroup[i]->Caption=DeleteGroup;//"Удалить группу"
   deletegroup[i]->Tag=i;
   deletegroup[i]->OnClick=Form1->MDeleteGroupClick;
  groups[i]->Add(deletegroup[i]);
}
//-------------------SearchNumbers(отделение с времени числа, ex.56 min.->56)---

AnsiString SearchNumbers(AnsiString CurComboBox)
{
  AnsiString Number,string=CurComboBox;
  for (int i=0;i<string.Length();i++)
	 if ((string.c_str()[i]>=48) && (string.c_str()[i]<=57))
	   Number=Number+string.c_str()[i];
  return Number;
}
//------------------------------------------------------------------------------

void DivisionYear(AnsiString CurYear,AnsiString& from,AnsiString& till)
{
  for(int j=0;j<CurYear.Length();j++)
	 {if(isdigit(CurYear.c_str()[j]))
		till+=CurYear.c_str()[j];
	  else
	   {from=till;till="";}
	 }
}
//-------------------------------------------------------------------------------

void Sort(TStringList *quantactive,int j)
{
  bool access=false,accessclb=false;
  for(int q=0;q<quantactive->Count;q++)
   {
    if(quantactive->Strings[q]=="1")
	 {
	  if(sortmode->Strings[0]=="1")
		 {if(genre->Strings[j].LowerCase().Pos(Form1->ComboBox1->Text.LowerCase())) access=true;else {access=false;break;}}
	  if(sortmode->Strings[0]=="2")
		{ accessclb=true;
		  for(int z=0;z<Form1->CheckListBox1->Count;z++)
		   if(Form1->CheckListBox1->Checked[z])
			 {if(genre->Strings[j].Pos(Form1->CheckListBox1->Items->Strings[z])){access=true;accessclb=true;break;}
			  else accessclb=false;}
		  if(accessclb==false)
			{access=false;break;}
		}
	  if(sortmode->Strings[0]=="3")
		{
		  accessclb=true;
		  for(int z=0;z<Form1->CheckListBox1->Count;z++)
		   if(Form1->CheckListBox1->Checked[z])
			 {if(!genre->Strings[j].Pos(Form1->CheckListBox1->Items->Strings[z])){access=true;accessclb=true;}
			  else {accessclb=false;break;}}
		  if(accessclb==false)
			{access=false;break;}
		}
	 }
	if(quantactive->Strings[q]=="2")
	 {
	  if(sortmode->Strings[1]=="1")
		 {if(country->Strings[j].LowerCase().Pos(Form1->ComboBox2->Text.LowerCase())) access=true;else {access=false;break;}}
	  if(sortmode->Strings[1]=="2")
		{ accessclb=true;
		  for(int z=0;z<Form1->CheckListBox2->Count;z++)
		   if(Form1->CheckListBox2->Checked[z])
			 {if(country->Strings[j].Pos(Form1->CheckListBox2->Items->Strings[z])){access=true;accessclb=true;break;}
			  else accessclb=false;}
		  if(accessclb==false)
			{access=false;break;}
		}
	  if(sortmode->Strings[1]=="3")
		{
		  accessclb=true;
		  for(int z=0;z<Form1->CheckListBox2->Count;z++)
		   if(Form1->CheckListBox2->Checked[z])
			 {if(!country->Strings[j].Pos(Form1->CheckListBox2->Items->Strings[z])){access=true;accessclb=true;}
			  else {accessclb=false;break;}}
		  if(accessclb==false)
			{access=false;break;}
		}
	 }
	if(quantactive->Strings[q]=="3")
	 {
	  if(sortmode->Strings[2]=="1")
		 {
		  if(type->Strings[j]=="Movie")
			{if(year->Strings[j]==Form1->ComboBox3->Text) access=true;else {access=false;break;}}
		  if(type->Strings[j]=="TV series")
			{AnsiString from,till;DivisionYear(year->Strings[j],from,till);
			 if(StrToInt(Form1->ComboBox3->Text)>=StrToInt(from)&&StrToInt(Form1->ComboBox3->Text)<=StrToInt(till)) access=true;
			 else {access=false;break;}}
		 }
	  if(sortmode->Strings[2]=="2")
		 {
		  if(type->Strings[j]=="Movie")
			{ accessclb=true;
			  for(int z=0;z<Form1->CheckListBox3->Count;z++)
				if(Form1->CheckListBox3->Checked[z])
				  {if(year->Strings[j]==Form1->CheckListBox3->Items->Strings[z]){access=true;accessclb=true;break;}
				   else accessclb=false;}
			  if(accessclb==false)
				{access=false;break;}
			}
		  if(type->Strings[j]=="TV series")
			{ accessclb=true;AnsiString from,till;DivisionYear(year->Strings[j],from,till);
			  for(int z=0;z<Form1->CheckListBox3->Count;z++)
				if(Form1->CheckListBox3->Checked[z])
				  {if(StrToInt(Form1->CheckListBox3->Items->Strings[z])>=StrToInt(from)&&StrToInt(Form1->CheckListBox3->Items->Strings[z])<=StrToInt(till))
					{access=true;accessclb=true;break;}
				  else accessclb=false;}
			  if(accessclb==false)
				{access=false;break;}
			}
		 }
	  if(sortmode->Strings[2]=="3")
		 {
		  if(type->Strings[j]=="Movie")
		   {
			if(((Form1->ComboBox3->ItemIndex>0||Form1->ComboBox3->ItemIndex==-1)&&Form1->ComboBox3->Text!=""&&!Form1->ComboBox3->Text.Pos('~'))&&
			   ((Form1->ComboBox7->ItemIndex>0||Form1->ComboBox7->ItemIndex==-1)&&Form1->ComboBox7->Text!=""&&!Form1->ComboBox7->Text.Pos('~')))
				 {if(StrToInt(year->Strings[j])>=StrToInt(Form1->ComboBox3->Text)&&
				   StrToInt(year->Strings[j])<=StrToInt(Form1->ComboBox7->Text))  access=true;else {access=false;break;}}
			if(((Form1->ComboBox3->ItemIndex>0||Form1->ComboBox3->ItemIndex==-1)&&Form1->ComboBox3->Text!=""&&!Form1->ComboBox3->Text.Pos('~'))&&
				(Form1->ComboBox7->ItemIndex==0||Form1->ComboBox7->ItemIndex==-1||Form1->ComboBox7->Text==""||Form1->ComboBox7->Text.Pos('~')))
				 {if(StrToInt(year->Strings[j])>=StrToInt(Form1->ComboBox3->Text)) access=true;else {access=false;break;}}
			if((Form1->ComboBox3->ItemIndex==0||Form1->ComboBox3->ItemIndex==-1||Form1->ComboBox3->Text==""||Form1->ComboBox3->Text.Pos('~'))&&
			   ((Form1->ComboBox7->ItemIndex>0||Form1->ComboBox7->ItemIndex==-1)&&Form1->ComboBox7->Text!=""&&!Form1->ComboBox7->Text.Pos('~')))
				 {if(StrToInt(year->Strings[j])<=StrToInt(Form1->ComboBox7->Text)) access=true;else {access=false;break;}}
		   }
		  if(type->Strings[j]=="TV series")
		   {AnsiString from,till;DivisionYear(year->Strings[j],from,till);
			if(((Form1->ComboBox3->ItemIndex>0||Form1->ComboBox3->ItemIndex==-1)&&Form1->ComboBox3->Text!=""&&!Form1->ComboBox3->Text.Pos('~'))&&
			   ((Form1->ComboBox7->ItemIndex>0||Form1->ComboBox7->ItemIndex==-1)&&Form1->ComboBox7->Text!=""&&!Form1->ComboBox7->Text.Pos('~')))
				 {if(StrToInt(till)>=StrToInt(Form1->ComboBox3->Text)&&
				   StrToInt(from)<=StrToInt(Form1->ComboBox7->Text))  access=true;else {access=false;break;}}
			if(((Form1->ComboBox3->ItemIndex>0||Form1->ComboBox3->ItemIndex==-1)&&Form1->ComboBox3->Text!=""&&!Form1->ComboBox3->Text.Pos('~'))&&
				(Form1->ComboBox7->ItemIndex==0||Form1->ComboBox7->ItemIndex==-1||Form1->ComboBox7->Text==""||Form1->ComboBox7->Text.Pos('~')))
				 {if(StrToInt(till)>=StrToInt(Form1->ComboBox3->Text)) access=true;else {access=false;break;}}
			if((Form1->ComboBox3->ItemIndex==0||Form1->ComboBox3->ItemIndex==-1||Form1->ComboBox3->Text==""||Form1->ComboBox3->Text.Pos('~'))&&
			   ((Form1->ComboBox7->ItemIndex>0||Form1->ComboBox7->ItemIndex==-1)&&Form1->ComboBox7->Text!=""&&!Form1->ComboBox7->Text.Pos('~')))
				 {if(StrToInt(from)<=StrToInt(Form1->ComboBox7->Text)) access=true;else {access=false;break;}}
		   }
		 }
	 }
	if(quantactive->Strings[q]=="4")
	 {
	  if(sortmode->Strings[3]=="1")
		{AnsiString number=SearchNumbers(Form1->ComboBox4->Text);
		 if(StrToInt(duration->Strings[j])>=StrToInt(number)-5 && StrToInt(duration->Strings[j])<=StrToInt(number)+5) access=true;
		 else {access=false;break;}}
	  if(sortmode->Strings[3]=="2")
		{
		 accessclb=true;
		 for(int z=0;z<duration_activated->Count;z++)
		   {if(StrToInt(duration->Strings[j])>=StrToInt(duration_activated->Strings[z])-5 &&
			  StrToInt(duration->Strings[j])<=StrToInt(duration_activated->Strings[z])+5)
			  {access=true;accessclb=true;break;}
			else accessclb=false;}
		 if(accessclb==false)
		   {access=false;break;}
		}
	  if(sortmode->Strings[3]=="3")
		{
		 if(((Form1->ComboBox4->ItemIndex>0||Form1->ComboBox4->ItemIndex==-1)&&Form1->ComboBox4->Text!="")&&
			((Form1->ComboBox8->ItemIndex>0||Form1->ComboBox8->ItemIndex==-1)&&Form1->ComboBox8->Text!=""))
			  {AnsiString numberfrom=SearchNumbers(Form1->ComboBox4->Text),numbertill=SearchNumbers(Form1->ComboBox8->Text);
			   if(StrToInt(duration->Strings[j])>=StrToInt(numberfrom)&&
				  StrToInt(duration->Strings[j])<=StrToInt(numbertill))  access=true;else {access=false;break;}}
		 if(((Form1->ComboBox4->ItemIndex>0||Form1->ComboBox4->ItemIndex==-1)&&Form1->ComboBox4->Text!="")&&
			 (Form1->ComboBox8->ItemIndex==0||Form1->ComboBox8->ItemIndex==-1||Form1->ComboBox8->Text==""))
			  {AnsiString number=SearchNumbers(Form1->ComboBox4->Text);
			   if(StrToInt(duration->Strings[j])>=StrToInt(number)) access=true;else {access=false;break;}}
		 if((Form1->ComboBox4->ItemIndex==0||Form1->ComboBox4->ItemIndex==-1||Form1->ComboBox4->Text=="")&&
		   ((Form1->ComboBox8->ItemIndex>0||Form1->ComboBox8->ItemIndex==-1)&&Form1->ComboBox8->Text!=""))
			  {AnsiString number=SearchNumbers(Form1->ComboBox8->Text);
			   if(StrToInt(duration->Strings[j])<=StrToInt(number)) access=true;else {access=false;break;}}
		}
	 }
	if(quantactive->Strings[q]=="5")
	  {if(release->Strings[j].LowerCase()==Form1->ComboBox5->Text.LowerCase()) access=true;else {access=false;break;}}
	if(quantactive->Strings[q]=="6")
	  {if(view->Strings[j].LowerCase()==Form1->ComboBox6->Text.LowerCase()) access=true;else {access=false;break;}}
   }
  if(access==true)
	Form1->ListBox1->Items->Add(list->Strings[j]);
}
//---------------------------------------------------------------------------

   void QuantityChecked(TCheckListBox*CLB,TStringList *quantactive,AnsiString number)
{
  bool k=false;
  for(int i=0;i<CLB->Count;i++)
	 if(CLB->Checked[i])
	   {k=true;break;}
  if(k==true)
	quantactive->Add(number);
}
//---------------------------------------------------------------------------

void VerifyEnteredData()
{
   bool Enabled=true;
   while(Enabled)
   {
   if(sortmode->Strings[0]=="1" && Form1->ComboBox1->Text==""||Form1->ComboBox1->ItemIndex==-1)Enabled=false;
   if(sortmode->Strings[1]=="1" && Form1->ComboBox2->Text==""||Form1->ComboBox2->ItemIndex==-1)Enabled=false;
   if(sortmode->Strings[2]=="1" && Form1->ComboBox3->Text==""||Form1->ComboBox3->ItemIndex==-1)Enabled=false;
   if(sortmode->Strings[2]=="3" && Form1->ComboBox3->Text==""||Form1->ComboBox3->ItemIndex==-1
							  || Form1->ComboBox7->Text==""||Form1->ComboBox7->ItemIndex==-1)Enabled=false;
   if(sortmode->Strings[3]=="1" && Form1->ComboBox4->Text==""||Form1->ComboBox4->ItemIndex==-1)Enabled=false;
   if(sortmode->Strings[3]=="3" && Form1->ComboBox4->Text==""||Form1->ComboBox4->ItemIndex==-1
							  || Form1->ComboBox8->Text==""||Form1->ComboBox8->ItemIndex==-1)Enabled=false;
   if(Form1->ComboBox5->Text==""||Form1->ComboBox5->ItemIndex==-1||
	  Form1->ComboBox6->Text==""||Form1->ComboBox6->ItemIndex==-1)Enabled=false;
   break;
   }
   if(Enabled){Form1->Image16->Enabled=true;Form1->Image16->Hint=lang->Strings[258];Form1->Image16->Picture->LoadFromFile("Soft/Buttons/AddFilter.png");}
   else {Form1->Image16->Enabled=false;Form1->Image16->Hint=lang->Strings[259];Form1->Image16->Picture->LoadFromFile("Soft/Buttons/AddFilter(colorless).png");}
}
//---------------------------------------------------------------------------

void Callsort()
{
  Form1->ListBox1->Clear();
  int index;bool k;
  TStringList *quantactive=new TStringList();
  if(sortmode->Strings[0]=="1")if((Form1->ComboBox1->ItemIndex>0||Form1->ComboBox1->ItemIndex==-1)&&Form1->ComboBox1->Text!="")quantactive->Add("1");
  if(sortmode->Strings[0]=="2")QuantityChecked(Form1->CheckListBox1,quantactive,"1");
  if(sortmode->Strings[0]=="3")QuantityChecked(Form1->CheckListBox1,quantactive,"1");
  if(sortmode->Strings[1]=="1")if((Form1->ComboBox2->ItemIndex>0||Form1->ComboBox2->ItemIndex==-1)&&Form1->ComboBox2->Text!="")quantactive->Add("2");
  if(sortmode->Strings[1]=="2")QuantityChecked(Form1->CheckListBox2,quantactive,"2");
  if(sortmode->Strings[1]=="3")QuantityChecked(Form1->CheckListBox2,quantactive,"2");
  if(sortmode->Strings[2]=="1")
	{bool b=true;
	 for(int i=0;i<Form1->ComboBox3->Text.Length();i++)
	  if(!isdigit(Form1->ComboBox3->Text.c_str()[i]))
		{b=false;break;}
	 if((Form1->ComboBox3->ItemIndex>0||Form1->ComboBox3->ItemIndex==-1)&&Form1->ComboBox3->Text!=""&&b==true)quantactive->Add("3");
	}
  if(sortmode->Strings[2]=="2")QuantityChecked(Form1->CheckListBox3,quantactive,"3");
  if(sortmode->Strings[2]=="3")
	if(((Form1->ComboBox3->ItemIndex>0||Form1->ComboBox3->ItemIndex==-1)&&Form1->ComboBox3->Text!=""&&!Form1->ComboBox3->Text.Pos('~'))||
	   ((Form1->ComboBox7->ItemIndex>0||Form1->ComboBox7->ItemIndex==-1)&&Form1->ComboBox7->Text!=""&&!Form1->ComboBox7->Text.Pos('~')))quantactive->Add("3");
  if(sortmode->Strings[3]=="1")if((Form1->ComboBox4->ItemIndex>0||Form1->ComboBox4->ItemIndex==-1)&&Form1->ComboBox4->Text!="")quantactive->Add("4");
  if(sortmode->Strings[3]=="2")
	{
	 bool k=false;
	 duration_activated->Clear();
	 for(int i=0;i<Form1->CheckListBox4->Count;i++)
	   if(Form1->CheckListBox4->Checked[i])
		{k=true;duration_activated->Add(Form1->CheckListBox4->Items->Strings[i]);
		 duration_activated->Strings[duration_activated->Count-1]=SearchNumbers(duration_activated->Strings[duration_activated->Count-1]);}
	 if(k==true)
		quantactive->Add("4");
	}
  if(sortmode->Strings[3]=="3")
	if(((Form1->ComboBox4->ItemIndex>0||Form1->ComboBox4->ItemIndex==-1)&&Form1->ComboBox4->Text!="")||
	   ((Form1->ComboBox8->ItemIndex>0||Form1->ComboBox8->ItemIndex==-1)&&Form1->ComboBox8->Text!=""))quantactive->Add("4");
  if((Form1->ComboBox5->ItemIndex>0||Form1->ComboBox5->ItemIndex==-1)&&Form1->ComboBox5->Text!="")quantactive->Add("5");
  if((Form1->ComboBox6->ItemIndex>0||Form1->ComboBox6->ItemIndex==-1)&&Form1->ComboBox6->Text!="")quantactive->Add("6");

  if(quantactive->Count==0)
    {if(Form1->RadioButton1->Checked==true)Form1->RadioButton1Click(Form1);if(Form1->RadioButton2->Checked==true)Form1->RadioButton2Click(Form1);
     if(Form1->RadioButton3->Checked==true)Form1->RadioButton3Click(Form1);if(Form1->RadioButton4->Checked==true)Form1->RadioButton4Click(Form1);
     delete quantactive;quantactive=NULL;return;}
  if(currentgroup=="MainGroup")
   for(int j=0;j<list->Count;j++)
     {
      if(Form1->RadioButton3->Checked==true)
			 Sort(quantactive,j);
      if(Form1->RadioButton1->Checked==true)
        if(type->Strings[j]=="Movie")
             Sort(quantactive,j);
      if(Form1->RadioButton2->Checked==true)
        if(type->Strings[j]=="TV series")
			 Sort(quantactive,j);
      if(Form1->RadioButton4->Checked==true)
        for(int k=0;k<elect->Count;k++)
          if(list->Strings[j]==elect->Strings[k])
			 Sort(quantactive,j);
     }
  else
    for(int j=0;j<listcurrentgroup->Count;j++)
     {index=list->IndexOf(listcurrentgroup->Strings[j]);
      if(Form1->RadioButton3->Checked==true)
             Sort(quantactive,index);
      if(Form1->RadioButton1->Checked==true)
        if(type->Strings[index]=="Movie")
             Sort(quantactive,index);
      if(Form1->RadioButton2->Checked==true)
        if(type->Strings[index]=="TV series")
             Sort(quantactive,index);
      if(Form1->RadioButton4->Checked==true)
        for(int k=0;k<elect->Count;k++)
          if(list->Strings[index]==elect->Strings[k])
			 Sort(quantactive,index);
     }
   delete quantactive;quantactive=NULL;
}
//-----------------------------------------------------------------------------

  void Reset()
  {
  Form1->ComboBox1->ItemIndex=0;Form1->ComboBox2->ItemIndex=0;Form1->ComboBox3->ItemIndex=0;
  Form1->ComboBox4->ItemIndex=0;Form1->ComboBox5->ItemIndex=0;Form1->ComboBox6->ItemIndex=0;
  Form1->ComboBox7->ItemIndex=0;Form1->ComboBox8->ItemIndex=0;
  for(int i=1;i<=4;i++)
   for(int j=0;j<((TCheckListBox*)Form1->FindComponent("CheckListBox"+IntToStr(i)))->Count;j++)
	 if(((TCheckListBox*)Form1->FindComponent("CheckListBox"+IntToStr(i)))->Checked[j]==true)
        ((TCheckListBox*)Form1->FindComponent("CheckListBox"+IntToStr(i)))->Checked[j]=false;
  }
//-----------------------------------------------------------------------------

  void BackgroundColor(TColor A)
  {
   Form1->Font->Color=A;Form1->Label1->Font->Color=A;Form1->Label9->Font->Color=A;Form1->Label11->Font->Color=A;
   Form1->Label12->Font->Color=A;Form1->Label13->Font->Color=A;Form1->Label16->Font->Color=A;
   Form1->Label17->Font->Color=A;Form1->Label18->Font->Color=A;Form1->Label21->Font->Color=A;
   for(int i=1;i<=7;i++)
	if(((TLabel*)Form1->FindComponent("Line"+IntToStr(i)))->Font->Color!=clGreen)
	 ((TLabel*)Form1->FindComponent("Line"+IntToStr(i)))->Font->Color=A;
   //Form1->RadioButton1->Refresh();Form1->RadioButton2->Refresh();Form1->RadioButton3->Refresh();Form1->RadioButton4->Refresh();
  }

//-----------------------------------------------------------------------------

  void Quantity()
  {
	Form1->Label18->Caption=FloatToStr(Form1->ListBox1->ItemIndex+1)+'-'+FloatToStr(Form1->ListBox1->Count);
  }
//-----------------------------------------------------------------------------

  void Logs(AnsiString Text,AnsiString Name,AnsiString Type,AnsiString Year,AnsiString Country,AnsiString Genre)
  {
   TDateTime CurrentDateTime=Now();
   logs->LoadFromFile("Data/Logs.temp");logs->Add("["+CurrentDateTime+"] ("+Text+"): "+Name+" - "+Type+" - "+Year+" - "+Country+" - "+Genre);
   logs->SaveToFile("Data/Logs.temp");logs->Clear();
  }
//-----------------------------------------------------------------------------

  void ChooseFunctionFont(int x)
  {
    switch(x)
    {case 1:{Form1->Font1Click(Form1);break;}
     case 2:{Form1->Font2Click(Form1);break;}
     case 3:{Form1->Font3Click(Form1);break;}
     case 4:{Form1->Font4Click(Form1);break;}
     case 5:{Form1->Font5Click(Form1);break;}
     default: break;
    }
  }
//----------------------------------------Перевірка, яка мова обрана, і її зміна---------------------------------------------

  void Selectlang(TStringList *lastlang,TStringList *Genre,TStringList *Country,TStringList *View,TStringList *Release)
  {
    TStringList *TempLastLang=new TStringList();TempLastLang->Text=lastlang->Text;
    for (int i=0; i<Genre->Count;i++)
      for (int j=31; j<=54;j++)
		Genre->Strings[i]=StringReplace(Genre->Strings[i],TempLastLang->Strings[j],lang->Strings[j],TReplaceFlags()<<rfReplaceAll);
    for (int i=0; i<Country->Count;i++)
	  for (int j=138; j<=168;j++)//168
        Country->Strings[i]=StringReplace(Country->Strings[i],TempLastLang->Strings[j],lang->Strings[j],TReplaceFlags()<<rfReplaceAll);
    for (int i=0; i<Release->Count;i++)
      for (int j=56; j<=57;j++)
		{Release->Strings[i]=StringReplace(Release->Strings[i],TempLastLang->Strings[j],lang->Strings[j],TReplaceFlags()<<rfReplaceAll);
         View->Strings[i]=StringReplace(View->Strings[i],TempLastLang->Strings[j],lang->Strings[j],TReplaceFlags()<<rfReplaceAll);}
    delete TempLastLang;TempLastLang=NULL;
  }
//-----------------------------------------------Зміна мови--------------------------------------------------------------

  void AboutBox_LicenseLanguage()
   {
	  AboutBox->Caption=lang->Strings[12];AboutBox->Version->Caption=lang->Strings[71];
	  AboutBox->Copyright->Caption=lang->Strings[72];AboutBox->Comments->Caption=lang->Strings[73];
	  AboutBox->TabSheet1->Caption=lang->Strings[16];AboutBox->TabSheet2->Caption=lang->Strings[214];
	  AboutBox->License->Caption=lang->Strings[215];AboutBox->TrialVersion->Caption=lang->Strings[216];
	  AboutBox->ClearList();
	  for(int i=217;i<=223;i++)//for(int i=214;i<=229;i++)
		 AboutBox->FillList(lang->Strings[i]);
	  Form12->Caption=lang->Strings[214];Form12->Button1->Caption=lang->Strings[228];
	  Form12->Label1->Caption=lang->Strings[226];Form12->Label2->Caption=lang->Strings[227];
	  Form12->SetLang(lang->Strings[229],lang->Strings[230]);
   }
  void Language() //останній елемент lang->Strings[350]315    Свободные:81,169,170,171   165+8
  {
 //Form1--------------------------------------------------------------------------
 //Интерфейс-Главное меню-Контекстное меню--------------------------------------
   Form1->Label2->Caption=lang->Strings[0];Form1->Label3->Caption=lang->Strings[1];Form1->Label4->Caption=lang->Strings[2];Form1->Label5->Caption=lang->Strings[0];Form1->Label6->Caption=lang->Strings[1];Form1->Label7->Caption=lang->Strings[2];
   Form1->Label8->Caption=lang->Strings[3];Form1->Label9->Caption=lang->Strings[4];Form1->Label10->Caption=lang->Strings[5];Form1->Label11->Caption=lang->Strings[6];Form1->Label12->Caption=lang->Strings[7];Form1->Label13->Caption=lang->Strings[8];
   Form1->Label14->Caption=lang->Strings[9];Form1->Label15->Caption=lang->Strings[10];Form1->Label16->Caption=lang->Strings[11];
   Form1->Caption=lang->Strings[12];Form1->MCatalogMenu->Caption=lang->Strings[13];Form1->MOptions->Caption=lang->Strings[14];Form1->MHelpNote->Caption=lang->Strings[15];Form1->MAbout->Caption=lang->Strings[16];
   Form1->MAdd->Caption=lang->Strings[17];Form1->MSave->Caption=lang->Strings[18];Form1->MRandomFilm->Caption=lang->Strings[196];
   Form1->MFilmsUnderMood->Caption=lang->Strings[175];Form1->MSort->Caption=lang->Strings[19];Form1->MReset->Caption=lang->Strings[20];
   Form1->MWebSite->Caption=lang->Strings[21];Form1->MQuit->Caption=lang->Strings[22];Form1->N8->Caption=lang->Strings[23];Form1->N9->Caption=lang->Strings[24];
   Form1->BG1->Caption=lang->Strings[24]+" "+1;Form1->BG2->Caption=lang->Strings[24]+" "+2;Form1->BG3->Caption=lang->Strings[24]+" "+3;Form1->BG4->Caption=lang->Strings[24]+" "+4;Form1->BG5->Caption=lang->Strings[24]+" "+5;
   Form1->Image5->Hint=lang->Strings[25];Form1->Image4->Hint=lang->Strings[26];Form1->MElect->Caption=lang->Strings[27];Form1->MDelete->Caption=lang->Strings[29];Form1->PDeleteFilm->Caption=lang->Strings[29];
   Form1->MEdit->Caption=lang->Strings[30];Form1->N2->Caption=lang->Strings[84];Form1->Edit5->Hint=lang->Strings[86];
   Form1->MQFilter->Caption=lang->Strings[91];Form1->MQAll->Caption=lang->Strings[92];Form1->MQView->Caption=lang->Strings[93];
   Form1->MQRls->Caption=lang->Strings[94];Form1->MQYear->Caption=lang->Strings[95];Form1->MSearch->Caption=lang->Strings[96];
   Form1->MSerialExpected->Caption=lang->Strings[245]+" ("+lang->Strings[79]+")";
   Form1->Image13->Hint=lang->Strings[204];
   Form1->MSeveralDeleting->Caption=lang->Strings[232];Form1->MFilter->Caption=lang->Strings[248];
   Form1->MAlphabetFilm->Caption=lang->Strings[293];Form1->MNewMovies->Caption=lang->Strings[349];
 //Группы
   Form1->AllGroups->Caption=lang->Strings[181];Form1->Groups->Caption=lang->Strings[181];Form1->MainGroup->Caption=lang->Strings[182];
   Form1->MAddGroup->Caption=lang->Strings[183];OpenGroup=lang->Strings[184];RenameGroup=lang->Strings[185];DeleteGroup=lang->Strings[186];
   Form1->Groups1->Caption=lang->Strings[187];Form1->Groups2->Caption=lang->Strings[188];Form1->FilmDel->Caption=lang->Strings[189];
   if(currentgroup=="MainGroup")Form1->Image12->Hint=lang->Strings[195]+" "+lang->Strings[182];
   else Form1->Image12->Hint=lang->Strings[195]+" "+currentgroup;
   for(int i=0;i<quantity;i++)
    {opengroup[i]->Caption=OpenGroup;renamegroup[i]->Caption=RenameGroup;deletegroup[i]->Caption=DeleteGroup;}
 //------
   Form1->MCatalog->Caption=lang->Strings[100];Form1->MFilms->Caption=lang->Strings[114];
   Form1->PAddToDesired->Caption=lang->Strings[132];Form1->PAddToMyCatalog->Caption=lang->Strings[115];
   Form1->Image7->Hint=lang->Strings[118];Form1->Image9->Hint=lang->Strings[172];Form1->Label17->Hint=lang->Strings[131]+": "+seasonfilm+", "+lang->Strings[199]+" "+seriesfilm;
   Form1->Label19->Caption=lang->Strings[133];Form1->Label20->Caption=lang->Strings[133];Form1->Label21->Caption=lang->Strings[134];
   Form1->Label22->Caption=lang->Strings[135];Form1->Label23->Caption=lang->Strings[136];Form1->Label24->Caption=lang->Strings[137];
   min=lang->Strings[55];
   Form1->N1->Caption=lang->Strings[175];Form1->MTurnOn->Caption=lang->Strings[176];Form1->MTurnOff->Caption=lang->Strings[177];
   Form1->N3->Caption=lang->Strings[209];
   //Form1:ComboBox & CheckListBox------------------------------------------------------
   Form1->ComboBox1->Clear();Form1->ComboBox1->Items->Add(lang->Strings[8]);
   for(int i=31;i<=54;i++)
	  Form1->ComboBox1->Items->Add(lang->Strings[i]);
   Form1->ComboBox1->ItemIndex=0;
   Form1->CheckListBox1->Clear();
   for(int i=31;i<=54;i++)
	  Form1->CheckListBox1->Items->Add(lang->Strings[i]);
   Form1->ComboBox2->Clear();Form1->ComboBox2->Items->Add(lang->Strings[8]);
   for(int i=138;i<=168;i++)
	  Form1->ComboBox2->Items->Add(lang->Strings[i]);
   Form1->ComboBox2->ItemIndex=0;
   Form1->CheckListBox2->Clear();
   for(int i=138;i<=168;i++)
	  Form1->CheckListBox2->Items->Add(lang->Strings[i]);
   if(sortmode->Strings[2]!="3")Form1->ComboBox3->Items->Strings[0]=lang->Strings[8];
   Form1->ComboBox3->ItemIndex=0;Form1->ComboBox7->ItemIndex=0;
   for(int i=0;i<Form1->CheckListBox3->Count;i++)
		if(Form1->CheckListBox3->Checked[i]==true)
           Form1->CheckListBox3->Checked[i]=false;
   Form1->ComboBox4->Clear();
   if(sortmode->Strings[3]!="3")Form1->ComboBox4->Items->Add(lang->Strings[8]);
   else Form1->ComboBox4->Items->Add("~");
   for(int i=20;i<=270;i++)
	  Form1->ComboBox4->Items->Add(IntToStr(i)+min);
   Form1->ComboBox4->ItemIndex=0;
   Form1->ComboBox8->Clear();Form1->ComboBox8->Items->Add("~");
   for(int i=20;i<=270;i++)
	  Form1->ComboBox8->Items->Add(IntToStr(i)+min);
   Form1->ComboBox8->ItemIndex=0;
   Form1->CheckListBox4->Clear();
   for(int i=20;i<=270;i++)
	  Form1->CheckListBox4->Items->Add(IntToStr(i)+min);
   Form1->ComboBox5->Clear();Form1->ComboBox5->Items->Add(lang->Strings[8]);Form1->ComboBox5->Items->Add(lang->Strings[56]);Form1->ComboBox5->Items->Add(lang->Strings[57]);
   Form1->ComboBox5->ItemIndex=0;
   Form1->ComboBox6->Clear();Form1->ComboBox6->Items->Add(lang->Strings[8]);Form1->ComboBox6->Items->Add(lang->Strings[56]);Form1->ComboBox6->Items->Add(lang->Strings[57]);
   Form1->ComboBox6->ItemIndex=0;
   //Save, sure, yes, not------------------------------------------------------------------
   yes=lang->Strings[56];not=lang->Strings[57];save=lang->Strings[65];sure=lang->Strings[66];
   //Form4----------------------------------------------------------------------
   Form4->Caption=lang->Strings[58];Form4->Button1->Caption=lang->Strings[59];Form4->Button2->Caption=lang->Strings[60];Form4->PAdd->Caption=lang->Strings[61];
   Form4->PDelete->Caption=lang->Strings[88];Form4->PEdit->Caption=lang->Strings[89];Form4->PCancel->Caption=lang->Strings[62];Form4->ListBox1->Clear();
   Form4->ListBox1->Items->Add(lang->Strings[63]);Form4->ListBox1->Items->Add(lang->Strings[64]);Form4->ListBox1->Items->Add(lang->Strings[65]);Form4->ListBox1->Items->Add(lang->Strings[66]);
   Form4->ListBox1->Hint=lang->Strings[261];
   Form4->SetLang(lang->Strings[63],lang->Strings[64],lang->Strings[65],lang->Strings[66]);
   //Form3--------------------------------------------------------------------------
   Form1->AlphabetPanelOptions->Caption=lang->Strings[296];
   Form3->Caption=lang->Strings[14];Form3->Button1->Caption=lang->Strings[208];Form3->Button2->Caption=lang->Strings[62];
   Form1->ExpandAllAlphabetPanel->Caption=lang->Strings[297];Form1->CollapseAllAlphabetPanel->Caption=lang->Strings[298];
   Form3->GroupBox1->Caption=lang->Strings[299];Form3->GroupBox2->Caption=lang->Strings[300];Form3->GroupBox3->Caption=lang->Strings[301];
   Form3->GroupBox5->Caption=lang->Strings[302];Form3->GroupBox6->Caption=lang->Strings[303];
   Form3->RBPanelNone->Caption=lang->Strings[304];Form3->RBFrameNone->Caption=lang->Strings[304];
   Form3->RBWindowOwn->Caption=lang->Strings[306];Form3->RBFrameOwn->Caption=lang->Strings[307];
   Form3->InfoTextColor->Caption=lang->Strings[308]+"    ";Form3->LabelsColor->Caption=lang->Strings[308]+"    ";
   if(lang->Strings[24]=="Background")Form3->InfoBackGroundColor->Caption="BG   ";
   else Form3->InfoBackGroundColor->Caption=lang->Strings[24]+"   ";
   Form3->ComboBox1->Clear();
   for(int i=1;i<=5;i++)
	  Form3->ComboBox1->Items->Add(lang->Strings[305]+" "+IntToStr(i));
   Form3->ComboBox2->Clear();Form3->ComboBox2->Items->Add(lang->Strings[305]+" 1");Form3->ComboBox2->Items->Add(lang->Strings[305]+" 2");
   //[67]-"Общие настройки" 67-PageControl1 296-PageControl2
   //AboutBox-------------------------------------------------------------------
   AboutBox_LicenseLanguage();
   //Form6----------------------------------------------------------------------
   Form6->Caption=lang->Strings[173];
   Form6->Image1->Hint=lang->Strings[39]+", "+lang->Strings[40]+", "+lang->Strings[43]+", "+lang->Strings[44];
   Form6->Image2->Hint=lang->Strings[31]+", "+lang->Strings[36]+", "+lang->Strings[39]+", "+lang->Strings[46]+", "+lang->Strings[47]+", "+lang->Strings[48];
   Form6->Image3->Hint=lang->Strings[37]+", "+lang->Strings[42];
   Form6->Image4->Hint=lang->Strings[33]+", "+lang->Strings[34]+", "+lang->Strings[35];
   Form6->Image5->Hint=lang->Strings[38]+", "+lang->Strings[41]+", "+lang->Strings[48];
   //Form2----------------------------------------------------------------------
   Form2->Caption=lang->Strings[75];Form2->Label1->Caption=lang->Strings[76];
   Form2->Label2->Caption=lang->Strings[0];Form2->Label3->Caption=lang->Strings[1];Form2->Label4->Caption=lang->Strings[2];Form2->Label1->Caption=lang->Strings[76];
   Form2->Label5->Caption=lang->Strings[3];Form2->Label6->Caption=lang->Strings[5];Form2->Label7->Caption=lang->Strings[181];
   Form2->RadioButton1->Caption=lang->Strings[78]+" ";Form2->RadioButton2->Caption=lang->Strings[79]+" ";
   Form2->CheckBox1->Caption=lang->Strings[9]+" ";Form2->CheckBox2->Caption=lang->Strings[10]+" ";
   Form2->Label11->Caption=lang->Strings[82];
   Form2->Label12->Caption=lang->Strings[61];Form2->Label13->Caption=lang->Strings[60];Form2->Label14->Caption=lang->Strings[131]+":";Form2->Label15->Caption=lang->Strings[133];
   Form2->Image3->Hint=lang->Strings[83];Form2->Image4->Hint=lang->Strings[83];Form2->Image5->Hint=lang->Strings[21];Form2->Image6->Hint=lang->Strings[90];
   Form2->Label16->Caption=lang->Strings[134]+":";Form2->Label17->Caption=lang->Strings[135];Form2->Label18->Caption=lang->Strings[136];
   Form2->Label19->Caption=lang->Strings[137];Form2->Label21->Caption=lang->Strings[199];Form2->Label12->Hint=lang->Strings[178];
   Form2->CheckListBox1->Clear();
   for(int i=31;i<=54;i++)
	  Form2->CheckListBox1->Items->Add(lang->Strings[i]);
   Form2->CheckListBox2->Clear();
   for(int i=138;i<=168;i++)
      Form2->CheckListBox2->Items->Add(lang->Strings[i]);
   Form2->ComboBox2->Clear();
   for(int i=20;i<=270;i++)
	  Form2->ComboBox2->Items->Add(IntToStr(i)+min);
   Form2->SetLang(lang->Strings[113],lang->Strings[129],min,lang->Strings[27],lang->Strings[28]);Form2->Edit1->Hint=lang->Strings[130];
   //Form7----------------------------------------------------------------------
   Form7->Caption=lang->Strings[96];Form7->Button1->Caption=lang->Strings[97];Form7->Button2->Caption=lang->Strings[60];
   Form7->Image2->Hint=lang->Strings[98];Form7->Image3->Hint=lang->Strings[69];
   Form7->CheckBox1->Caption=lang->Strings[76]+" ";Form7->CheckBox2->Caption=lang->Strings[0]+" ";Form7->CheckBox3->Caption=lang->Strings[133]+" ";
   Form7->CheckBox4->Caption=lang->Strings[1]+" ";Form7->CheckBox5->Caption=lang->Strings[2]+" ";Form7->CheckBox6->Caption=lang->Strings[10]+" ";
   Form7->CheckBox7->Caption=lang->Strings[9]+" ";Form7->CheckBox8->Caption=lang->Strings[200]+" ";Form7->CheckBox9->Caption=lang->Strings[136]+" ";
   Form7->CheckBox10->Caption=lang->Strings[201]+" ";Form7->CheckBox11->Caption=lang->Strings[134]+" ";Form7->CheckBox12->Caption=lang->Strings[202]+" ";
   Form7->CheckBox13->Caption=lang->Strings[203]+" ";Form7->CheckBox14->Caption=lang->Strings[231]+" ";Form7->CheckBox15->Caption=lang->Strings[80]+" ";
   Form7->RadioButton1->Caption=lang->Strings[8]+" ";Form7->RadioButton2->Caption=lang->Strings[6]+" ";
   Form7->RadioButton3->Caption=lang->Strings[7]+" ";Form7->RadioButton4->Caption=lang->Strings[11]+" ";
   notfound=lang->Strings[99];
   Form7->ComboBox1->Clear();
   for(int i=31;i<=54;i++)
	  Form7->ComboBox1->Items->Add(lang->Strings[i]);
   Form7->ComboBox2->Clear();
   for(int i=138;i<=168;i++)
	  Form7->ComboBox2->Items->Add(lang->Strings[i]);
   Form7->ComboBox4->Clear();
   if(Form7->ComboBox8->Visible==true)Form7->ComboBox4->Items->Add("~");
   for(int i=20;i<=270;i++)
	  Form7->ComboBox4->Items->Add(IntToStr(i)+min);
   Form7->ComboBox8->Clear();Form7->ComboBox8->Items->Add("~");
   for(int i=20;i<=270;i++)
	  Form7->ComboBox8->Items->Add(IntToStr(i)+min);
   Form7->ComboBox5->Clear();Form7->ComboBox5->Items->Add(lang->Strings[56]);Form7->ComboBox5->Items->Add(lang->Strings[57]);
   Form7->ComboBox6->Clear();Form7->ComboBox6->Items->Add(lang->Strings[56]);Form7->ComboBox6->Items->Add(lang->Strings[57]);
   Form7->CheckListBox1->Clear();
   for(int i=31;i<=54;i++)
	  Form7->CheckListBox1->Items->Add(lang->Strings[i]);
   Form7->CheckListBox2->Clear();
   for(int i=138;i<=168;i++)
	  Form7->CheckListBox2->Items->Add(lang->Strings[i]);
   Form7->CheckListBox4->Clear();
   for(int i=20;i<=270;i++)
	  Form7->CheckListBox4->Items->Add(IntToStr(i)+min);
   Form7->SetLang(min);
   //Form8----------------------------------------------------------------------
   Form8->Caption=lang->Strings[100];Form8->PAddCatalog->Caption=lang->Strings[101];Form8->POpenCatalog->Caption=lang->Strings[102];
   Form8->PDeleteCatalog->Caption=lang->Strings[103];Form8->PCreateCatalog->Caption=lang->Strings[104];Form8->PRenameCatalog->Caption=lang->Strings[179];
   Form8->Hint=lang->Strings[105];
   Form8->PCreateDublicateSelected->Caption=lang->Strings[241];Form8->PCreateDublicate->Caption=lang->Strings[127];
   Form8->PCreateEmpty->Caption=lang->Strings[128];
   Form8->PPassword->Caption=lang->Strings[122];Form8->PPasswordCreate->Caption=lang->Strings[123];Form8->PPasswordDelete->Caption=lang->Strings[88];
   Form8->Label3->Caption=lang->Strings[122]+":";
   Form8->ClearList();Form8->FillList(lang->Strings[66]);
   for(int i=106;i<=112;i++)
	 Form8->FillList(lang->Strings[i]);
   Form8->FillList(lang->Strings[124]);Form8->FillList(lang->Strings[125]);
   Form8->FillList(lang->Strings[180]);Form8->FillList(lang->Strings[263]);
   Form8->ForbiddenChars(lang->Strings[129]);
   //Form9----------------------------------------------------------------------
   PasswordDlg->Label1->Caption=lang->Strings[119];PasswordDlg->Label2->Caption=lang->Strings[120];PasswordDlg->Label3->Caption=lang->Strings[121];
   PasswordDlg->Setname(lang->Strings[126]);
   //Form10----------------------------------------------------------------------
   Form10->Caption=lang->Strings[204];Form10->Button1->Caption=lang->Strings[208];Form10->Button2->Caption=lang->Strings[60];
   Form10->GroupBox1->Caption=lang->Strings[0];Form10->GroupBox2->Caption=lang->Strings[133];
   Form10->GroupBox3->Caption=lang->Strings[1];Form10->GroupBox4->Caption=lang->Strings[2];
   Form10->RadioButton1->Caption=lang->Strings[205];Form10->RadioButton2->Caption=lang->Strings[206];
   Form10->RadioButton3->Caption=lang->Strings[213];Form10->RadioButton4->Caption=lang->Strings[205];
   Form10->RadioButton5->Caption=lang->Strings[206];Form10->RadioButton6->Caption=lang->Strings[213];
   Form10->RadioButton7->Caption=lang->Strings[205];Form10->RadioButton8->Caption=lang->Strings[206];
   Form10->RadioButton9->Caption=lang->Strings[207];Form10->RadioButton10->Caption=lang->Strings[205];
   Form10->RadioButton11->Caption=lang->Strings[206];Form10->RadioButton12->Caption=lang->Strings[207];
   Form11->Caption=lang->Strings[210];
   //Form11----------------------------------------------------------------------
   Form11->SetCaptions(lang->Strings[212],lang->Strings[240]);
   //Form13----------------------------------------------------------------------
   Form13->Caption=lang->Strings[232];Form13->Label1->Caption=lang->Strings[233];Form13->Label2->Caption=lang->Strings[234];
   Form13->Button1->Caption=lang->Strings[88];Form13->Button2->Caption=lang->Strings[62];
   Form13->MRemoveSelectionL1->Caption=lang->Strings[235];Form13->MRemoveSelectionL2->Caption=lang->Strings[235];
   Form13->MoveAllMovieLR->Hint=lang->Strings[236];Form13->MoveAllMovieRL->Hint=lang->Strings[237];
   Form13->MoveMovieLR->Hint=lang->Strings[238];Form13->MoveMovieRL->Hint=lang->Strings[239];
   Form13->SetLang(lang->Strings[97],lang->Strings[66]);
   //Form15----------------------------------------------------------------------
   Form15->Caption=lang->Strings[242];Form15->Button1->Caption=lang->Strings[208];Form15->Button2->Caption=lang->Strings[62];
   Form15->ComboBox1->Hint=lang->Strings[243]+" ";Form15->ComboBox2->Hint=lang->Strings[244]+" ";
   Form15->Label1->Caption=lang->Strings[245];
   //Form16----------------------------------------------------------------------
   Form16->Caption=lang->Strings[248];Form16->GroupBox1->Caption=lang->Strings[249];Form16->GroupBox2->Caption=lang->Strings[250];
   Form16->Panel1->Caption=lang->Strings[251];Form16->AddFilter->Caption=lang->Strings[252];Form16->EditFilter->Caption=lang->Strings[253];
   Form16->DeleteFilter->Caption=lang->Strings[254];Form16->FavouriteFilter->Caption=lang->Strings[265];
   Form16->Button1->Caption=lang->Strings[255];Form16->Button2->Caption=lang->Strings[60];
   Form16->Label1->Caption=lang->Strings[0];Form16->Label2->Caption=lang->Strings[133];
   Form16->Label3->Caption=lang->Strings[1];Form16->Label4->Caption=lang->Strings[2];
   Form16->Label5->Caption=lang->Strings[10];Form16->Label6->Caption=lang->Strings[9];
   Form16->RadioButton1->Caption=lang->Strings[6]+" ";Form16->RadioButton2->Caption=lang->Strings[7]+" ";
   Form16->RadioButton3->Caption=lang->Strings[8]+" ";Form16->RadioButton4->Caption=lang->Strings[11]+" ";
   AnsiString _Words[8]={lang->Strings[8],lang->Strings[65],sure,lang->Strings[129],lang->Strings[256],lang->Strings[257],lang->Strings[265],lang->Strings[266]};
   Form16->SetLang(_Words,min);
   Form1->Image16->Hint=lang->Strings[258];Form1->MLastFilter->Caption=lang->Strings[262];Form1->MFavouriteFilter->Caption=lang->Strings[264];
   Form16->ListBox1->Hint=lang->Strings[260];
   //Form16:ComboBox & CheckListBox----------------------------------------------
   Form16->ComboBox1->Clear();Form16->ComboBox1->Items->Add(lang->Strings[8]);
   for(int i=31;i<=54;i++)
	  Form16->ComboBox1->Items->Add(lang->Strings[i]);
   Form16->ComboBox1->ItemIndex=0;
   Form16->CheckListBox1->Clear();
   for(int i=31;i<=54;i++)
	  Form16->CheckListBox1->Items->Add(lang->Strings[i]);
   Form16->ComboBox2->Clear();Form16->ComboBox2->Items->Add(lang->Strings[8]);
   for(int i=138;i<=168;i++)
	  Form16->ComboBox2->Items->Add(lang->Strings[i]);
   Form16->ComboBox2->ItemIndex=0;
   Form16->CheckListBox2->Clear();
   for(int i=138;i<=168;i++)
	  Form16->CheckListBox2->Items->Add(lang->Strings[i]);
   Form16->ComboBox3->Items->Strings[0]=lang->Strings[8];
   Form16->ComboBox3->ItemIndex=0;Form16->ComboBox7->ItemIndex=0;
   for(int i=0;i<Form16->CheckListBox3->Count;i++)
		if(Form16->CheckListBox3->Checked[i]==true)
		   Form16->CheckListBox3->Checked[i]=false;
   Form16->ComboBox4->Clear();
   Form16->ComboBox4->Items->Add(lang->Strings[8]);
   for(int i=20;i<=270;i++)
	  Form16->ComboBox4->Items->Add(IntToStr(i)+min);
   Form16->ComboBox4->ItemIndex=0;
   Form16->ComboBox8->Clear();Form16->ComboBox8->Items->Add("~");
   for(int i=20;i<=270;i++)
	  Form16->ComboBox8->Items->Add(IntToStr(i)+min);
   Form16->ComboBox8->ItemIndex=0;
   Form16->CheckListBox4->Clear();
   for(int i=20;i<=270;i++)
	  Form16->CheckListBox4->Items->Add(IntToStr(i)+min);
   Form16->ComboBox5->Clear();Form16->ComboBox5->Items->Add(lang->Strings[8]);Form16->ComboBox5->Items->Add(lang->Strings[56]);Form16->ComboBox5->Items->Add(lang->Strings[57]);
   Form16->ComboBox5->ItemIndex=0;
   Form16->ComboBox6->Clear();Form16->ComboBox6->Items->Add(lang->Strings[8]);Form16->ComboBox6->Items->Add(lang->Strings[56]);Form16->ComboBox6->Items->Add(lang->Strings[57]);
   Form16->ComboBox6->ItemIndex=0;
   //Form17--------
   Form1->MStatistic->Caption=lang->Strings[269];
   Form17->Caption=lang->Strings[269];Form17->TabSheet1->Caption=lang->Strings[13];
   Form17->TabSheet2->Caption=lang->Strings[270];Form17->TabSheet3->Caption=lang->Strings[271];
   Form17->Label15->Caption=lang->Strings[282];Form17->Label16->Caption=lang->Strings[286];Form17->Saving->Caption=lang->Strings[287];
   Form17->RadioButton1->Caption=lang->Strings[0]+" ";Form17->RadioButton2->Caption=lang->Strings[133]+" ";
   Form17->RadioButton3->Caption=lang->Strings[1]+" ";Form17->RadioButton4->Caption=lang->Strings[2]+" ";
   Form17->RadioButton5->Caption=lang->Strings[295]+" ";
   int index=Form17->ComboBox1->ItemIndex;
   Form17->ComboBox1->Items->Strings[0]=lang->Strings[0]+" ";Form17->ComboBox1->Items->Strings[1]=lang->Strings[133]+" ";
   Form17->ComboBox1->Items->Strings[2]=lang->Strings[1]+" ";Form17->ComboBox1->Items->Strings[3]=lang->Strings[2]+" ";
   Form17->ComboBox1->Items->Strings[4]=lang->Strings[295]+" ";
   Form17->ComboBox1->ItemIndex=index;
   Form17->Label19->Caption=lang->Strings[316];
   Form17->SetLang(lang->Strings[286],lang->Strings[263],lang->Strings[288],lang->Strings[317],lang->Strings[97]);

   int currentmonth=FormatDateTime("mm", Now()).ToInt(),currentyear=FormatDateTime("yyyy", Now()).ToInt(),month,year;
   Form17->CategoryButtons1->Categories->Items[0]->Caption=lang->Strings[8];
   for(int i=0;i<4;i++)
	  Form17->CategoryButtons1->Categories->Items[i+1]->Caption=lang->Strings[i+318];
   for(int i=1;i<=5;i++)
   {
	  month=currentmonth-i;year=currentyear;
	  if(month<=0){month=12-abs(month);year--;}
	  Form17->CategoryButtons1->Categories->Items[i+4]->Caption=lang->Strings[323+month-1]+AnsiString(" ")+AnsiString(year);
   }
   Form17->CategoryButtons1->Categories->Items[10]->Caption=lang->Strings[322];//335
   int EventsBoxItemIndex=Form17->EventsBox->ItemIndex;
   Form17->EventsBox->Clear();
   Form17->EventsBox->Items->Add(lang->Strings[8]);
   for(int i=0;i<14;i++)
	  Form17->EventsBox->Items->Add(lang->Strings[i+335]);
   Form17->EventsBox->ItemIndex=EventsBoxItemIndex;
   //Form18--------
   Form2->Image12->Hint=lang->Strings[289];Form18->Caption=lang->Strings[289];Form18->Label1->Caption=lang->Strings[290];
   Form18->ImageInfo->Hint=lang->Strings[291];Form18->Seasons->Hint=lang->Strings[292];
   Form18->AddSeason->Hint=lang->Strings[61]+" (Ctrl+A)";Form18->DeleteSeason->Hint=lang->Strings[88]+" (Ctrl+D)";
   Form18->ApplyButton->Caption=lang->Strings[208];
   //Form19--------
   Form19->Caption=lang->Strings[294];
   //Form20--------
   Form20->OrigName->Caption=lang->Strings[135]+":";Form20->Genre->Caption=lang->Strings[0]+":";Form20->Country->Caption=lang->Strings[133]+":";
   Form20->Year->Caption=lang->Strings[1]+":";Form20->Time->Caption=lang->Strings[2]+":";
   //Form21--------
   Form1->MTemplateCommands->Caption=lang->Strings[309];
   Form21->Caption=lang->Strings[309];Form21->Button1->Caption=lang->Strings[208];Form21->Button2->Caption=lang->Strings[62];
   //Form22--------
   Form22->Caption=lang->Strings[349];Form22->Button1->Caption=lang->Strings[61];Form22->Button2->Caption=lang->Strings[60];
   for(int i=1;i<=6;i++)
   {
	  ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Clear();
	  ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Items->Add("-:-:-");
	  ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Items->Add(OpenGroup);
	  ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Items->Add(lang->Strings[310]);
	  ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Items->Add(lang->Strings[311]);
   }
   Form21->ImageInfo->Hint=AnsiString("Ctrl+1 - ")+lang->Strings[8]+AnsiString("\nCtrl+2 - ")+
	  lang->Strings[6]+AnsiString("\nCtrl+3 - ")+lang->Strings[7]+AnsiString("\nCtrl+4 - ")+lang->Strings[11];
   }
//---------------------------------------------------------------options->Strings[7]-индикатор на язык, который был изначально

void InfoOnFirstPage(bool f) //InfoOnFirstPage
{
  Form1->Label1->Visible=f;Form1->Label5->Visible=f;Form1->Label6->Visible=f;
  Form1->Label7->Visible=f;Form1->Label8->Visible=f;Form1->Label10->Visible=f;Form1->Label19->Visible=f;
  Form1->Edit1->Visible=f;Form1->Edit2->Visible=f;Form1->Edit3->Visible=f;Form1->Edit4->Visible=f;Form1->Edit6->Visible=f;
  Form1->Memo1->Visible=f;Form1->Image4->Visible=f;Form1->Image5->Visible=f;Form1->Image9->Visible=f;
  for (int j=1;j<=5;j++)
	 ((TImage*)Form1->FindComponent("Star"+IntToStr(j)))->Visible=f;
}
//---------------------------------------------------------------------------

void InfoOnSecondPage(bool f)
{
  Form1->Label21->Visible=f;Form1->Label22->Visible=f;Form1->Label23->Visible=f;Form1->Label24->Visible=f;
  Form1->Edit7->Visible=f;Form1->Edit8->Visible=f;Form1->Memo2->Visible=f;
  if(Form1->Image7->Visible==true)Form1->Label26->Visible=false;
  else Form1->Label26->Visible=f;
}
//---------------------------------------------------------------------------

void FilmsFromOtherCatalogs()
{
  Form1->ListBox2->Clear();AnsiString name;
  TSearchRec sr;
  if (FindFirst("Films from other catalogs\\*.*", faDirectory, sr) == 0)
	{
		do {
			if( faDirectory  == sr.Attr )
				if( sr.Name != "." && sr.Name != "..")
					{name=sr.Name;
					 for(int j=0;j<name.Length();j++)
						{if(name.c_str()[j]=='_')
						   name.c_str()[j]=':';
						 if(name.c_str()[j]=='[')
						   name.c_str()[j]='«';
						 if(name.c_str()[j]==']')
						   name.c_str()[j]='»';}
					 Form1->ListBox2->Items->Add(name);
					}
		} while (FindNext(sr) == 0);
    FindClose(sr);
	}
}
//---------------------------------------------------------------------------

void Backup()
   {
	   TStringList *initiallang=new TStringList();
	   if(InitialLang=="Ukrainian")
		  {initiallang->LoadFromFile("Soft/Language/Language.ua");
		   Selectlang(initiallang,genreb,countryb,viewb,releaseb);}
	   if(InitialLang=="Russian")
		  {initiallang->LoadFromFile("Soft/Language/Language.ru");
		   Selectlang(initiallang,genreb,countryb,viewb,releaseb);}
	   if(InitialLang=="English")
		  {initiallang->LoadFromFile("Soft/Language/Language.en");
		   Selectlang(initiallang,genreb,countryb,viewb,releaseb);}
	   genreb->SaveToFile("Data/Genres.dat");countryb->SaveToFile("Data/Country.dat");
	   viewb->SaveToFile("Data/Views.dat");releaseb->SaveToFile("Data/Release.dat");
	   if(options->Strings[5]=="Ukrainian")InitialLang="Ukrainian";
	   if(options->Strings[5]=="Russian")InitialLang="Russian";
	   if(options->Strings[5]=="English")InitialLang="English";
	   delete initiallang;initiallang=NULL;
   }
//-----------------------------------------------------------------------------

void SaveCatalog()
{
	  list->SaveToFile("Data/Names.dat");
	  genre->SaveToFile("Data/Genres.dat");
	  year->SaveToFile("Data/Years.dat");
	  duration->SaveToFile("Data/Duration.dat");
	  country->SaveToFile("Data/Country.dat");
	  link->SaveToFile("Data/Links.dat");
	  view->SaveToFile("Data/Views.dat");
	  type->SaveToFile("Data/Type.dat");
	  type1->SaveToFile("Data/TypeA.dat");
      release->SaveToFile("Data/Release.dat");
	  elect->SaveToFile("Data/Elect.dat");
	  trailer->SaveToFile("Data/Trailer.dat");
	  season->SaveToFile("Data/Seasons.dat");
      tagline->SaveToFile("Data/Tagline.dat");
      originalname->SaveToFile("Data/Original name.dat");
      director->SaveToFile("Data/Director.dat");
	  cast->SaveToFile("Data/Cast.dat");
	  rating->SaveToFile("Data/Rating.dat");
	  episode->SaveToFile("Data/CurrentEpisode.dat");
	  date->SaveToFile("Data/Dates.dat");
	  if(options->Strings[5]=="Ukrainian")InitialLang="Ukrainian";
	  if(options->Strings[5]=="Russian")InitialLang="Russian";
	  if(options->Strings[5]=="English")InitialLang="English";
	  logs->LoadFromFile("Data/Logs.temp");logs->SaveToFile("Data/Logs.txt");logs->Clear();
	  TemplateCommands->SaveToFile("Data/TemplateCommands.txt");
}
//---------------------------------------------------------------------------

void AccessToForbiddenChar(AnsiString changename)
{
      for(int i=0;i<changename.Length();i++)
        {if(changename.c_str()[i]==':')
           changename.c_str()[i]='_';
         if(changename.c_str()[i]=='«')
           changename.c_str()[i]='[';
         if(changename.c_str()[i]=='»')
           changename.c_str()[i]=']';}
}
//---------------------------------------------------------------------------

void ConvertTime(AnsiString timefilm,TObject *Obj)
{
      int time=StrToInt(timefilm),b=time,hour=0;AnsiString minend,beginhour;
        hour=time/60;time=b-hour*60;
        if(time<10)
          minend="0"+IntToStr(time);
        else
          minend=IntToStr(time);
        if(hour<10)
          beginhour="0"+IntToStr(hour);
        else
		  beginhour=IntToStr(hour);
		if(Obj==Form1->Edit3)Form1->Edit3->Text=IntToStr(b)+min+"/"+beginhour+":"+minend;
		//else Form20->Label5->Caption=IntToStr(b)+min+"/"+beginhour+":"+minend;
}
//---------------------Для разделения количества сезонов и серий----------------

void SeparationSeasonSeries(AnsiString string)
{
  bool b=false;seasonfilm="";seriesfilm="";
  for(int i=0;i<string.Length();i++)
    {
     if(b==true)
      seriesfilm+=string.c_str()[i];
     if(b==false&&string.c_str()[i]!=':')
      seasonfilm+=string.c_str()[i];
     if(string.c_str()[i]==':')
      b=true;
    }
}
//---------------------------------------------------------------------------

AnsiString QuantityElements(TCheckListBox *CheckLB)
{
 int n=0;AnsiString a="";
    for(int z=0;z<CheckLB->Count;z++)
      if(CheckLB->Checked[z])
      {
      if(n>0)
       {a=a+", "+CheckLB->Items->Strings[z];n++;}
      if(n==0)
       {a=a+CheckLB->Items->Strings[z];n++;}
      }
  return a;
}
//---------------------------------------------------------------------------

AnsiString ExpressionNumberFromString(TComboBox*combobox)
{
   AnsiString number,temp,string=combobox->Text;bool null=false;
   for (int i=0;i<string.Length();i++)
	 if ((string.c_str()[i]>=48) && (string.c_str()[i]<=57))
	   temp = temp+string.c_str()[i];
   if(temp==""||temp=="0")number="1";
   else
	 for (int i=0;i<temp.Length();i++)
		{
		 if(temp.c_str()[i]!='0')
		   null=true;
		 if(null==true)
		   number+=temp.c_str()[i];
		}
	return number;
}
//---------------------------------------------------------------------------

void FilmsUnderMood()
{
   Form6->Position=poScreenCenter;Form6->ShowModal();
   if(Form6->Tag==1||Form6->Tag==2||Form6->Tag==3||Form6->Tag==4||Form6->Tag==5)
	   {
         if(currentgroup!="MainGroup")
		  Form1->MainGroupClick(Form1);
		 Form1->ListBox1->Items->Clear();
		 for(int i=0;i<list->Count;i++)
		  if(view->Strings[i]==not)
		   {
			if(Form6->Tag==1)
			  if(genre->Strings[i].Pos(lang->Strings[39])||genre->Strings[i].Pos(lang->Strings[40])||
				 genre->Strings[i].Pos(lang->Strings[43])||genre->Strings[i].Pos(lang->Strings[44]))
				   Form1->ListBox1->Items->Add(list->Strings[i]);
			if(Form6->Tag==2)
			  if(genre->Strings[i].Pos(lang->Strings[31])||genre->Strings[i].Pos(lang->Strings[36])||
				 genre->Strings[i].Pos(lang->Strings[39])||genre->Strings[i].Pos(lang->Strings[46])||
				 genre->Strings[i].Pos(lang->Strings[47])||genre->Strings[i].Pos(lang->Strings[48]))
				   Form1->ListBox1->Items->Add(list->Strings[i]);
			if(Form6->Tag==3)
			  if(genre->Strings[i].Pos(lang->Strings[37])||genre->Strings[i].Pos(lang->Strings[42]))
				   Form1->ListBox1->Items->Add(list->Strings[i]);
			if(Form6->Tag==4)
			  if(genre->Strings[i].Pos(lang->Strings[33])||genre->Strings[i].Pos(lang->Strings[34])||
				 genre->Strings[i].Pos(lang->Strings[35]))
				   Form1->ListBox1->Items->Add(list->Strings[i]);
			if(Form6->Tag==5)
			  if(genre->Strings[i].Pos(lang->Strings[38])||genre->Strings[i].Pos(lang->Strings[41])||
				 genre->Strings[i].Pos(lang->Strings[48]))
				   Form1->ListBox1->Items->Add(list->Strings[i]);
		   }
		  if(Form1->ListBox1->Count==0)
			{ShowMessage(lang->Strings[174]);
			 for(int i=0;i<list->Count;i++)
			   Form1->ListBox1->Items->Add(list->Strings[i]);}
		  Quantity();
	   }
}
//---------------------------------------------------------------------------

void TrialTime()
{
  int globaltime=86400-trial; //86400 - 1 day  //3675(01:01:15)
  int temp,hour,minutes,seconds;AnsiString beginhour,beginmin,beginsec,caption;
  minutes=globaltime/60;temp=minutes;
  seconds=globaltime-minutes*60;
  hour=minutes/60;minutes=temp-hour*60;
  if(hour<10)
	 beginhour="0"+IntToStr(hour);
  else
	 beginhour=IntToStr(hour);
  if(minutes<10)
	 beginmin="0"+IntToStr(minutes);
  else
	 beginmin=IntToStr(minutes);
  if(seconds<10)
	 beginsec="0"+IntToStr(seconds);
  else
	 beginsec=IntToStr(seconds);

  if(options->Strings[5]=="Ukrainian")
	 caption=lang->Strings[225]+"\n"+beginhour+"год. "+beginmin+"хв. "+beginsec+"сек.";
  if(options->Strings[5]=="Russian")
	 caption=lang->Strings[225]+"\n"+beginhour+"час. "+beginmin+"мин. "+beginsec+"сек.";
  if(options->Strings[5]=="English")
	 caption=lang->Strings[225]+"\n"+beginhour+"hour. "+beginmin+"min. "+beginsec+"sec.";
  AboutBox->LicenseInfo->Caption=caption;
  Form1->Image14->Hint=caption;
  //lang->Strings[225] - "До конца ознакомительной версии осталось:\n"
}
//---------------------------------------------------------------------------

void ShowStars(TForm *Form,TStringList *_rating,int index)
{
  AnsiString rat;float test;
  if(TryStrToFloat(_rating->Strings[index],test)) rat=_rating->Strings[index];
  else rat=AnsiString(_rating->Strings[index].c_str()[0])+","+_rating->Strings[index].c_str()[2];

  for (int j=1;j<=5;j++)
	{((TImage*)Form->FindComponent("Star"+IntToStr(j)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
	 ((TImage*)Form->FindComponent("Star"+IntToStr(j)))->Hint=_rating->Strings[index];}
  if(_rating->Strings[index]!="0.0")
	{
	 if(_rating->Strings[index]=="0.5")
		((TImage*)Form->FindComponent("Star"+IntToStr(1)))->Picture->LoadFromFile("Soft/Buttons/Star_half.png");
	 else
		{for(int j=1;j<=(int)StrToFloat(rat);j++)
		   ((TImage*)Form->FindComponent("Star"+IntToStr(j)))->Picture->LoadFromFile("Soft/Buttons/Star.png");
		 if(StrToFloat(rat)-(int)StrToFloat(rat)==0);
		 else
		  ((TImage*)Form->FindComponent("Star"+IntToStr((int)StrToFloat(rat)+1)))->Picture->LoadFromFile("Soft/Buttons/Star_half.png");
		}
	}
}
//---------------------------------------------------------------------------
//***************************Работа с панелью**********************************

void UpdateAlphabetPanel(AnsiString _namefilm)
{
  AnsiString chars="абвгдеєжзиіїйклмнопрстуфхцчшщэюяabcdefghijklmnopqrstuvwxyz",letter;
  int index;
  for (int i=0;i<59;i++)
  {
	letter=((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(i+1)))->Caption;
	if(letter=="#")
	 if(!chars.Pos(_namefilm.LowerCase().c_str()[0]))
	   {index=i+1;break;}
	if(letter!="#")//else
	 if(letter.LowerCase().c_str()[0]==_namefilm.LowerCase().c_str()[0])
	   {index=i+1;break;}
  }
  if(((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(index)))->Hint!="0")
  {
	Form1->CategoryPanelCollapse(((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(index))));
	Form1->CategoryPanelExpand(((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(index))));
  }
}
//---------------------------------------------------------------------------

void SetPanelParameters()
{
  if(AlphabetOptions->Strings[1]=="NONE")Form1->Panel2->Visible=false;
  else {Form1->Panel2->Visible=true;Form1->PanelImage->Picture->LoadFromFile("Soft/AlphabetPanel/Style"+AlphabetOptions->Strings[1]+".png");}
  if(AlphabetOptions->Strings[3]=="NONE")Form20->FrameImage->Visible=false;
  else
  {
	if(AlphabetOptions->Strings[3].Length()==1)
	 {Form20->FrameImage->Visible=true;FrameProperties::LoadComponent(Form20->FrameImage,"Soft/AlphabetPanel/FrameImage"+AlphabetOptions->Strings[3]+".dat");}
	else
	{
	  Form20->FrameImage->Visible=true;
	  FrameProperties::LoadComponent(Form20->FrameImage,"Soft/AlphabetPanel/FrameImageOwn.dat");
	  Form20->FrameImage->Canvas->Brush->Color=StringToColor(AlphabetOptions->Strings[3]);
	  Form20->FrameImage->Canvas->Rectangle(-1,-1,Form20->FrameImage->Width+1,Form20->FrameImage->Height+1);
	}
  }
  if(AlphabetOptions->Strings[5].Length()==1)
  {
	FrameProperties::LoadComponent(Form3->Panel1,"Soft/AlphabetPanel/WindowStyle"+AlphabetOptions->Strings[5]+".dat");
	Form20->Color=Form3->Panel1->Color;Form20->Font->Color=Form3->Panel1->Font->Color;
	SetLabelsFont(Form20,"WindowStyle"+AlphabetOptions->Strings[5]);
  }
  else
  {
	FrameProperties::LoadComponent(Form3->Panel1,"Soft/AlphabetPanel/WindowStyleOwn.dat");
	Form20->Color=Form3->Panel1->Color;Form20->Font->Color=Form3->Panel1->Font->Color;
	SetLabelsFont(Form20,"WindowStyleOwn");
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
  shadow = new CShadowClass(this);
//Курсори для AboutBox, License, Form8 и Пароля--------------------------------------------------
  Screen->Cursors[1] = LoadCursorFromFile("Soft/Cursors/Cursor.cur");
  Screen->Cursors[2] = LoadCursorFromFile("Soft/Cursors/Cursor_select.cur");//Screen->Cursors[3] - в Shadow.cpp
  Screen->Cursors[4] = LoadCursorFromFile("Soft/Cursors/Zoom(+).cur");
  Screen->Cursors[5] = LoadCursorFromFile("Soft/Cursors/Zoom(-).cur");
  AboutBox->Cursor=(TCursor)1;AboutBox->PageControl1->Cursor=(TCursor)1;
  AboutBox->TabSheet1->Cursor=(TCursor)1;AboutBox->TabSheet2->Cursor=(TCursor)1;
  AboutBox->OKButton->Cursor=(TCursor)1;AboutBox->Image1->Cursor=(TCursor)1;AboutBox->Panel1->Cursor=(TCursor)1;
  AboutBox->OKButton1->Cursor=(TCursor)1;AboutBox->Panel2->Cursor=(TCursor)1;AboutBox->License->Cursor=(TCursor)1;
  AboutBox->TrialVersion->Cursor=(TCursor)1;AboutBox->Label1->Cursor=(TCursor)2;
  Form8->Cursor=(TCursor)1;Form8->Image1->Cursor=(TCursor)1;Form8->ListBox1->Cursor=(TCursor)1;
  PasswordDlg->Cursor=(TCursor)1;PasswordDlg->OKBtn->Cursor=(TCursor)1;PasswordDlg->CancelBtn->Cursor=(TCursor)1;
  PasswordDlg->Image1->Cursor=(TCursor)2;
 //Язык для AboutBox и License--------------------------------------------------
	  Form8->CreateList();AboutBox->CreateList();
	  TStringList *CurrentLang=new TStringList();
	  CurrentLang->LoadFromFile("Soft/Language/Language.txt");
	  options->LoadFromFile("Data/Options.ini");
	  AnsiString lastlang=options->Strings[5];//для правильного показа текущего языка для TrialTime в лицензии
	  if(CurrentLang->Strings[1]=="Ukrainian")
		  {lang->LoadFromFile("Soft/Language/Language.ua");options->Strings[5]="Ukrainian";AboutBox_LicenseLanguage();}
	  if(CurrentLang->Strings[1]=="Russian")
		  {lang->LoadFromFile("Soft/Language/Language.ru");options->Strings[5]="Russian";AboutBox_LicenseLanguage();}
	  if(CurrentLang->Strings[1]=="English")
		  {lang->LoadFromFile("Soft/Language/Language.en");options->Strings[5]="English";AboutBox_LicenseLanguage();}
 //Проверка лицензии------------------------------------------------------------

	  Form1->MCatalogMenu->Enabled=false;Form1->MQFilter->Enabled=false;Form1->AllGroups->Enabled=false;
	  TRegistry *reg=new TRegistry();
	  reg->RootKey=HKEY_CLASSES_ROOT;
	  if(reg->KeyExists("\System.IndexOfOperation\\CLSD"))AboutBox->Tag=0;      //Лицензия стоит
	  else
	  {
		AboutBox->PageControl1->ActivePageIndex=1;
		if(reg->KeyExists("\System.Globalization.DateInfo\\CLSD"))
		 {
		  reg->OpenKey("\System.Globalization.DateInfo\\CLSD",true);
		  trial=reg->ReadInteger("");
		  if(trial==86400)
			{trial_temp=trial;AboutBox->Tag=3;AboutBox->ShowModal();            //НУЖНО активировать, иначе выход
			 if(AboutBox->Tag==0);
			 if(AboutBox->Tag==3) exit(0); //Без чистки
			}
		  else
			{                                                                   //Можно активировать,или дождаться конца триала
			 TrialTime();
			 trial_temp=trial;
			 AboutBox->Tag=2;
			 if(AboutBox->ShowModal()==mrCancel && AboutBox->Tag!=0) exit(0);
			 if(AboutBox->Tag==0);
			 if(AboutBox->Tag==2) {trialtimer=true;Image14->Visible=true;}
			}
		  reg->CloseKey();
		 }
		else
		 {
		  AboutBox->Tag=1;AboutBox->ShowModal();                                //Первый запуск программы
		  if(AboutBox->Tag==0);
		  if(AboutBox->Tag==1) exit(0);
		  if(AboutBox->Tag==2)
			{
			   reg->OpenKey("\System.Globalization.DateInfo\\CLSD",true);
			   reg->WriteInteger("",trial);
			   reg->CloseKey();
			   trialtimer=true;Image14->Visible=true;
            }
		 }
	  }
	  delete reg;
	  Form1->MCatalogMenu->Enabled=true;Form1->MQFilter->Enabled=true;Form1->AllGroups->Enabled=true;
  //--------------------------------------------------------
	  options->Strings[5]=lastlang;//возвращение начального языка
	  int font_kind;
	  list->LoadFromFile("Data/Names.dat");ListBox1->Items->Assign(list);
	  genre->LoadFromFile("Data/Genres.dat");
      year->LoadFromFile("Data/Years.dat");
      duration->LoadFromFile("Data/Duration.dat");
	  country->LoadFromFile("Data/Country.dat");
      link->LoadFromFile("Data/Links.dat");
	  view->LoadFromFile("Data/Views.dat");
      type->LoadFromFile("Data/Type.dat");
      type1->LoadFromFile("Data/TypeA.dat");
      release->LoadFromFile("Data/Release.dat");
      elect->LoadFromFile("Data/Elect.dat");
      trailer->LoadFromFile("Data/Trailer.dat");
      season->LoadFromFile("Data/Seasons.dat");
	  tagline->LoadFromFile("Data/Tagline.dat");
      originalname->LoadFromFile("Data/Original name.dat");
      director->LoadFromFile("Data/Director.dat");
	  cast->LoadFromFile("Data/Cast.dat");
	  rating->LoadFromFile("Data/Rating.dat");
	  episode->LoadFromFile("Data/CurrentEpisode.dat");
	  date->LoadFromFile("Data/Dates.dat");
	  TemplateCommands->LoadFromFile("Data/TemplateCommands.txt");
	  for(int i=0; i<4;i++)sortmode->Add("1");//Режим сортировки
	  //Установка настроек
      if(options->Strings[1]=="1")
		 {Form1->BG1->Checked=true;Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 1.jpg");BackgroundColor(clBlack);}
      if(options->Strings[1]=="2")
		 {Form1->BG2->Checked=true;Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 2.jpg");BackgroundColor(clBlack);}
	  if(options->Strings[1]=="3")
		 {Form1->BG3->Checked=true;Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 3.jpg");BackgroundColor(clBlack);}
	  if(options->Strings[1]=="4")
		 {Form1->BG4->Checked=true;Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 4.jpg");BackgroundColor(clCream);}
	  if(options->Strings[1]=="5")
		 {Form1->BG5->Checked=true;Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 5.jpg");BackgroundColor(clBlack);}
	  font_kind=StrToInt(options->Strings[3]);ChooseFunctionFont(font_kind);
	  if(options->Strings[9]=="TurnOn")
		   MTurnOn->Checked=true;
	  if(options->Strings[9]=="TurnOff")
		   MTurnOff->Checked=true;
      if (FileExists("Data/Logs.txt") == false)
		  {logs->Add("["+Now()+"] (Created catalog): "+options->Strings[7]);
		   logs->SaveToFile("Data/Logs.txt");logs->SaveToFile("Data/Logs.temp");}
	  if (FileExists("Data/Logs.txt") == true)
		  {logs->LoadFromFile("Data/Logs.txt");logs->SaveToFile("Data/Logs.temp");logs->Clear();}
	  //Любимый фильтр
	  favouritefilter->LoadFromFile("Soft/Favourite filter.txt");
	  if(favouritefilter->Strings[0]!="-")Form1->MFavouriteFilter->Enabled=true;
	  else Form1->MFavouriteFilter->Enabled=false;
	  //AlphabetPanel
	  AlphabetOptions->LoadFromFile("Soft/AlphabetOptions.txt");
	  SetPanelParameters();
	  //+2 года от текущего (напр. 2017-2019)-----------------
	  while(ComboBox3->Items->Strings[ComboBox7->Items->Count-1].ToInt()<FormatDateTime("yyyy", Now()).ToInt()+2)
	  {
			int Year=ComboBox3->Items->Strings[ComboBox3->Items->Count-1].ToInt()+1;
			ComboBox3->Items->Add(Year);ComboBox7->Items->Add(Year);
			Form2->ComboBox1->Items->Add(Year);Form2->ComboBox3->Items->Add(Year);
			Form7->ComboBox3->Items->Add(Year);Form7->ComboBox7->Items->Add(Year);
			Form16->ComboBox3->Items->Add(Year);Form16->ComboBox7->Items->Add(Year);
			CheckListBox3->Items->Add(Year);Form7->CheckListBox3->Items->Add(Year);
			Form16->CheckListBox3->Items->Add(Year);
	  }
	  //Создание списков-----------------------------------
	  Form2->CreateList();Form7->CreateList();Form22->CreateList();
//Определение языка и его смена----------------------------
	  if(CurrentLang->Strings[1]=="Ukrainian")
		{
		 UA->Checked=true;InitialLang="Ukrainian";lang->LoadFromFile("Soft/Language/Language.ua");Language();
		 if(options->Strings[5]=="Russian")
		  {CurrentLang->LoadFromFile("Soft/Language/Language.ru");
		   Selectlang(CurrentLang,genre,country,view,release);
		   options->Strings[7]=StringReplace(options->Strings[7],"каталог удален","каталог видалений",TReplaceFlags()<<rfReplaceAll);
		  }
		 if(options->Strings[5]=="English")
		  {CurrentLang->LoadFromFile("Soft/Language/Language.en");
		   Selectlang(CurrentLang,genre,country,view,release);
		   options->Strings[7]=StringReplace(options->Strings[7],"catalog deleted","каталог видалений",TReplaceFlags()<<rfReplaceAll);
		  }
		 options->Strings[5]="Ukrainian";
		}
	  if(CurrentLang->Strings[1]=="Russian")
		{
		 RU->Checked=true;InitialLang="Russian";lang->LoadFromFile("Soft/Language/Language.ru");Language();
		 if(options->Strings[5]=="Ukrainian")
		  {CurrentLang->LoadFromFile("Soft/Language/Language.ua");
		   Selectlang(CurrentLang,genre,country,view,release);
		   options->Strings[7]=StringReplace(options->Strings[7],"каталог видалений","каталог удален",TReplaceFlags()<<rfReplaceAll);
		  }
		 if(options->Strings[5]=="English")
		  {CurrentLang->LoadFromFile("Soft/Language/Language.en");
		   Selectlang(CurrentLang,genre,country,view,release);
		   options->Strings[7]=StringReplace(options->Strings[7],"catalog deleted","каталог удален",TReplaceFlags()<<rfReplaceAll);
		  }
		 options->Strings[5]="Russian";
		}
	  if(CurrentLang->Strings[1]=="English")
		{
		 English->Checked=true;InitialLang="English";lang->LoadFromFile("Soft/Language/Language.en");Language();
		 if(options->Strings[5]=="Ukrainian")
		  {CurrentLang->LoadFromFile("Soft/Language/Language.ua");
		   Selectlang(CurrentLang,genre,country,view,release);
		   options->Strings[7]=StringReplace(options->Strings[7],"каталог видалений","catalog deleted",TReplaceFlags()<<rfReplaceAll);
		  }
		 if(options->Strings[5]=="Russian")
		  {CurrentLang->LoadFromFile("Soft/Language/Language.ru");
		   Selectlang(CurrentLang,genre,country,view,release);
		   options->Strings[7]=StringReplace(options->Strings[7],"каталог удален","catalog deleted",TReplaceFlags()<<rfReplaceAll);
		  }
		 options->Strings[5]="English";
		}
	  delete CurrentLang;
//--------------------------------------------------------
//Создание групп-----
  TSearchRec sr;
   if (FindFirst("Data\\Groups\\*.dat*", faAnyFile | faDirectory, sr) == 0)
     {
        do
        {
			sr.Name=sr.Name.Delete(sr.Name.Length()-4+1, 4);
            namegroups->Add(sr.Name);quantity=namegroups->Count;
        }
        while(FindNext(sr) == 0);
	 }
    for(int i=0;i<quantity;i++)
      CreateGroup(i,namegroups->Strings[i]);
   currentgroup="MainGroup";Image12->Hint=lang->Strings[195]+" "+lang->Strings[182];
//--------------------
  genreb->Text=genre->Text;countryb->Text=country->Text;releaseb->Text=release->Text;viewb->Text=view->Text;
  MkDir("Data/Backup");
  FilmsFromOtherCatalogs();
  Quantity();
  Edit5->Text=lang->Strings[97];Form13->Edit1->Text=lang->Strings[97];Form13->Edit2->Text=lang->Strings[97];Form17->Edit5->Text=lang->Strings[97];
//----------------------
  if(Screen->Height<900)
	{if(Screen->Height==800)Form1->Height=726; else Form1->Height=721;}
  //*---Во время релиза, очистить данные Image, которые указаны внизу
  const char *pictures[12] = {"Search","Youtube-play-button","Arrow-Button","Delete","Cancel","Indicator",
							"Wikipedia","Arrow(left_inactive)","Arrow(right_active)","Group","Optionsort","No license"};
  for (int i=3;i<=14;i++)
	((TImage*)FindComponent("Image"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/"+AnsiString(pictures[i-3])+".png");
  Image16->Picture->LoadFromFile("Soft/Buttons/AddFilter.png");
  //*/
//Пароль----------------------------------------------------------------------------
  PasswordDlg->Image1->OnMouseDown=ImageDown;PasswordDlg->Image1->OnMouseUp=ImageUp;
  Form1->MCatalogMenu->Enabled=false;Form1->MQFilter->Enabled=false;Form1->AllGroups->Enabled=false;
  if(options->Strings[8]=="0")
	{Form1->MCatalogMenu->Enabled=true;Form1->MQFilter->Enabled=true;Form1->AllGroups->Enabled=true;}
  else
	  {
	   wchar_t *a=options->Strings[8].c_str();
	   AnsiString temp=a;PasswordDlg->SetPassword(temp);PasswordDlg->Tag=3;
	   AnsiString caption="Password of catalog \""+options->Strings[7]+"\"";
	   PasswordDlg->Caption=caption;PasswordDlg->Image1->Hint=lang->Strings[198];
	   PasswordDlg->ShowModal();
	   if(PasswordDlg->Tag==0)
		{openpassworddlg=true;ExitMsgDlg=false;Close();exit(0);}
	   if(PasswordDlg->Tag==1)
		  {Form1->MCatalogMenu->Enabled=true;Form1->MQFilter->Enabled=true;Form1->AllGroups->Enabled=true;}
	   if(PasswordDlg->Tag==2)
		 {pasagreement=true;openpassworddlg=true;MCatalogClick(Form1);}
	  }
//Курсоры-----------------------------------------------------------------------
  Form1->Cursor=(TCursor)1;ListBox1->Cursor=(TCursor)1;ListBox2->Cursor=(TCursor)1;Label17->Cursor=(TCursor)2;
  CategoryPanelGroup1->Cursor=(TCursor)1;ExpandAllAlphabetPanel->Cursor=(TCursor)2;CollapseAllAlphabetPanel->Cursor=(TCursor)2;
  ExpandCollapseButton->Cursor=(TCursor)2;Panel2->Cursor=(TCursor)1;Panel3->Cursor=(TCursor)1;
  Label11->Cursor=(TCursor)2;Label12->Cursor=(TCursor)2;Label13->Cursor=(TCursor)2;Label16->Cursor=(TCursor)2;
  Form3->Button1->Cursor=(TCursor)1;Form3->Button2->Cursor=(TCursor)1;Form3->Image1->Cursor=(TCursor)1;
  Form3->Panel1->Cursor=(TCursor)1;Form3->ComboBox1->Cursor=(TCursor)1;Form3->ComboBox2->Cursor=(TCursor)1;
  Form3->InfoFont->Cursor=(TCursor)2;Form3->LabelsFont->Cursor=(TCursor)2;Form3->ButtonColor1->Cursor=(TCursor)1;
  Form3->InfoTextColor->Cursor=(TCursor)1;Form3->InfoBackGroundColor->Cursor=(TCursor)1;Form3->LabelsColor->Cursor=(TCursor)1;
  Form4->Button1->Cursor=(TCursor)1;Form4->Button2->Cursor=(TCursor)1;Form4->Image1->Cursor=(TCursor)1;Form4->ListBox1->Cursor=(TCursor)1;
  Form7->Cursor=(TCursor)1;Form7->Button1->Cursor=(TCursor)1;Form7->Button2->Cursor=(TCursor)1;
  Form7->Image2->Cursor=(TCursor)2;Form7->Image3->Cursor=(TCursor)2;Form7->Image4->Cursor=(TCursor)2;Form7->Image5->Cursor=(TCursor)2;
  Form7->DateTimePicker1->Cursor=(TCursor)1;Form7->DateTimePicker2->Cursor=(TCursor)1;
  Form10->Cursor=(TCursor)1;Form10->Image1->Cursor=(TCursor)1;Form10->Button1->Cursor=(TCursor)1;Form10->Button2->Cursor=(TCursor)1;
  Form10->GroupBox1->Cursor=(TCursor)1;Form10->GroupBox2->Cursor=(TCursor)1;Form10->GroupBox3->Cursor=(TCursor)1;Form10->GroupBox4->Cursor=(TCursor)1;
  Form11->ProgressBar1->Cursor=(TCursor)1;
  Form12->Cursor=(TCursor)1;Form12->Button1->Cursor=(TCursor)1;
  Form13->Cursor=(TCursor)1;Form13->ListBox1->Cursor=(TCursor)1;Form13->ListBox2->Cursor=(TCursor)1;
  Form13->Button1->Cursor=(TCursor)1;Form13->Button2->Cursor=(TCursor)1;
  Form13->MoveAllMovieLR->Cursor=(TCursor)1;Form13->MoveAllMovieRL->Cursor=(TCursor)1;
  Form13->MoveMovieLR->Cursor=(TCursor)1;Form13->MoveMovieRL->Cursor=(TCursor)1;
  Form13->Image3->Cursor=(TCursor)2;Form13->Image4->Cursor=(TCursor)2;
  Form15->Cursor=(TCursor)1;Form15->Button1->Cursor=(TCursor)1;Form15->Button2->Cursor=(TCursor)1;
  Form15->ComboBox1->Cursor=(TCursor)1;Form15->ComboBox2->Cursor=(TCursor)1;Form15->CheckBox1->Cursor=(TCursor)1;
  Form16->Cursor=(TCursor)1;Form16->Button1->Cursor=(TCursor)1;Form16->Button2->Cursor=(TCursor)1;
  Form16->GroupBox1->Cursor=(TCursor)1;Form16->GroupBox2->Cursor=(TCursor)1;
  Form16->Panel1->Cursor=(TCursor)1;Form16->ListBox1->Cursor=(TCursor)1;
  Form16->Image1->Cursor=(TCursor)2;Form16->Image2->Cursor=(TCursor)2;Form16->Image3->Cursor=(TCursor)2;
  Form16->Image4->Cursor=(TCursor)2;
  Form17->Cursor=(TCursor)1;Form17->Image1->Cursor=(TCursor)1;Form17->PageControl1->Cursor=(TCursor)1;
  Form17->TabSheet1->Cursor=(TCursor)1;Form17->TabSheet2->Cursor=(TCursor)1;Form17->TabSheet3->Cursor=(TCursor)1;
  Form17->Chart1->OriginalCursor=(TCursor)4;Form17->ComboBox1->Cursor=(TCursor)1;
  Form17->Saving->Cursor=(TCursor)2;
  Form17->EventsBox->Cursor=(TCursor)1;Form17->DateTimePicker1->Cursor=(TCursor)1;Form17->DateTimePicker2->Cursor=(TCursor)1;
  Form17->DatePicker1->Cursor=(TCursor)1;Form17->DatePicker2->Cursor=(TCursor)1;Form17->CategoryButtons1->Cursor=(TCursor)1;
  Form17->Image6->Cursor=(TCursor)2;
  for(int i=1;i<=7;i++)
	{
	  if(i<=5)
	  {((TListBox*)Form17->FindComponent("ListBox"+IntToStr(i)))->Cursor=(TCursor)1;
	   ((TChartSeries*)Form17->FindComponent("Series"+IntToStr(i)))->Cursor=(TCursor)1;}
	  ((TRadioButton*)Form17->FindComponent("RadioButton"+IntToStr(i)))->Cursor=(TCursor)1;
	}
  Form18->Cursor=(TCursor)1;Form18->ScrollBox1->Cursor=(TCursor)1;
  Form18->ApplyButton->Cursor=(TCursor)2;Form18->ImageInfo->Cursor=(TCursor)2;
  Form18->AddSeason->Cursor=(TCursor)2;Form18->DeleteSeason->Cursor=(TCursor)2;
  Form19->Cursor=(TCursor)1;
  Form21->Cursor=(TCursor)1;Form21->Button1->Cursor=(TCursor)1;Form21->Button2->Cursor=(TCursor)1;
  Form22->Cursor=(TCursor)1;Form22->Button1->Cursor=(TCursor)1;Form22->Button2->Cursor=(TCursor)1;
  Form22->MovieImage1->Cursor=(TCursor)2;Form22->MovieImage2->Cursor=(TCursor)2;Form22->MovieImage3->Cursor=(TCursor)2;
  Form22->MovieLabel1->Cursor=(TCursor)2;Form22->MovieLabel2->Cursor=(TCursor)2;Form22->MovieLabel3->Cursor=(TCursor)2;
  Form22->SelectedMovieImage->Cursor=(TCursor)1;

  Form23->Cursor=(TCursor)1;Form23->CityBox->Cursor=(TCursor)1;Form23->CityBox1->Cursor=(TCursor)1;
  Form23->CinemaBox->Cursor=(TCursor)1;

  for (int i=0;i<59;i++)
	((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Cursor=(TCursor)1;
  for (int i=1;i<=6;i++)
	{((TGroupBox*)Form3->FindComponent("GroupBox"+IntToStr(i)))->Cursor=(TCursor)1;
	 if(i<=5)((TImage*)Form3->FindComponent("Style"+IntToStr(i)))->Cursor=(TCursor)2;
	}
  for(int i=0;i<Form3->ComponentCount;i++)
	if(Form3->Components[i]->ClassNameIs("TRadioButton"))
	   ((TRadioButton *)Form3->Components[i])->Cursor=(TCursor)1;

  for(int i=4;i<=18;i++)
	if(i!=8)
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->Cursor=(TCursor)2;
  for(int i=1;i<=15;i++)
     {
	  if(i<=8)
		{((TComboBox*)FindComponent("ComboBox"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TComboBox*)Form7->FindComponent("ComboBox"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TComboBox*)Form16->FindComponent("ComboBox"+IntToStr(i)))->Cursor=(TCursor)1;}
	  if(i<=4)
		{((TRadioButton*)FindComponent("RadioButton"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TCheckListBox*)Form7->FindComponent("CheckListBox"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TRadioButton*)Form7->FindComponent("RadioButton"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TCheckListBox*)Form16->FindComponent("CheckListBox"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TRadioButton*)Form16->FindComponent("RadioButton"+IntToStr(i)))->Cursor=(TCursor)1;}
	  if(i<=5)
		((TImage*)Form6->FindComponent("Image"+IntToStr(i)))->Cursor=(TCursor)2;
	  if(i<=12)
		{((TRadioButton*)Form10->FindComponent("RadioButton"+IntToStr(i)))->Cursor=(TCursor)1;
		 ((TRadioButton*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Cursor=(TCursor)1;
		}
	  ((TCheckBox*)Form7->FindComponent("CheckBox"+IntToStr(i)))->Cursor=(TCursor)1;
	 }
//События-----------------------------------------------------------------------
  for(int i=1;i<=8;i++)
	 {((TComboBox*)FindComponent("ComboBox"+IntToStr(i)))->OnKeyPress=ComboBoxPress;
	  if(i<=4)
		{((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClick=CheckListBoxClick;
         ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnClickCheck=CheckListBoxClick;
		 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnMouseEnter=CheckListBoxMouseEnter;
		 ((TCheckListBox*)FindComponent("CheckListBox"+IntToStr(i)))->OnMouseLeave=CheckListBoxMouseLeave;}
	 }
  for(int i=4;i<=18;i++)
   if(i!=8&&i!=12&&i!=14&&i!=15)
	 {((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseDown=ImageDown;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseUp=ImageUp;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseEnter=ImageMouseEnter;
	  ((TImage*)FindComponent("Image"+IntToStr(i)))->OnMouseLeave=ImageMouseLeave;}
  ExpandCollapseButton->OnMouseDown=ImageDown;ExpandCollapseButton->OnMouseUp=ImageUp;
  for(int i=3;i<=12;i++)
   if(i!=7&&i!=8)
	 {((TImage*)Form2->FindComponent("Image"+IntToStr(i)))->OnMouseDown=ImageDown;
	  ((TImage*)Form2->FindComponent("Image"+IntToStr(i)))->OnMouseUp=ImageUp;}
  Form2->ComboBox2->OnKeyPress=ComboBoxPress;
  Form3->InfoFont->OnMouseDown=ImageDown;Form3->InfoFont->OnMouseUp=ImageUp;
  Form3->LabelsFont->OnMouseDown=ImageDown;Form3->LabelsFont->OnMouseUp=ImageUp;
  for(int i=1;i<=5;i++)
	 {((TImage*)Form6->FindComponent("Image"+IntToStr(i)))->OnMouseDown=ImageDown;
	  ((TImage*)Form6->FindComponent("Image"+IntToStr(i)))->OnMouseUp=ImageUp;}
  Form7->Image2->OnMouseDown=ImageDown;Form7->Image2->OnMouseUp=ImageUp;
  Form7->Image3->OnMouseDown=ImageDown;Form7->Image3->OnMouseUp=ImageUp;
  for(int i=1;i<=8;i++)
	 {((TComboBox*)Form7->FindComponent("ComboBox"+IntToStr(i)))->OnKeyPress=ComboBoxPress;
	  ((TComboBox*)Form16->FindComponent("ComboBox"+IntToStr(i)))->OnKeyPress=ComboBoxPress;}
  for(int i=2;i<=7;i++)
	 ((TEdit*)Form7->FindComponent("Edit"+IntToStr(i)))->OnKeyPress=EditPress;
  for(int i=1;i<=4;i++)
	 {((TImage*)Form16->FindComponent("Image"+IntToStr(i)))->OnMouseDown=ImageDown;
	  ((TImage*)Form16->FindComponent("Image"+IntToStr(i)))->OnMouseUp=ImageUp;}
  Form13->Image3->OnMouseDown=ImageDown;Form13->Image3->OnMouseUp=ImageUp;
  Form13->Image4->OnMouseDown=ImageDown;Form13->Image4->OnMouseUp=ImageUp;
  Form18->AddSeason->OnMouseDown=ImageDown;Form18->AddSeason->OnMouseUp=ImageUp;
  Form18->DeleteSeason->OnMouseDown=ImageDown;Form18->DeleteSeason->OnMouseUp=ImageUp;
  Form18->ImageInfo->OnMouseDown=ImageDown;Form18->ImageInfo->OnMouseUp=ImageUp;

  ComboBox1->OnKeyUp=ComboBoxKeyUp;ComboBox2->OnKeyUp=ComboBoxKeyUp;
  ComboBox5->OnKeyUp=ComboBoxKeyUp;ComboBox6->OnKeyUp=ComboBoxKeyUp;
  ComboBox4->OnDropDown=ComboBoxDropDown;ComboBox8->OnDropDown=ComboBoxDropDown;
  Form7->ComboBox4->OnDropDown=ComboBoxDropDown;Form7->ComboBox8->OnDropDown=ComboBoxDropDown;
  Form15->ComboBox1->OnKeyPress=ComboBoxPress;
  Form16->ComboBox4->OnDropDown=ComboBoxDropDown;Form16->ComboBox8->OnDropDown=ComboBoxDropDown;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
 if(FirstExecute==false){Timer2->Enabled=true;FirstExecute=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)//Полоса прогресса
{
 Timer2->Enabled=false;Form11->Tag=1;Form11->ShowModal();
 if(openmode==false)
   if(MTurnOn->Checked==true)
	{
	  openmode=true;
	  FilmsUnderMood();
	}
 if(trialtimer==true)
	{Timer3->Enabled=true;Timer4->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)//Время пробной версии
{
  if(trial!=86400)trial++;                                       //86400 - 1 day
  if(trial==86400 && Form1->Active && close_access==true && !shadow->CheckVisible())        //86400 - 1 day
	{Timer3->Enabled=false;Timer4->Enabled=false;ShowMessage(lang->Strings[224]);//"The trial version is over!"
	 AboutBox->PageControl1->ActivePageIndex=1;
	 AboutBox->Tag=3;AboutBox->ShowModal();
	 if(AboutBox->Tag==0)Image14->Visible=false;
	 if(AboutBox->Tag==3) {ExitMsgDlg=false;Close();}
	}
  else
	TrialTime();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer4Timer(TObject *Sender)//Предупреждение об окончание пробной версии
{
   if(trial>=85800)//85800 - вкл (0:10:00)
	{
	 if(trial<86220 && trial%60==0)MessageBeep(MB_ICONEXCLAMATION);
	 if(trial>=86220 && trial%30==0)MessageBeep(MB_ICONEXCLAMATION);
	 if(blinking==false){Image14->Picture->LoadFromFile("Soft/Buttons/No license(light).png");blinking=true;return;}
	 if(blinking==true){Image14->Picture->LoadFromFile("Soft/Buttons/No license.png");blinking=false;return;}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer5Timer(TObject *Sender)//Проверка видимости увеличенного изображения
{
   if(!shadow->CheckVisible())
   {
	MCatalogMenu->Enabled=true;MQFilter->Enabled=true;AllGroups->Enabled=true;MOptions->Enabled=true;MAbout->Enabled=true;
	if(ListBox1->Visible)FocusControl(ListBox1); else FocusControl(ListBox2);
	Timer5->Enabled=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(ExitMsgDlg==true)
  {
	if(MessageDlg(lang->Strings[70],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)//Вы действительно хотите выйти?
	   Action=(TCloseAction)true;
	else
	  {Action=(TCloseAction)false;return;}
  }
  else
	   Action=(TCloseAction)true;
  if(Action==true)
  {
   if(trial_temp!=trial)
	{
	  Timer3->Enabled=false;Timer4->Enabled=false;
	  TRegistry *reg=new TRegistry();
	  reg->RootKey=HKEY_CLASSES_ROOT;
	  reg->OpenKey("\System.Globalization.DateInfo\\CLSD",true);
	  reg->WriteInteger("",trial);
	  reg->CloseKey();
	  delete reg;
	}
   if(s==true)
	 {
	 if(MessageDlg(save,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
		SaveCatalog();
	 else
	   {
		DeleteDir("Data/Image");MoveFiles("Data/Backup/Image/","Data/Image");
		DeleteDir("Data/Plot");MoveFiles("Data/Backup/Plot/","Data/Plot");
		DeleteDir("Data/Seasons");MoveFiles("Data/Backup/Seasons/","Data/Seasons");
		for(int i=0;i<quantity;i++)
		 DeleteFile("Data/Groups/"+namegroups->Strings[i]+".dat");
		MoveFiles("Data/Backup/Groups","Data/");
		Backup();
	   }
	 }
   if(s==false)
	 Backup();
   DeleteDir("Data/Backup");DeleteFile("Data/Logs.temp");
   options->SaveToFile("Data/Options.ini");
   favouritefilter->SaveToFile("Soft/Favourite filter.txt");
   AnsiString selectcatalog=options->Strings[7];
   if(!selectcatalog.Pos("удален")&&!selectcatalog.Pos("deleted")&&!selectcatalog.Pos("видалений")&&openpassworddlg==false)
	{
	  Form11->Tag=3;Form11->Position=poScreenCenter;Form11->Hint=selectcatalog;Form11->ShowModal();
	}
   //Saving CurrentLanguage
   options->LoadFromFile("Soft/Language/Language.txt");options->Strings[1]=InitialLang;options->SaveToFile("Soft/Language/Language.txt");
   //AlphabetPanel----------------------
   AlphabetOptions->SaveToFile("Soft/AlphabetOptions.txt");
   for (int i=0;i<59;i++)
	if(((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Hint!="0")
	{
	  for (int j=0;j<StrToInt(((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Hint);j++)
		  {delete Alphabet[i][j];Alphabet[i][j]=NULL;}
	  delete Alphabet[i];Alphabet[i]=NULL;
	}
   delete []Alphabet;Alphabet=NULL;
   delete AlphabetOptions;AlphabetOptions=NULL;
   //----------------------
   Form2->DeleteList();Form8->DeleteList();Form7->DeleteList();AboutBox->DeleteList();Form22->DeleteList();
   delete list,genre,year,duration,country,link,view,type,type1,release,elect,trailer,season,
   tagline,originalname,director,cast,rating,episode,date,options,lang,logs,genreb,countryb,viewb,releaseb,
   sortmode,duration_activated,favouritefilter,TemplateCommands;
   list = NULL;genre = NULL;year = NULL;duration = NULL;country = NULL;link = NULL;view = NULL;type = NULL;
   type1 = NULL;release = NULL;elect = NULL;trailer = NULL;season=NULL;tagline=NULL;originalname=NULL;
   director=NULL;cast=NULL;rating=NULL;episode=NULL;date=NULL;
   options = NULL;logs=NULL;lang = NULL;genreb=NULL;countryb=NULL;viewb=NULL;releaseb=NULL;
   sortmode=NULL;duration_activated=NULL;favouritefilter=NULL;TemplateCommands=NULL;
   for(int i=0;i<quantity;i++)
	{delete groups[i],opengroup[i],renamegroup[i],deletegroup[i];groups[i]=NULL;opengroup[i]=NULL;renamegroup[i]=NULL;deletegroup[i]=NULL;}
   for(int i=0;i<quantityadd;i++)
	{delete addtogroups[i];addtogroups[i]=NULL;}
   for(int i=0;i<quantitydelete;i++)
	{delete deletefromgroups[i];deletefromgroups[i]=NULL;}
   delete namegroups,listcurrentgroup,listgroupsmovie;namegroups=NULL;listcurrentgroup=NULL;listgroupsmovie=NULL;
   shadow->ResetVisible();delete shadow;shadow=NULL;
   //delete []groups,[]opengroup,[]renamegroup,[]deletegroup,[]addtogroups,[]deletefromgroups;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
 if(ListBox1->ItemIndex!=-1)
  {
   for(int i=0;i<list->Count;i++)
	 if(ListBox1->Items->Strings[ListBox1->ItemIndex]==list->Strings[i])
	  {
		if(Image10->Enabled==false)Image10Click(Sender);
		else Image11Click(Sender);
		if(season->Strings[i]!="0")
		{
			Label17->Visible=true;Image8->Visible=true;
			if(episode->Strings[i].c_str()[0]=='X')//Просмотрено(ожидается)
				{AnsiString string=episode->Strings[i];string=string.Delete(1,1);SeparationSeasonSeries(string);}
			else                                   //Нужно смотреть
				SeparationSeasonSeries(episode->Strings[i]);
			currentseason=seasonfilm;currentepisode=seriesfilm;
			SeparationSeasonSeries(season->Strings[i]);
			Label17->Caption=seasonfilm;
			Label17->Hint=lang->Strings[131]+": "+seasonfilm+", "+lang->Strings[199]+" "+seriesfilm;
		}
		else
			{Label17->Visible=false;Image8->Visible=false;seasonfilm="0";}
		Image10->Visible=true;Image11->Visible=true;Image15->Visible=true;
		wchar_t *a=list->Strings[i].c_str();AnsiString namefilm=a;
        AccessToForbiddenChar(namefilm);
		Image1->Picture->LoadFromFile("Data/Image/"+namefilm+".jpg");Memo2->Lines->Clear();
		Memo1->Lines->LoadFromFile("Data/Plot/"+namefilm+".dat");Memo2->Text=cast->Strings[i];
		Label1->Caption=list->Strings[i];
		Label21->Caption=lang->Strings[134]+":"+tagline->Strings[i];
		Label21->Hint=lang->Strings[134]+":"+tagline->Strings[i];
		Label26->Caption=lang->Strings[80]+": "+date->Strings[i]+" ";
		Edit1->Text=genre->Strings[i];Edit1->Hint=genre->Strings[i];Edit2->Text=year->Strings[i];
        Edit4->Text=link->Strings[i];Edit6->Text=country->Strings[i];Edit6->Hint=country->Strings[i];
		Edit7->Text=originalname->Strings[i];Edit7->Hint=originalname->Strings[i];
		Edit8->Text=director->Strings[i];Edit8->Hint=director->Strings[i];
		ConvertTime(duration->Strings[i],Form1->Edit3);
		ShowStars(Form1,rating,i);
		if(view->Strings[i]==yes){Image15->Hint=lang->Strings[247];Image15->Picture->LoadFromFile("Soft/Buttons/Seen.ico");}
		else {Image15->Hint=lang->Strings[246];Image15->Picture->LoadFromFile("Soft/Buttons/Unseen.ico");}
		SelectedFilm=i;watchtrailer=trailer->Strings[i];
		if(type->Strings[i]=="Movie")TypeFilm=lang->Strings[78];
		else TypeFilm=lang->Strings[79];
	  }
	Label18->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
	SizeOfIndicatorViewed();//Для Image15->Left(глаз-индикатор просмотра)
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label11Click(TObject *Sender)
{
	 RadioButton1->Checked=true;
	 Label11->Font->Style = TFontStyles()<<fsUnderline;
	 Label12->Font->Style = TFontStyles()>>fsUnderline;Label13->Font->Style = TFontStyles()>>fsUnderline;
	 Label16->Font->Style = TFontStyles()>>fsUnderline;
	 Line3->Font->Color=clGreen;Pointer->Top=81;
	 if(BG4->Checked==true){Line1->Font->Color=clCream;Line5->Font->Color=clCream;Line7->Font->Color=clCream;}
	 else {Line1->Font->Color=clBlack;Line5->Font->Color=clBlack;Line7->Font->Color=clBlack;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label12Click(TObject *Sender)
{
	 RadioButton2->Checked=true;
	 Label12->Font->Style = TFontStyles()<<fsUnderline;
	 Label13->Font->Style = TFontStyles()>>fsUnderline;Label11->Font->Style = TFontStyles()>>fsUnderline;
	 Label16->Font->Style = TFontStyles()>>fsUnderline;
	 Line5->Font->Color=clGreen;Pointer->Top=106;
	 if(BG4->Checked==true){Line1->Font->Color=clCream;Line3->Font->Color=clCream;Line7->Font->Color=clCream;}
	 else {Line1->Font->Color=clBlack;Line3->Font->Color=clBlack;Line7->Font->Color=clBlack;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Label13Click(TObject *Sender)
{
	 RadioButton3->Checked=true;
	 Label13->Font->Style = TFontStyles()<<fsUnderline;
	 Label11->Font->Style = TFontStyles()>>fsUnderline;Label12->Font->Style = TFontStyles()>>fsUnderline;
	 Label16->Font->Style = TFontStyles()>>fsUnderline;
	 Line1->Font->Color=clGreen;Pointer->Top=56;
	 if(BG4->Checked==true){Line3->Font->Color=clCream;Line5->Font->Color=clCream;Line7->Font->Color=clCream;}
	 else {Line3->Font->Color=clBlack;Line5->Font->Color=clBlack;Line7->Font->Color=clBlack;}
}
//---------------------------------------------------------------------------

 void __fastcall TForm1::Label16Click(TObject *Sender)
{
	 RadioButton4->Checked=true;
	 Label16->Font->Style = TFontStyles()<<fsUnderline;
	 Label11->Font->Style = TFontStyles()>>fsUnderline;Label12->Font->Style = TFontStyles()>>fsUnderline;
	 Label13->Font->Style = TFontStyles()>>fsUnderline;
	 Line7->Font->Color=clGreen;Pointer->Top=134;
	 if(BG4->Checked==true){Line1->Font->Color=clCream;Line3->Font->Color=clCream;Line5->Font->Color=clCream;}
	 else {Line1->Font->Color=clBlack;Line3->Font->Color=clBlack;Line5->Font->Color=clBlack;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox3Change(TObject *Sender)
{
  if(sortmode->Strings[2]=="3"&&ComboBox3->Text!=""&&ComboBox7->Text!=""&&!ComboBox3->Text.Pos('~')&&!ComboBox7->Text.Pos('~'))
   if(StrToInt(ComboBox3->Text)>StrToInt(ComboBox7->Text))
	if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0)
	   ComboBox7->ItemIndex=ComboBox3->ItemIndex;
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox4Change(TObject *Sender)
{
   AnsiString numbercb4=ExpressionNumberFromString(ComboBox4);
   ComboBox4->Text=numbercb4+min;
   if(sortmode->Strings[3]=="3"&&ComboBox4->Text!=""&&ComboBox8->Text!=""&&!ComboBox4->Text.Pos('~')&&!ComboBox8->Text.Pos('~'))
	   {int numbercb8=StrToInt(ExpressionNumberFromString(ComboBox8));
		if(StrToInt(numbercb4)>numbercb8)
			ComboBox8->ItemIndex=ComboBox4->ItemIndex;}
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox5Change(TObject *Sender)
{
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox6Change(TObject *Sender)
{
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox7Change(TObject *Sender)
{
  if(sortmode->Strings[2]=="3"&&ComboBox3->Text!=""&&ComboBox7->Text!=""&&!ComboBox3->Text.Pos('~')&&!ComboBox7->Text.Pos('~'))
   if(StrToInt(ComboBox3->Text)>StrToInt(ComboBox7->Text))
	 if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0)
		ComboBox7->ItemIndex=ComboBox3->ItemIndex;
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox8Change(TObject *Sender)
{
   AnsiString numbercb8=ExpressionNumberFromString(ComboBox8);
   ComboBox8->Text=numbercb8+min;
   if(sortmode->Strings[3]=="3"&&ComboBox4->Text!=""&&ComboBox8->Text!=""&&!ComboBox4->Text.Pos('~')&&!ComboBox8->Text.Pos('~'))
	   {int numbercb4=StrToInt(ExpressionNumberFromString(ComboBox4));
		if(StrToInt(numbercb4)>numbercb8)
			ComboBox8->ItemIndex=ComboBox4->ItemIndex;}
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox3Exit(TObject *Sender)
{
  if(ComboBox3->Items->IndexOf(ComboBox3->Text)<0&&sortmode->Strings[2]=="3"
   &&ComboBox3->Text!=""&&!ComboBox3->Text.Pos('~'))
	 {if(ComboBox7->Items->IndexOf(ComboBox7->Text)>=0&&ComboBox7->Text!="")
		 ComboBox3->ItemIndex=ComboBox7->ItemIndex;
	  else
		 ComboBox3->ItemIndex=0;}
  Callsort();Quantity();
  VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox7Exit(TObject *Sender)
{
  if(ComboBox7->Items->IndexOf(ComboBox7->Text)<0&&sortmode->Strings[2]=="3"
   &&ComboBox7->Text!=""&&!ComboBox7->Text.Pos('~'))
	 {if(ComboBox3->Items->IndexOf(ComboBox3->Text)>=0&&ComboBox3->Text!="")
		 ComboBox7->ItemIndex=ComboBox3->ItemIndex;
	  else
		 ComboBox7->ItemIndex=0;}
  Callsort();Quantity();
  VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox4Exit(TObject *Sender)
{
  if(ComboBox4->Items->IndexOf(ComboBox4->Text)<0&&sortmode->Strings[3]=="3"
   &&ComboBox4->Text!=""&&!ComboBox4->Text.Pos('~'))
	 {if(ComboBox8->Items->IndexOf(ComboBox8->Text)>=0&&ComboBox8->Text!="")
		 ComboBox4->ItemIndex=ComboBox8->ItemIndex;
	  else
		 ComboBox4->ItemIndex=0;}
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBox8Exit(TObject *Sender)
{
  if(ComboBox8->Items->IndexOf(ComboBox8->Text)<0&&sortmode->Strings[3]=="3"
   &&ComboBox8->Text!=""&&!ComboBox8->Text.Pos('~'))
	 {if(ComboBox4->Items->IndexOf(ComboBox4->Text)>=0&&ComboBox4->Text!="")
		 ComboBox8->ItemIndex=ComboBox4->ItemIndex;
	  else
		 ComboBox8->ItemIndex=0;}
   Callsort();Quantity();
   VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckListBoxClick(TObject *Sender)
{
  TCheckListBox * current = dynamic_cast<TCheckListBox*>(Sender);
  if(checkedclb==true)
  {
  for(int i=0;i<current->Count;i++)
    if(current->Selected[i])
       {if(current->Checked[i]==true)
           current->Checked[i]=false;
        else
           current->Checked[i]=true;
        break;}
  }
  checkedclb=true;
  Callsort();Quantity();
}

void __fastcall TForm1::CheckListBoxClickCheck(TObject *Sender)
{
  checkedclb=false;
}
//---------------------------------------------------------------------------

 void Category(TRadioButton *M,TStringList *t, AnsiString m)
  {
    int index;
    if(currentgroup=="MainGroup")
      if(M->Checked==true)
       {Form1->ListBox1->Items->Clear();
        for(int i=0;i<list->Count;i++)
           if(t->Strings[i]==m)
              Form1->ListBox1->Items->Add(list->Strings[i]);
       }
    if(currentgroup!="MainGroup")
      if(M->Checked==true)
       {Form1->ListBox1->Items->Clear();
        for(int i=0;i<listcurrentgroup->Count;i++)
          {index=list->IndexOf(listcurrentgroup->Strings[i]);//Form1->Caption=index;break;
           if(t->Strings[index]==m)
              Form1->ListBox1->Items->Add(list->Strings[index]);}
       }
     Reset();
     Quantity();
  }
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
 Category(RadioButton1,type,"Movie");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
 Category(RadioButton2,type,"TV series");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
 Category(RadioButton3,type1,"All");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
  int index;
  if(currentgroup=="MainGroup")
   if(RadioButton4->Checked==true)
    {ListBox1->Items->Clear();
	 for(int i=0;i<elect->Count;i++)
	   ListBox1->Items->Add(elect->Strings[i]);
    }
  if(currentgroup!="MainGroup")
    if(RadioButton4->Checked==true)
    {ListBox1->Items->Clear();
     for(int i=0;i<elect->Count;i++)
      {index=listcurrentgroup->IndexOf(elect->Strings[i]);
       if(index>=0)
         ListBox1->Items->Add(elect->Strings[i]);
      }
    }
  Reset();
  Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PopupMenuPopup(TObject *Sender)
{
	if(ListBox1->Count==0 || ListBox1->ItemIndex==-1)
	  {MElect->Enabled=false;MDelete->Enabled=false;MEdit->Enabled=false;PAddToDesired->Enabled=false;Groups->Enabled=false;FilmDel->Enabled=false;}
    else
	  {
		/*if(currentgroup=="MainGroup")
		 {MElect->Enabled=true;MDelete->Enabled=true;MEdit->Enabled=true;PAddToDesired->Enabled=true;}
		if(currentgroup!="MainGroup")
		 {MElect->Enabled=false;MDelete->Enabled=false;MEdit->Enabled=false;PAddToDesired->Enabled=false;}*/
		MElect->Enabled=true;MDelete->Enabled=true;MEdit->Enabled=true;PAddToDesired->Enabled=true;
		Groups->Enabled=true;FilmDel->Enabled=true;

		if(elect->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex])>=0)
		  {Form1->MElect->Caption=lang->Strings[28];electmode=0;}
		else
		  {Form1->MElect->Caption=lang->Strings[27];electmode=1;}
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MElectClick(TObject *Sender)
{
	int nIndex;
	if(electmode==1)
	  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
	   {
		 elect->Add(ListBox1->Items->Strings[ListBox1->ItemIndex]);nIndex=list->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
		 Logs("Added to Favorites",list->Strings[nIndex],TypeFilm,year->Strings[nIndex],country->Strings[nIndex],genre->Strings[nIndex]);
		 s=true;
	   }
	if(electmode==0)
	  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
	   {
		 elect->Delete(elect->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]));
		 nIndex=list->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
		 Logs("Removed from Favorites",list->Strings[nIndex],TypeFilm,year->Strings[nIndex],country->Strings[nIndex],genre->Strings[nIndex]);
		 if(RadioButton4->Checked==true)
		   {ListBox1->Items->Delete(ListBox1->ItemIndex);Label18->Caption="0-"+FloatToStr(ListBox1->Count);}
		 else Label18->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
		 s=true;
	   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MAddClick(TObject *Sender)
{
   close_access=false;
   AnsiString namefilm;
   Form2->Caption=lang->Strings[75];Form2->Label12->Caption=lang->Strings[61];
   Form2->RadioButton1->Checked=true;
   for(int i=0;i<Form2->CheckListBox1->Count;i++)
	if(Form2->CheckListBox1->Checked[i]==true)
	   Form2->CheckListBox1->Checked[i]=false;
   for(int i=0;i<Form2->CheckListBox2->Count;i++)
	if(Form2->CheckListBox2->Checked[i]==true)
	   Form2->CheckListBox2->Checked[i]=false;
   Form2->CheckListBox3->Items->Assign(namegroups);
   Form2->CheckListBox1->Checked[0]=true;Form2->CheckListBox2->Checked[0]=true;
   Form2->CheckBox1->Checked=false;Form2->CheckBox2->Checked=false;Form2->Memo1->Clear();Form2->Memo2->Clear();
   Form2->Edit1->Text=lang->Strings[77];Form2->Edit2->Text="";Form2->Edit3->Text="";Form2->Edit4->Text="1";
   Form2->Edit5->Text="";Form2->Edit6->Text="";Form2->Edit7->Text="";Form2->Edit8->Text="1";
   Form2->ComboBox1->ItemIndex=25;Form2->ComboBox2->ItemIndex=70;Form2->ComboBox3->ItemIndex=25;
   Form2->Image1->Picture->LoadFromFile("Soft/Buttons/Download.jpg");
   for (int i=1;i<=5;i++)
	((TImage*)Form2->FindComponent("Star"+IntToStr(i)))->Picture->LoadFromFile("Soft/Buttons/Star_empty.png");
   Form2->SetFavourite(false);//Избранные
   Form2->Rating->Caption="0.0";
   Form2->SetOpenMode("openadd");Form2->FillList(list);
   Form2->seasons->Clear();Form2->seasons->Add("1");//Сезоны для сериала
   Form2->Position=poScreenCenter;
   Form2->ShowModal();
   if(Form2->Tag==0)
	 {close_access=true;return;}
   if(Form2->Tag==1)
	{ MainGroupClick(Form1);
 //--------------------------------------Сохранение названия--------------------
	list->Add(Form2->Edit1->Text);namefilm=Form2->Edit1->Text;
    AccessToForbiddenChar(namefilm);
 //--------------------------------------Сохранение жанра и страны--------------
    AnsiString g=QuantityElements(Form2->CheckListBox1),c=QuantityElements(Form2->CheckListBox2);
    genre->Add(g);country->Add(c);
 //------------------------------Сохранение продолжительности-------------------
	AnsiString number=SearchNumbers(Form2->ComboBox2->Text);
	if(StrToInt(number)<20)number="90";
    duration->Add(number);
 //--------------------------------------Сохранение сюжета----------------------
	Form2->Memo1->Lines->SaveToFile("Data/Plot/"+namefilm+".dat");
 //--------------------------------------Сохранение фото------------------------
    Form2->Image1->Picture->SaveToFile("Data/Image/"+namefilm+".jpg");
 //-----------------------------Сохранение ссылки на фильм----------------------
    link->Add(Form2->Edit2->Text);
 //-----------------------------Сохранение ссылки на трейлер фильма-------------
    trailer->Add(Form2->Edit3->Text);
 //---------------Сохранение слогана,режиссера,актёров и ориг.названия----------
    director->Add(Form2->Edit5->Text);originalname->Add(Form2->Edit7->Text);
    cast->Add(Form2->Memo2->Text);
    if(Form2->Edit6->Text=="")tagline->Add("-");
    else tagline->Add(Form2->Edit6->Text);
 //---------------Сохранение года,вида кино,к-ства сезонов,к-ства серий---------
	AnsiString years;
	if(Form2->RadioButton1->Checked==true)
	   {
		TypeFilm=lang->Strings[78];
		year->Add(Form2->ComboBox1->Text);type->Add("Movie");season->Add("0");seasonfilm="0";episode->Add("0");
	   }
    else
	   {
		TypeFilm=lang->Strings[79];
		years=Form2->ComboBox1->Text+"-"+Form2->ComboBox3->Text;year->Add(years);
		type->Add("TV series");season->Add(Form2->Edit4->Text+":"+Form2->Edit8->Text);episode->Add("1:1");
		Form2->seasons->SaveToFile("Data/Seasons/"+namefilm+".dat");
	   }
	type1->Add("All");
 //--------------------------------------Сохранение просмотра-------------------
    if(Form2->CheckBox1->Checked==true)
       view->Add(yes);
    else
       view->Add(not);
 //--------------------------------------Сохранение релиза-------------------
    if(Form2->CheckBox2->Checked==true)
       release->Add(yes);
    else
	   release->Add(not);
 //-------------------------------------Сохранение рейтинга------------------
	rating->Add(Form2->Rating->Caption);
 //-------------------------------------Сохранение даты добавления------------------
	date->Add(Now().CurrentDate());
 //--------------------------------------------------------------------------
	Logs("Added",Form2->Edit1->Text,TypeFilm,year->Strings[year->Count-1],c,g);
 //-------------------------------------Добавление фильма в группы-----------
	TStringList *current=new TStringList();int index;
	for(int i=0;i<Form2->CheckListBox3->Count;i++)
	 if(Form2->CheckListBox3->Checked[i]==true)
	   {
		current->LoadFromFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		current->Add(Form2->Edit1->Text);
		current->SaveToFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		Logs("Added to group "+Form2->CheckListBox3->Items->Strings[i],Form2->Edit1->Text,TypeFilm,year->Strings[year->Count-1],c,g);
	   }
	delete current;current=NULL;
 //-------------------------------------Добавление фильма в избранные-----------
	if(Form2->GetFavourite())
	{
		elect->Add(Form2->Edit1->Text);
		Logs("Added to Favorites",Form2->Edit1->Text,TypeFilm,year->Strings[year->Count-1],c,g);
	}
 //---------------------------------------------------------------------------
	Callsort();
	Quantity();
	s=true;
    }
  ListBox1->ItemIndex=ListBox1->Items->IndexOf(Form2->Edit1->Text);ListBox1Click(Sender);
  Form2->Image1->Picture->Assign(NULL);
  UpdateAlphabetPanel(namefilm);
  close_access=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MDeleteClick(TObject *Sender)
{
  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
     {
	  int index;AnsiString namefilm;
	  for(int i=0;i<list->Count;i++)
        if(ListBox1->Items->Strings[ListBox1->ItemIndex]==list->Strings[i])
          {
			index=ListBox1->ItemIndex;
			Logs("Removed",list->Strings[i],TypeFilm,year->Strings[i],country->Strings[i],genre->Strings[i]);
			namefilm=list->Strings[i];
            list->Delete(i);genre->Delete(i);country->Delete(i);year->Delete(i);duration->Delete(i);link->Delete(i);
            view->Delete(i);type->Delete(i);type1->Delete(i);release->Delete(i);trailer->Delete(i);season->Delete(i);
			tagline->Delete(i);originalname->Delete(i);director->Delete(i);cast->Delete(i);rating->Delete(i);episode->Delete(i);
			date->Delete(i);
			AccessToForbiddenChar(namefilm);
			DeleteFile("Data/Image/"+namefilm+".jpg");DeleteFile("Data/Plot/"+namefilm+".dat");
			DeleteFile("Data/Seasons/"+namefilm+".dat");
            for(int k=0;k<elect->Count;k++)
			   if(ListBox1->Items->Strings[ListBox1->ItemIndex]==elect->Strings[k])
                  {elect->Delete(k);break;}
            AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
            TStringList *current=new TStringList();
			for(int i=0;i<namegroups->Count;i++)
              {current->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
               if(current->IndexOf(name)>=0)
                 {current->Delete(current->IndexOf(name));current->SaveToFile("Data/Groups/"+namegroups->Strings[i]+".dat");}
              }
            delete current;current=NULL;
          }
	   seasonfilm="0";
	   if(currentgroup!="MainGroup")
	   {
		ListBox1->Items->LoadFromFile("Data/Groups/"+currentgroup+".dat");
		listcurrentgroup->Assign(ListBox1->Items);
       }
	   Callsort();
	   s=true;
	   UpdateAlphabetPanel(namefilm);
	   if(index!=0)ListBox1->ItemIndex=index-1;
	   Label18->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
	   MDelete->Tag=1;//Чтобы не было контуров от компонентов (в Image10Click(Sender) не выполнялся код InfoOnFirstPage(true) после перехода с 2-1ст.)
	   Image10Click(Sender);InfoOnFirstPage(false);
	   MDelete->Tag=0;
	   Image1->Picture->Assign(NULL);Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MEditClick(TObject *Sender)
{
  close_access=false;
  int q;
  AnsiString firstname;
  Form2->ComboBox3->ItemIndex=Form2->ComboBox1->ItemIndex;
  for(int i=0;i<list->Count;i++)
     if(ListBox1->Items->Strings[ListBox1->ItemIndex]==list->Strings[i])
	  {
		q=i;
		Form2->Label12->Caption=lang->Strings[85];Form2->Caption=lang->Strings[87];
		for(int e=0;e<Form2->CheckListBox1->Count;e++)
		  {if(genre->Strings[i].Pos(Form2->CheckListBox1->Items->Strings[e]))
			   Form2->CheckListBox1->Checked[e]=true;
          else
			   Form2->CheckListBox1->Checked[e]=false;}
		for(int e=0;e<Form2->CheckListBox2->Count;e++)
          {if(country->Strings[i].Pos(Form2->CheckListBox2->Items->Strings[e]))
               Form2->CheckListBox2->Checked[e]=true;
          else
			   Form2->CheckListBox2->Checked[e]=false;}

		if(Form2->ComboBox2->Items->IndexOf(duration->Strings[i]+min)>=0)
		   Form2->ComboBox2->ItemIndex=Form2->ComboBox2->Items->IndexOf(duration->Strings[i]+min);
		else
		   Form2->ComboBox2->Text=duration->Strings[i]+min;
		Form2->Edit1->Text=list->Strings[i];
		Form2->Edit2->Text=link->Strings[i];Form2->Edit3->Text=trailer->Strings[i];
		Form2->Edit5->Text=director->Strings[i];Form2->Edit6->Text=tagline->Strings[i];
        Form2->Edit7->Text=originalname->Strings[i];
        Form2->Image1->Picture=Form1->Image1->Picture;
        Form2->Memo1->Text=Form1->Memo1->Text;Form2->Memo2->Text=cast->Strings[i];
        Form2->SetOpenMode("openedit");Form2->FillList(list);
		wchar_t *b=list->Strings[i].c_str();firstname=b;
		AccessToForbiddenChar(firstname);
        if(type->Strings[i]=="Movie")
		   {Form2->RadioButton1->Checked=true;
			Form2->seasons->Clear();Form2->seasons->Add("1");//Сезонов:1, серий:1
			Form2->Edit4->Text="1";Form2->Edit8->Text="1";
			Form2->ComboBox1->ItemIndex=Form2->ComboBox1->Items->IndexOf(year->Strings[i]);
		   }
		if(type->Strings[i]=="TV series")
		   {Form2->RadioButton2->Checked=true;Form2->Edit4->Text=seasonfilm;Form2->Edit8->Text=seriesfilm;
			Form2->seasons->LoadFromFile("Data/Seasons/"+firstname+".dat");
			AnsiString from,till;
			DivisionYear(year->Strings[i],from,till);
			Form2->ComboBox1->ItemIndex=Form2->ComboBox1->Items->IndexOf(from);
			Form2->ComboBox3->ItemIndex=Form2->ComboBox3->Items->IndexOf(till);
           }
        if(view->Strings[i]==yes)
           Form2->CheckBox1->Checked=true;
        if(view->Strings[i]==not)
           Form2->CheckBox1->Checked=false;
        if(release->Strings[i]==yes)
           Form2->CheckBox2->Checked=true;
        if(release->Strings[i]==not)
		   Form2->CheckBox2->Checked=false;
		ShowStars(Form2,rating,i);Form2->Rating->Caption=rating->Strings[i];
	  }
  //Вычисление групп фильма----------
   AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
   listgroupsmovie->Clear();
   TStringList *current=new TStringList();
   for(int i=0;i<namegroups->Count;i++)
	 {current->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
	  if(current->IndexOf(name)>=0)
		listgroupsmovie->Add(namegroups->Strings[i]);
	 }
   Form2->CheckListBox3->Items->Assign(namegroups);
   int index;
   if(listgroupsmovie->Count!=0)
	for(int i=0;i<listgroupsmovie->Count;i++)
	 {index=Form2->CheckListBox3->Items->IndexOf(listgroupsmovie->Strings[i]);
	  Form2->CheckListBox3->Checked[index]=true;
	 }
  //--------------Избранные----------
   bool PrevFavourite;
   if(elect->IndexOf(name)>=0){Form2->SetFavourite(true);PrevFavourite=true;}
   else {Form2->SetFavourite(false);PrevFavourite=false;}
  //---------------------------------
   Form2->Position=poScreenCenter;
   Form2->ShowModal();
   if(Form2->Tag==0)
	 {close_access=true;return;}
   if(Form2->Tag==1)
    {
	for(int i=0;i<elect->Count;i++)
      if(list->Strings[q]==elect->Strings[i])
		{elect->Strings[i]=Form2->Edit1->Text;break;}
	list->Strings[q]=Form2->Edit1->Text;Label1->Caption=list->Strings[q];ListBox1->Items->Strings[ListBox1->ItemIndex]=list->Strings[q];
    genre->Strings[q]=QuantityElements(Form2->CheckListBox1);country->Strings[q]=QuantityElements(Form2->CheckListBox2);
    AnsiString number=SearchNumbers(Form2->ComboBox2->Text);
    duration->Strings[q]=number;
    link->Strings[q]=Form2->Edit2->Text;trailer->Strings[q]=Form2->Edit3->Text;
    director->Strings[q]=Form2->Edit5->Text;originalname->Strings[q]=Form2->Edit7->Text;
    cast->Strings[q]=Form2->Memo2->Text;
    if(Form2->Edit6->Text=="")tagline->Strings[q]="-";
    else tagline->Strings[q]=Form2->Edit6->Text;
	AnsiString namefilm=Form2->Edit1->Text;
    AccessToForbiddenChar(namefilm);
    RenameFile("Data/Image/"+firstname+".jpg","Data/Image/"+namefilm+".jpg");
	RenameFile("Data/Plot/"+firstname+".dat","Data/Plot/"+namefilm+".dat");
	Form2->Memo1->Lines->SaveToFile("Data/Plot/"+namefilm+".dat");
	Form2->Image1->Picture->SaveToFile("Data/Image/"+namefilm+".jpg");

	AnsiString years;
	if(Form2->RadioButton1->Checked==true)
	   {
		if(type->Strings[q]=="TV series")DeleteFile("Data/Seasons/"+firstname+".dat");
		TypeFilm=lang->Strings[78];
		year->Strings[q]=Form2->ComboBox1->Text;type->Strings[q]="Movie";season->Strings[q]="0";seasonfilm="0";episode->Strings[q]="0";
	   }
    else
	   {
		if(type->Strings[q]=="Movie")Form2->seasons->SaveToFile("Data/Seasons/"+namefilm+".dat");
		if(type->Strings[q]=="TV series")
		{
			RenameFile("Data/Seasons/"+firstname+".dat","Data/Seasons/"+namefilm+".dat");
			Form2->seasons->SaveToFile("Data/Seasons/"+namefilm+".dat");
		}
		TypeFilm=lang->Strings[79];
		years=Form2->ComboBox1->Text+"-"+Form2->ComboBox3->Text;year->Strings[q]=years;
		type->Strings[q]="TV series";season->Strings[q]=Form2->Edit4->Text+":"+Form2->Edit8->Text;
		if(episode->Strings[q]=="0")episode->Strings[q]="1:1";
		else
		  {
		   if(episode->Strings[q].c_str()[0]=='X')//Просмотрено(ожидается)                                     //*
			 {AnsiString string=episode->Strings[q];string=string.Delete(1,1);SeparationSeasonSeries(string);} //
		   else                                   //Нужно смотреть                                             //*
			 SeparationSeasonSeries(episode->Strings[q]);
		   if(StrToInt(seasonfilm)>StrToInt(Form2->Edit4->Text))seasonfilm=Form2->Edit4->Text;
		   if(StrToInt(seriesfilm)>Form2->seasons->Strings[StrToInt(seasonfilm)-1])seriesfilm=Form2->seasons->Strings[StrToInt(seasonfilm)-1];
		   if(episode->Strings[q].c_str()[0]=='X')episode->Strings[q]="X"+seasonfilm+":"+seriesfilm;           //*
		   else episode->Strings[q]=seasonfilm+":"+seriesfilm;
		  }
	   }
	if(Form2->CheckBox1->Checked==true)
       view->Strings[q]=yes;
    else
       view->Strings[q]=not;

    if(Form2->CheckBox2->Checked==true)
       release->Strings[q]=yes;
    else
	   release->Strings[q]=not;

	rating->Strings[q]=Form2->Rating->Caption;

    for(int i=0;i<Form2->CheckListBox1->Count;i++)
       if(Form2->CheckListBox1->Checked[i])
		  Form2->CheckListBox1->Checked[i]=false;

//Лог------------------------------
	Logs("Edited",list->Strings[q],TypeFilm,year->Strings[q],country->Strings[q],genre->Strings[q]);
//Добавление/удаление групп фильма
	current->Clear();
	for(int i=0;i<Form2->CheckListBox3->Count;i++)
	  {
	  if(Form2->CheckListBox3->Checked[i]==true)
		{
		 if(listgroupsmovie->IndexOf(Form2->CheckListBox3->Items->Strings[i])>=0)          //Если фильм есть в группе - переименовать
		  {
		   current->LoadFromFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		   current->Strings[current->IndexOf(name)]=Form2->Edit1->Text;
		   current->SaveToFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		  }
		 else                                                                              //Если фильма не было - добавить
		  {
		   current->LoadFromFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		   current->Add(Form2->Edit1->Text);
		   current->SaveToFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		   Logs("Added to group "+Form2->CheckListBox3->Items->Strings[i],Form2->Edit1->Text,TypeFilm,
				year->Strings[q],country->Strings[q],genre->Strings[q]);
		  }
		}
	  if(Form2->CheckListBox3->Checked[i]==false)
		{
		 if(listgroupsmovie->IndexOf(Form2->CheckListBox3->Items->Strings[i])>=0)         //Если фильм есть в группе - удалить
		  {
		   current->LoadFromFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		   current->Delete(current->IndexOf(name));
		   current->SaveToFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
		   Logs("Removed from group "+Form2->CheckListBox3->Items->Strings[i],name,TypeFilm,
				year->Strings[q],country->Strings[q],genre->Strings[q]);
		  }
		 else;                                                                            //Если фильма не было - ничего не делать
		}
	  }
	delete current;current=NULL;
//Добавление/удаление из избранных--------
	bool CurrentFavourite=Form2->GetFavourite();
	if(PrevFavourite!=CurrentFavourite) //произошли изменения
	{
		if(CurrentFavourite) //Добавить к избранным
		{
		  elect->Add(namefilm);
		  Logs("Added to Favorites",namefilm,TypeFilm,year->Strings[q],country->Strings[q],genre->Strings[q]);
		}
		if(!CurrentFavourite)//Удалить из избранных
		{
		  elect->Delete(elect->IndexOf(namefilm));
		  Logs("Removed from Favorites",namefilm,TypeFilm,year->Strings[q],country->Strings[q],genre->Strings[q]);
		}
	}
//----------------------------------------
	if(currentgroup!="MainGroup")
	{
		ListBox1->Items->LoadFromFile("Data/Groups/"+currentgroup+".dat");
		listcurrentgroup->Assign(ListBox1->Items);
		if(listcurrentgroup->IndexOf(Form2->Edit1->Text)>=0)                    //Фильм остался в группе после редактирования
		   ListBox1->ItemIndex=ListBox1->Items->IndexOf(Form2->Edit1->Text);
		else                                                                    //Фильм удалился из группе после редактирования
		  {ListBox1->Items->Add(Form2->Edit1->Text);ListBox1->ItemIndex=ListBox1->Count-1;}
	}
	ListBox1Click(Form1);//Обновление инфы на интерфейсе (выделенный элемент)
	Callsort();
	Quantity();
	ListBox1->ItemIndex=ListBox1->Items->IndexOf(list->Strings[q]);
	Label18->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
	s=true;
	UpdateAlphabetPanel(firstname);
	if(firstname.LowerCase().c_str()[0]!=namefilm.LowerCase().c_str()[0])
	   UpdateAlphabetPanel(namefilm);
	}
   Form2->Image1->Picture->Assign(NULL);
   close_access=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MSaveClick(TObject *Sender)
{
  if(s==true)
     {
       if(MessageDlg(save,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes)
		  {
		   SaveCatalog();
		   Form11->Tag=2;Form11->Caption=lang->Strings[211];Form11->Position=poScreenCenter;Form11->ShowModal();
		   genreb->Text=genre->Text;countryb->Text=country->Text;releaseb->Text=release->Text;viewb->Text=view->Text;
		   s=false;
		  }
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MRandomFilmClick(TObject *Sender)
{
  if(list->Count!=0)
  {
	int viewyes=0,viewnot=0,random;
	for(int i=0;i<list->Count;i++)
	 {if(view->Strings[i]==not)
	   viewnot++;
	 if(view->Strings[i]==yes)
	   viewyes++;}
	if(viewnot!=0)
	   {
		int *a=new int[viewnot];viewnot=0;
		for(int i=0;i<list->Count;i++)
		  if(view->Strings[i]==not)
		   {a[viewnot]=i;viewnot++;}
		random=a[rand()%viewnot];
		if(currentgroup!="MainGroup")
		  MainGroupClick(Sender);
		ListBox1->Clear();ListBox1->Items->Add(list->Strings[random]);Quantity();
		ListBox1->ItemIndex=0;ListBox1Click(Form1);
		delete []a;
	   }
	if(viewnot==0)
	  if(MessageDlg(lang->Strings[197],mtConfirmation,TMsgDlgButtons()<<mbYes<<mbCancel,0)==mrYes)
		{
		 int *a=new int[viewyes];viewyes=0;
		 for(int i=0;i<list->Count;i++)
		   if(view->Strings[i]==yes)
			 {a[viewyes]=i;viewyes++;}
		 random=a[rand()%viewyes];
		 if(currentgroup!="MainGroup")
		   MainGroupClick(Sender);
		 ListBox1->Clear();ListBox1->Items->Add(list->Strings[random]);Quantity();
		 ListBox1->ItemIndex=0;ListBox1Click(Form1);
		 delete []a;
		}
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MFilmsUnderMoodClick(TObject *Sender)
{
  FilmsUnderMood();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MAlphabetFilmClick(TObject *Sender)
{
  Form19->Position=poScreenCenter;
  if(Form19->ShowModal()==mrCancel)
	  return;
  if(currentgroup!="MainGroup")
	 MainGroupClick(Sender);
  AnsiString symbol=Form19->Char;
  AnsiString name,chars="абвгдеєжзиіїйклмнопрстуфхцчшщэюяabcdefghijklmnopqrstuvwxyz",letter;
  ListBox1->Clear();
  for(int i=0;i<list->Count;i++)
  {
	name=list->Strings[i];
	if(symbol=="#")
	  {
	  letter=list->Strings[i].LowerCase().c_str()[0];
	  if(!chars.Pos(letter))
	   ListBox1->Items->Add(list->Strings[i]);
	  }
	else
	 if(name.LowerCase().c_str()[0]==symbol.LowerCase().c_str()[0])
	  ListBox1->Items->Add(list->Strings[i]);
  }
  Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MSortClick(TObject *Sender)
{
 AnsiString name;
 if(MSort->Checked==false)
	{
	 if(ListBox1->ItemIndex!=-1)name=ListBox1->Items->Strings[ListBox1->ItemIndex];
	 ListBox1->Sorted=true;MSort->Checked=true;
	 if(ListBox1->ItemIndex!=-1){ListBox1->ItemIndex=ListBox1->Items->IndexOf(name);ListBox1Click(Sender);}
	 }
 else
	{ListBox1->Sorted=false;MSort->Checked=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MResetClick(TObject *Sender)
{
 int index;
 ListBox1->Items->Clear();
 if(currentgroup=="MainGroup")
  {
   if(RadioButton1->Checked==true)
    for(int i=0;i<list->Count;i++)
      if(type->Strings[i]=="Movie")
       ListBox1->Items->Add(list->Strings[i]);
   if(RadioButton2->Checked==true)
	for(int i=0;i<list->Count;i++)
      if(type->Strings[i]=="TV series")
       ListBox1->Items->Add(list->Strings[i]);
   if(RadioButton3->Checked==true)
    for(int i=0;i<list->Count;i++)
      if(type1->Strings[i]=="All")
       ListBox1->Items->Add(list->Strings[i]);
   if(RadioButton4->Checked==true)
    for(int i=0;i<elect->Count;i++)
       ListBox1->Items->Add(elect->Strings[i]);
  }
 if(currentgroup!="MainGroup")
 {
   if(RadioButton1->Checked==true)
    for(int i=0;i<listcurrentgroup->Count;i++)
     {index=list->IndexOf(listcurrentgroup->Strings[i]);
      if(type->Strings[index]=="Movie")
       ListBox1->Items->Add(list->Strings[index]);}
   if(RadioButton2->Checked==true)
    for(int i=0;i<listcurrentgroup->Count;i++)
     {index=list->IndexOf(listcurrentgroup->Strings[i]);
      if(type->Strings[index]=="TV series")
       ListBox1->Items->Add(list->Strings[index]);}
   if(RadioButton3->Checked==true)
    for(int i=0;i<listcurrentgroup->Count;i++)
     {index=list->IndexOf(listcurrentgroup->Strings[i]);
      if(type1->Strings[index]=="All")
       ListBox1->Items->Add(list->Strings[index]);}
   if(RadioButton4->Checked==true)
    for(int i=0;i<listcurrentgroup->Count;i++)
     {index=elect->IndexOf(listcurrentgroup->Strings[i]);
      if(index>=0)
       ListBox1->Items->Add(elect->Strings[index]);}
 }
 Reset();
 Quantity();
 VerifyEnteredData();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MQuitClick(TObject *Sender)
{
 Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo1Change(TObject *Sender)
{
 if(Memo1->Lines->Count<9)
   Memo1->ScrollBars=ssNone;
 else
   Memo1->ScrollBars=ssVertical;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Memo2Change(TObject *Sender)
{
   if(Memo2->Lines->Count<4)
      Memo2->ScrollBars=ssNone;
   else
      Memo2->ScrollBars=ssVertical;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BG1Click(TObject *Sender)
{
		Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 1.jpg");
		options->Strings[1]="1";BackgroundColor(clBlack);
		BG1->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BG2Click(TObject *Sender)
{
		Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 2.jpg");
		options->Strings[1]="2";BackgroundColor(clBlack);
		BG2->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BG3Click(TObject *Sender)
{
		Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 3.jpg");
		options->Strings[1]="3";BackgroundColor(clBlack);
		BG3->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BG4Click(TObject *Sender)
{
		Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 4.jpg");
		options->Strings[1]="4";BackgroundColor(clCream);
		BG4->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BG5Click(TObject *Sender)
{
		Image2->Picture->LoadFromFile("Soft/Backgrounds/Background 5.jpg");
		options->Strings[1]="5";BackgroundColor(clBlack);
		BG5->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Font1Click(TObject *Sender)
{
         Form1->Font->Name="Monotype Corsiva";Label1->Font->Name="Monotype Corsiva";
         Label9->Font->Name="Monotype Corsiva";Label21->Font->Name="Monotype Corsiva";
         options->Strings[3]="1";Font1->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Font2Click(TObject *Sender)
{
         Form1->Font->Name="Times New Roman";Label1->Font->Name="Times New Roman";
         Label9->Font->Name="Times New Roman";Label21->Font->Name="Times New Roman";
         options->Strings[3]="2";Font2->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Font3Click(TObject *Sender)
{
         Form1->Font->Name="Bookman Old Style";Label1->Font->Name="Bookman Old Style";
         Label9->Font->Name="Bookman Old Style";Label21->Font->Name="Bookman Old Style";
         options->Strings[3]="3";Font3->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Font4Click(TObject *Sender)
{
		 Form1->Font->Name="Garamond";Label1->Font->Name="Garamond";
		 Label9->Font->Name="Garamond";Label21->Font->Name="Garamond";
         options->Strings[3]="4";Font4->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Font5Click(TObject *Sender)
{
		 Form1->Font->Name="Century";Label1->Font->Name="Century";
		 Label9->Font->Name="Century";Label21->Font->Name="Century";
         options->Strings[3]="5";Font5->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UAClick(TObject *Sender)
{
		 TStringList *LastLang=new TStringList();LastLang->Text=lang->Text;
		 lang->LoadFromFile("Soft/Language/Language.ua");Language();
		 if(options->Strings[5]=="Russian")
			{Selectlang(LastLang,genre,country,view,release);
            options->Strings[7]=StringReplace(options->Strings[7],"каталог удален","каталог видалений",TReplaceFlags()<<rfReplaceAll);}
		 if(options->Strings[5]=="English")
			{Selectlang(LastLang,genre,country,view,release);
             options->Strings[7]=StringReplace(options->Strings[7],"catalog deleted","каталог видалений",TReplaceFlags()<<rfReplaceAll);}
		 options->Strings[5]="Ukrainian";UA->Checked=true;//Image10Click(Sender);
		 if(ListBox1->ItemIndex!=-1) ListBox1Click(Form1);
		 else
		   {if(Image10->Visible==false);//InfoOnFirstPage(false);               //Если не выбран фильм (не показывается инфа)
			else {Edit1->Text=genre->Strings[SelectedFilm];Edit3->Text=duration->Strings[SelectedFilm];Edit6->Text=country->Strings[SelectedFilm];
				  Label21->Caption=lang->Strings[134]+":"+tagline->Strings[SelectedFilm];
				  Label21->Hint=lang->Strings[134]+":"+tagline->Strings[SelectedFilm];
				  Label26->Caption=lang->Strings[80]+date->Strings[SelectedFilm]+" ";
				  ConvertTime(duration->Strings[SelectedFilm],Form1->Edit3);}
		   }
		 if(ListBox2->ItemIndex!=-1&&ListBox2->Visible==true) ListBox2Click(Form1);
		 if(Edit5->Text==LastLang->Strings[97]) Edit5->Text=lang->Strings[97];
		 if(Form13->Edit1->Text==LastLang->Strings[97]) Form13->Edit1->Text=lang->Strings[97];
		 if(Form13->Edit2->Text==LastLang->Strings[97]) Form13->Edit2->Text=lang->Strings[97];
		 if(Form17->Edit5->Text==LastLang->Strings[97]) Form17->Edit5->Text=lang->Strings[97];
		 VerifyEnteredData();
		 delete LastLang;LastLang=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RUClick(TObject *Sender)
{
		 TStringList *LastLang=new TStringList();LastLang->Text=lang->Text;
         lang->LoadFromFile("Soft/Language/Language.ru");Language();
         if(options->Strings[5]=="Ukrainian")
			{Selectlang(LastLang,genre,country,view,release);
            options->Strings[7]=StringReplace(options->Strings[7],"каталог видалений","каталог удален",TReplaceFlags()<<rfReplaceAll);}
         if(options->Strings[5]=="English")
            {Selectlang(LastLang,genre,country,view,release);
            options->Strings[7]=StringReplace(options->Strings[7],"catalog deleted","каталог удален",TReplaceFlags()<<rfReplaceAll);}
		 options->Strings[5]="Russian";RU->Checked=true;//Image10Click(Sender);
		 if(ListBox1->ItemIndex!=-1) ListBox1Click(Form1);
		 else
		   {if(Image10->Visible==false);//InfoOnFirstPage(false);               //Если не выбран фильм (не показывается инфа)
			else {Edit1->Text=genre->Strings[SelectedFilm];Edit3->Text=duration->Strings[SelectedFilm];Edit6->Text=country->Strings[SelectedFilm];
				  Label21->Caption=lang->Strings[134]+":"+tagline->Strings[SelectedFilm];
				  Label21->Hint=lang->Strings[134]+":"+tagline->Strings[SelectedFilm];
				  Label26->Caption=lang->Strings[80]+date->Strings[SelectedFilm]+" ";
				  ConvertTime(duration->Strings[SelectedFilm],Form1->Edit3);}
		   }
		 if(ListBox2->ItemIndex!=-1&&ListBox2->Visible==true) ListBox2Click(Form1);
		 if(Edit5->Text==LastLang->Strings[97]) Edit5->Text=lang->Strings[97];
		 if(Form13->Edit1->Text==LastLang->Strings[97]) Form13->Edit1->Text=lang->Strings[97];
		 if(Form13->Edit2->Text==LastLang->Strings[97]) Form13->Edit2->Text=lang->Strings[97];
		 if(Form17->Edit5->Text==LastLang->Strings[97]) Form17->Edit5->Text=lang->Strings[97];
		 VerifyEnteredData();
		 delete LastLang;LastLang=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EnglishClick(TObject *Sender)
{
		TStringList *LastLang=new TStringList();LastLang->Text=lang->Text;
        lang->LoadFromFile("Soft/Language/Language.en");Language();
        if(options->Strings[5]=="Ukrainian")
            {Selectlang(LastLang,genre,country,view,release);
            options->Strings[7]=StringReplace(options->Strings[7],"каталог видалений","catalog deleted",TReplaceFlags()<<rfReplaceAll);}
         if(options->Strings[5]=="Russian")
            {Selectlang(LastLang,genre,country,view,release);
            options->Strings[7]=StringReplace(options->Strings[7],"каталог удален","catalog deleted",TReplaceFlags()<<rfReplaceAll);}
		 options->Strings[5]="English";English->Checked=true;//Image10Click(Sender);
         if(ListBox1->ItemIndex!=-1) ListBox1Click(Form1);
         else
		   {if(Image10->Visible==false);//InfoOnFirstPage(false);               //Если не выбран фильм (не показывается инфа)
			else {Edit1->Text=genre->Strings[SelectedFilm];Edit3->Text=duration->Strings[SelectedFilm];Edit6->Text=country->Strings[SelectedFilm];
				  Label21->Caption=lang->Strings[134]+":"+tagline->Strings[SelectedFilm];
				  Label21->Hint=lang->Strings[134]+":"+tagline->Strings[SelectedFilm];
				  Label26->Caption=lang->Strings[80]+date->Strings[SelectedFilm]+" ";
				  ConvertTime(duration->Strings[SelectedFilm],Form1->Edit3);}
		   }
         if(ListBox2->ItemIndex!=-1&&ListBox2->Visible==true) ListBox2Click(Form1);
		 if(Edit5->Text==LastLang->Strings[97]) Edit5->Text=lang->Strings[97];
		 if(Form13->Edit1->Text==LastLang->Strings[97]) Form13->Edit1->Text=lang->Strings[97];
		 if(Form13->Edit2->Text==LastLang->Strings[97]) Form13->Edit2->Text=lang->Strings[97];
		 if(Form17->Edit5->Text==LastLang->Strings[97]) Form17->Edit5->Text=lang->Strings[97];
		 VerifyEnteredData();
		 delete LastLang;LastLang=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MTurnOnClick(TObject *Sender)
{
   MTurnOn->Checked=true;options->Strings[9]="TurnOn";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MTurnOffClick(TObject *Sender)
{
   MTurnOff->Checked=true;options->Strings[9]="TurnOff";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MWebSiteClick(TObject *Sender)
{
	 Form4->Position=poScreenCenter;Form4->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MAboutClick(TObject *Sender)
{
	 Timer3->Enabled=false;Timer4->Enabled=false;
	 AboutBox->Position=poScreenCenter;AboutBox->ShowModal();
	 if(AboutBox->Tag==0)
		Image14->Visible=false;
	 if(AboutBox->Tag==2)
		{Timer3->Enabled=true;Timer4->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Change(TObject *Sender)
{
 TStringList *name=new TStringList();
 Callsort();
 if(Edit5->Text=="")
    {Image6->Visible=false;Quantity();}
 if(Edit5->Text!=""&&Edit5->Text!=lang->Strings[97])
   {Image6->Visible=true;
    for(int i=0;i<ListBox1->Items->Count;i++)
      if(ListBox1->Items->Strings[i].LowerCase().Pos(Edit5->Text.LowerCase())>0)
        name->Add(ListBox1->Items->Strings[i]);
    ListBox1->Items->Assign(name);
    Quantity();if(ListBox1->Items->Count>0)ListBox1->ItemIndex=0;}
  delete name;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Enter(TObject *Sender)
{
   if(Edit5->Text==lang->Strings[97])
     Edit5->Text="";
   Edit5->Font->Color=clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5Exit(TObject *Sender)
{
   if(Edit5->Text=="")
	{Edit5->Text=lang->Strings[97];Edit5->Font->Color=clBtnShadow;Image6->Visible=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit5KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
         if (Key == VK_RETURN && Edit5->Text!="")
            ListBox1Click(Form1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image5Click(TObject *Sender)
{
  AnsiString _url= Edit4->Text;
  if(Edit4->Text!="")
     ShellExecute (Handle, "open", _url.c_str(), NULL, NULL, SW_SHOW );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image4Click(TObject *Sender)
{
  AnsiString a = watchtrailer,c;
  bool b=false;
  for (int i=0; i<a.Length();i++)
  {
        if ((b==true)&&(a.c_str()[i]!='"'))
          {
            c=c+a.c_str()[i];
          }
        if (a.c_str()[i]=='"')
          {
             if (b==true)
                   b=false;
             else
                if (a.c_str()[i+1]=='h')
                   b=true;
          }
  }
  TStringList *trailerlink  = new TStringList();trailerlink->Add(c);trailerlink->SaveToFile("Soft/Link.dat");
  delete trailerlink;trailerlink=NULL;
  ShellExecute(0,"open","Soft\\Additional screen.exe",NULL,NULL,SW_NORMAL);
  Form1->Enabled=false;Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)//Для блокировки экрана во время просмотра трейлера
{
  if(FileExists("Soft/Link.dat")==false)
    {Form1->Enabled=true;Timer1->Enabled=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MHelpNoteClick(TObject *Sender)
{
 ShellExecute(0,"open","µMovies.chm",NULL,NULL,SW_NORMAL);
}
//---------------------------------------------------------------------------

void FastFilter(TComboBox *indexcomb,int number,AnsiString word,TStringList *ts)
{
  AnsiString from,till;
  int index;
  if(currentgroup=="MainGroup")
   if(list->Count!=0)
	  {
		//Form1->RadioButton3->Checked=true;Reset();
		Form1->Label13Click(Form1);Reset();
		Form1->ListBox1->Clear();
		for(int i=0;i<list->Count;i++)
		  {
		   if(ts==year)
			{if(type->Strings[i]=="Movie")
			   if(ts->Strings[i]==word)Form1->ListBox1->Items->Add(list->Strings[i]);
             if(type->Strings[i]=="TV series")
			   {DivisionYear(year->Strings[i],from,till);
				if(from==word||till==word)Form1->ListBox1->Items->Add(list->Strings[i]);}
            }
		   if(ts!=year)
			 if(ts->Strings[i]==word)
			   Form1->ListBox1->Items->Add(list->Strings[i]);
          }
		indexcomb->ItemIndex=number;
	  }
  if(currentgroup!="MainGroup")
   if(listcurrentgroup->Count!=0&&list->Count!=0)
	  {
		//Form1->RadioButton3->Checked=true;Reset();
		Form1->Label13Click(Form1);Reset();
		Form1->ListBox1->Clear();
        for(int i=0;i<listcurrentgroup->Count;i++)
		  {index=list->IndexOf(listcurrentgroup->Strings[i]);
		   if(ts==year)
            {if(type->Strings[index]=="Movie")
			   if(ts->Strings[index]==word)Form1->ListBox1->Items->Add(list->Strings[index]);
			 if(type->Strings[index]=="TV series")
			   {DivisionYear(year->Strings[index],from,till);
				if(from==word||till==word)Form1->ListBox1->Items->Add(list->Strings[index]);}
            }
           if(ts!=year)
             if(ts->Strings[index]==word)
               Form1->ListBox1->Items->Add(list->Strings[index]);
		  }
		indexcomb->ItemIndex=number;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MQAllClick(TObject *Sender)
{
		//Category(RadioButton3,type1,"All");RadioButton3->Checked=true;
		Label13Click(Form1);Category(RadioButton3,type1,"All");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MQViewClick(TObject *Sender)
{
		FastFilter(Form1->ComboBox6,2,not,view);Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MQRlsClick(TObject *Sender)
{
		FastFilter(Form1->ComboBox5,1,yes,release);Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MQYearClick(TObject *Sender)
{
   sortmode->Strings[2]="1";ComboBox3->Visible=true;ComboBox7->Visible=false;CheckListBox3->Visible=false;
   ComboBox3->Width=145;ComboBox3->Items->Strings[0]=lang->Strings[8];
		FastFilter(Form1->ComboBox3,Form1->ComboBox3->Items->IndexOf(FormatDateTime("yyyy", Date())),
                   StrToInt(FormatDateTime("yyyy", Date())),year);
        Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MSerialExpectedClick(TObject *Sender)
{
  int index;
  if(currentgroup=="MainGroup")
   if(list->Count!=0)
	  {
		Form1->Label12Click(Form1);Reset();
		Form1->ListBox1->Clear();
		for(int i=0;i<list->Count;i++)
		  if(episode->Strings[i].c_str()[0]=='X')
			 ListBox1->Items->Add(list->Strings[i]);
	  }
  if(currentgroup!="MainGroup")
   if(listcurrentgroup->Count!=0&&list->Count!=0)
	  {
		Form1->Label12Click(Form1);Reset();
		Form1->ListBox1->Clear();
		for(int i=0;i<listcurrentgroup->Count;i++)
		  {
		   index=list->IndexOf(listcurrentgroup->Strings[i]);
		   if(episode->Strings[index].c_str()[0]=='X')
			 ListBox1->Items->Add(list->Strings[index]);
		  }
	  }
  Quantity();
}
//---------------------------------------------------------------------------

void GlobalSearch(TStringList *quantactive,TStringList *gsearchmode,int j)
{
  bool access=false,accessclb=false;
  for(int q=0;q<quantactive->Count;q++)
   {
	if(quantactive->Strings[q]=="1")
	  {if(list->Strings[j].LowerCase().Pos(Form7->Edit1->Text.LowerCase())>0) access=true;else {access=false;break;}}
	if(quantactive->Strings[q]=="2")
	{
	  if(gsearchmode->Strings[0]=="1")
		 {if(genre->Strings[j].LowerCase().Pos(Form7->ComboBox1->Text.LowerCase())) access=true;else {access=false;break;}}
	  if(gsearchmode->Strings[0]=="2")
		{ accessclb=true;
		  for(int z=0;z<Form7->CheckListBox1->Count;z++)
		   if(Form7->CheckListBox1->Checked[z])
			 {if(genre->Strings[j].Pos(Form7->CheckListBox1->Items->Strings[z])){access=true;accessclb=true;break;}
			  else accessclb=false;}
		  if(accessclb==false)
			{access=false;break;}
		}
	  if(gsearchmode->Strings[0]=="3")
		{
		  accessclb=true;
		  for(int z=0;z<Form7->CheckListBox1->Count;z++)
		   if(Form7->CheckListBox1->Checked[z])
			 {if(!genre->Strings[j].Pos(Form7->CheckListBox1->Items->Strings[z])){access=true;accessclb=true;}
			  else {accessclb=false;break;}}
		  if(accessclb==false)
			{access=false;break;}
		}
	 }
	if(quantactive->Strings[q]=="3")
	 {
	  if(gsearchmode->Strings[1]=="1")
		 {if(country->Strings[j].LowerCase().Pos(Form7->ComboBox2->Text.LowerCase())) access=true;else {access=false;break;}}
	  if(gsearchmode->Strings[1]=="2")
		{ accessclb=true;
		  for(int z=0;z<Form7->CheckListBox2->Count;z++)
		   if(Form7->CheckListBox2->Checked[z])
			 {if(country->Strings[j].Pos(Form7->CheckListBox2->Items->Strings[z])){access=true;accessclb=true;break;}
			  else accessclb=false;}
		  if(accessclb==false)
			{access=false;break;}
		}
	  if(gsearchmode->Strings[1]=="3")
		{
		  accessclb=true;
		  for(int z=0;z<Form7->CheckListBox2->Count;z++)
		   if(Form7->CheckListBox2->Checked[z])
			 {if(!country->Strings[j].Pos(Form7->CheckListBox2->Items->Strings[z])){access=true;accessclb=true;}
			  else {accessclb=false;break;}}
		  if(accessclb==false)
			{access=false;break;}
		}
	 }
	if(quantactive->Strings[q]=="4")
	 {
	  if(gsearchmode->Strings[2]=="1")
		 {
		  if(type->Strings[j]=="Movie")
			{if(year->Strings[j]==Form7->ComboBox3->Text) access=true;else {access=false;break;}}
		  if(type->Strings[j]=="TV series")
			{AnsiString from,till;DivisionYear(year->Strings[j],from,till);
			 if(StrToInt(Form7->ComboBox3->Text)>=StrToInt(from)&&StrToInt(Form7->ComboBox3->Text)<=StrToInt(till)) access=true;
			 else {access=false;break;}}
		 }
	  if(gsearchmode->Strings[2]=="2")
		 {
		  if(type->Strings[j]=="Movie")
			{ accessclb=true;
			  for(int z=0;z<Form7->CheckListBox3->Count;z++)
				if(Form7->CheckListBox3->Checked[z])
				  {if(year->Strings[j]==Form7->CheckListBox3->Items->Strings[z]){access=true;accessclb=true;break;}
				   else accessclb=false;}
			  if(accessclb==false)
				{access=false;break;}
			}
		  if(type->Strings[j]=="TV series")
			{ accessclb=true;AnsiString from,till;DivisionYear(year->Strings[j],from,till);
			  for(int z=0;z<Form7->CheckListBox3->Count;z++)
				if(Form7->CheckListBox3->Checked[z])
				  {if(StrToInt(Form7->CheckListBox3->Items->Strings[z])>=StrToInt(from)&&StrToInt(Form7->CheckListBox3->Items->Strings[z])<=StrToInt(till))
					{access=true;accessclb=true;break;}
				  else accessclb=false;}
			  if(accessclb==false)
				{access=false;break;}
			}
		 }
	  if(gsearchmode->Strings[2]=="3")
		 {
		  if(type->Strings[j]=="Movie")
		   {
			if(!Form7->ComboBox3->Text.Pos('~')&&!Form7->ComboBox7->Text.Pos('~'))
				 {if(StrToInt(year->Strings[j])>=StrToInt(Form7->ComboBox3->Text)&&
					 StrToInt(year->Strings[j])<=StrToInt(Form7->ComboBox7->Text))  access=true;else {access=false;break;}}
			if(!Form7->ComboBox3->Text.Pos('~')&&Form7->ComboBox7->Text.Pos('~'))
				 {if(StrToInt(year->Strings[j])>=StrToInt(Form7->ComboBox3->Text)) access=true;else {access=false;break;}}
			if(Form7->ComboBox3->Text.Pos('~')&&!Form7->ComboBox7->Text.Pos('~'))
				 {if(StrToInt(year->Strings[j])<=StrToInt(Form7->ComboBox7->Text)) access=true;else {access=false;break;}}
		   }
		  if(type->Strings[j]=="TV series")
		   {AnsiString from,till;DivisionYear(year->Strings[j],from,till);
			if(!Form7->ComboBox3->Text.Pos('~')&&!Form7->ComboBox7->Text.Pos('~'))
			  {if(StrToInt(till)>=StrToInt(Form7->ComboBox3->Text)&&
				  StrToInt(from)<=StrToInt(Form7->ComboBox7->Text))  access=true;else {access=false;break;}}
			if(!Form7->ComboBox3->Text.Pos('~')&&Form7->ComboBox7->Text.Pos('~'))
				 {if(StrToInt(till)>=StrToInt(Form7->ComboBox3->Text)) access=true;else {access=false;break;}}
			if(Form7->ComboBox3->Text.Pos('~')&&!Form7->ComboBox7->Text.Pos('~'))
				 {if(StrToInt(from)<=StrToInt(Form7->ComboBox7->Text)) access=true;else {access=false;break;}}
		   }
		 }
	 }
	if(quantactive->Strings[q]=="5")
	 {
	  if(gsearchmode->Strings[3]=="1")
		{AnsiString number=SearchNumbers(Form7->ComboBox4->Text);
		 if(number==""||number=="0")number="1";
		 if(StrToInt(duration->Strings[j])>=StrToInt(number)-5 && StrToInt(duration->Strings[j])<=StrToInt(number)+5) access=true;
		 else {access=false;break;}}
	  if(gsearchmode->Strings[3]=="2")
		{
		 accessclb=true;
		 for(int z=0;z<duration_activated->Count;z++)
		   {if(StrToInt(duration->Strings[j])>=StrToInt(duration_activated->Strings[z])-5 &&
			  StrToInt(duration->Strings[j])<=StrToInt(duration_activated->Strings[z])+5)
			  {access=true;accessclb=true;break;}
			else accessclb=false;}
		 if(accessclb==false)
		   {access=false;break;}
		}
	  if(gsearchmode->Strings[3]=="3")
		{
		 if(!Form7->ComboBox4->Text.Pos('~')&&!Form7->ComboBox8->Text.Pos('~'))
		   {AnsiString numberfrom=SearchNumbers(Form7->ComboBox4->Text),numbertill=SearchNumbers(Form7->ComboBox8->Text);
			if(StrToInt(duration->Strings[j])>=StrToInt(numberfrom)&&
			   StrToInt(duration->Strings[j])<=StrToInt(numbertill))  access=true;else {access=false;break;}}
		 if(!Form7->ComboBox4->Text.Pos('~')&&Form7->ComboBox8->Text.Pos('~'))
			  {AnsiString number=SearchNumbers(Form7->ComboBox4->Text);
			   if(StrToInt(duration->Strings[j])>=StrToInt(number)) access=true;else {access=false;break;}}
		 if(Form7->ComboBox4->Text.Pos('~')&&!Form7->ComboBox8->Text.Pos('~'))
			  {AnsiString number=SearchNumbers(Form7->ComboBox8->Text);
			   if(StrToInt(duration->Strings[j])<=StrToInt(number)) access=true;else {access=false;break;}}
		}
	 }
	if(quantactive->Strings[q]=="6")
	  {if(release->Strings[j].LowerCase()==Form7->ComboBox5->Text.LowerCase()) access=true;else {access=false;break;}}
    if(quantactive->Strings[q]=="7")
      {if(view->Strings[j].LowerCase()==Form7->ComboBox6->Text.LowerCase()) access=true;else {access=false;break;}}
    if(quantactive->Strings[q]=="8")
      {if(originalname->Strings[j].LowerCase().Pos(Form7->Edit2->Text.LowerCase())>0) access=true;else {access=false;break;}}
	if(quantactive->Strings[q]=="9")
      {if(director->Strings[j].LowerCase().Pos(Form7->Edit3->Text.LowerCase())>0) access=true;else {access=false;break;}}
    if(quantactive->Strings[q]=="10")
      {if(cast->Strings[j].LowerCase().Pos(Form7->Edit4->Text.LowerCase())>0) access=true;else {access=false;break;}}
    if(quantactive->Strings[q]=="11")
	  {if(tagline->Strings[j].LowerCase().Pos(Form7->Edit5->Text.LowerCase())>0) access=true;else {access=false;break;}}
    if(quantactive->Strings[q]=="12")
	  {if(season->Strings[j]!="0")
		{SeparationSeasonSeries(season->Strings[j]);
		 if(seasonfilm==Form7->Edit6->Text) access=true;else {access=false;break;}}
	   if(season->Strings[j]=="0"){access=false;break;}
	  }
	if(quantactive->Strings[q]=="13")
	  {if(season->Strings[j]!="0")
		{SeparationSeasonSeries(season->Strings[j]);
		 if(seriesfilm==Form7->Edit7->Text) access=true;else {access=false;break;}}
	   if(season->Strings[j]=="0"){access=false;break;}
	  }
	if(quantactive->Strings[q]=="14")
	  {if(rating->Strings[j]==Form7->Rating->Caption) access=true;else {access=false;break;}}
	if(quantactive->Strings[q]=="15")
	{
		if(Form7->Image4->Tag==1 && Form7->Image5->Tag==1)
			{if(StrToDate(date->Strings[j])>=Form7->DateTimePicker1->Date &&
				StrToDate(date->Strings[j])<=Form7->DateTimePicker2->Date) access=true;else {access=false;break;}}
		if(Form7->Image4->Tag==1 && Form7->Image5->Tag==0)
			{if(StrToDate(date->Strings[j])>=Form7->DateTimePicker1->Date) access=true;else {access=false;break;}}
		if(Form7->Image4->Tag==0 && Form7->Image5->Tag==1)
			{if(StrToDate(date->Strings[j])<=Form7->DateTimePicker2->Date) access=true;else {access=false;break;}}
	}
   }
  if(access==true)
	{Form1->ListBox1->Items->Add(list->Strings[j]);search++;}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MSearchClick(TObject *Sender)
{
  Form7->Position=poScreenCenter;
  if (Form7->ShowModal()==mrCancel)
	return;
  MSearch->Tag=1;//Чтобы не было контуров от компонентов (в Image10Click(Sender) не выполнялся код InfoOnFirstPage(true) после перехода со 2 на 1 ст.)
  search=0;int index;
  TStringList *quantactive=new TStringList();bool access;
  TStringList *gsearchmode=new TStringList();gsearchmode->Text=Form7->GetSearchMode();
  if(Form7->CheckBox1->Checked==true&&Form7->Edit1->Text!="")quantactive->Add("1");
  if(gsearchmode->Strings[0]=="1")if(Form7->CheckBox2->Checked==true&&Form7->ComboBox1->Text!="")quantactive->Add("2");
  if(gsearchmode->Strings[0]=="2")if(Form7->CheckBox2->Checked==true)QuantityChecked(Form7->CheckListBox1,quantactive,"2");
  if(gsearchmode->Strings[0]=="3")if(Form7->CheckBox2->Checked==true)QuantityChecked(Form7->CheckListBox1,quantactive,"2");
  if(gsearchmode->Strings[1]=="1")if(Form7->CheckBox3->Checked==true&&Form7->ComboBox2->Text!="")quantactive->Add("3");
  if(gsearchmode->Strings[1]=="2")if(Form7->CheckBox3->Checked==true)QuantityChecked(Form7->CheckListBox2,quantactive,"3");
  if(gsearchmode->Strings[1]=="3")if(Form7->CheckBox3->Checked==true)QuantityChecked(Form7->CheckListBox2,quantactive,"3");
  if(gsearchmode->Strings[2]=="1")if(Form7->CheckBox4->Checked==true&&Form7->ComboBox3->Text!="")quantactive->Add("4");
  if(gsearchmode->Strings[2]=="2")if(Form7->CheckBox4->Checked==true)QuantityChecked(Form7->CheckListBox3,quantactive,"4");
  if(gsearchmode->Strings[2]=="3")if(Form7->CheckBox4->Checked==true&&Form7->ComboBox3->Text!=""&&Form7->ComboBox7->Text!="")
	 if(!Form7->ComboBox3->Text.Pos('~')||!Form7->ComboBox7->Text.Pos('~'))quantactive->Add("4");
  if(gsearchmode->Strings[3]=="1")if(Form7->CheckBox5->Checked==true&&Form7->ComboBox4->Text!="")quantactive->Add("5");
  if(gsearchmode->Strings[3]=="2")if(Form7->CheckBox5->Checked==true)
  {
	 bool k=false;
	 duration_activated->Clear();
	 for(int i=0;i<Form7->CheckListBox4->Count;i++)
	   if(Form7->CheckListBox4->Checked[i])
		{k=true;duration_activated->Add(Form7->CheckListBox4->Items->Strings[i]);
		 duration_activated->Strings[duration_activated->Count-1]=SearchNumbers(duration_activated->Strings[duration_activated->Count-1]);}
	 if(k==true)
		quantactive->Add("5");
  }
  if(gsearchmode->Strings[3]=="3")if(Form7->CheckBox5->Checked==true&&Form7->ComboBox4->Text!=""&&Form7->ComboBox8->Text!="")
	 if(!Form7->ComboBox4->Text.Pos('~')||!Form7->ComboBox8->Text.Pos('~'))quantactive->Add("5");
  for(int i=6;i<=13;i++)
   {if(i<=7)
	 if(((TCheckBox*)Form7->FindComponent("CheckBox"+IntToStr(i)))->Checked==true && ((TComboBox*)Form7->FindComponent("ComboBox"+IntToStr(i-1)))->Text!="")
	  quantactive->Add(i);
	if(i>=8)
	 if(Form7->RadioButton2->Checked==false||(Form7->RadioButton2->Checked==true&&i!=12&&i!=13))
	   if(((TCheckBox*)Form7->FindComponent("CheckBox"+IntToStr(i)))->Checked==true && ((TEdit*)Form7->FindComponent("Edit"+IntToStr(i-6)))->Text!="")
		 quantactive->Add(i);
   }
  if(Form7->CheckBox14->Checked==true) quantactive->Add(14);
  if(Form7->CheckBox15->Checked==true) quantactive->Add(15);

  if(quantactive->Count==0)
   {
	ListBox1->Clear();
	MSearch->Tag=0;
	if(Form7->RadioButton1->Checked==true)
	  {Label13Click(Form1);RadioButton3Click(Form1);return;}
	if(Form7->RadioButton2->Checked==true)
	  {Label11Click(Form1);RadioButton1Click(Form1);return;}
	if(Form7->RadioButton3->Checked==true)
	  {Label12Click(Form1);RadioButton2Click(Form1);return;}
	if(Form7->RadioButton4->Checked==true)
	  {Label16Click(Form1);RadioButton4Click(Form1);return;}
   }
   else
   {
	if(Form7->RadioButton1->Checked==true)
	  Label13Click(Form1);
	if(Form7->RadioButton2->Checked==true)
	  Label11Click(Form1);
	if(Form7->RadioButton3->Checked==true)
	  Label12Click(Form1);
	if(Form7->RadioButton4->Checked==true)
	  Label16Click(Form1);
	ListBox1->Clear();
   }

  if(currentgroup=="MainGroup")
	for(int j=0;j<list->Count;j++)
	 {
      if(Form7->RadioButton1->Checked==true)
			 GlobalSearch(quantactive,gsearchmode,j);
      if(Form7->RadioButton2->Checked==true)
        if(type->Strings[j]=="Movie")
			 GlobalSearch(quantactive,gsearchmode,j);
      if(Form7->RadioButton3->Checked==true)
        if(type->Strings[j]=="TV series")
			 GlobalSearch(quantactive,gsearchmode,j);
      if(Form7->RadioButton4->Checked==true)
        for(int k=0;k<elect->Count;k++)
          if(list->Strings[j]==elect->Strings[k])
			 GlobalSearch(quantactive,gsearchmode,j);
      }
  else
    for(int j=0;j<listcurrentgroup->Count;j++)
     {index=list->IndexOf(listcurrentgroup->Strings[j]);
      if(Form1->RadioButton3->Checked==true)
			 GlobalSearch(quantactive,gsearchmode,index);
      if(Form1->RadioButton1->Checked==true)
        if(type->Strings[index]=="Movie")
			 GlobalSearch(quantactive,gsearchmode,index);
      if(Form1->RadioButton2->Checked==true)
        if(type->Strings[index]=="TV series")
			 GlobalSearch(quantactive,gsearchmode,index);
      if(Form1->RadioButton4->Checked==true)
        for(int k=0;k<elect->Count;k++)
          if(list->Strings[index]==elect->Strings[k])
			 GlobalSearch(quantactive,gsearchmode,index);
     }
  if(search==0)
	 {ShowMessage(notfound);MResetClick(this);} //notfound-за заданим фільтром фільм не знайдено!
  Quantity();
  if(Image10->Visible==true){Image10Click(Sender);InfoOnFirstPage(false);}//if - Чтобы не мелькало контурами от компонентов
  Image1->Picture->Assign(NULL);Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
  Label17->Visible=false;Image8->Visible=false;
  MSearch->Tag=0;
  delete quantactive;quantactive=NULL;delete gsearchmode;gsearchmode=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image6Click(TObject *Sender)
{
 if(Edit5->Focused()) Edit5->Clear();
 else {Edit5->Text=lang->Strings[97];Edit5->Font->Color=clBtnShadow;}
 Image6->Visible=false;
 Callsort();Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MCatalogClick(TObject *Sender)
{
  close_access=false;
  Form8->SetPas_NameCatalog(options->Strings[7],options->Strings[8]);//options->Strings[7]=Имя открытого каталога,options->Strings[8]=пароль к каталогу
  Form8->SetAgreement(pasagreement);Form8->SetNameDeletedCatalog("");
  AnsiString selectcatalog=options->Strings[7];
  Form8->Label1->Caption=lang->Strings[106]+options->Strings[7];    //Открытый каталог:
  Form8->Label2->Caption=lang->Strings[263]+AnsiString(list->Count);//Количество фильмов:
  if(options->Strings[8]=="0")
     Form8->Image2->Picture->LoadFromFile("Soft/Buttons/Filter_Cancel.png");
  else
	 Form8->Image2->Picture->LoadFromFile("Soft/Buttons/Apply.png");
  Form8->Position=poScreenCenter;
  Form8->ShowModal();
  options->Strings[7]=Form8->GetNamecatalog();
  options->Strings[8]=Form8->GetPas();
  if(Form8->GetNameDeletedCatalog()!="")
      options->Strings[7]=Form8->GetNameDeletedCatalog();
  if(Form8->Tag==1)//OpenCatalog
    {
      AnsiString name=Form8->ListBox1->Items->Strings[0];
      TStringList *temp=new TStringList();temp->Assign(namegroups);
	  ExitMsgDlg=false;Close();
	  /*while(FileExists("Soft/Name.txt")==true)
	  {}*/
	  DeleteFile("Soft/Name.txt");
      for(int i=0;i<quantity;i++)
		DeleteFile("Data/Groups/"+temp->Strings[i]+".dat");
	  DeleteDir("Data/Image");DeleteDir("Data/Plot");DeleteDir("Data/Seasons");
	  delete temp;temp=NULL;
	  ZipForge1->FileName ="Catalogs\\"+name+".cof";
	  ZipForge1->OpenArchive(fmOpenRead);
      ZipForge1->BaseDir = "";
	  ZipForge1->ExtractFiles("*.*");
	  ZipForge1->CloseArchive();
	  FileCreate("Soft/WaitingForClosingProgram.dat"); //Для ожидания закрытия программы
	  ShellExecute(0,"open","µMovies.exe",NULL,NULL,SW_NORMAL);return;
	}
  if(Form8->Tag==2)//CreateCatalog
	{
	  TStringList *realoptions  = new TStringList();realoptions->Text=options->Text;
      AnsiString name=Form8->ListBox1->Items->Strings[0];
	  options->Strings[7]=name;options->Strings[8]="0";options->Strings[10]="[DateOfCreation]="+Now();
	  ExitMsgDlg=false;Close();//unsigned long i = 500;Sleep(i);
	  //Очистка лога и запись даты создания каталога
	  TStringList *logs  = new TStringList();logs->LoadFromFile("Data/Logs.txt");//бэкап лога открытого каталога
	  ListBox1->Clear();ListBox1->Items->SaveToFile("Data/Logs.txt");//очистка
	  ListBox1->Items->Add(logs->Strings[logs->Count-1]);ListBox1->Items->SaveToFile("Data/Logs.txt");//Запись даты создания каталога
	  //---
	  ZipForge1->FileName="Catalogs\\"+name+".cof";
	  ZipForge1->OpenArchive(fmCreate);
	  ZipForge1->AddFiles("\\Data\\*.*");
	  ZipForge1->CloseArchive();
	  //---возвращение лога и настроек открытого каталога
	  realoptions->SaveToFile("Data/Options.ini");
	  logs->SaveToFile("Data/Logs.txt");
	  delete realoptions,logs;realoptions=NULL;logs=NULL;
	  FileCreate("Soft/WaitingForClosingProgram.dat"); //Для ожидания закрытия программы
      ShellExecute(0,"open","µMovies.exe",NULL,NULL,SW_NORMAL);return;
    }
  pasagreement=Form8->GetAgreement();
  if(pasagreement==true)
	{ExitMsgDlg=false;Close();exit(0);}
  close_access=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PAddToDesiredClick(TObject *Sender)
{
  TStringList *savefilm  = new TStringList();
  AnsiString memoout,memoin,imageout,imagein,seasonout,seasonin;
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
  if(ListBox2->Items->IndexOf(name)>=0)
      ShowMessage(lang->Strings[117]); //"Этот фильм уже есть в вашей коллекции!"
  else
  {
  for(int i=0;i<list->Count;i++)
     if(ListBox1->Items->Strings[ListBox1->ItemIndex]==list->Strings[i])
	   if(MessageDlg(lang->Strings[116]+" "+'"'+list->Strings[i]+'"'+"?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes) //"Добавить в свою коллекцию фильм "
           {
            AccessToForbiddenChar(name);
            MkDir("Films from other catalogs/"+name);savefilm->Clear();
            savefilm->Add(list->Strings[i]);savefilm->Add(genre->Strings[i]);savefilm->Add(country->Strings[i]);savefilm->Add(year->Strings[i]);
            savefilm->Add(duration->Strings[i]);savefilm->Add(link->Strings[i]);savefilm->Add(trailer->Strings[i]);
            savefilm->Add(originalname->Strings[i]);savefilm->Add(tagline->Strings[i]);savefilm->Add(director->Strings[i]);
            savefilm->Add(cast->Strings[i]);savefilm->Add(season->Strings[i]);savefilm->Add(type->Strings[i]);
			savefilm->Add(type1->Strings[i]);savefilm->Add(view->Strings[i]);savefilm->Add(release->Strings[i]);
			savefilm->Add(rating->Strings[i]);savefilm->Add(episode->Strings[i]);
			savefilm->Add(options->Strings[5]);
			memoout="Data/Plot/"+name+".dat";memoin="Films from other catalogs/"+name+"/"+name+"_plot.dat";
			imageout="Data/Image/"+name+".jpg";imagein="Films from other catalogs/"+name+"/"+name+".jpg";
			CopyFile(imageout.c_str(),imagein.c_str(),true);CopyFile(memoout.c_str(),memoin.c_str(),true);
			if(type->Strings[i]=="TV series")
			{
			  seasonout="Data/Seasons/"+name+".dat";seasonin="Films from other catalogs/"+name+"/"+name+"_seasons.dat";
			  CopyFile(seasonout.c_str(),seasonin.c_str(),true);
			}
			savefilm->SaveToFile("Films from other catalogs/"+name+"/"+name+".dat");
            FilmsFromOtherCatalogs();break;
		   }
  }
  delete savefilm;savefilm=NULL;
}
//---------------------------------------------------------------------------

void VisibleFilmsFromOtherCatalogs(bool b)
{
  Form1->Label2->Visible=b;Form1->Label3->Visible=b;Form1->Label4->Visible=b;
  Form1->Label11->Visible=b;Form1->Label12->Visible=b;Form1->Label13->Visible=b;
  Form1->Label14->Visible=b;Form1->Label15->Visible=b;Form1->Label16->Visible=b;Form1->Label20->Visible=b;
  Form1->Pointer->Visible=b;
  for(int i=1;i<=7;i++)
	 ((TLabel*)Form1->FindComponent("Line"+IntToStr(i)))->Visible=b;
  if(sortmode->Strings[0]=="1")Form1->ComboBox1->Visible=b;
  if(sortmode->Strings[0]=="2")Form1->CheckListBox1->Visible=b;
  if(sortmode->Strings[1]=="1")Form1->ComboBox2->Visible=b;
  if(sortmode->Strings[1]=="2")Form1->CheckListBox2->Visible=b;
  if(sortmode->Strings[2]=="1")Form1->ComboBox3->Visible=b;
  if(sortmode->Strings[2]=="2")Form1->CheckListBox3->Visible=b;
  if(sortmode->Strings[2]=="3"){Form1->ComboBox3->Visible=b;Form1->ComboBox7->Visible=b;}
  if(sortmode->Strings[3]=="1")Form1->ComboBox4->Visible=b;
  if(sortmode->Strings[3]=="2")Form1->CheckListBox4->Visible=b;
  if(sortmode->Strings[3]=="3"){Form1->ComboBox4->Visible=b;Form1->ComboBox8->Visible=b;}
  Form1->ComboBox5->Visible=b;Form1->ComboBox6->Visible=b;
  Form1->MCatalogMenu->Enabled=b;Form1->MQFilter->Enabled=b;Form1->AllGroups->Enabled=b;
  Form1->ListBox1->Visible=b;
  Form1->Edit5->Visible=b;Form1->Image3->Visible=b;Form1->Image1->Picture->Assign(NULL);
  Form1->Image12->Visible=b;Form1->Image13->Visible=b;Form1->Image16->Visible=b;
  Form1->Panel1->Visible=b;Form1->Panel2->Visible=b;Form1->Panel3->Visible=b;Form1->CategoryPanelGroup1->Visible=b;
  InfoOnFirstPage(false); //if(Form1->Image10->Visible==true)
}
//---------------------------------------------------------------------------

void LangFilmsFromOtherCatalogs(TStringList *savefilm1,TStringList *temp1)
{
    TStringList *initiallang=new TStringList();
		  if(savefilm1->Strings[18]=="Russian")
			if(options->Strings[5]=="Ukrainian"||options->Strings[5]=="English")
			  {initiallang->LoadFromFile("Soft/Language/Language.ru");Selectlang(initiallang,temp1,temp1,temp1,temp1);}
		  if(savefilm1->Strings[18]=="Ukrainian")
			if(options->Strings[5]=="Russian"||options->Strings[5]=="English")
			  {initiallang->LoadFromFile("Soft/Language/Language.ua");Selectlang(initiallang,temp1,temp1,temp1,temp1);}
		  if(savefilm1->Strings[18]=="English")
            if(options->Strings[5]=="Ukrainian"||options->Strings[5]=="Russian")
              {initiallang->LoadFromFile("Soft/Language/Language.en");Selectlang(initiallang,temp1,temp1,temp1,temp1);}
    delete initiallang;initiallang=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MFilmsClick(TObject *Sender)
{
  MFilms->Tag=1;//Чтобы не мигали контуры при Image10Click
  Image10Click(Sender);VisibleFilmsFromOtherCatalogs(false);
  ListBox2->Visible=true;Image7->Visible=true;
  Image6->Visible=false;Image8->Visible=false;Label17->Visible=false;
  Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
  for (int i=1;i<=5;i++)
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->Visible=false;
  FilmsFromOtherCatalogs();
  Label17->Cursor=(TCursor)1;
  Label18->Caption=FloatToStr(ListBox2->ItemIndex+1)+'-'+FloatToStr(ListBox2->Count);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox2Click(TObject *Sender)
{
  MFilms->Tag=0;//разрешение отображения компонентов на 1 странице
  TStringList *savefilm  = new TStringList();TStringList *temp  = new TStringList();
  AnsiString selfilm;
  if(ListBox2->ItemIndex!=-1)
       {
        Image10->Visible=true;Image11->Visible=true;
        selfilm=ListBox2->Items->Strings[ListBox2->ItemIndex];
        AccessToForbiddenChar(selfilm);
        savefilm->LoadFromFile("Films from other catalogs/"+selfilm+"/"+selfilm+".dat");
        temp->Add(savefilm->Strings[1]);temp->Add(savefilm->Strings[2]);
        LangFilmsFromOtherCatalogs(savefilm,temp);
        savefilm->Strings[1]=temp->Strings[0];savefilm->Strings[2]=temp->Strings[1];
        Image1->Picture->LoadFromFile("Films from other catalogs/"+selfilm+"/"+selfilm+".jpg");
        Memo1->Lines->LoadFromFile("Films from other catalogs/"+selfilm+"/"+selfilm+"_plot.dat");
		Label1->Caption=ListBox2->Items->Strings[ListBox2->ItemIndex];
		Label21->Caption=lang->Strings[134]+":"+savefilm->Strings[8];
		Label21->Hint=lang->Strings[134]+":"+savefilm->Strings[8];
		//Label26->Caption=lang->Strings[18]+savefilm->Strings[18]+" ";
		Edit1->Text=savefilm->Strings[1];Edit1->Hint=savefilm->Strings[1];Edit6->Text=savefilm->Strings[2];Edit6->Hint=savefilm->Strings[2];
		Edit2->Text=savefilm->Strings[3];Edit4->Text=savefilm->Strings[5];seasonfilm=savefilm->Strings[11];watchtrailer=savefilm->Strings[6];
		Edit7->Text=savefilm->Strings[7];Edit7->Hint=savefilm->Strings[7];
		Edit8->Text=savefilm->Strings[9];Edit8->Hint=savefilm->Strings[9];
		Memo2->Lines->Clear();Memo2->Text=savefilm->Strings[10];
		ConvertTime(savefilm->Strings[4],Form1->Edit3);ShowStars(Form1,savefilm,16);
		if(Image10->Enabled==false)Image10Click(Sender);
		else Image11Click(Sender);
		if(savefilm->Strings[11]!="0")
		{
			Label17->Visible=true;Image8->Visible=true;SeparationSeasonSeries(savefilm->Strings[11]);
			Label17->Caption=seasonfilm;
			Label17->Hint=lang->Strings[131]+": "+seasonfilm+", "+lang->Strings[199]+" "+seriesfilm;
		}
		else
			{Label17->Visible=false;Image8->Visible=false;seasonfilm="0";}
		if(savefilm->Strings[12]=="Movie")TypeFilm=lang->Strings[78];
		else TypeFilm=lang->Strings[79];
      }
  Label18->Caption=FloatToStr(ListBox2->ItemIndex+1)+'-'+FloatToStr(ListBox2->Count);
  delete savefilm,temp;savefilm=NULL;temp=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image7Click(TObject *Sender)
{
  MFilms->Tag=1;//На случай, если выполнялся ListBox2Click(нажатие на фильм и его показ)
  Image10Click(Sender);VisibleFilmsFromOtherCatalogs(true);
  ListBox2->Visible=false;Image7->Visible=false;
  Label17->Visible=false;Image8->Visible=false;Image10->Visible=false;Image11->Visible=false;
  for (int j=1;j<=5;j++)
	 ((TImage*)FindComponent("Star"+IntToStr(j)))->Visible=false;
  if(Edit5->Text!=""&&Edit5->Text!=lang->Strings[97])Image6->Visible=true; //lang->Strings[97]="Поиск"
  else Image6->Visible=false;
  Label17->Cursor=(TCursor)2;
  MResetClick(this);
  MFilms->Tag=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PAddToMyCatalogClick(TObject *Sender)
{
  TStringList *savefilm  = new TStringList();TStringList *temp  = new TStringList();
  AnsiString name=ListBox2->Items->Strings[ListBox2->ItemIndex];
    if(list->IndexOf(name)>=0)
	  ShowMessage(lang->Strings[117]);
    else
      if(MessageDlg(lang->Strings[116]+" "+'"'+name+'"'+"?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
         {
          AccessToForbiddenChar(name);
		  savefilm->LoadFromFile("Films from other catalogs/"+name+"/"+name+".dat");temp->Add(savefilm->Strings[1]);temp->Add(savefilm->Strings[2]);
          temp->Add(savefilm->Strings[14]);temp->Add(savefilm->Strings[15]);
		  LangFilmsFromOtherCatalogs(savefilm,temp);
          savefilm->Strings[1]=temp->Strings[0];savefilm->Strings[2]=temp->Strings[1];
          savefilm->Strings[14]=temp->Strings[2];savefilm->Strings[15]=temp->Strings[3];
		  list->Add(savefilm->Strings[0]);genre->Add(savefilm->Strings[1]);country->Add(savefilm->Strings[2]);
          year->Add(savefilm->Strings[3]);duration->Add(savefilm->Strings[4]);link->Add(savefilm->Strings[5]);
		  trailer->Add(savefilm->Strings[6]);originalname->Add(savefilm->Strings[7]);tagline->Add(savefilm->Strings[8]);
          director->Add(savefilm->Strings[9]);cast->Add(savefilm->Strings[10]);
		  season->Add(savefilm->Strings[11]);type->Add(savefilm->Strings[12]);
		  type1->Add(savefilm->Strings[13]);view->Add(savefilm->Strings[14]);release->Add(savefilm->Strings[15]);
		  rating->Add(savefilm->Strings[16]);episode->Add(savefilm->Strings[17]);date->Add(Now().CurrentDate());
		  Memo1->Lines->SaveToFile("Data/Plot/"+name+".dat");
		  Image1->Picture->SaveToFile("Data/Image/"+name+".jpg");
		  if(savefilm->Strings[12]=="TV series")
		  {temp->LoadFromFile("Films from other catalogs/"+name+"/"+name+"_seasons.dat");temp->SaveToFile("Data/Seasons/"+name+".dat");}
		  Logs("Added",ListBox2->Items->Strings[ListBox2->ItemIndex],TypeFilm,savefilm->Strings[3],savefilm->Strings[2],savefilm->Strings[1]);
		  s=true;
         }
  delete savefilm,temp;savefilm=NULL;temp=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PDeleteFilmClick(TObject *Sender)
{
  AnsiString selfilm=ListBox2->Items->Strings[ListBox2->ItemIndex];
  AccessToForbiddenChar(selfilm);
  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
     {DeleteFile("Films from other catalogs/"+selfilm+"/"+selfilm+".dat");
	  DeleteFile("Films from other catalogs/"+selfilm+"/"+selfilm+"_plot.dat");
	  DeleteFile("Films from other catalogs/"+selfilm+"/"+selfilm+"_seasons.dat");
	  DeleteFile("Films from other catalogs/"+selfilm+"/"+selfilm+".jpg");
      RmDir("Films from other catalogs/"+selfilm);
      Image1->Picture->Assign(NULL);MFilmsClick(Form1);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PopupMenu1Popup(TObject *Sender)
{
   if(ListBox2->Count==0 || ListBox2->ItemIndex==-1)
	  {PAddToMyCatalog->Enabled=false;PDeleteFilm->Enabled=false;}
	else
	  {PAddToMyCatalog->Enabled=true;PDeleteFilm->Enabled=true;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image9Click(TObject *Sender)
{
  AnsiString wiki="https://ru.wikipedia.org/wiki/";
  wiki+=Label1->Caption;
  TStringList *wikilink  = new TStringList();wikilink->Add(wiki);wikilink->SaveToFile("Soft/Link.dat");
  delete wikilink;wikilink=NULL;
  ShellExecute(0,"open","Soft\\Additional screen.exe",NULL,NULL,SW_NORMAL);
  Form1->Enabled=false;Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image10Click(TObject *Sender)
{
   Image10->Enabled=false;Image11->Enabled=true;
   if(MSearch->Tag==0&&MFilms->Tag==0&&MainGroup->Tag==0&&MDelete->Tag==0)InfoOnFirstPage(true);//Если 1(после поиска/фильмов с других кат./Нажатия кнопки гл.группы/Удаления фильма) - не мигали контуры компонентов после перекл.с 2 на 1 страницу
   InfoOnSecondPage(false);
   Image10->Picture->LoadFromFile("Soft/Buttons/Arrow(left_inactive).png");
   Image11->Picture->LoadFromFile("Soft/Buttons/Arrow(right_active).png");
   if(seasonfilm!="0")
	 {Label17->Visible=true;Image8->Visible=true;Label17->Caption=seasonfilm;
	  Label17->Hint=lang->Strings[131]+": "+seasonfilm+", "+lang->Strings[199]+" "+seriesfilm;}
   else
	 {Label17->Visible=false;Image8->Visible=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11Click(TObject *Sender)
{
   Image10->Enabled=true;Image11->Enabled=false;InfoOnFirstPage(false);InfoOnSecondPage(true);Label1->Visible=true;
   Image10->Picture->LoadFromFile("Soft/Buttons/Arrow(left_active).png");
   Image11->Picture->LoadFromFile("Soft/Buttons/Arrow(right_inactive).png");
}
//---------------------------------------------------------------------------

  /*if (! ((TMenuItem *)Sender)->Checked)
                ((TMenuItem *)Sender)->Checked = true;*/

//----------------------------------------------------------GROUPS---------------------------------------------------------------------------------------

void __fastcall TForm1::MOpenGroupClick(TObject *Sender)
 {
     TMenuItem * item = dynamic_cast<TMenuItem*>(Sender);
	 currentgroup=groups[item->Tag]->Hint;Image12->Hint=lang->Strings[195]+" "+currentgroup;
	 FilmDel->Visible=true;
	 //MElect->Visible=false;MDelete->Visible=false;MEdit->Visible=false;PAddToDesired->Visible=false;
	 //MElect->Enabled=false;MDelete->Enabled=false;MEdit->Enabled=false;PAddToDesired->Enabled=false;
	 ListBox1->Items->LoadFromFile("Data/Groups/"+namegroups->Strings[item->Tag]+".dat");
	 listcurrentgroup->Assign(ListBox1->Items);
	 Label13Click(Form1);RadioButton3Click(Sender);
	 Reset();Quantity();
 }
void __fastcall TForm1::MRenameGroupClick(TObject *Sender)
 {
     TMenuItem * item = dynamic_cast<TMenuItem*>(Sender);
	 AnsiString firstname=namegroups->Strings[item->Tag],ForbiddenChars = "\\/*:<>«»|";
	 UnicodeString name;
	 if (InputQuery(lang->Strings[192],lang->Strings[191], name)==False)//lang->Strings[192]="Изменение названия группы"
	   return;                                                        //lang->Strings[191]="Введите название группы"
	 else
	   {
		for(int i=0;i<name.Length();i++)
		  if(ForbiddenChars.Pos(name.c_str()[i])||name.c_str()[i]=='"')
			{ShowMessage(lang->Strings[129]);return;}//lang->Strings[129]="Имя содержит недопустимые символы!"
		if(namegroups->IndexOf(name)>=0 || name=="MainGroup")
		 {ShowMessage(lang->Strings[193]);return;}//lang->Strings[193]="Группа с таким названием уже есть!"
		else
		 {
		  groups[item->Tag]->Caption=name;groups[item->Tag]->Hint=name;namegroups->Strings[item->Tag]=name;
		  if(currentgroup==firstname){currentgroup=name;Image12->Hint=lang->Strings[195]+" "+currentgroup;}
		  TStringList *temp=new TStringList();temp->LoadFromFile("Data/Groups/"+firstname+".dat");temp->SaveToFile("Data/Groups/"+name+".dat");
		  DeleteFile("Data/Groups/"+firstname+".dat");delete temp;temp=NULL;
		  s=true;
		  TDateTime CurrentDateTime=Now();logs->LoadFromFile("Data/Logs.temp");logs->Add("["+CurrentDateTime+"] (Renamed group): "+firstname+" -> "+name);
		  logs->SaveToFile("Data/Logs.temp");logs->Clear();
		  //Переименование шаблонных команд,которые включают действия с этой группой
		  AnsiString group;
		  for(int i=0;i<TemplateCommands->Count;i++)
		   if(TemplateCommands->Strings[i].Pos(firstname))
			{
			 group=CutTemplateCommand(TemplateCommands->Strings[i]);
			 TemplateCommands->Strings[i]=group+":"+name;
			}
		 }
	   }
 }
void __fastcall TForm1::MDeleteGroupClick(TObject *Sender)
 {
  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
   {
     TMenuItem * item = dynamic_cast<TMenuItem*>(Sender);AnsiString name=namegroups->Strings[item->Tag];
     namegroups->Delete(item->Tag);
     DeleteFile("Data/Groups/"+name+".dat");
     for(int i=0;i<quantity;i++)
        {delete groups[i],opengroup[i],renamegroup[i],deletegroup[i];groups[i]=NULL;opengroup[i]=NULL;renamegroup[i]=NULL;deletegroup[i]=NULL;}
     quantity--;
     for(int i=0;i<quantity;i++)
        CreateGroup(i,namegroups->Strings[i]);
	 MainGroupClick(this);
	 MDelete->Tag=1;//Чтобы не было контуров от компонентов (в Image10Click(Sender) не выполнялся код InfoOnFirstPage(true) после перехода с 2-1ст.)
	 Image10Click(Sender);InfoOnFirstPage(false);
	 MDelete->Tag=0;
	 Image1->Picture->Assign(NULL);Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
	 Label17->Visible=false;Image8->Visible=false;//Индикатор сериала
	 s=true;
	 TDateTime CurrentDateTime=Now();logs->LoadFromFile("Data/Logs.temp");logs->Add("["+CurrentDateTime+"] (Removed group): "+name);
	 logs->SaveToFile("Data/Logs.temp");logs->Clear();
	 //Очистка шаблонных команд,которые включают действия с этой группой
	 for(int i=0;i<TemplateCommands->Count;i++)
	  if(TemplateCommands->Strings[i].Pos(name))
		 TemplateCommands->Strings[i]="-";
	}
 }
//---------------------------------------------------------------------------

void __fastcall TForm1::MAddFilmToGroupClick(TObject *Sender)
{
  TMenuItem * item = dynamic_cast<TMenuItem*>(Sender);
  for(int i=0;i<quantity;i++)
    if(groups[i]->Hint==item->Hint)
	  {
	   TStringList *current=new TStringList();
	   current->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
	   current->Add(ListBox1->Items->Strings[ListBox1->ItemIndex]);
	   int index=list->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
	   current->SaveToFile("Data/Groups/"+namegroups->Strings[i]+".dat");
	   Logs("Added to group "+namegroups->Strings[i],list->Strings[index],TypeFilm,year->Strings[index],country->Strings[index],genre->Strings[index]);
	   s=true;
	   delete current;current=NULL;break;
	  }
}

void __fastcall TForm1::MRemoveFilmFromGroupClick(TObject *Sender)
{
  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
   {
    TMenuItem * item = dynamic_cast<TMenuItem*>(Sender);
    for(int i=0;i<quantity;i++)
	 if(groups[i]->Hint==item->Hint)
	  {
	   TStringList *current=new TStringList();
	   current->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
	   int index=current->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]),index1=list->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
	   current->Delete(index);
	   current->SaveToFile("Data/Groups/"+namegroups->Strings[i]+".dat");
	   Logs("Removed from group "+namegroups->Strings[i],list->Strings[index1],TypeFilm,year->Strings[index1],country->Strings[index1],genre->Strings[index1]);
	   s=true;
	   delete current;current=NULL;
	   if(item->Hint==currentgroup)
		 {
		  ListBox1->Items->Delete(ListBox1->ItemIndex);listcurrentgroup->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
		  Callsort();Quantity();
		  MDelete->Tag=1;//Чтобы не было контуров от компонентов (в Image10Click(Sender) не выполнялся код InfoOnFirstPage(true) после перехода с 2-1ст.)
		  Image10Click(Sender);InfoOnFirstPage(false);
		  MDelete->Tag=0;
		  Image1->Picture->Assign(NULL);
		  Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
		  Label17->Visible=false;Image8->Visible=false;//Индикатор сериала
		  }
	   break;
	  }
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MainGroupClick(TObject *Sender)
{
  currentgroup="MainGroup";Image12->Hint=lang->Strings[195]+" "+lang->Strings[182];
  listcurrentgroup->Clear();
  ListBox1->Items->Assign(list);Label13Click(Form1);Reset();Quantity();
  MainGroup->Tag=1;
  if(Image10->Visible==true){Image10Click(Sender);InfoOnFirstPage(false);}//if - Чтобы не мелькало контурами от компонентов
  Image10Click(Sender);InfoOnFirstPage(false);
  Image1->Picture->Assign(NULL);Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
  Label17->Visible=false;Image8->Visible=false;
  FilmDel->Visible=false;
  MainGroup->Tag=0;
  /*MElect->Visible=true;MDelete->Visible=true;MEdit->Visible=true;PAddToDesired->Visible=true;
  MElect->Enabled=true;MDelete->Enabled=true;MEdit->Enabled=true;PAddToDesired->Enabled=true;*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MAddGroupClick(TObject *Sender)
{
  if(quantity==20)
   {ShowMessage(lang->Strings[194]);return;}//lang->Strings[194]"Вы достигли лимита количества групп!(Лимит:20)"
  AnsiString ForbiddenChars = "\\/*:<>«»|?";UnicodeString name;
  if (InputQuery(lang->Strings[190],lang->Strings[191], name)==False)//lang->Strings[190]-"Новая группа"
	return;                                                                 //lang->Strings[191]="Введите название группы"
  else
	 {
	  for(int i=0;i<name.Length();i++)
		  if(ForbiddenChars.Pos(name.c_str()[i])||name.c_str()[i]=='"')
			{ShowMessage(lang->Strings[129]);return;}//lang->Strings[129]="Имя содержит недопустимые символы!"
	  if(namegroups->IndexOf(name)>=0 || name=="MainGroup")
	   {ShowMessage(lang->Strings[193]);return;}//lang->Strings[193]="Группа с таким названием уже есть!"
	  else
		{
		CreateGroup(quantity,name);
		namegroups->Add(name);
		TStringList *temp=new TStringList();temp->SaveToFile("Data/Groups/"+name+".dat");
		delete temp;temp=NULL;
		quantity++;s=true;
		TDateTime CurrentDateTime=Now();logs->LoadFromFile("Data/Logs.temp");logs->Add("["+CurrentDateTime+"] (Added group): "+name);
		logs->SaveToFile("Data/Logs.temp");logs->Clear();
		}
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GroupsClick(TObject *Sender)
{
  if(quantityadd!=0)
    for(int i=0;i<quantityadd;i++)
      {delete addtogroups[i];addtogroups[i]=NULL;}
  if(quantitydelete!=0)
    for(int i=0;i<quantitydelete;i++)
      {delete deletefromgroups[i];deletefromgroups[i]=NULL;}
  quantityadd=0;quantitydelete=0;
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
  TStringList *current=new TStringList();
  for(int i=0;i<namegroups->Count;i++)
	 {
	  current->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
		if(current->IndexOf(name)>=0)
		  {deletefromgroups[quantitydelete]=new TMenuItem(Groups2);
		   deletefromgroups[quantitydelete]->Caption=namegroups->Strings[i];
           deletefromgroups[quantitydelete]->Hint=namegroups->Strings[i];
           deletefromgroups[quantitydelete]->Tag=quantitydelete;
           deletefromgroups[quantitydelete]->OnClick=MRemoveFilmFromGroupClick;
		   Groups2->Add(deletefromgroups[quantitydelete]);
		   quantitydelete++;}
        else
		  {addtogroups[quantityadd]=new TMenuItem(Groups1);
		   addtogroups[quantityadd]->Caption=namegroups->Strings[i];
		   addtogroups[quantityadd]->Hint=namegroups->Strings[i];
		   addtogroups[quantityadd]->Tag=quantityadd;
           addtogroups[quantityadd]->OnClick=MAddFilmToGroupClick;
           Groups1->Add(addtogroups[quantityadd]);
           quantityadd++;}
	 }
  if(quantityadd==0)
    Groups1->Visible=false;
  else
    Groups1->Visible=true;
  if(quantitydelete==0)
    Groups2->Visible=false;
  else
    Groups2->Visible=true;
  delete current;current=NULL;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FilmDelClick(TObject *Sender)
{
  if(MessageDlg(sure,mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
   {
	int index=listcurrentgroup->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
	int index1=list->IndexOf(ListBox1->Items->Strings[ListBox1->ItemIndex]);
	listcurrentgroup->Delete(index);
	listcurrentgroup->SaveToFile("Data/Groups/"+currentgroup+".dat");
	ListBox1->Items->Delete(ListBox1->ItemIndex);
	Callsort();Quantity();s=true;
	Logs("Removed from group "+currentgroup,list->Strings[index1],TypeFilm,year->Strings[index1],country->Strings[index1],genre->Strings[index1]);
	MDelete->Tag=1;//Чтобы не было контуров от компонентов (в Image10Click(Sender) не выполнялся код InfoOnFirstPage(true) после перехода с 2-1ст.)
	Image10Click(Sender);InfoOnFirstPage(false);
	MDelete->Tag=0;
	Image1->Picture->Assign(NULL);
	Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
	Label17->Visible=false;Image8->Visible=false;
   }
}
//------------------------------------------------------------------------------

void __fastcall TForm1::Image13Click(TObject *Sender)
{
   SetRadioButtons(sortmode);
   Form10->Position=poScreenCenter;
   if (Form10->ShowModal()==mrCancel)
    return;
   SetOptions(Form1,sortmode,lang->Strings[8]);
}
//---------------------------------------------------------------------------
//-------------------------------------------------Размеры------------------------------------------

int GetTextLength(TWinControl *AControl)
{
  TComboBox *pComboBox = dynamic_cast <TComboBox *> (AControl);
  int Length = 0;
  TCanvas *pCanvas = new TCanvas();
  pCanvas->Handle = GetDC(pComboBox->Handle);
  for(int i = 0; i < pComboBox->Items->Count; i++)
	{
	 AnsiString Text = pComboBox->Items->Strings[i];
	 int TempLength = pCanvas->TextWidth(Text);
	 if(TempLength > Length)
		Length = TempLength;
	}
  delete pCanvas;
  return Length;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ComboBoxDropDown(TObject *Sender)
{
 TComboBox *current = static_cast <TComboBox *> (Sender);
 if(options->Strings[5]!="Ukrainian")
   SendMessage(current->Handle, CB_SETDROPPEDWIDTH, GetTextLength(current) + 40, 0);
 else
   SendMessage(current->Handle, CB_SETDROPPEDWIDTH, GetTextLength(current) + 20, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SizeOfIndicatorViewed()
{
   int size=Label1->Width - Label1->Canvas->TextWidth(Label1->Caption);
   int sum=71-size;
   if(size<71) //Пересекает индикатор
   {
	 if(Memo1->Left-sum>Memo1->Left-33)Image15->Left=Memo1->Left-sum;
	 else Image15->Left=Memo1->Left-33;
   }
   else Image15->Left=Memo1->Left;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
   Image4->Top=ClientHeight-46;
   Image5->Top=ClientHeight-50;
   if(ClientHeight>=694)
   {
   ComboBox1->Top=ClientHeight-210;
   ComboBox2->Top=ClientHeight-210;
   ComboBox3->Top=ClientHeight-146;
   ComboBox4->Top=ClientHeight-146;
   ComboBox5->Top=ClientHeight-82;
   ComboBox6->Top=ClientHeight-82;
   ComboBox7->Top=ClientHeight-146;
   ComboBox8->Top=ClientHeight-146;
   CheckListBox1->Top=ClientHeight-210;
   CheckListBox2->Top=ClientHeight-210;
   CheckListBox3->Top=ClientHeight-146;
   CheckListBox4->Top=ClientHeight-146;
   Label2->Top=ClientHeight-242;
   Label3->Top=ClientHeight-178;
   Label4->Top=ClientHeight-178;
   Label14->Top=ClientHeight-114;
   Label15->Top=ClientHeight-114;
   Label20->Top=ClientHeight-242;
   Image13->Top=ClientHeight-244;
   Image16->Top=ClientHeight-239;
   }
   else
   {
   ComboBox1->Top=484;
   ComboBox2->Top=484;
   ComboBox3->Top=548;
   ComboBox4->Top=548;
   ComboBox5->Top=612;
   ComboBox6->Top=612;
   ComboBox7->Top=548;
   ComboBox8->Top=548;
   CheckListBox1->Top=484;
   CheckListBox2->Top=484;
   CheckListBox3->Top=548;
   CheckListBox4->Top=548;
   Label2->Top=452;
   Label3->Top=516;
   Label4->Top=516;
   Label14->Top=580;
   Label15->Top=580;
   Label20->Top=452;
   Image13->Top=450;
   Image16->Top=455;
   }
   //Memo1->Left-------------------------------------------------
   if(Memo1->Left>=449 && Memo1->Left<=654 && Memo1->Width<=625)
	{
	 if(ClientWidth>1144 && ClientWidth<1350)Memo1->Left=ClientWidth-Memo1->Width-71;
	 if(ClientWidth>=1350)Memo1->Left=654;
	}
   else
	if(Memo1->Left>=449 && Memo1->Left<=654 && Memo1->Width>625 && ClientWidth<=1350)
	  {Memo1->Width=625;Memo1->Left=ClientWidth-Memo1->Width-71;}
   if(ClientWidth<=1144) Memo1->Left=449;
   //Memo1->Top--------------------------------------------------
   if(ClientHeight<=722) Memo1->Top=441;
   if(ClientHeight>722 && ClientHeight<872)Memo1->Top=ClientHeight-282;//ClientHeight<832
   if(ClientHeight>=872)Memo1->Top=590;                                //Memo1->Top=550
   //Memo1->Top=ClientHeight-282; //Для определения высоты опускания
   //Top------------------------------------------------------------------
   Label1->Top=Memo1->Top-145;
   Label5->Top=Memo1->Top-89;Label6->Top=Memo1->Top-89;
   Label7->Top=Memo1->Top-89;Label19->Top=Memo1->Top-89;
   Label8->Top=Memo1->Top-33;
   Label10->Top=ClientHeight-66;
   Label17->Top=Memo1->Top-140;
   Edit1->Top=Memo1->Top-57;Edit2->Top=Memo1->Top-57;
   Edit3->Top=Memo1->Top-57;Edit6->Top=Memo1->Top-57;
   Edit4->Top=ClientHeight-34;
   Image8->Top=Memo1->Top-145;
   Image9->Top=Memo1->Top;
   Image10->Top=Memo1->Top-63;Image11->Top=Memo1->Top-63;
   Image15->Top=Memo1->Top-145;
   for (int i=1;i<=5;i++)
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->Top=Memo1->Top-27;
   //Height and Width------------------------------------------------------
   ListBox1->Width=ClientWidth-ListBox1->Left-863;
   ListBox1->Height=ClientHeight-357;//[
   Label18->Top=ListBox1->Height+55;//]
   Label9->Width=ClientWidth-Label18->Left-863;
   Label18->Width=ClientWidth-Label18->Left-863;
   ListBox2->Width=ListBox1->Width;ListBox2->Height=ListBox1->Height;
   Memo1->Height=ClientHeight-Memo1->Top-72;
   Memo1->Width=ClientWidth-Memo1->Left-71;//[
   Label1->Width=Memo1->Width;
   Image1->Width=Memo1->Width;
   Image1->Height=Label1->Top-15;
   Edit4->Width=Memo1->Width-48;//]
   //Left------------------------------------------------------------------
   Label1->Left=Memo1->Left;
   Label8->Left=Memo1->Left;Label10->Left=Memo1->Left;
   Label17->Left=ClientWidth-Label17->Width-24;
   Edit4->Left=Memo1->Left;
   Edit5->Left=ListBox1->Width+50;Edit5->Width=ClientWidth-Edit5->Left-719;//Edit5->Width------------
   Image6->Left=Edit5->Width+Edit5->Left;
   Image1->Left=Memo1->Left;
   Image3->Left=ListBox1->Width+16;
   Image4->Left=ClientWidth-Image4->Width-21;
   Image5->Left=ClientWidth-Image5->Width-71;
   Image8->Left=ClientWidth-Image8->Width-23;
   Image9->Left=ClientWidth-Image9->Width-23;
   Image10->Left=ClientWidth-Image10->Width-35;
   Image11->Left=ClientWidth-Image11->Width;
   Image14->Left=ClientWidth-Image14->Width-22;
   SizeOfIndicatorViewed();//Image15->Left=Memo1->Left;

   Star1->Left=ClientWidth-Star1->Width-168;
   for (int i=2;i<=5;i++)
	 ((TImage*)FindComponent("Star"+IntToStr(i)))->Left=((TImage*)FindComponent("Star"+IntToStr(i-1)))->Left+25;

   RadioButton1->Left=ListBox1->Width+39;Label11->Left=ListBox1->Width+63;
   RadioButton2->Left=ListBox1->Width+39;Label12->Left=ListBox1->Width+63;
   RadioButton3->Left=ListBox1->Width+39;Label13->Left=ListBox1->Width+63;
   RadioButton4->Left=ListBox1->Width+39;Label16->Left=ListBox1->Width+63;

   Pointer->Left=ListBox1->Width+40;
   Line1->Left=ListBox1->Width+10;Line2->Left=ListBox1->Width+24;
   Line3->Left=ListBox1->Width+10;Line4->Left=ListBox1->Width+24;
   Line5->Left=ListBox1->Width+10;Line6->Left=ListBox1->Width+24;
   Line7->Left=ListBox1->Width+10;

   Edit1->Left=Memo1->Left;Edit1->Width=(Memo1->Width/3.397)-23;
   Edit6->Left=Edit1->Left+Edit1->Width+23;Edit6->Width=(Memo1->Width/3.55)-23;
   Edit2->Left=Edit6->Left+Edit6->Width+23;Edit2->Width=(Memo1->Width/4.085)-23;
   Edit3->Left=Edit2->Left+Edit2->Width+23;Edit3->Width=Memo1->Width/5.53;
   Label5->Left=Edit1->Left;Label5->Width=Edit1->Width;
   Label19->Left=Edit6->Left;Label19->Width=Edit6->Width;
   Label6->Left=Edit2->Left;Label6->Width=Edit2->Width;
   Label7->Left=Edit3->Left-18;Label7->Width=Edit3->Width+36;

   Memo2->Width=Memo1->Width;Memo2->Left=Memo1->Left;Memo2->Top=Memo1->Top+81;
   Label21->Width=Memo2->Width;Label21->Left=Memo2->Left;Label21->Top=Memo2->Top-162;
   Label24->Left=Memo2->Left;Label24->Top=Memo2->Top-33;
   Label26->Left=Memo2->Left;Label26->Top=Memo2->Top+Memo2->Height+10;
   Edit7->Left=Memo2->Left+44;Edit7->Width=(Memo2->Width/2.17)-39;Edit7->Top=Memo2->Top-67;
   Edit8->Width=(Memo2->Width/2.133)-44;Edit8->Left=Memo2->Width+Memo2->Left-Edit8->Width-44;Edit8->Top=Memo2->Top-67;
   //Label22->Left=Edit7->Left;Label22->Width=Edit7->Width;Label22->Top=Edit7->Top-33;
   Label22->Left=Edit7->Left-30;Label22->Width=Edit7->Width+59;Label22->Top=Edit7->Top-33;
   Label23->Left=Edit8->Left;Label23->Width=Edit8->Width;Label23->Top=Edit8->Top-33;
   //AlphabetPanel
   CategoryPanelGroup1->Height=ClientHeight;
   Panel1->Top=CategoryPanelGroup1->Height/2-42;
   Panel2->Height=CategoryPanelGroup1->Height;
   //Form1->Caption=IntToStr(Form1->Width)+" "+IntToStr(ClientWidth)+" "+IntToStr(Form1->Height)+" "+IntToStr(ClientHeight);
   //Label9->Caption=IntToStr(Edit7->Left-Memo2->Left)+" "+IntToStr(Memo2->Width+Memo2->Left-Edit8->Width-Edit8->Left);
   if(shadow!=NULL && shadow->CheckVisible())
	  shadow->SetSizes();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox1DrawItem(TWinControl *Control, int Index, TRect &Rect,
		  TOwnerDrawState State)
{
  TCanvas *pCanvas = ((TListBox *)Control)->Canvas;
  if(State.Contains(odSelected))
  {
	switch(StrToInt(options->Strings[1]))
	{
	 case 1:{pCanvas->Brush->Color =(TColor)RGB(51,153,255);break;}
	 case 2:{pCanvas->Brush->Color =(TColor)RGB(255,255,168);break;}
	 case 3:{pCanvas->Brush->Color =(TColor)RGB(121,255,155);break;}
	 case 4:{pCanvas->Brush->Color =(TColor)RGB(255,72,72);break;}
	 case 5:{pCanvas->Brush->Color =(TColor)RGB(255,153,0);break;}
	}
  }
  pCanvas->FillRect(Rect);
  if(options!=NULL)if(options->Strings[1]=="2"||options->Strings[1]=="3")pCanvas->Font->Color=clBlack;
  pCanvas->TextOut(Rect.Left , Rect.Top, ((TListBox *)Control)->Items->Strings[Index]);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListBox2DrawItem(TWinControl *Control, int Index, TRect &Rect,
		  TOwnerDrawState State)
{
  TCanvas *pCanvas = ((TListBox *)Control)->Canvas;
  if(State.Contains(odSelected))
  {
	switch(StrToInt(options->Strings[1]))
	{
	 case 1:{pCanvas->Brush->Color =(TColor)RGB(51,153,255);break;}
	 case 2:{pCanvas->Brush->Color =(TColor)RGB(255,255,168);break;}
	 case 3:{pCanvas->Brush->Color =(TColor)RGB(121,255,155);break;}
	 case 4:{pCanvas->Brush->Color =(TColor)RGB(255,72,72);break;}
	 case 5:{pCanvas->Brush->Color =(TColor)RGB(255,153,0);break;}
	}
  }
  pCanvas->FillRect(Rect);
  if(options!=NULL)if(options->Strings[1]=="2"||options->Strings[1]=="3")pCanvas->Font->Color=clBlack;
  pCanvas->TextOut(Rect.Left , Rect.Top, ((TListBox *)Control)->Items->Strings[Index]);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MSeveralDeletingClick(TObject *Sender)
{
   Form13->ListBox1->Items->Assign(list);Form13->ListBox2->Clear();
   Form13->Position=poScreenCenter;
   if(Form13->ShowModal()==mrCancel)
	  return;
   if(Form13->ListBox2->Items->Count!=0)
   {
	  int index;AnsiString namefilm,name;
	  TStringList *current=new TStringList();
	  for(int i=0;i<Form13->ListBox2->Count;i++)
		  {
			index=list->IndexOf(Form13->ListBox2->Items->Strings[i]);
			AnsiString typefilm;
			if(type->Strings[index]=="Movie")typefilm=lang->Strings[78];else typefilm=lang->Strings[79];
			Logs("Removed",list->Strings[index],typefilm,year->Strings[index],country->Strings[index],genre->Strings[index]);
			namefilm=list->Strings[index];
			list->Delete(index);genre->Delete(index);country->Delete(index);year->Delete(index);duration->Delete(index);link->Delete(index);
			view->Delete(index);type->Delete(index);type1->Delete(index);release->Delete(index);trailer->Delete(index);season->Delete(index);
			tagline->Delete(index);originalname->Delete(index);director->Delete(index);cast->Delete(index);rating->Delete(index);episode->Delete(index);
			AccessToForbiddenChar(namefilm);
			DeleteFile("Data/Image/"+namefilm+".jpg");DeleteFile("Data/Plot/"+namefilm+".dat");
			DeleteFile("Data/Seasons/"+namefilm+".dat");
			for(int k=0;k<elect->Count;k++)
			   if(elect->Strings[k]==Form13->ListBox2->Items->Strings[i])
				  {elect->Delete(k);break;}
			name=Form13->ListBox2->Items->Strings[i];
			current->Clear();
			for(int i=0;i<namegroups->Count;i++)
			  {current->LoadFromFile("Data/Groups/"+namegroups->Strings[i]+".dat");
			   if(current->IndexOf(name)>=0)
				 {current->Delete(current->IndexOf(name));current->SaveToFile("Data/Groups/"+namegroups->Strings[i]+".dat");}
			  }
		  }
	   seasonfilm="0";
	   if(currentgroup=="MainGroup")
		  Callsort();
	   if(currentgroup!="MainGroup")
	   {
		   ListBox1->Items->LoadFromFile("Data/Groups/"+currentgroup+".dat");
		   listcurrentgroup->Assign(ListBox1->Items);
		   Callsort();
       }
	   Quantity();
	   s=true;
	   Label18->Caption=FloatToStr(ListBox1->ItemIndex+1)+'-'+FloatToStr(ListBox1->Count);
	   MDelete->Tag=1;//Чтобы не было контуров от компонентов (в Image10Click(Sender) не выполнялся код InfoOnFirstPage(true) после перехода с 2-1ст.)
	   Image10Click(Sender);InfoOnFirstPage(false);
	   MDelete->Tag=0;
	   Image1->Picture->Assign(NULL);Image10->Visible=false;Image11->Visible=false;Image15->Visible=false;
	   //Обновление панели
	   for (int i=0;i<59;i++)
	   if(((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(i+1)))->Hint!="0")
	   {
		Form1->CategoryPanelCollapse(((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(i+1))));
		Form1->CategoryPanelExpand(((TCategoryPanel*)Form1->FindComponent("CategoryPanel"+IntToStr(i+1))));
	   }
   }
}
//---------------------------Текущая серия сериала--------------------------

void __fastcall TForm1::Label17Click(TObject *Sender)
{
  if(MCatalogMenu->Enabled==true)
  {
   AnsiString namefilm=list->Strings[SelectedFilm];
   AccessToForbiddenChar(namefilm);
   Form15->SerialSeasons->LoadFromFile("Data/Seasons/"+namefilm+".dat");
   Form15->SetEpisode(StrToInt(currentseason),StrToInt(currentepisode));
   if(episode->Strings[SelectedFilm].c_str()[0]=='X')Form15->CheckBox1->Checked=true;//*
   else Form15->CheckBox1->Checked=false;                                            //*
   Form15->Position=poScreenCenter;
   if(Form15->ShowModal()==mrCancel)
	  return;
   currentseason=Form15->ComboBox1->ItemIndex+1;currentepisode=Form15->ComboBox2->ItemIndex+1;
   if(Form15->CheckBox1->Checked)episode->Strings[SelectedFilm]="X"+currentseason+":"+currentepisode;//*
   else episode->Strings[SelectedFilm]=currentseason+":"+currentepisode;
   s=true;
  }
}
//--------------------------Увеличение фото фильма--------------------------

void __fastcall TForm1::Image1Click(TObject *Sender)
{
	 if(Image1->Picture->Graphic!=NULL)
	 {
	   MCatalogMenu->Enabled=false;MQFilter->Enabled=false;AllGroups->Enabled=false;
	   MOptions->Enabled=false;MAbout->Enabled=false;
	   if(Edit1->Visible)FocusControl(Edit1);
	   else FocusControl(Edit7);
	   shadow->ShowPicture(Image1);Timer5->Enabled=true;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image1MouseEnter(TObject *Sender)
{
   if(Image1->Picture->Graphic!=NULL)Image1->Cursor=(TCursor)4;
   else Image1->Cursor=(TCursor)1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CatchDrag(TMessage &Msg)
{
  TForm::Dispatch(&Msg);
  if(Msg.Msg == WM_MOVING)
  {
   if(shadow!=NULL && shadow->CheckVisible())
	  FormResize(Form1);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image15Click(TObject *Sender)
{
  if(Image15->Hint==lang->Strings[246])
	 {view->Strings[SelectedFilm]=yes;Image15->Hint=lang->Strings[247];Image15->Picture->LoadFromFile("Soft/Buttons/Seen.ico");}
  else
	 {view->Strings[SelectedFilm]=not;Image15->Hint=lang->Strings[246];Image15->Picture->LoadFromFile("Soft/Buttons/Unseen.ico");}
  s=true;
  Beep();
}
//---------------------------------------------------------------------------
//------------------------------Собственные фильтры--------------------------

void SetOptionsFavouriteFilter()
{
  favouritefilter->Strings[0]=Form16->GetFavouriteFilter();
  if(favouritefilter->Strings[0]=="-")Form1->MFavouriteFilter->Enabled=false;
  else Form1->MFavouriteFilter->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MFilterClick(TObject *Sender)
{
  Form16->SetFavouriteFilter(favouritefilter->Strings[0]);
  Form16->Position=poScreenCenter;
  if(Form16->ShowModal()==mrCancel)
	  {SetOptionsFavouriteFilter();return;}
  Form16->GetSortMode(sortmode);
  SetOptionsFavouriteFilter();
  Callsort();Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image16Click(TObject *Sender)
{
  Form16->SetFavouriteFilter(favouritefilter->Strings[0]);
  Form16->Position=poScreenCenter;Form16->Tag=1;
  SetRadioButtons(sortmode);
  if(Form16->ShowModal()==mrCancel)
	  {SetOptionsFavouriteFilter();return;}
  Form16->GetSortMode(sortmode);
  SetOptionsFavouriteFilter();
  Callsort();Quantity();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MLastFilterClick(TObject *Sender)
{
  AnsiString name=MLastFilter->Hint;AccessToForbiddenChar(name);
  TStringList *filter=new TStringList();
  filter->LoadFromFile("Filters/"+name+".dat");
  SetRadioButtons(filter);
  //Для установки параметров фильтра(отключение в SetOptions условия &&Filter->Strings[0]!="1")
  for(int i=0; i<4;i++)filter->Strings[i]="0";
  SetOptions(Form1,filter,lang->Strings[8]);
  filter->LoadFromFile("Filters/"+name+".dat");
  //----
  SetOptions(Form1,filter,lang->Strings[8]);
  Form16->ShowInformation(Form1,filter);

  for(int i=0; i<4;i++)sortmode->Strings[i]=filter->Strings[i];
  Callsort();Quantity();
  MessageDlg(lang->Strings[267]+AnsiString(MLastFilter->Hint),mtInformation,TMsgDlgButtons()<<mbOK,0);
  delete filter;filter=NULL; //"Был применён последний фильтр: "
}
//------------------------------------------------------------------------------

void __fastcall TForm1::MFavouriteFilterClick(TObject *Sender)
{
  AnsiString name=favouritefilter->Strings[0];AccessToForbiddenChar(name);
  TStringList *filter=new TStringList();
  filter->LoadFromFile("Filters/"+name+".dat");
  SetRadioButtons(filter);
  //Для установки параметров фильтра(отключение в SetOptions условия &&Filter->Strings[0]!="1")
  for(int i=0; i<4;i++)filter->Strings[i]="0";
  SetOptions(Form1,filter,lang->Strings[8]);
  filter->LoadFromFile("Filters/"+name+".dat");
  //----
  SetOptions(Form1,filter,lang->Strings[8]);
  Form16->ShowInformation(Form1,filter);

  for(int i=0; i<4;i++)sortmode->Strings[i]=filter->Strings[i];
  Callsort();Quantity();
  MessageDlg(lang->Strings[268]+AnsiString(favouritefilter->Strings[0]),mtInformation,TMsgDlgButtons()<<mbOK,0);
  delete filter;filter=NULL; //"Был применён любимый фильтр: "
}
//---------------------------------------------------------------------------
//-------------------------------Статистика-------------------------------------

void QuantityElements_Statistic(TStringList *List,TCheckListBox *CLB,TChartSeries *LSeries)
{
  int k=0,z;
  for(int i=0;i<CLB->Count;i++)
  {
	k=0;z=0;
	for(int j=0;j<List->Count;j++)
	  if(List->Strings[j].Pos(CLB->Items->Strings[i]))
		 k++;
	LSeries->AddXY(k,i+z, CLB->Items->Strings[i]);//4 параметр - цвет (clRed)
  }
}
//---------------------------------------------------------------------------

int QuickQuantityElements(TStringList *List,AnsiString string)
{
  int k=0;
  for(int i=0;i<list->Count;i++)
	 if(List->Strings[i]==string)
		k++;
  return k;
}
//---------------------------------------------------------------------------

void RadioButtonsLeftValue(int l1,int l2,int l3,int l4,int l5)
{
  Form17->RadioButton1->Left=l1;Form17->RadioButton2->Left=l2;Form17->RadioButton3->Left=l3;
  Form17->RadioButton4->Left=l4;Form17->RadioButton5->Left=l5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MStatisticClick(TObject *Sender)
{
  int k=0;AnsiString name,from,till;
  //Каталог---------------------------------------------------------------------
  Form17->Label1->Caption=lang->Strings[272]+AnsiString(list->Count)+" ";//"Общее количество фильмов:"
  Form17->Label2->Caption=lang->Strings[273]+AnsiString(QuickQuantityElements(type,"Movie"))+" ";//"– фильмов:"
  Form17->Label3->Caption=lang->Strings[274]+AnsiString(QuickQuantityElements(type,"TV series"))+" ";//"– сериалов:"
  Form17->Label4->Caption=lang->Strings[275]+AnsiString(elect->Count)+" ";//"– избранных:"
  Form17->Label5->Caption=lang->Strings[276]+AnsiString(QuickQuantityElements(view,yes))+" ";//"Просмотренных фильмов:"
  Form17->Label6->Caption=lang->Strings[277]+AnsiString(QuickQuantityElements(view,not))+" ";//"Непросмотренных фильмов:"
  Form17->Label7->Caption=lang->Strings[278]+AnsiString(QuickQuantityElements(release,yes))+" ";//"Вышедших фильмов:"
  Form17->Label8->Caption=lang->Strings[279]+AnsiString(QuickQuantityElements(release,not))+" ";//"Не вышедших фильмов:"
  k=0;
  for(int i=0;i<list->Count;i++)if(episode->Strings[i].c_str()[0]=='X')k++;
  Form17->Label9->Caption=lang->Strings[245]+" ("+lang->Strings[79]+"):"+AnsiString(k)+" ";//"Ожидается серия/сезон(сериал):"

  TStringList *websites=new TStringList();websites->LoadFromFile("Soft/Websites.txt");
  Form17->Label10->Caption=lang->Strings[280]+AnsiString(websites->Count)+" ";//"Сайтов с фильмами:"
  delete websites;websites=NULL;
  Form17->Label11->Caption=lang->Strings[281]+AnsiString(quantity)+" ";//"Груп:"
  Form17->ListBox1->Items->Assign(namegroups);
  const char *Ratings[11] = {"5.0","4.5","4.0","3.5","3.0","2.5","2.0","1.5","1.0","0.5","0.0"};
  const char *LabelStar[11] = {"LabelStar5","LabelStar4_5","LabelStar4","LabelStar3_5","LabelStar3","LabelStar2_5",
							   "LabelStar2","LabelStar1_5","LabelStar1","LabelStar0_5","LabelStar0"};
  for (int i=0;i<=10;i++)
	((TLabel*)Form17->FindComponent(AnsiString(LabelStar[i])))->Caption="– "+AnsiString(QuickQuantityElements(rating,AnsiString(Ratings[i])))+" ";

  QuantityElements_Statistic(genre,CheckListBox1,Form17->Series1);
  QuantityElements_Statistic(country,CheckListBox2,Form17->Series2);
  //Год------------------
  k=0;
  for(int i=0;i<CheckListBox3->Count;i++)
  {
	k=0;
	for(int j=0;j<year->Count;j++)
	{
	  if(type->Strings[j]=="Movie")
		if(year->Strings[j]==CheckListBox3->Items->Strings[i])
		   k++;
	  if(type->Strings[j]=="TV series")
	   {from=till="";DivisionYear(year->Strings[j],from,till);
		if(StrToInt(CheckListBox3->Items->Strings[i])>=StrToInt(from)&&StrToInt(CheckListBox3->Items->Strings[i])<=StrToInt(till))
		   k++;
	   }
	}
	Form17->Series3->AddXY(i,k, CheckListBox3->Items->Strings[i]);
  }
  //Время-----------------
  k=0;
  for(int i=0;i<=270;i=i+10)
  {
	if(i==270)break;
	k=0;
	for(int j=0;j<duration->Count;j++)
	  if(duration->Strings[j].ToInt()>=i && duration->Strings[j].ToInt()<=i+10)
		k++;
	Form17->Series4->AddXY(k,i, IntToStr(i)+"-"+IntToStr(i+10)+min);
  }
  //Алфавит----------------
  k=0;
  AnsiString chars="абвгдеєжзиіїйклмнопрстуфхцчшщэюяabcdefghijklmnopqrstuvwxyz",letter;
  for(int i=0;i<list->Count;i++)
  {
	  letter=list->Strings[i].LowerCase().c_str()[0];
	  if(!chars.Pos(letter))
		k++;
  }
  Form17->Series5->AddXY(0,k,"#");
  k=0;
  for(int i=0;i<58;i++)
  {
	k=0;
	for(int j=0;j<list->Count;j++)
	{
	 name=list->Strings[j];
	 if(name.LowerCase().c_str()[0]==chars.c_str()[i])
	  k++;
	}
	Form17->Series5->AddXY(i+1,k, AnsiString(chars.UpperCase().c_str()[i]));//UpperCase().
  }
  //Лог-------------------------------------------------------------------------
  Form17->EventsBoxChange(Form17);
  //Общая информация------------------------------------------------------------
  Form17->ListBox3->Clear();Form17->ListBox4->Clear();Form17->ListBox5->Clear();
  TSearchRec sr;
  k=0;
  if (FindFirst("Catalogs\\*.cof", faAnyFile | faDirectory, sr) == 0)
	 {
		do
		{
		  k++;
		  name=sr.Name;name=name.Delete(name.Length()-4+1, 4);
		  Form17->ListBox3->Items->Add(name);
		}
		while(FindNext(sr) == 0);
		FindClose(sr);
	 }
  Form17->Label12->Caption=lang->Strings[283]+AnsiString(k)+" ";//"Количество каталогов:"
  k=0;
  if (FindFirst("Films from other catalogs\\*.*", faDirectory, sr) == 0)
	 {
		do
		 if(faDirectory  == sr.Attr)
		   if(sr.Name != "." && sr.Name != "..")
			{
			 k++;
			 name=sr.Name;
			 for(int j=0;j<name.Length();j++)
			   {if(name.c_str()[j]=='_')
				   name.c_str()[j]=':';
				if(name.c_str()[j]=='[')
				   name.c_str()[j]='«';
				if(name.c_str()[j]==']')
				   name.c_str()[j]='»';}
			 Form17->ListBox4->Items->Add(name);
			}
		while(FindNext(sr) == 0);
		FindClose(sr);
	 }
  Form17->Label13->Caption=lang->Strings[284]+AnsiString(k)+" ";//"Количество фильмов из других каталогов:"
  k=0;
  if (FindFirst("Filters\\*.dat", faAnyFile | faDirectory, sr) == 0)
	 {
		do
		{   k++;
			name=sr.Name;name=name.Delete(name.Length()-4+1, 4);
			for(int i=0; i<name.Length();i++)
			{
			  if(name.c_str()[i]=='_')
				 name.c_str()[i]=':';
			  if(name.c_str()[i]=='[')
				 name.c_str()[i]='«';
			  if(name.c_str()[i]==']')
				 name.c_str()[i]='»';
			}
			Form17->ListBox5->Items->Add(name);
		}
		while(FindNext(sr) == 0);
		FindClose(sr);
	 }
  Form17->Label14->Caption=lang->Strings[285]+AnsiString(k)+" ";//"Количество собственных фильтров:"
  if(favouritefilter->Strings[0]=="-")Form17->Label17->Caption=lang->Strings[265]+":- ";
  else Form17->Label17->Caption=lang->Strings[265]+":\n"+favouritefilter->Strings[0]+" ";
  Form17->Label18->Caption=lang->Strings[263]+" ";
  //----------------------------------------------------------------------------
  if(options->Strings[5]=="Russian")  RadioButtonsLeftValue(558,654,770,852,960);
  if(options->Strings[5]=="Ukrainian")RadioButtonsLeftValue(535,631,747,829,984);
  if(options->Strings[5]=="English")  RadioButtonsLeftValue(568,664,780,865,956);
  Form17->Position=poScreenCenter;Form17->ShowModal();
}
//---------------------------------------------------------------------------
/*Series5 - Алфавит

*/

 /*
 AnsiString namefilm;TStringList *temp=new TStringList();
  for(int i=0;i<list->Count;i++)
	if(type->Strings[i]=="TV series")
	 {
	  namefilm=list->Strings[i];
	  AccessToForbiddenChar(namefilm);
	  temp->Clear();
	  SeparationSeasonSeries(season->Strings[i]);
	  for(int j=0;j<seasonfilm.ToInt();j++)
		  temp->Add("1");
	  temp->SaveToFile("e:/Seasons/"+namefilm+".dat");
	 }
 */
//----------------------------------------------------------------------------------
//-------------------------------Alphabet Panel-------------------------------------

void __fastcall TForm1::ExpandCollapseButtonClick(TObject *Sender)
{
  Timer6->Enabled=true;
  CategoryPanelGroup1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer6Timer(TObject *Sender)
{
  if(Timer6->Tag==0)
  {
   if(CategoryPanelGroup1->Width>=232){Timer6->Enabled=false;Timer6->Tag=1;ExpandCollapseButton->Picture->LoadFromFile("Soft/Buttons/CollapseArrow.png");}
   else {CategoryPanelGroup1->Width+=40;Panel3->Width+=40;}
  }
  else
  {
   if(CategoryPanelGroup1->Width==0){Timer6->Enabled=false;Timer6->Tag=0;ExpandCollapseButton->Picture->LoadFromFile("Soft/Buttons/ExpandArrow.jpg");}
   else {CategoryPanelGroup1->Width-=40;Panel3->Width-=40;}
  }
  Panel1->Left=CategoryPanelGroup1->Left+CategoryPanelGroup1->Width;
  Panel2->Left=CategoryPanelGroup1->Left+CategoryPanelGroup1->Width;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AlphabetPanelOptionsClick(TObject *Sender)
{
  for(int i=0;i<Form3->ComponentCount;i++)
	if(Form3->Components[i]->ClassNameIs("TRadioButton"))
	   ((TRadioButton *)Form3->Components[i])->Checked=false;

  if(AlphabetOptions->Strings[1]=="NONE")Form3->RBPanelNone->Checked=true;
  else {((TRadioButton*)Form3->FindComponent("RBPanel"+AlphabetOptions->Strings[1]))->Checked=true;Form3->GroupBox1->Tag=AlphabetOptions->Strings[1].ToInt();}
  if(AlphabetOptions->Strings[3]=="NONE")Form3->RBFrameNone->Checked=true;
  else
  {
  if(AlphabetOptions->Strings[3].Length()==1){Form3->ComboBox1->ItemIndex=StrToInt(AlphabetOptions->Strings[3])-1;Form3->RBFrameStyle->Checked=true;}
  else {Form3->ButtonColor1->SymbolColor=StringToColor(AlphabetOptions->Strings[3]);Form3->RBFrameOwn->Checked=true;}
  }
  if(AlphabetOptions->Strings[5].Length()==1)
  {
	Form3->ComboBox2->ItemIndex=StrToInt(AlphabetOptions->Strings[5])-1;
	Form3->RBWindowStyles->Checked=true;
  }
  else
	Form3->RBWindowOwn->Checked=true;
  //Надписи
  Form3->OrigName->Caption=lang->Strings[135]+":";Form3->Genre->Caption=lang->Strings[0]+":";Form3->Country->Caption=lang->Strings[133]+":";
  Form3->Year->Caption=lang->Strings[1]+":";Form3->Time->Caption=lang->Strings[2]+":";
  Form3->Label1->Left=Form3->OrigName->Left+Form3->OrigName->Width+3;Form3->Label2->Left=Form3->Genre->Left+Form3->Genre->Width+3;
  Form3->Label3->Left=Form3->Country->Left+Form3->Country->Width+3;Form3->Label4->Left=Form3->Year->Left+Form3->Year->Width+3;
  Form3->Label5->Left=Form3->Time->Left+Form3->Time->Width+3;
  //------
  Form3->Position=poScreenCenter;
  if(Form3->ShowModal()==mrCancel)
	  return;

  if(Form3->RBPanelNone->Checked)AlphabetOptions->Strings[1]="NONE";
  else AlphabetOptions->Strings[1]=Form3->GroupBox1->Tag;
  if(Form3->RBFrameNone->Checked)AlphabetOptions->Strings[3]="NONE";
  if(Form3->RBFrameStyle->Checked)AlphabetOptions->Strings[3]=Form3->ComboBox1->ItemIndex+1;
  if(Form3->RBFrameOwn->Checked)AlphabetOptions->Strings[3]=ColorToString(Form3->ButtonColor1->SymbolColor);
  if(Form3->RBWindowStyles->Checked)AlphabetOptions->Strings[5]=Form3->ComboBox2->ItemIndex+1;
  if(Form3->RBWindowOwn->Checked)
	{
	 AlphabetOptions->Strings[5]="Own";FrameProperties::SaveComponent(Form3->Panel1,"Soft/AlphabetPanel/WindowStyleOwn.dat");
	 FrameProperties::SaveComponent(Form3->OrigName,"Soft/AlphabetPanel/WindowStyleOwn/OrigName.dat");
	 FrameProperties::SaveComponent(Form3->Genre,"Soft/AlphabetPanel/WindowStyleOwn/Genre.dat");
	 FrameProperties::SaveComponent(Form3->Country,"Soft/AlphabetPanel/WindowStyleOwn/Country.dat");
	 FrameProperties::SaveComponent(Form3->Year,"Soft/AlphabetPanel/WindowStyleOwn/Year.dat");
	 FrameProperties::SaveComponent(Form3->Time,"Soft/AlphabetPanel/WindowStyleOwn/Time.dat");
	}
  SetPanelParameters();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CategoryPanelExpand(TObject *Sender)
{
  TCategoryPanel* current=static_cast<TCategoryPanel*>(Sender);
  TStringList *films=new TStringList();
  TStringList *list_sorted=new TStringList();
  list_sorted->Assign(list);list_sorted->Sort();
  AnsiString symbol=current->Caption;
  AnsiString name,chars="абвгдеєжзиіїйклмнопрстуфхцчшщэюяabcdefghijklmnopqrstuvwxyz",letter;
  int index=current->Tag;
  int height=0;
  for(int i=0;i<list_sorted->Count;i++)
   {
	 name=list_sorted->Strings[i];
	 if(symbol=="#")
	  {
	  letter=list_sorted->Strings[i].LowerCase().c_str()[0];
	  if(!chars.Pos(letter))
		films->Add(list_sorted->Strings[i]);
	  }
	 else
	  if(name.LowerCase().c_str()[0]==symbol.LowerCase().c_str()[0])
		films->Add(list_sorted->Strings[i]);
   }
  if(films->Count!=0)//Если фильмы есть
  {
   Alphabet[index]=new TLabel*[films->Count];//Создание массива надписей с названиями с к-ством films->Count
   for(int i=0;i<films->Count;i++)
   {
	Alphabet[index][i]=new TLabel(current);
	Alphabet[index][i]->Parent=current;
	Alphabet[index][i]->Name="Symbol"+IntToStr(index+1)+"_"+IntToStr(i+1);//Symbol1_4(1 категория_4 надпись)
	Alphabet[index][i]->Caption=films->Strings[i];
	Alphabet[index][i]->Constraints->MinWidth=207;Alphabet[index][i]->Constraints->MaxWidth=207;
	Alphabet[index][i]->Font->Name="Tahoma";Alphabet[index][i]->Font->Size=10;
	Alphabet[index][i]->Font->Style=TFontStyles()<<fsBold;
	Alphabet[index][i]->WordWrap=true;
	Alphabet[index][i]->Left=3;Alphabet[index][i]->Top=height+3;//+3 - отступ
	Alphabet[index][i]->Cursor=(TCursor)2;
	Alphabet[index][i]->Tag=current->Tag;
	Alphabet[index][i]->OnMouseEnter=LabelMouseEnter;Alphabet[index][i]->OnMouseLeave=LabelMouseLeave;
	Alphabet[index][i]->OnClick=LabelClick;
	height+=Alphabet[index][i]->Height+2;//+3 - отступ между строк
   }
   current->Hint=films->Count;//К-ство фильмов
   current->Height=height+33;//30+3, где 30-высота названия панели, 3-отступ от начала панели
  }
  else current->Collapsed=true;
  delete list_sorted;list_sorted=NULL;
  delete films;films=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CategoryPanelCollapse(TObject *Sender)
{
  TCategoryPanel* current=static_cast<TCategoryPanel*>(Sender);
  if(current->Hint!=0)//Если фильмы есть
  {
   for (int i=0;i<StrToInt(current->Hint);i++)
	{delete Alphabet[current->Tag][i];Alphabet[current->Tag][i]=NULL;}
   delete Alphabet[current->Tag];Alphabet[current->Tag]=NULL;
   current->Hint=0;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabelClick(TObject *Sender)
{
  TLabel* current=static_cast<TLabel*>(Sender);
  Form20->Close();
  Form20->Image1->Picture->Assign(NULL);
  if(currentgroup!="MainGroup")
	 Form1->MainGroupClick(Form1);
  if(currentgroup=="MainGroup")
	  {Label13Click(Form1);Category(RadioButton3,type1,"All");}
  ListBox1->ItemIndex=ListBox1->Items->IndexOf(current->Caption);
  ListBox1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabelMouseEnter(TObject *Sender)
{
  TLabel* current=static_cast<TLabel*>(Sender);
  CategoryPanelGroup1->SetFocus();
  current->Font->Color=(TColor)RGB(200,7,80);
  current->Font->Style= TFontStyles()<<fsUnderline<<fsBold;
  current->Font->Name="Tahoma";current->Font->Size=10;
  //************Информация про фильм
  int index=list->IndexOf(current->Caption);
  AnsiString namefilm=current->Caption;
  AccessToForbiddenChar(namefilm);
  Form20->Image1->Picture->LoadFromFile("Data/Image/"+namefilm+".jpg");
  Form20->Memo1->Lines->LoadFromFile("Data/Plot/"+namefilm+".dat");
  Form20->Label1->Caption=originalname->Strings[index];
  Form20->Label2->Caption=genre->Strings[index];
  Form20->Label3->Caption=country->Strings[index];
  Form20->Label4->Caption=year->Strings[index];
  ConvertTime(duration->Strings[index],Form20->Label5);
  ShowStars(Form20,rating,index);
  //if(type->Strings[index]=="Movie")Form2->Label6->Caption="Фильм";
  //else Form2->Label6->Caption="Сериал";

  //************Параметры формы
  Form20->Country->Top=Form20->Label2->Top+Form20->Label2->Height+5;Form20->Label3->Top=Form20->Country->Top;
  Form20->Year->Top=Form20->Label3->Top+Form20->Label3->Height+5;Form20->Label4->Top=Form20->Year->Top;
  Form20->Time->Top=Form20->Year->Top+Form20->Year->Height+5;Form20->Label5->Top=Form20->Time->Top;
  Form20->Height=Form20->Time->Top+Form20->Time->Height+9;//Высота зависит от положения надписи "Время:"
  Form20->Label1->Left=Form20->OrigName->Left+Form20->OrigName->Width+3;Form20->Label2->Left=Form20->Genre->Left+Form20->Genre->Width+3;
  Form20->Label3->Left=Form20->Country->Left+Form20->Country->Width+3;Form20->Label4->Left=Form20->Year->Left+Form20->Year->Width+3;
  Form20->Label5->Left=Form20->Time->Left+Form20->Time->Width+3;
  //long _Y = Mouse->CursorPos.y;
  //long _X = Mouse->CursorPos.x;
  int LabelTopPos=Top+28+18+((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(current->Tag+1)))->Top+30+current->Top+24;//+24 - панель выше categorypanelgroup
  Form20->Top=LabelTopPos;//Form2->Top=_Y;
  Form20->Left=Form1->Left+CategoryPanelGroup1->Width;
  if((Form20->Top+Form20->Height)>Screen->Height){Form20->Top=Screen->Height-Form20->Height-45;Form20->Image2->Top=LabelTopPos-Form20->Top;}
  else Form20->Image2->Top=0;

  Form20->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LabelMouseLeave(TObject *Sender)
{
  TLabel* current=static_cast<TLabel*>(Sender);
  current->Font->Color=clBlack;
  current->Font->Style= TFontStyles()>>fsUnderline<<fsBold;
  current->Font->Name="Tahoma";current->Font->Size=10;
  Form20->Close();
  Form20->Image1->Picture->Assign(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CategoryPanelGroup1MouseWheelDown(TObject *Sender, TShiftState Shift,
          TPoint &MousePos, bool &Handled)
{
  CategoryPanelGroup1->VertScrollBar->Position+=30;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CategoryPanelGroup1MouseWheelUp(TObject *Sender, TShiftState Shift,
		  TPoint &MousePos, bool &Handled)
{
  CategoryPanelGroup1->VertScrollBar->Position-=30;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExpandCollapseButtonMouseEnter(TObject *Sender)
{
  if(CategoryPanelGroup1->Width==0)ExpandCollapseButton->Picture->LoadFromFile("Soft/Buttons/ExpandArrow(light).jpg");
  else ExpandCollapseButton->Picture->LoadFromFile("Soft/Buttons/CollapseArrow(light).png");
  CategoryPanelGroup1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExpandCollapseButtonMouseLeave(TObject *Sender)
{
  if(CategoryPanelGroup1->Width==0)ExpandCollapseButton->Picture->LoadFromFile("Soft/Buttons/ExpandArrow.jpg");
  else ExpandCollapseButton->Picture->LoadFromFile("Soft/Buttons/CollapseArrow.png");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExpandAllAlphabetPanelMouseEnter(TObject *Sender)
{
  ImageMouseEnter(Image17);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExpandAllAlphabetPanelMouseLeave(TObject *Sender)
{
  ImageMouseLeave(Image17);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CollapseAllAlphabetPanelMouseEnter(TObject *Sender)
{
  ImageMouseEnter(Image18);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CollapseAllAlphabetPanelMouseLeave(TObject *Sender)
{
  ImageMouseLeave(Image18);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExpandAllAlphabetPanelClick(TObject *Sender)
{
  if(Form20->Active){Form20->Close();Form20->Image1->Picture->Assign(NULL);}
  for (int i=0;i<59;i++)
	if(((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Collapsed)
	  {
	   ((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Collapsed=false;
	   if(((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Hint==0)//Если фильмов нету, то свернуть
		 {((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Collapsed=true;CategoryPanelGroup1->Invalidate();}
	  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CollapseAllAlphabetPanelClick(TObject *Sender)
{
  if(Form20->Active){Form20->Close();Form20->Image1->Picture->Assign(NULL);}
  for (int i=0;i<59;i++)
	if(!((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Collapsed)
	  ((TCategoryPanel*)FindComponent("CategoryPanel"+IntToStr(i+1)))->Collapsed=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image17Click(TObject *Sender)
{
  ExpandAllAlphabetPanelClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image18Click(TObject *Sender)
{
  CollapseAllAlphabetPanelClick(Sender);
}
//---------------------------------------------------------------------------

AnsiString CutTemplateCommand(AnsiString command)
{
   AnsiString string="";
   for(int i=0;i<command.Length();i++)
   {
	if(command.c_str()[i]==':')
	   return string;
	string=string+command.c_str()[i];
   }
   return string;
}
//---------------------------------------------------------------------------

void PressingHotKeys(AnsiString mode)
{
  if(mode=="-")return;
  if(CutTemplateCommand(mode)=="OpenGroup")//mode.Pos("OpenGroup")
  {
	mode=mode.Delete(1,10);
	currentgroup=mode;Form1->Image12->Hint=lang->Strings[195]+" "+currentgroup;
	Form1->FilmDel->Visible=true;
	Form1->ListBox1->Items->LoadFromFile("Data/Groups/"+currentgroup+".dat");
	listcurrentgroup->Assign(Form1->ListBox1->Items);
	Form1->Label13Click(Form1);Form1->RadioButton3Click(Form1);
	Reset();Quantity();
	MessageBeep(MB_ICONASTERISK);ShowMessage(lang->Strings[195]+" "+currentgroup);
  }
  if(CutTemplateCommand(mode)=="AddToGroup"&&Form1->ListBox1->ItemIndex!=-1)//mode.Pos("AddToGroup")
  {
   mode=mode.Delete(1,11);
   AnsiString name=Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
   TStringList *current=new TStringList();
   current->LoadFromFile("Data/Groups/"+mode+".dat");
   if(current->IndexOf(name)>=0)                  //"Этот фильм уже есть в группе"
	 {MessageBeep(MB_ICONEXCLAMATION);ShowMessage(lang->Strings[312]+AnsiString(" ")+'"'+mode+'"'+"!");}
   else          //"Ви хотите добавить этот фильм в группу"
	if(MessageDlg(lang->Strings[313]+AnsiString(" ")+'"'+mode+'"'+"?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
	 {
	  current->Add(name);
	  current->SaveToFile("Data/Groups/"+mode+".dat");
	  int index=list->IndexOf(name);
	  Logs("Added to group "+mode,list->Strings[index],TypeFilm,year->Strings[index],country->Strings[index],genre->Strings[index]);
	  s=true;
	  MessageBeep(MB_ICONASTERISK);
	 }
   delete current;current=NULL;
  }
  if(CutTemplateCommand(mode)=="DeleteFromGroup"&&Form1->ListBox1->ItemIndex!=-1)//mode.Pos("DeleteFromGroup")
  {
   mode=mode.Delete(1,16);
   AnsiString name=Form1->ListBox1->Items->Strings[Form1->ListBox1->ItemIndex];
   TStringList *current=new TStringList();
   current->LoadFromFile("Data/Groups/"+mode+".dat");
   if(current->IndexOf(name)==-1)                 //"Этого фильма нету в группе"
	 {MessageBeep(MB_ICONEXCLAMATION);ShowMessage(lang->Strings[314]+AnsiString(" ")+'"'+mode+'"'+"!");}
   else           //"Ви хотите удалить этот фильм из группы"
	if(MessageDlg(lang->Strings[315]+AnsiString(" ")+'"'+mode+'"'+"?",mtConfirmation,TMsgDlgButtons()<<mbYes<<mbNo,0)==mrYes)
	 {
	   int index=current->IndexOf(name),index1=list->IndexOf(name);
	   current->Delete(index);
	   current->SaveToFile("Data/Groups/"+mode+".dat");
	   Logs("Removed from group "+mode,list->Strings[index1],TypeFilm,year->Strings[index1],country->Strings[index1],genre->Strings[index1]);
	   s=true;
	   MessageBeep(MB_ICONASTERISK);
	   if(mode==currentgroup)
		{Form1->ListBox1->Items->Delete(Form1->ListBox1->ItemIndex);listcurrentgroup->LoadFromFile("Data/Groups/"+mode+".dat");
		 Callsort();Quantity();
		 Form1->Image10Click(Form1);InfoOnFirstPage(false);Form1->Image1->Picture->Assign(NULL);
		 Form1->Image10->Visible=false;Form1->Image11->Visible=false;Form1->Image15->Visible=false;
		 }
	 }
   delete current;current=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
  if(!shadow->CheckVisible())
  {
	if(Key=='1' && Shift.Contains(ssCtrl))Label13Click(Form1);//49
	if(Key=='2' && Shift.Contains(ssCtrl))Label11Click(Form1);//50
	if(Key=='3' && Shift.Contains(ssCtrl))Label12Click(Form1);//51
	if(Key=='4' && Shift.Contains(ssCtrl))Label16Click(Form1);//52
	if(Key=='5' && Shift.Contains(ssCtrl))PressingHotKeys(TemplateCommands->Strings[0]);//53
	if(Key=='6' && Shift.Contains(ssCtrl))PressingHotKeys(TemplateCommands->Strings[1]);//54
	if(Key=='7' && Shift.Contains(ssCtrl))PressingHotKeys(TemplateCommands->Strings[2]);//55
	if(Key=='8' && Shift.Contains(ssCtrl))PressingHotKeys(TemplateCommands->Strings[3]);//56
	if(Key=='9' && Shift.Contains(ssCtrl))PressingHotKeys(TemplateCommands->Strings[4]);//57
	if(Key=='0' && Shift.Contains(ssCtrl))PressingHotKeys(TemplateCommands->Strings[5]);//48
	if(Key==char(65) && Shift.Contains(ssAlt))ExpandCollapseButtonClick(Sender);
	if(Key==char(73) && Shift.Contains(ssCtrl) && Panel3->Width!=0)ExpandAllAlphabetPanelClick(Sender);
	if(Key==char(79) && Shift.Contains(ssCtrl) && Panel3->Width!=0)CollapseAllAlphabetPanelClick(Sender);
	if(Key==char(27))Close();
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MTemplateCommandsClick(TObject *Sender)
{
  for(int i=7;i<=12;i++)
   ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Items->Assign(namegroups);
  AnsiString name;
  for(int i=1;i<=6;i++)
  {
	name=TemplateCommands->Strings[i-1];
	if(TemplateCommands->Strings[i-1]=="-")((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex=0;
	if(CutTemplateCommand(TemplateCommands->Strings[i-1])=="OpenGroup") //TemplateCommands->Strings[i-1].Pos("OpenGroup")
	{
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex=1;name=name.Delete(1,10);
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->ItemIndex=
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->Items->IndexOf(name);
	}
	if(CutTemplateCommand(TemplateCommands->Strings[i-1])=="AddToGroup")//TemplateCommands->Strings[i-1].Pos("AddToGroup")
	{
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex=2;name=name.Delete(1,11);
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->ItemIndex=
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->Items->IndexOf(name);
	}
	if(CutTemplateCommand(TemplateCommands->Strings[i-1])=="DeleteFromGroup")//TemplateCommands->Strings[i-1].Pos("DeleteFromGroup")
	{
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex=3;name=name.Delete(1,16);
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->ItemIndex=
	 ((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i+6)))->Items->IndexOf(name);
	}
  }
  for(int i=1;i<=6;i++)
   Form21->ComboBoxChange(((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i))));

  Form21->Position=poScreenCenter;
  if(Form21->ShowModal()==mrCancel)
	  return;
  if(namegroups->Count!=0)
  {
   s=true;
   int tag,index;
   for(int i=1;i<=6;i++)
   {
	tag=((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->Tag;
	index=((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(tag)))->ItemIndex;
	if(((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex==0)TemplateCommands->Strings[i-1]="-";
	if(((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex==1)TemplateCommands->Strings[i-1]="OpenGroup:"+((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(tag)))->Items->Strings[index];
	if(((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex==2)TemplateCommands->Strings[i-1]="AddToGroup:"+((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(tag)))->Items->Strings[index];
	if(((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(i)))->ItemIndex==3)TemplateCommands->Strings[i-1]="DeleteFromGroup:"+((TComboBox*)Form21->FindComponent("ComboBox"+IntToStr(tag)))->Items->Strings[index];
   }
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PanelImageMouseEnter(TObject *Sender)
{
  CategoryPanelGroup1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image3Click(TObject *Sender)//8,6,7,11
{
   //ListBox1->Items->Assign(TemplateCommands);
}
//---------------------------------------------------------------------------

//Caption=int(Edit5->Text.c_str()[0]);

void __fastcall TForm1::MNewMoviesClick(TObject *Sender)
{
	close_access=false;
	//Parsing--------------------------------------------------------
	//Cursor=crHourGlass;
	char* szPath = "Soft/Parser/Parser.exe";
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));

	bool result = false;
	if (CreateProcess(NULL, szPath, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
	{
		DWORD dwWait = WaitForSingleObject(pi.hProcess, 10000);
		if ( dwWait == WAIT_OBJECT_0 ) result = true;

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	if(result==false){ShowMessage(lang->Strings[350]);return;}//"Check your connection to the Internet and try again!"
	if(!FileExists("Soft/Parser/Movies/Movies_links.dat"))
		{ShowMessage(lang->Strings[350]);return;}
	//Cursor=(TCursor)1;
	//Adding a movies and opening the window------------------------------
	TStringList *nameOfMovie = new TStringList();
	for(int i=0;i<=2;i++)
	{								//Soft/Parser/Movies/Movie0/Movie0.txt
		nameOfMovie->LoadFromFile("Soft/Parser/Movies/Movie"+AnsiString(i)+"/Movie"+AnsiString(i)+".dat");
		((TImage*)Form22->FindComponent("MovieImage"+IntToStr(i+1)))->Picture->LoadFromFile("Soft/Parser/Movies/Movie"+AnsiString(i)+"/Image.jpg");
		((TImage*)Form22->FindComponent("MovieImage"+IntToStr(i+1)))->Hint=nameOfMovie->Strings[0];
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(i+1)))->Caption=nameOfMovie->Strings[0];
		((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(i+1)))->Hint=nameOfMovie->Strings[0];
		if(list->IndexOf(nameOfMovie->Strings[0])>=0)
		{
			((TImage*)Form22->FindComponent("MovieExistsImage"+IntToStr(i+1)))->Picture->LoadFromFile("Soft/Buttons/Apply.png");
			((TImage*)Form22->FindComponent("MovieExistsImage"+IntToStr(i+1)))->Tag=1;
			((TImage*)Form22->FindComponent("MovieImage"+IntToStr(i+1)))->Cursor=(TCursor)1;
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(i+1)))->Cursor=(TCursor)1;
		}
		else
		{
			((TImage*)Form22->FindComponent("MovieExistsImage"+IntToStr(i+1)))->Picture->Assign(NULL);
			((TImage*)Form22->FindComponent("MovieExistsImage"+IntToStr(i+1)))->Tag=0;
			((TImage*)Form22->FindComponent("MovieImage"+IntToStr(i+1)))->Cursor=(TCursor)2;
			((TLabel*)Form22->FindComponent("MovieLabel"+IntToStr(i+1)))->Cursor=(TCursor)2;
		}
	}
	delete nameOfMovie;nameOfMovie=NULL;
	Form22->Button1->Enabled=false;
	Form22->SelectedMovieImage->Visible=false;
	Form22->SelectedMovieImage->Tag=0;
	Form22->Button1->ModalResult=mrNone;
	Form22->SetCurrentLanguage(options->Strings[5],min);
	Form22->FillList(lang);
	Form2->FillList(list);                               // В случае добавления
	Form2->CheckListBox3->Items->Assign(namegroups);     //  фильма
	Form22->Position=poScreenCenter;
	if(Form22->ShowModal()==mrCancel && Form22->Button1->ModalResult==mrNone)
		{close_access=true;return;}
	//Adding the film--------------------------------------------------- 2330 - edit
	MainGroupClick(Form1);
	AnsiString namefilm;
	//--------------------------------------Сохранение названия--------------------
	list->Add(Form2->Edit1->Text);namefilm=Form2->Edit1->Text;
	AccessToForbiddenChar(namefilm);
	//--------------------------------------Сохранение жанра и страны--------------
	AnsiString movieGenre=QuantityElements(Form2->CheckListBox1),movieCountry=QuantityElements(Form2->CheckListBox2);
	genre->Add(movieGenre);country->Add(movieCountry);
	//------------------------------Сохранение продолжительности-------------------
	AnsiString number=SearchNumbers(Form2->ComboBox2->Text);
	if(StrToInt(number)<20)number="90";
	duration->Add(number);
	//--------------------------------------Сохранение сюжета----------------------
	Form2->Memo1->Lines->SaveToFile("Data/Plot/"+namefilm+".dat");
	//--------------------------------------Сохранение фото------------------------
	Form2->Image1->Picture->SaveToFile("Data/Image/"+namefilm+".jpg");
	//-----------------------------Сохранение ссылки на фильм----------------------
	link->Add(Form2->Edit2->Text);
	//-----------------------------Сохранение ссылки на трейлер фильма-------------
	trailer->Add(Form2->Edit3->Text);
	//---------------Сохранение слогана,режиссера,актёров и ориг.названия----------
	director->Add(Form2->Edit5->Text);originalname->Add(Form2->Edit7->Text);
	cast->Add(Form2->Memo2->Text);
	if(Form2->Edit6->Text=="")tagline->Add("-");
	else tagline->Add(Form2->Edit6->Text);
	//---------------Сохранение года,вида кино,к-ства сезонов,к-ства серий---------
	AnsiString years;
	if(Form2->RadioButton1->Checked==true)
	{
		TypeFilm=lang->Strings[78];
		year->Add(Form2->ComboBox1->Text);type->Add("Movie");season->Add("0");seasonfilm="0";episode->Add("0");
	}
	else
	{
		TypeFilm=lang->Strings[79];
		years=Form2->ComboBox1->Text+"-"+Form2->ComboBox3->Text;year->Add(years);
		type->Add("TV series");season->Add(Form2->Edit4->Text+":"+Form2->Edit8->Text);episode->Add("1:1");
		Form2->seasons->SaveToFile("Data/Seasons/"+namefilm+".dat");
	}
	type1->Add("All");
	//--------------------------------------Сохранение просмотра-------------------
	if(Form2->CheckBox1->Checked==true)
	   view->Add(yes);
	else
	   view->Add(not);
	//--------------------------------------Сохранение релиза-------------------
	if(Form2->CheckBox2->Checked==true)
	   release->Add(yes);
	else
	   release->Add(not);
	//-------------------------------------Сохранение рейтинга------------------
	rating->Add(Form2->Rating->Caption);
	//-------------------------------------Сохранение даты добавления------------------
	date->Add(Now().CurrentDate());
	//--------------------------------------------------------------------------
	Logs("Added",Form2->Edit1->Text,TypeFilm,year->Strings[year->Count-1],movieCountry,movieGenre);
	//-------------------------------------Добавление фильма в группы-----------
	TStringList *current=new TStringList();int index;
	for(int i=0;i<Form2->CheckListBox3->Count;i++)
		if(Form2->CheckListBox3->Checked[i]==true)
		{
			current->LoadFromFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
			current->Add(Form2->Edit1->Text);
			current->SaveToFile("Data/Groups/"+Form2->CheckListBox3->Items->Strings[i]+".dat");
			Logs("Added to group "+Form2->CheckListBox3->Items->Strings[i],Form2->Edit1->Text,TypeFilm,year->Strings[year->Count-1],movieCountry,movieGenre);
		}
	delete current;current=NULL;
	//-------------------------------------Добавление фильма в избранные-----------
	if(Form2->GetFavourite())
	{
		elect->Add(Form2->Edit1->Text);
		Logs("Added to Favorites",Form2->Edit1->Text,TypeFilm,year->Strings[year->Count-1],movieCountry,movieGenre);
	}
	//---------------------------------------------------------------------------
	Callsort();
	Quantity();
	s=true;
	ListBox1->ItemIndex=ListBox1->Items->IndexOf(Form2->Edit1->Text);ListBox1Click(Sender);
	Form2->Image1->Picture->Assign(NULL);
	UpdateAlphabetPanel(namefilm);
	close_access=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::MCinemaAfficheClick(TObject *Sender)
{
	Form23->Position=poScreenCenter;
	if(Form23->ShowModal()==mrCancel)
	  return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MMoviesAnalysisClick(TObject *Sender)
{
	/*TemperamentDeterminant temperamentDeterminant;
	std::vector<TemperamentDeterminant::GenreTypes> genreTypes;
	for (int i = 0; i < list->Count; i++)
		if (view->Strings[i] == yes)
		{
			TemperamentDeterminant::GenreTypes genreType;
			for(int j = 0; j < CheckListBox1->Count; j++)      // be cearful with genres order, it must be the same as in enum in .h file
			{
			   if(genre->Strings[i].Pos(CheckListBox1->Items->Strings[j]))
			   {
					genreType = TemperamentDeterminant::GenreTypes(j);
					genreTypes.push_back(genreType);
			   }
			}
			temperamentDeterminant.addMovieParameters(genreTypes, rating->Strings[i]/5);
			genreTypes.clear();
		}
	temperamentDeterminant.saveMoviesParametersToScv("EstimatedMovies.csv");
	temperamentDeterminant.clear();*/
	ShowMessage("Аналіз відеоконтенту виконано!");
	ListBox1->Items->LoadFromFile("Movies.dat");
	// Execute Python code
}
//---------------------------------------------------------------------------


