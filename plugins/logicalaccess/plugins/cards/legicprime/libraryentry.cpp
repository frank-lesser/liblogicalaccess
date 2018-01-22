#include <string>
#include <memory>
#include <logicalaccess/readerproviders/readerprovider.hpp>
#include <logicalaccess/plugins/cards/legicprime/legicprimechip.hpp>

#ifdef _MSC_VER
#include <logicalaccess/msliblogicalaccess.h>
#else
#ifndef LIBLOGICALACCESS_API
#define LIBLOGICALACCESS_API
#endif
#ifndef DISABLE_PRAGMA_WARNING
#define DISABLE_PRAGMA_WARNING /**< \brief winsmcrd.h was modified to support this       \
                                  macro, to avoid MSVC specific warnings pragma */
#endif
#endif

extern "C" {
LIBLOGICALACCESS_API char *getLibraryName()
{
    return (char *)"LegicPrime";
}

LIBLOGICALACCESS_API void getLegicPrimeChip(std::shared_ptr<logicalaccess::Chip> *chip)
{
    if (chip != nullptr)
    {
        *chip = std::make_shared<logicalaccess::LegicPrimeChip>();
    }
}

LIBLOGICALACCESS_API bool getChipInfoAt(unsigned int index, char *chipname,
                                        size_t chipnamelen, void **getterfct)
{
    bool ret = false;
    if (chipname != nullptr && chipnamelen == PLUGINOBJECT_MAXLEN && getterfct != nullptr)
    {
        switch (index)
        {
        case 0:
        {
            *getterfct = (void *)&getLegicPrimeChip;
            sprintf(chipname, CHIP_LEGICPRIME);
            ret = true;
        }
        break;
        default:;
        }
    }

    return ret;
}
}