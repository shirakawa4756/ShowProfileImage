///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met :
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.
// 
//
// 主に Windows で Unicode を使用するために使用する
// マルチバイト文字からワイド文字への変換と逆変換を定義します．
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef SHOW_PROFILE_IMAGE_MISC_STRING_HPP
#define SHOW_PROFILE_IMAGE_MISC_STRING_HPP

#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
#   include <tchar.h>
#endif

#include <stdlib.h>
#include <string>

namespace show_profile_image {
/*******************************************************************************************/// ***
/**
 * wstring(ワイド文字)への変換します
 *
 * 入力が wstring でも string のどちらにも対応するために
 * 引数が wstring でも定義します．
 *
 * @param wstr ワイド文字列
 * @return 元の文字列
 *
 *************************************************************************************************/
inline std::wstring toWString(const std::wstring &wstr)
{
    return wstr;
}


/*******************************************************************************************/// ***
/**
 * wstring(ワイド文字)への変換
 *
 * マルチバイト文字列からワイド文字列へ変換します
 *
 * @param str マルチバイト文字列
 * @return ワイド文字列
 *
 *************************************************************************************************/
inline std::wstring toWString(const std::string &str)
{
    const size_t wstrSize = str.size() + 1;
    wchar_t *wstr = new wchar_t[wstrSize];

    size_t converted = 0;
    mbstowcs_s(&converted, wstr, wstrSize, str.data(), _TRUNCATE);

    std::wstring dst(wstr);
    delete[] wstr;
    return dst;
}



/*******************************************************************************************/// ***
/**
 * string(マルチバイト文字)への変換
 *
 * 入力が wstring でも string のどちらにも対応するために
 * 引数が string でも定義します．
 *
 * @param str マルチバイト文字列
 * @return 元の文字列
 *
 *************************************************************************************************/
inline std::string toString(const std::string &str)
{
    return str;
}



/*******************************************************************************************/// ***
/**
 * string(マルチバイト文字)への変換
 *
 * ワイド文字列からマルチバイト文字列へ変換します
 *
 * @param wstr ワイド文字列
 * @return マルチバイト文字列
 *
 *************************************************************************************************/
inline std::string toString(const std::wstring &wstr)
{
    const size_t strSize = wstr.size() * 2 + 1;
    char *str = new char[strSize];

    size_t conveted = 0;
    wcstombs_s(&conveted, str, strSize, wstr.data(), _TRUNCATE);

    std::string dst(str);
    delete[] str;
    return dst;
}

} // namespace show_profile_image


#endif