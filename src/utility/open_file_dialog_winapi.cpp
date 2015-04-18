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