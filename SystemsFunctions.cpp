#include <vcl.h>
//---------------------------------------------------------------------------
int  CopyFiles( AnsiString slSourceDir, AnsiString slTargetDir, bool toCopy = true  )
{
	SHFILEOPSTRUCT sh;
	sh.fFlags = FOF_NOCONFIRMATION | FOF_SILENT |  FOF_FILESONLY;
	sh.wFunc = FO_COPY;
	sh.pFrom =  slSourceDir.c_str();
	sh.pTo = slTargetDir.c_str();
	sh.hNameMappings =  NULL;
	sh.lpszProgressTitle = NULL;
	return SHFileOperation ( &sh  );
}
int  MoveFiles( AnsiString slSourceDir, AnsiString slTargetDir, bool toCopy = true  )
{
	SHFILEOPSTRUCT sh;
	sh.fFlags = FOF_NOCONFIRMATION | FOF_SILENT |  FOF_FILESONLY;
	sh.wFunc = FO_MOVE;
	sh.pFrom =  slSourceDir.c_str();
	sh.pTo = slTargetDir.c_str();
	sh.hNameMappings =  NULL;
	sh.lpszProgressTitle = NULL;
	return SHFileOperation ( &sh  );
}
//---------------------------------------------------------------------------

int  DeleteFiles( AnsiString slSourceDir)
{
	SHFILEOPSTRUCT sh;
	sh.fFlags = FOF_NOCONFIRMATION | FOF_SILENT |  FOF_FILESONLY;
	sh.wFunc = FO_DELETE;
	sh.pFrom =  slSourceDir.c_str();
	sh.hNameMappings =  NULL;
	sh.lpszProgressTitle = NULL;
	return SHFileOperation ( &sh  );
}
//---------------------------------------------------------------------------

bool DeleteDir(AnsiString DirName)
{
TSearchRec sr;
if (DirName.Length())
 {
 if (!FindFirst(DirName+"\\*.*",faAnyFile,sr))
 do
  {
  if (!(sr.Name=="." || sr.Name==".."))// это удалять не надо
   if (((sr.Attr & faDirectory) == faDirectory ) ||
   (sr.Attr == faDirectory))// найдена папка
	{
	FileSetAttr(DirName+"\\"+sr.Name, faDirectory );// сброс всяких read-only
	DeleteDir(DirName+"\\"+sr.Name);//рекурсивно удаляем содержимое
	RemoveDir(DirName + "\\"+sr.Name);// удаляем теперь уже пустую папку
	}
	else// иначе найден файл
	{
	FileSetAttr(DirName+"\\"+sr.Name, 0);// сброс всяких read-only
	DeleteFile(DirName+"\\"+sr.Name);// удаляем файл
	}
  }
 while (!FindNext(sr));// ищем опять, пока не найдем все
 FindClose(sr);
 }
RemoveDir(DirName);
return true;
}

