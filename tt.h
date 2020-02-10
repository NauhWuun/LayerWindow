//---------------------------------------------------------------------------

#ifndef ttH
#define ttH

//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <windows.h>
#include <AppEvnts.hpp>
#include <algorithm>
using std::min; 
using std::max; 
#include <gdiplus.h>
using namespace Gdiplus;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    void __fastcall FormShow(TObject *Sender);
    void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations

    ULONG_PTR m_GdiplusToken; 
    Gdiplus::GdiplusStartupInput m_GdiplusStartupInput;
    int __fastcall SetTransparent(LPWSTR lpSkinFile, int nTran, int totalNum); 

    BLENDFUNCTION m_Blend; 
    //HDC    m_hdcMemory;

    BOOL __fastcall FindDesktopHandle(HWND IN OUT &hHandle); 
    int num;
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
    __fastcall ~TForm1(void);

    int   iX0,iY0; //   User   declarations
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
