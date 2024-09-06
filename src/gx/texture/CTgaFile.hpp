#ifndef GX_TEXTURE_C_TGA_FILE_HPP
#define GX_TEXTURE_C_TGA_FILE_HPP

#include <cstdint>

#include "util/SFile.hpp"

class CTgaFile {
    private:
        enum {
            TGA_NO_IMAGE_DATA = 0x0,
            TGA_COLOR_MAPPED = 0x1,
            TGA_TRUE_COLOR = 0x2,
            TGA_BLACK_N_WHITE = 0x3,
            TGA_RLE_COLOR_MAPPED = 0x9,
            TGA_RLE_TRUE_COLOR = 0xA,
            TGA_RLE_BLACK_N_WHITE = 0xB
        };

// This class casts raw memory into these structures, so pack them tightly
#pragma pack(push, 1)
        struct TGAHeader {
            uint8_t bIDLength;
            uint8_t bColorMapType;
            uint8_t bImageType;
            // byte packed
            uint16_t wColorMapStartIndex;
            uint16_t wColorMapEntries;
            uint8_t bColorMapEntrySize;
            uint16_t wXOrigin;
            uint16_t wYOrigin;
            uint16_t wWidth;
            uint16_t wHeight;
            uint8_t bPixelDepth;
            union {
                uint8_t bImageDescriptor;
                struct {
                    uint8_t bAlphaChannelBits : 4;
                    uint8_t bLeftRightOrder : 1;
                    uint8_t bTopBottomOrder : 1;
                    uint8_t bReserved : 2;
                } desc;
            };
        };

        struct TGAFooter {
            uint32_t dwExtensionOffset;
            uint32_t dwDeveloperOffset;
            uint8_t szSigniture[18];
        };
#pragma pack(pop)

        SFile* m_file = nullptr;
        uint8_t* m_image = nullptr;
        TGAHeader m_header;
        uint8_t* m_addlHeaderData = nullptr;
        TGAFooter m_footer;
        uint32_t m_imageBytes = 0;
        uint8_t* m_colorMap = nullptr;

    private:
        void AddAlphaChannel(uint8_t* pAlphaData, uint8_t* pNoAlphaData, const uint8_t* alpha);
        int32_t RemoveAlphaChannels();
        int32_t ReadRawImage(uint32_t flags);
        int32_t RLEDecompressImage(uint8_t* pRLEData, uint8_t* pData);
        int32_t ReadRleImage(uint32_t flags);
        int32_t ReadColorMappedImage(uint32_t flags);
        int32_t ValidateColorDepth();
        void ConvertColorMapped(uint32_t flags);
        uint32_t PreImageBytes() const;
        uint32_t ColorMapEntryBytes() const;
        uint32_t ColorMapEntries() const;
        uint32_t ColorMapBytes() const;
        uint32_t BytesPerPixel() const;
        // int32_t CountRun(uint8_t* pImage ,int32_t nMax);
        // int32_t RleCompressLine(uint8_t** uncompressed, uint8_t** compressed);

    public:
        struct TGA32Pixel {
            uint8_t b;
            uint8_t g;
            uint8_t r;
            uint8_t a;
        };

        int32_t Open(const char* filename, int32_t a3);
        void Close();
        uint32_t Width() const;
        uint32_t Height() const;
        uint32_t Size() const;
        uint32_t Bytes() const;
        uint8_t AlphaBits() const;
        uint8_t* Image();
        TGA32Pixel* ImageTGA32Pixel();
        int32_t LoadImageData(uint32_t flags);
        int32_t AddAlphaChannel(const void* pImg);
        void SetTopDown(int32_t set);
};

#endif
