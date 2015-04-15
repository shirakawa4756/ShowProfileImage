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
// WinWPI32 のオープンダイアログを呼び出します
// 
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#if (defined WIN32 || defined _WIN32 || defined _WIN64 || defined WINCE) 
#include "utility/open_file_dialog_winapi.hpp"

#ifndef USE_PRECOMPILED_HEADER
#   include <Windows.h>
#   include <commdlg.h>
#   include <memory>
#   include <iostream>
#   include <string>
#   include <sstream>
#   include <vector>
#
#   pragma comment(lib, "Comdlg32.lib")
#endif


namespace {
/**
 * OpenFileDialog で使用するフィルタの区切り文字(.NET 式)
 */
const wchar_t OPEN_DIALOG_FILTER_SEP_DOT_NET = L'|';


/**
 * OpenFileDialog で使用するフィルタの区切り文字(WinAPI 式)
 */
const wchar_t OPEN_DIALOG_FILTER_SEP_WIN_API = L'\0';


/*******************************************************************************************/// ***
/**
 * OpenDialog で使用するフィルタの構築を行う．
 * .NET 形式で使用するフィルタ形式(区切り文字 '|') から，
 * WinAPI で使用するフィルタ形式(区切り文字 '\0') 形式に変換する．
 * NULL文字を使用するので出力型式は，wchar_t * 型で行う．
 *
 * @param dstFilter  WinAPI形式のフィルタ文字列
 * @param dstSize    dstFilter の配列サイズ
 * @param srcFilter  .NET形式のフィルタ文字列
 *
 *************************************************************************************************/
void makeOpenFileDialogFilter(wchar_t *dstFilter, size_t dstSize, const std::wstring &srcFilter)
{
    if (dstSize < srcFilter.size()) {
        std::stringstream ss;
        ss << "Assert! dstSize < srcFilter.size(). "
           << "Function: makeOpenFileDialogFilter."
           << "File: " << __FILE__ << "(" << __LINE__ << ")";
        throw  std::runtime_error(ss.str().c_str());
    }


    wcscpy_s(dstFilter, dstSize, srcFilter.c_str());
    for (size_t i = 0; i < srcFilter.size(); ++i) {
        if (dstFilter[i] == OPEN_DIALOG_FILTER_SEP_DOT_NET) {
            dstFilter[i] = OPEN_DIALOG_FILTER_SEP_WIN_API;
        }
    }
}



/*******************************************************************************************/// ***
/**
 * OpenFileName クラス.
 * OPENFILENAMEW の各種メモリ管理版．
 *
 *************************************************************************************************/
class OpenFileName
{
public:
    /**
     * コンストラクタ.
     */
    OpenFileName()
      : openFileNamePtr_(new OPENFILENAMEW)
    {
        initialize();
    }


    /**
     * デストラクタ.
     */
    ~OpenFileName()
    {
        delete[] safetyFilter_;
        delete openFileNamePtr_;
    }


    /**
     * OpenFileName のポインタを取得する.
     *
     * @return 設定済みファイル構造体
     */
    OPENFILENAMEW* data() const
    {
        return openFileNamePtr_;
    }


    /**
     * 選択したファイル名.
     *
     * @param ファイル名
     */
    std::wstring selectFilePath() const
    {
        return std::wstring(selectFileNamePath_);
    }


    /**
     * フィルタを設定する.
     * フィルタの形式は，
     * "表示項目名|拡張子|..." と続く．
     *
     * @param filter フィルタ文字列
     */
    void setFilter(const std::wstring &filter)
    {
        std::wstring safetyFilter = filter;
        safetyFilter.push_back(OPEN_DIALOG_FILTER_SEP_DOT_NET);
        safetyFilter.push_back(OPEN_DIALOG_FILTER_SEP_DOT_NET);

        const size_t size = 2 * safetyFilter.capacity();
        safetyFilter_ = new wchar_t[size];
        makeOpenFileDialogFilter(safetyFilter_, size, safetyFilter);
        openFileNamePtr_->lpstrFilter = safetyFilter_;
        openFileNamePtr_->nFilterIndex = 1;
    }


private:
    /**
     * 拡張子の大きさ
     */
    static const size_t EXTENSION_SIZE = 10;


    /**
     * 初期化
     */
    void initialize()
    {
        // 構造体を0埋めし，構造体サイズを設定
        ZeroMemory(openFileNamePtr_, sizeof(OPENFILENAMEW));
        openFileNamePtr_->lStructSize = sizeof(OPENFILENAMEW);

        // 選択されたファイル名の保存先を確保
        openFileNamePtr_->lpstrFile    = selectFileNamePath_;
        openFileNamePtr_->lpstrFile[0] = L'\0';
        openFileNamePtr_->nMaxFile     = MAX_PATH;

        // 拡張子の保存先を決定
        openFileNamePtr_->lpstrDefExt    = selectExtentionName_;
        openFileNamePtr_->nFileExtension = EXTENSION_SIZE;

        // オプション設定
        openFileNamePtr_->Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    }


    /**
     * OpenFileName 構造体
     */
    OPENFILENAMEW *openFileNamePtr_;


    /**
     * フィルタ文字列
     */
    wchar_t *safetyFilter_;


    /**
     * 選択したファイルの拡張子
     */
    wchar_t selectExtentionName_[EXTENSION_SIZE];


    /**
     * 選択したファイル名
     */
    wchar_t selectFileNamePath_[MAX_PATH];


    ///////////////////////////////////////////////////////////////////////////////////////////////
    //
    // コピーコンストラクタ，代入演算子の禁止
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    OpenFileName(const OpenFileName &rhs);
    OpenFileName& operator=(const OpenFileName &rhs);
}; // class OpenFileName


} // namespace




namespace show_profile_image {
std::wstring openFileDialog(const std::wstring &filter)
{
    OpenFileName openFile;
    openFile.setFilter(filter);

    std::wstring selectFilePath;
    if (GetOpenFileNameW(openFile.data())) {
        selectFilePath = openFile.selectFilePath();
    }

    return selectFilePath;
}


std::wstring saveFileDialog(const std::wstring &filter)
{
    OpenFileName openFile;
    openFile.setFilter(filter);

    std::wstring selectFilePath;
    if (GetSaveFileNameW(openFile.data())) {
        selectFilePath = openFile.selectFilePath();
    }

    return selectFilePath;
}
} // namespace show_profile_image
#endif // #if (defined WIN32 || defined _WIN32 || defined _WIN64 || defined WINCE)