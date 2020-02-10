//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop


#include "tt2.h"
#include "tt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "pngimage"
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void   __fastcall TForm2::CreateParams(TCreateParams &Params)
{
    TForm::CreateParams(Params);
    Params.Style = (Params.Style | WS_POPUP) & (~ WS_DLGFRAME);
}