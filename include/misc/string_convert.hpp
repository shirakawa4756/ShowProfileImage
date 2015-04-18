///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright(c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// * 2 clause BSD license
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
//
// * 二条項BSDライセンス　和訳
//
// Copyright (c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// ソースコード形式かバイナリ形式か、変更するかしないかを問わず、
// 以下の条件を満たす場合に限り、再頒布および使用が許可されます。
//
// 1. ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、
//    および下記免責条項を含めること。
//
// 2. バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の
//    資料に、上記の著作権表示、本条件一覧、および下記免責条項を含
//    めること。
//
// 本ソフトウェアは、著作権者およびコントリビューターによって「現状のまま」提供されており、
// 明示黙示を問わず、商業的な使用可能性、および特定の目的に対する適合性に関する暗黙の保証
// も含め、またそれに限定されない、いかなる保証もありません。
// 著作権者もコントリビューターも、事由のいかんを問わず、損害発生の原因いかんを問わず、
// かつ責任の根拠が契約であるか厳格責任であるか（過失その他の）不法行為であるかを問わず、
// 仮にそのような損害が発生する可能性を知らされていたとしても、本ソフトウェアの使用に
// よって発生した（代替品または代用サービスの調達、使用の喪失、データの喪失、利益の喪失、
// 業務の中断も含め、またそれに限定されない）直接損害、間接損害、偶発的な損害、特別損害、
// 懲罰的損害、または結果損害について、一切責任を負わないものとします。
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