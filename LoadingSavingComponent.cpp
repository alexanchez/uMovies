#include <vcl.h>
namespace FrameProperties
{
 void SaveComponent(TComponent* Component,String FileName)
  {
  TMemoryStream *Ms = new TMemoryStream();
  Ms->WriteComponent(Component);
  TFileStream *Fs = new  TFileStream(FileName,fmCreate);
  Ms->Position = 0;
  ObjectBinaryToText(Ms,Fs);
  delete Fs,Ms;
  }

 void LoadComponent(TComponent* Component,String FileName)
  {
  TFileStream *Fs = new TFileStream(FileName,fmOpenRead);
  TMemoryStream *Ms = new TMemoryStream();
  ObjectTextToBinary(Fs,Ms);
  Ms->Position = 0;
  Ms->ReadComponent(Component);
  delete Fs,Ms;
  }
}
//---------------------------------------------------------------------------

void SetLabelsFont(TForm *Form,AnsiString WindowStyle)
{
  TLabel *L1=((TLabel*)Form->FindComponent("OrigName")),*L2=((TLabel*)Form->FindComponent("Genre")),
		 *L3=((TLabel*)Form->FindComponent("Country")),*L4=((TLabel*)Form->FindComponent("Year")),
		 *L5=((TLabel*)Form->FindComponent("Time"));
  FrameProperties::LoadComponent(L1,"Soft/AlphabetPanel/"+WindowStyle+"/OrigName.dat");
  FrameProperties::LoadComponent(L2,"Soft/AlphabetPanel/"+WindowStyle+"/Genre.dat");
  FrameProperties::LoadComponent(L3,"Soft/AlphabetPanel/"+WindowStyle+"/Country.dat");
  FrameProperties::LoadComponent(L4,"Soft/AlphabetPanel/"+WindowStyle+"/Year.dat");
  FrameProperties::LoadComponent(L5,"Soft/AlphabetPanel/"+WindowStyle+"/Time.dat");
}
//---------------------------------------------------------------------------
