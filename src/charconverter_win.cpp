/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#include "platform/charconverter.h"
#include <windows.h>
namespace douml
{

du_char *CharConverter::UnicodeToUtf8(du_unicode *u)
{
    du_int len;
    len = ::WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)u, -1, NULL, 0, NULL, NULL);
    du_char *szUtf8 = (du_char *)malloc(len + 1);
    memset(szUtf8, 0, len + 1);
    ::WideCharToMultiByte(CP_UTF8, 0, (LPCWCH)u, -1, szUtf8, len, NULL, NULL);
    return szUtf8;
}
#if 0
du_unicode *CharConverter::Utf8ToUnicode(du_char *c)
{
    unsigned char *p = (unsigned char*)c;

    unsigned short *result = NULL;

    du_int resultsize = 0;

	unsigned char *tmp = NULL;

    result = (unsigned short *)malloc(strlen(c) * 2 + 2); /* should be enough */

    memset(result, 0, strlen(c) * 2 + 2);

    tmp = (unsigned char *)result;

    while (*p)

    {

        if (*p >= 0x00 && *p <= 0x7f)

        {

            *tmp = *p;

            tmp++;

            *tmp = (unsigned char)'/0';

            resultsize += 2;
        }

        else if ((*p & (0xff << 5)) == 0xc0)

        {

			unsigned short t = 0;

			unsigned char t1 = 0;

			unsigned char t2 = 0;

            t1 = *p & (0xff >> 3);

            p++;

            t2 = *p & (0xff >> 2);

            *tmp = t2 | ((t1 & (0xff >> 6)) << 6); //t1 >> 2;

            tmp++;

            *tmp = t1 >> 2; //t2 | ((t1 & (0xff >> 6)) << 6);

            tmp++;

            resultsize += 2;
        }

        else if ((*p & (0xff << 4)) == 0xe0)

        {

			unsigned short t = 0;

			unsigned char t1 = 0;

			unsigned char t2 = 0;

			unsigned char t3 = 0;

            t1 = *p & (0xff >> 3);

            p++;

            t2 = *p & (0xff >> 2);

            p++;

            t3 = *p & (0xff >> 2);

            //Little Endian

            *tmp = ((t2 & (0xff >> 6)) << 6) | t3; //(t1 << 4) | (t2 >> 2);

            tmp++;

            *tmp = (t1 << 4) | (t2 >> 2); //((t2 & (0xff >> 6)) << 6) | t3;

            tmp++;

            resultsize += 2;
        }

        p++;
    }

    *tmp = (unsigned char)'/0';

    tmp++;

    *tmp = (unsigned char)'/0';

    resultsize += 2;


    return (du_unicode*)result;
}
#endif
bool CharConverter::IsUtf8(du_char *c)
{

    du_int nBytes = 0;
    unsigned char chr;
    du_int length = strlen(c);
    bool bAllAscii = true;
    for (du_int i = 0; i < length; ++i)
    {
        chr = *(c + i);
        if ((chr & 0x80) != 0)
            bAllAscii = false;
        if (nBytes == 0)
        {
            if (chr >= 0x80)
            {
                if (chr >= 0xFC && chr <= 0xFD)
                    nBytes = 6;
                else if (chr >= 0xF8)
                    nBytes = 5;
                else if (chr >= 0xF0)
                    nBytes = 4;
                else if (chr >= 0xE0)
                    nBytes = 3;
                else if (chr >= 0xC0)
                    nBytes = 2;
                else
                    return false;

                nBytes--;
            }
        }
        else
        {
            if ((chr & 0xC0) != 0x80)
                return false;

            nBytes--;
        }
    }
    if (nBytes > 0)
        return false;
    if (bAllAscii)
        return false;

    return true;
}

} // namespace douml