//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit20.h"
#include "LoadingSavingComponent.cpp" - загрузка/сохранение параметров компонентов
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm20 *Form20;
//---------------------------------------------------------------------------
__fastcall TForm20::TForm20(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm20::FormActivate(TObject *Sender)
{
  Memo1->Enabled=false;Memo1->Enabled=true;
}
//---------------------------------------------------------------------------
