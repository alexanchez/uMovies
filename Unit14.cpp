//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit14.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm14 *Form14;
//---------------------------------------------------------------------------
__fastcall TForm14::TForm14(TComponent* Owner)
	: TForm(Owner)
{
}
//--------------------------------------------------------------------------- //��� ��������� ListBox��� �� Form13

void __fastcall TForm14::FormMouseWheel(TObject *Sender, TShiftState Shift, int WheelDelta,
          TPoint &MousePos, bool &Handled)
{
  Close();
}
//---------------------------------------------------------------------------//��� ������� ������� ������ �� Form13


void __fastcall TForm14::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
  Close();
}
//---------------------------------------------------------------------------




