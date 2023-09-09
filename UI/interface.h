extern "C" {
    int StretchDIBits(
        HDC hdc,
        int xDest,
        int yDest,
        int DestWidth,
        int DestHeight,
        int xSrc,
        int ySrc,
        int SrcWidth,
        int SrcHeight,
        const void *lpBits,
        const BITMAPINFO *lpbmi,
        UINT iUsage,
        DWORD rop
    );
}

#include <UI/interface.cpp>