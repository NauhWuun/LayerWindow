//---------------------------------------------------------------------------

#ifndef tt2H
#define tt2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "pngimage.hpp"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TImage *img1;
    TImage *img2;
private:	// User declarations
public:		// User declarations
    __fastcall TForm2(TComponent* Owner);

    void __fastcall CreateParams(TCreateParams &Params);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
