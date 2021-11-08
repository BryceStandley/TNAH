#pragma once
#include "Texture.h"

namespace tnah {

    /**
     * @class	Image
     *
     * @brief	An image class that inherits from the texture2D class
     *
     * @author	Bryce Standley
     * @date	12/09/2021
     */

    class Image : public Texture2D
    {
    public:

        /**
         * @fn	virtual Image::~Image();
         *
         * @brief	Destructor
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        virtual ~Image();

        /**
         * @fn	void Image::SetData(void* data, uint32_t size) override;
         *
         * @brief	Sets image data
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	data	If non-null, the data.
         * @param 		  	size	The size.
         */

        void SetData(void* data, uint32_t size) override;

        /**
         * @fn	void Image::Bind(uint32_t slot) const override
         *
         * @brief	Binds the given slot
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param 	slot	The slot.
         */

        void Bind(uint32_t slot) const override {}

        /**
         * @fn	void Image::Bind() const override
         *
         * @brief	Binds this object
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        void Bind() const override {}

        /**
         * @fn	void Image::Free() override;
         *
         * @brief	Frees this object
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         */

        void Free() override;

        /**
         * @fn	void Image::Free(void* data) override;
         *
         * @brief	Frees the given data
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @param [in,out]	data	If non-null, the data.
         */

        void Free(void* data) override;

        /**
         * @fn	ktxTexture* Image::GetKtxData() const override;
         *
         * @brief	Gets ktx data
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	Null if it fails, else the ktx data.
         */

        ktxTexture* GetKtxData() const override;

        /**
         * @fn	uchar8_t* Image::GetImageData() const override;
         *
         * @brief	Gets image data
         *
         * @author	Bryce Standley
         * @date	12/09/2021
         *
         * @returns	Null if it fails, else the image data.
         */

        uchar8_t* GetImageData() const override;
    };
}
