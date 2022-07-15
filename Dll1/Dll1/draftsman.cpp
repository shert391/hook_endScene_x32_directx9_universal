#include "includes.h"

ID3DXFont* m_font = 0;
D3DRECT rec = { 10, 10, 120, 30 };
RECT fontRect = { 10, 15, 120, 120 };
D3DCOLOR fontColor = D3DCOLOR_XRGB(1, 1, 1);
D3DCOLOR bkgColor = D3DCOLOR_XRGB(164, 39, 227);

void draftsman::Paint(LPDIRECT3DDEVICE9 pDevise)
{
    pDevise->Clear(1, &rec, D3DCLEAR_TARGET, bkgColor, 1.0f, 0);
    if (m_font == NULL) {
        D3DXCreateFont(pDevise, 12, 0, FW_BOLD, 0, 0, 1, 0, 0, 0 | FF_DONTCARE, TEXT("Arial"), &m_font);
    }
    m_font->DrawText(0, L"YES! IZI HOOK :-)", -1, &fontRect, 0, fontColor);
}
