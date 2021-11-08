#include "tnahpch.h"
#include "Image.h"

#include "stb_image.h"

namespace tnah {


    Image::~Image()
    {
    }

    void Image::SetData(void* data, uint32_t size)
    {
        TNAH_CORE_ASSERT(size == m_Width * m_Height * m_Channels, "Data must be entire image!");
        switch (m_LoadFormat)
        {
            case ImageLoadFormat::KTX: m_ImageData = static_cast<uchar8_t*>(data); break;
            case ImageLoadFormat::STB: m_ImageData = static_cast<uchar8_t*>(data); break;
            default: ;
        }
    }

    void Image::Free()
    {
        switch (m_LoadFormat)
        {
            case ImageLoadFormat::KTX: TNAH_CORE_ERROR("Cant free a KTX image without data!"); TNAH_CORE_ASSERT(false, "No KTX image data to free"); break;
            case ImageLoadFormat::STB: stbi_image_free(m_ImageData); m_Loaded = false; break;
            default: break;
        }
    }

    void Image::Free(void* data)
    {
        switch (m_LoadFormat)
        {
            case ImageLoadFormat::KTX:
                {
                    ktxTexture* dataToFree = static_cast<ktxTexture*>(data);
                    ktxTexture_Destroy(dataToFree);
                    m_Loaded = false;
                    break;
                }
            case ImageLoadFormat::STB:
                {
                    auto dataToFree = static_cast<uchar8_t*>(data);
                    stbi_image_free(dataToFree);
                    m_Loaded = false;
                    break;
                }
            default: break;
        }
    
    }

    ktxTexture* Image::GetKtxData() const
    {
        if(m_LoadFormat == ImageLoadFormat::KTX)
        {
            return static_cast<ktxTexture*>(m_ImageData);
        }

        return nullptr;
    }

    uchar8_t* Image::GetImageData() const
    {
        if(m_LoadFormat == ImageLoadFormat::STB)
        {
            return static_cast<uchar8_t*>(m_ImageData);
        }

        if(m_LoadFormat == ImageLoadFormat::KTX)
        {
            return ktxTexture_GetData(static_cast<ktxTexture*>(m_ImageData));
        }
        
        return nullptr;
    }

}
