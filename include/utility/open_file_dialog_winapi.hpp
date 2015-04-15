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
// WinAPI32 のオープンダイアログを呼び出します
// 
///////////////////////////////////////////////////////////////////////////////////////////////////
#if (defined WIN32 || defined _WIN32 || defined _WIN64 || defined WINCE) 
#ifndef SHOW_PROFILE_IMAGE_UTILITY_OPEN_FILE_DIALOG_WINAPI_HPP
#define SHOW_PROFILE_IMAGE_UTILITY_OPEN_FILE_DIALOG_WINAPI_HPP

#include <string>
#include <vector>

#include "misc/string_convert.hpp"

namespace show_profile_image {
/*******************************************************************************************/// ***
/**
 * OpenFileDialog を呼び出します.
 *
 * Windows の OpenFileDialog によってファイルを1つ選択します．
 * ファイルを選択する際の選択フィルタを入力すると簡易的な OpenFileDialog が呼び出されます．
 *
 *
 * @param filters フィルタ(区切り文字は'|')
 * @return 選択したファイルパス．選択せずに終了したときは空文字．
 *
 *
 * 使用例
 * @code
 * // 動画ファイルと画像ファイルを選択できる OpenFileDialog を呼び出します
 * std::wstring selectedPath = openFileDialog(L"動画ファイル(*.avi)|*.avi|"
 *                                            L"画像ファイル(*.png)|*.png|"
 *                                            L"すべてのファイル|*.*");
 *
 * std::wcout << L"選択ファイル: " << selectedPath << std::endl;
 * @endcode
 *
 *************************************************************************************************/
std::wstring openFileDialog(const std::wstring &filter);



/*******************************************************************************************/// ***
/**
* OpenFileDialog を呼び出します.
*
* Windows の OpenFileDialog によってファイルを1つ選択します．
* ファイルを選択する際の選択フィルタを入力すると簡易的な OpenFileDialog が呼び出されます．
*
*
* @param filters フィルタ(区切り文字は'|')
* @return 選択したファイルパス．選択せずに終了したときは空文字．
*
*
* 使用例
* @code
* // 動画ファイルと画像ファイルを選択できる OpenFileDialog を呼び出します
* std::string selectedPath = openFileDialog("動画ファイル(*.avi)|*.avi|"
*                                           "画像ファイル(*.png)|*.png|"
*                                           "すべてのファイル|*.*");
*
* std::cout << "選択ファイル: " << selectedPath << std::endl;
* @endcode
*
*************************************************************************************************/
inline std::string openFileDialog(const std::string &filter)
{
    return toString(openFileDialog(toWString(filter)));
}


/*******************************************************************************************/// ***
/**
* SaveFileDialog を呼び出します.
*
* Windows の SaveFileDialog によってファイルの保存先を決定します.
*
* @param filters フィルタ(区切り文字は'|')
* @return 選択したファイルパス．確定せずに終了したときは空文字．
*
*************************************************************************************************/
std::wstring saveFileDialog(const std::wstring &filter);


/*******************************************************************************************/// ***
/**
 * SaveFileDialog を呼び出します.
 *
 * Windows の SaveFileDialog によってファイルの保存先を決定します.
 *
 * @param filters フィルタ(区切り文字は'|')
 * @return 選択したファイルパス．確定せずに終了したときは空文字．
 *
 *************************************************************************************************/
inline std::string saveFileDialog(const std::string &filter)
{
    return toString(saveFileDialog(toWString(filter)));
}
} // namespace show_profile_image
#endif // #ifndef SHOW_PROFILE_IMAGE_UTILITY_OPEN_FILE_DIALOG_WINAPI_HPP
#endif // #if (defined WIN32 || defined _WIN32 || defined _WIN64 || defined WINCE) 