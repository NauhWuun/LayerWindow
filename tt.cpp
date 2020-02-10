//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "tt2.h"
#include "tt.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    num = 1; 
    BorderStyle = bsNone;

    GdiplusStartup(&m_GdiplusToken, &m_GdiplusStartupInput, NULL); 

    m_Blend.BlendOp = 0;                
    m_Blend.BlendFlags = 0;             
    m_Blend.AlphaFormat = 1;            
    m_Blend.SourceConstantAlpha = 255; // AC_SRC_ALPHA
}
//--------------------------------------------------------------------------- 

__fastcall TForm1::~TForm1(void) 
{ 
    GdiplusShutdown(m_GdiplusToken); // Close GDI+ 
} 
//--------------------------------------------------------------------------- 
int __fastcall TForm1::SetTransparent(LPWSTR lpSkinFile, int nTran, int totalNum) 
{ 
    Gdiplus::Image *m_Image = Gdiplus::Image::FromFile(lpSkinFile); 

    Width = m_Image->GetWidth(); 
    Height = m_Image->GetHeight(); 
    
    HWND  hWnd23      =   GetDesktopWindow(); 
    HDC   hdcScreen   =   GetWindowDC(hWnd23); 
    //HDC hdcScreen   =   ::GetDC   (Handle);//GetDC()-> m_hDC; 
    HDC   m_hdcMemory =   CreateCompatibleDC(hdcScreen); 

    BYTE  *   pBits; 
    BITMAPINFOHEADER bmih; 
    ZeroMemory(&bmih, sizeof(BITMAPINFO)); 

    bmih.biSize                    =   sizeof(BITMAPINFOHEADER); 
    bmih.biWidth                   =   m_Image->GetWidth(); 
    bmih.biHeight                  =   totalNum*(m_Image->GetHeight()+0); 
    bmih.biPlanes                  =   1 ; 
    bmih.biBitCount                =   32;           
    bmih.biCompression             =   BI_RGB; 
    bmih.biSizeImage               =   0 ; 
    bmih.biXPelsPerMeter           =   0 ; 
    bmih.biYPelsPerMeter           =   0 ; 
    bmih.biClrUsed                 =   0 ; 
    bmih.biClrImportant            =   0 ; 

    HBITMAP hBitMap = CreateDIBSection(NULL, (BITMAPINFO   *)&bmih, 0, (VOID**)&pBits, NULL, 0); 
    SelectObject(m_hdcMemory,hBitMap); 

    if (nTran <0  || nTran >100) 
        nTran = 100; 
    m_Blend.SourceConstantAlpha = int(nTran * 2.55);

    RECT rct; 
    GetWindowRect(Handle, &rct); 

    POINT ptWinPos = {rct.left, rct.top}; 
    Gdiplus::Graphics graph(m_hdcMemory); 

    // 63 63 72 75 6E 2E 63 6F 6D 

    int tmpLeft = 0; 
    int tmpTop = 0; 
    for (int n = 0; n < totalNum; n++) 
    { 
        graph.DrawImage(m_Image, tmpLeft, tmpTop, m_Image->GetWidth(), m_Image->GetHeight()); 

        Gdiplus::Font font(L"����_GB2312",   12,   FontStyleBold ,   UnitPoint    );
        PointF pointF(20,   tmpTop+3);
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 0, 0, 0)); 
        Gdiplus::StringFormat stringFormatTmp(StringFormatFlagsNoFontFallback); 

        tmpTop += m_Image->GetHeight()+0; 
    } 

    SIZE sizeWindow = {m_Image->GetWidth(), tmpTop-0}; 
    POINT ptSrc = {0, 0}; 

    BOOL bRet = UpdateLayeredWindow(Handle, hdcScreen, &ptWinPos, &sizeWindow, m_hdcMemory, &ptSrc, 0, &m_Blend, ULW_ALPHA); 
    int a7 = GetLastError() ; 

    graph.ReleaseHDC(m_hdcMemory); 
    ReleaseDC(0, hdcScreen); 
    hdcScreen = NULL; 

    DeleteObject(hBitMap); 
    DeleteDC(m_hdcMemory); 
    m_hdcMemory = NULL; 

    delete m_Image; 
    m_Image = NULL; 
    return bRet;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
    Form2 = new TForm2(NULL);
    Form2->Show();

    SetWindowLong(Handle, GWL_STYLE, 0x96000000);
    SetWindowLong(Handle, GWL_EXSTYLE, 0x00080080);
    SetTransparent(WideString("ip_search.png"), 250, 1);
     
    SetWindowPos(Handle, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOMOVE  | SWP_NOSIZE);     
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
/*
    if(Button == mbLeft) 
    { 
        ReleaseCapture(); 
        Perform(WM_SYSCOMMAND, SC_MOVE  | HTCAPTION, 0); 
    }
*/
    iX0   =   X;
    iY0   =   Y;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    SetProcessWorkingSetSize(GetCurrentProcess(), -1, -1);    
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    int   iDeltaX,   iDeltaY;
    if (Shift.Contains(ssLeft))
    {
          iDeltaX = X - iX0;
          iDeltaY = Y - iY0;
          
          if (iDeltaY)
          {
              Form1->Left += iDeltaX;   
              Form2->Left += iDeltaX;
          }
          if (iDeltaY)   
          {
              Form1->Top += iDeltaY;
              Form2->Top += iDeltaY;
          }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    delete Form2;    
}
//---------------------------------------------------------------------------

