//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit17.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Chart"
#pragma link "Series"
#pragma link "TeEngine"
#pragma link "TeeProcs"
#pragma link "TeCanvas"
#pragma link "ZipForge"
#pragma link "TeeEdiGrad"
#pragma resource "*.dfm"
#include "SystemsFunctions.cpp"
TForm17 *Form17;
int CurrentIndex;
//---------------------------------------------------------------------------
__fastcall TForm17::TForm17(TComponent* Owner)
	: TForm(Owner)
{
  ComboBox1->Left=925;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::SeriesMouseEnter(TObject *Sender)
{
  TChartSeries *current=static_cast<TChartSeries *>(Sender);
  CurrentIndex=current->GetCursorValueIndex();
  if(current->Tag!=3&&current->Tag!=5)Form17->Chart1->Title->Text->Text="                               "+current->XLabel[CurrentIndex]+" – "+current->XValue[CurrentIndex];
  else Form17->Chart1->Title->Text->Text="                               "+current->XLabel[CurrentIndex]+" – "+current->YValue[CurrentIndex];
  switch(current->Tag)
  {
   case 1:current->ValueColor[CurrentIndex]=(TColor)RGB(248,234,105);break;//255,155,155
   case 2:current->ValueColor[CurrentIndex]=(TColor)RGB(128,255,0);break;
   case 3:current->ValueColor[CurrentIndex]=(TColor)RGB(254,159,1);break;
   case 4:current->ValueColor[CurrentIndex]=(TColor)RGB(0,128,255);break;//128,128,255
   case 5:current->ValueColor[CurrentIndex]=(TColor)RGB(255,255,0);break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm17::SeriesMouseLeave(TObject *Sender)
{
  TChartSeries *current=static_cast<TChartSeries *>(Sender);
  Chart1->Title->Text->Text=" ";
  switch(current->Tag)
  {
   case 1:current->ValueColor[CurrentIndex]=clRed;break;
   case 2:current->ValueColor[CurrentIndex]=clGreen;break;
   case 3:current->ValueColor[CurrentIndex]=clYellow;break;
   case 4:current->ValueColor[CurrentIndex]=clBlue;break;
   case 5:current->ValueColor[CurrentIndex]=(TColor)RGB(0,255,128);break;
  }
}
//---------------------------------------------------------------------------

void SeriesActive(bool v1,bool v2,bool v3,bool v4,bool v5)
{
  Form17->Series1->Active=v1;Form17->Series2->Active=v2;
  Form17->Series3->Active=v3;Form17->Series4->Active=v4;
  Form17->Series5->Active=v5;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::FormCreate(TObject *Sender)
{
   for (int i=1;i<=5;i++)
	{
	 ((TChartSeries*)FindComponent("Series"+IntToStr(i)))->OnMouseEnter=SeriesMouseEnter;
	 ((TChartSeries*)FindComponent("Series"+IntToStr(i)))->OnMouseLeave=SeriesMouseLeave;
	}
   CategoryButtons1->SelectedItem = CategoryButtons1->GetCategoryAt(0,0);
   DateTimePicker1->Date=TDateTime::CurrentDate()-366;
   DateTimePicker2->Date=TDateTime::CurrentDate();
   DateTimePicker1->MaxDate=Now().CurrentDate();
   DateTimePicker2->MaxDate=Now().CurrentDate();
}
//---------------------------------------------------------------------------

void __fastcall TForm17::FormClose(TObject *Sender, TCloseAction &Action)
{
  if(FileExists("Data/Backup/Data/Options.ini")==true) //{DeleteFile("Data/Backup/Data/Logs.txt");RemoveDir("Data/Backup/Data");}
   {DeleteFile("Data/Backup/Data/Options.ini");DeleteDir("Data/Backup/Data");}
  Chart1->Align=alNone;Chart1->OriginalCursor=(TCursor)4;ComboBox1->Visible=false;
  Series1->Clear();Series2->Clear();Series3->Clear();Series4->Clear();Series5->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm17::PageControl1Change(TObject *Sender)
{
   if(PageControl1->ActivePage==TabSheet1||PageControl1->ActivePage==TabSheet2)Form17->Height=666;
   else Form17->Height=330;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::Chart1Click(TObject *Sender)
{
  if(Chart1->Align==alNone){Chart1->Align=alClient;Chart1->OriginalCursor=(TCursor)5;ComboBox1->Visible=true;}
  else {Chart1->Align=alNone;Chart1->OriginalCursor=(TCursor)4;ComboBox1->Visible=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm17::RadioButton1Click(TObject *Sender)
{
  SeriesActive(true,false,false,false,false);
  Chart1->Legend->Alignment=laRight;
  Chart1->LeftAxis->Grid->Visible=false;Chart1->BottomAxis->Grid->Visible=true;
  ComboBox1->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::RadioButton2Click(TObject *Sender)
{
  SeriesActive(false,true,false,false,false);
  Chart1->Legend->Alignment=laRight;
  Chart1->LeftAxis->Grid->Visible=false;Chart1->BottomAxis->Grid->Visible=true;
  ComboBox1->ItemIndex=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::RadioButton3Click(TObject *Sender)
{
  SeriesActive(false,false,true,false,false);
  Chart1->Legend->Alignment=laTop;
  Chart1->LeftAxis->Grid->Visible=true;Chart1->BottomAxis->Grid->Visible=false;
  ComboBox1->ItemIndex=2;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::RadioButton4Click(TObject *Sender)
{
  SeriesActive(false,false,false,true,false);
  Chart1->Legend->Alignment=laRight;
  Chart1->LeftAxis->Grid->Visible=false;Chart1->BottomAxis->Grid->Visible=true;
  ComboBox1->ItemIndex=3;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::RadioButton5Click(TObject *Sender)
{
  SeriesActive(false,false,false,false,true);
  Chart1->Legend->Alignment=laTop;
  Chart1->LeftAxis->Grid->Visible=true;Chart1->BottomAxis->Grid->Visible=false;
  ComboBox1->ItemIndex=4;
}
//---------------------------------------------------------------------------


void __fastcall TForm17::RadioButton6Click(TObject *Sender)
{
  Chart1->Legend->TextStyle=ltsLeftValue;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::RadioButton7Click(TObject *Sender)
{
  Chart1->Legend->TextStyle=ltsLeftPercent;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::ListBox1Click(TObject *Sender)
{
  if(ListBox1->ItemIndex!=-1)
  {
  AnsiString name=ListBox1->Items->Strings[ListBox1->ItemIndex];
  TStringList *group=new TStringList();group->LoadFromFile("Data/Groups/"+name+".dat");
  Label18->Caption=QuantityFilms+IntToStr(group->Count)+" ";
  delete group;group=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm17::ListBox3Click(TObject *Sender)
{
  if(ListBox3->ItemIndex!=-1)
  {
  AnsiString name=ListBox3->Items->Strings[ListBox3->ItemIndex];
  ZipForge1->FileName ="Catalogs\\"+name+".cof";
  ZipForge1->OpenArchive(fmOpenRead);
  ZipForge1->BaseDir = "Data/Backup";
  ZipForge1->ExtractFiles("*Options.ini*");
  ZipForge1->CloseArchive();
  TStringList *DateOfCreation=new TStringList();DateOfCreation->LoadFromFile("Data/Backup/Data/Options.ini");
  DateOfCreation->Strings[10]=DateOfCreation->Strings[10].Delete(1,17);
  Label16->Caption=DateofCreation+"\n"+DateOfCreation->Strings[10]+" ";//"Дата создания: \n"
  delete DateOfCreation;DateOfCreation=NULL;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm17::ComboBox1Change(TObject *Sender)
{
   if(ComboBox1->ItemIndex==0)RadioButton1->Checked=true;
   if(ComboBox1->ItemIndex==1)RadioButton2->Checked=true;
   if(ComboBox1->ItemIndex==2)RadioButton3->Checked=true;
   if(ComboBox1->ItemIndex==3)RadioButton4->Checked=true;
   if(ComboBox1->ItemIndex==4)RadioButton5->Checked=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::SavingMouseEnter(TObject *Sender)
{
  Saving->Font->Color=clBlue;PageControl1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm17::SavingMouseLeave(TObject *Sender)
{
  Saving->Font->Color=clBlack;PageControl1->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm17::SavingClick(TObject *Sender)
{
  int index=PageControl1->ActivePageIndex;AnsiString align;
  if(Chart1->Align==alNone)align="alNone";
  else align="alClient";

  AnsiString time=Now();
  for(int i=0;i<time.Length();i++)
   if(time.c_str()[i]==':')
	  time.c_str()[i]=';';
  AnsiString way="Statistics/"+time;
  MkDir(way);

  TCanvas* dtCanvas = new TCanvas;
  dtCanvas->Handle = GetDC(0);
  Graphics::TBitmap*bitmap = new Graphics::TBitmap;
  TJPEGImage *tJpg=new TJPEGImage;
  TRect src = BoundsRect;
  TRect dest = Rect(0, 0, Width, Height);

  if(Form17->Height!=666)Form17->Height=666;                                    //****
  Chart1->Align=alClient;
  RadioButton1Click(Sender);Chart1->SaveToBitmapFile("Statistics/"+time+"/Chart_Genre.bmp");
  RadioButton2Click(Sender);Chart1->SaveToBitmapFile("Statistics/"+time+"/Chart_Country.bmp");
  RadioButton3Click(Sender);Chart1->SaveToBitmapFile("Statistics/"+time+"/Chart_Year.bmp");
  RadioButton4Click(Sender);Chart1->SaveToBitmapFile("Statistics/"+time+"/Chart_Duration.bmp");
  RadioButton5Click(Sender);Chart1->SaveToBitmapFile("Statistics/"+time+"/Chart_Alphabet.bmp");
  Chart1->Align=alNone;
  PageControl1->Refresh();

  bitmap->Width = Width;bitmap->Height = Height;
  PageControl1->ActivePageIndex=2;
  bitmap->Canvas->CopyRect(dest, dtCanvas, src);
  tJpg->Assign(bitmap);tJpg->SaveToFile("Statistics/"+time+"/GeneralInfo.jpg");
  PageControl1->ActivePageIndex=0;
  bitmap->Canvas->CopyRect(Rect(0, 0, Width, Height), dtCanvas, Rect(Form17->Left, Form17->Top, Form17->Left+Width, Form17->Top+Height));
  tJpg->Assign(bitmap);tJpg->SaveToFile("Statistics/"+time+"/Catalog.jpg");
  bitmap->Width = 194;bitmap->Height = 377;
  bitmap->Canvas->CopyRect(Rect(0, 0, 194, 377),Canvas,Rect(331, 18+20, 525, 390+25));
  tJpg->Assign(bitmap);tJpg->SaveToFile("Statistics/"+time+"/Rating.jpg");
  delete bitmap;
  delete tJpg;
  delete dtCanvas;

  ListBox1->Items->SaveToFile("Statistics/"+time+"/Groups.txt");
  ListBox2->Items->LoadFromFile("Data/Logs.txt");
  ListBox2->Items->SaveToFile("Statistics/"+time+"/Logs.txt");
  EventsBoxChange(Sender);
  ListBox3->Items->SaveToFile("Statistics/"+time+"/Catalogs.txt");
  ListBox4->Items->SaveToFile("Statistics/"+time+"/Films from other catalogs.txt");
  ListBox5->Items->SaveToFile("Statistics/"+time+"/Own filters.txt");

  TStringList *info=new TStringList();
  for(int i=1;i<=14;i++)
	 info->Add(((TLabel*)FindComponent("Label"+IntToStr(i)))->Caption);
  info->Add(Label17->Caption);
  info->SaveToFile("Statistics/"+time+"/Statistics.txt");
  delete info;info=NULL;

  if(align=="alNone")Chart1->Align=alNone;
  if(align=="alClient")Chart1->Align=alClient;
  if(index==0 && PageControl1->ActivePageIndex!=0)PageControl1->ActivePageIndex=0;
  if(index==1)PageControl1->ActivePageIndex=1;
  if(index==2)PageControl1->ActivePageIndex=2;
  if(RadioButton1->Checked==true)RadioButton1Click(Sender);
  if(RadioButton2->Checked==true)RadioButton2Click(Sender);
  if(RadioButton3->Checked==true)RadioButton3Click(Sender);
  if(RadioButton4->Checked==true)RadioButton4Click(Sender);
  if(RadioButton5->Checked==true)RadioButton5Click(Sender);
  PageControl1Change(Sender);
  Saving->Font->Color=clBlack;
  MessageDlg(Saved,mtInformation,TMsgDlgButtons()<<mbOK,0); //Saved-"Статистика сохранена!"
}
//---------------------------------------------------------------------------

//Saving->Left=ClientWidth-Saving->Width-98;

bool SetDate(AnsiString date)
{
  if(Form17->DatePicker1->Checked)
  {
	if(Form17->CategoryButtons1->SelectedItem->Index==0||Form17->CategoryButtons1->SelectedItem->Index==10)return true;
	else
	{
	  TDateTime Start = TDateTime(date);
	  TDateTime End   = TDateTime::CurrentDate();
	  unsigned short YearStart, MonthStart, DayStart,YearEnd,MonthEnd,DayEnd;
	  Start.DecodeDate(&YearStart, &MonthStart, &DayStart);
	  End.DecodeDate(&YearEnd, &MonthEnd, &DayEnd);
	  int Difference,YearDifference;
	  if(Form17->CategoryButtons1->SelectedItem->Index==1||Form17->CategoryButtons1->SelectedItem->Index==2||
		 Form17->CategoryButtons1->SelectedItem->Index==3)												//Дни
			Difference = End - Start;
	  else                                                                                              //Месяца
	  {
	   Difference = MonthEnd-MonthStart;YearDifference=YearEnd-YearStart;
	   if(Difference<0){Difference=12-abs(Difference);if(YearDifference>1)Difference+=12*YearDifference;}
	   else if(Difference>=0&&YearDifference!=0)Difference+=12*YearDifference;
	  }
	  switch (Form17->CategoryButtons1->SelectedItem->Index)
	  {
		case 1:{if(Difference==0)return true;break;}
		case 2:{if(Difference==0||Difference==1)return true;break;}
		case 3:{if(Difference>=0&&Difference<=6)return true;break;}
		case 4:{if(Difference==0)return true;break;}
		case 5:{if(Difference<=1)return true;break;}
		case 6:{if(Difference<=2)return true;break;}
		case 7:{if(Difference<=3)return true;break;}
		case 8:{if(Difference<=4)return true;break;}
		case 9:{if(Difference<=5)return true;break;}
	  }
	}
  }
  else
  {
	if(StrToDate(date)>=Form17->DateTimePicker1->Date &&
	   StrToDate(date)<=Form17->DateTimePicker2->Date)
	   return true;
  }
  return false;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::EventsBoxChange(TObject *Sender)
{
  TStringList *logs=new TStringList();
  logs->LoadFromFile("Data/Logs.temp");
  ListBox2->Items->Clear();
  if(EventsBox->ItemIndex==0)
  {
	if(DatePicker1->Checked)
	{
	  for(int i=0;i<logs->Count;i++)
		if(!SetDate(logs->Strings[i].SubString(2,10)))
		   {logs->Delete(i);i--;}
		else
		  if(Edit5->Text!=""&&Edit5->Text!=Search)
			if(!logs->Strings[i].LowerCase().Pos(Edit5->Text.LowerCase())>0)
			   {logs->Delete(i);i--;}
	  ListBox2->Items=logs;
	}
	else
	  for(int i=0;i<logs->Count;i++)
		if(SetDate(logs->Strings[i].SubString(2,10)))
		{
		  if(Edit5->Text!=""&&Edit5->Text!=Search)
			if(logs->Strings[i].LowerCase().Pos(Edit5->Text.LowerCase())>0)
			   ListBox2->Items->Add(logs->Strings[i]);
		  if(Edit5->Text==""||Edit5->Text==Search)
			   ListBox2->Items->Add(logs->Strings[i]);
		}
  }
  else
  {
	const char *actions[14] = {"(Added)","Edited","(Removed)","Added to Favorites","Removed from Favorites",
						   "Added group","Renamed group","Removed group","Added to group","Removed from group",
						   "Created catalog","Added catalog","Renamed catalog","Removed catalog"};
	for(int i=0;i<logs->Count;i++)
		if(logs->Strings[i].Pos(actions[EventsBox->ItemIndex-1]) && SetDate(logs->Strings[i].SubString(2,10)))
		{
		  if(Edit5->Text!=""&&Edit5->Text!=Search)
			if(logs->Strings[i].LowerCase().Pos(Edit5->Text.LowerCase())>0)
			   ListBox2->Items->Add(logs->Strings[i]);
		  if(Edit5->Text==""||Edit5->Text==Search)
			   ListBox2->Items->Add(logs->Strings[i]);
		}
  }
  EventsQuantity->Caption=EventNumbers+AnsiString(ListBox2->Count);//"Количество событий: "
  delete logs;logs=NULL;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::DatePicker1Click(TObject *Sender)
{
  CategoryButtons1->Enabled=true;
  DateTimePicker1->Enabled=false;
  DateTimePicker2->Enabled=false;
  EventsBoxChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm17::DatePicker2Click(TObject *Sender)
{
  CategoryButtons1->Enabled=false;
  DateTimePicker1->Enabled=true;
  DateTimePicker2->Enabled=true;
  EventsBoxChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm17::DateTimePicker1Click(TObject *Sender)
{
  DateTimePicker1->MaxDate=Now().CurrentDate();
  DateTimePicker2->MaxDate=Now().CurrentDate();
}
//---------------------------------------------------------------------------

void __fastcall TForm17::Edit5Change(TObject *Sender)
{
  /*
  if(Edit5->Text=="")
	{Image6->Visible=false;EventsBoxChange(Sender);}
  if(Edit5->Text!=""&&Edit5->Text!=Search)
	{Image6->Visible=true;
	 EventsBoxChange(Sender);
	 for(int i=0;i<ListBox2->Items->Count;i++)
	   if(!ListBox2->Items->Strings[i].LowerCase().Pos(Edit5->Text.LowerCase())>0)
		   {ListBox2->Items->Delete(i);i--;}
	}
  EventsQuantity->Caption=EventNumbers+AnsiString(ListBox2->Count);//"Количество событий: "
  */
  if(Edit5->Text=="")Image6->Visible=false;
  if(Edit5->Text!=""&&Edit5->Text!=Search)Image6->Visible=true;
  EventsBoxChange(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm17::Edit5Enter(TObject *Sender)
{
  if(Edit5->Text==Search)
	 Edit5->Text="";
   Edit5->Font->Color=clBlack;
}
//---------------------------------------------------------------------------

void __fastcall TForm17::Edit5Exit(TObject *Sender)
{
  if(Edit5->Text=="")
	{Edit5->Text=Search;Edit5->Font->Color=clBtnShadow;Image6->Visible=false;}
}
//---------------------------------------------------------------------------

void __fastcall TForm17::Image6Click(TObject *Sender)
{
  if(Edit5->Focused()) Edit5->Clear();
  else {Edit5->Text=Search;Edit5->Font->Color=clBtnShadow;}
  Image6->Visible=false;
}
//---------------------------------------------------------------------------
//Movie - lang->Strings[78]
//TV series - lang->Strings[79]
