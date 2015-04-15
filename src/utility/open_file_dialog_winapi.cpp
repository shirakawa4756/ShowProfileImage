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
// WinWPI32 �̃I�[�v���_�C�A���O���Ăяo���܂�
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
 * OpenFileDialog �Ŏg�p����t�B���^�̋�؂蕶��(.NET ��)
 */
const wchar_t OPEN_DIALOG_FILTER_SEP_DOT_NET = L'|';


/**
 * OpenFileDialog �Ŏg�p����t�B���^�̋�؂蕶��(WinAPI ��)
 */
const wchar_t OPEN_DIALOG_FILTER_SEP_WIN_API = L'\0';


/*******************************************************************************************/// ***
/**
 * OpenDialog �Ŏg�p����t�B���^�̍\�z���s���D
 * .NET �`���Ŏg�p����t�B���^�`��(��؂蕶�� '|') ����C
 * WinAPI �Ŏg�p����t�B���^�`��(��؂蕶�� '\0') �`���ɕϊ�����D
 * NULL�������g�p����̂ŏo�͌^���́Cwchar_t * �^�ōs���D
 *
 * @param dstFilter  WinAPI�`���̃t�B���^������
 * @param dstSize    dstFilter �̔z��T�C�Y
 * @param srcFilter  .NET�`���̃t�B���^������
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
 * OpenFileName �N���X.
 * OPENFILENAMEW �̊e�탁�����Ǘ��ŁD
 *
 *************************************************************************************************/
class OpenFileName
{
public:
    /**
     * �R���X�g���N�^.
     */
    OpenFileName()
      : openFileNamePtr_(new OPENFILENAMEW)
    {
        initialize();
    }


    /**
     * �f�X�g���N�^.
     */
    ~OpenFileName()
    {
        delete[] safetyFilter_;
        delete openFileNamePtr_;
    }


    /**
     * OpenFileName �̃|�C���^���擾����.
     *
     * @return �ݒ�ς݃t�@�C���\����
     */
    OPENFILENAMEW* data() const
    {
        return openFileNamePtr_;
    }


    /**
     * �I�������t�@�C����.
     *
     * @param �t�@�C����
     */
    std::wstring selectFilePath() const
    {
        return std::wstring(selectFileNamePath_);
    }


    /**
     * �t�B���^��ݒ肷��.
     * �t�B���^�̌`���́C
     * "�\�����ږ�|�g���q|..." �Ƒ����D
     *
     * @param filter �t�B���^������
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
     * �g���q�̑傫��
     */
    static const size_t EXTENSION_SIZE = 10;


    /**
     * ������
     */
    void initialize()
    {
        // �\���̂�0���߂��C�\���̃T�C�Y��ݒ�
        ZeroMemory(openFileNamePtr_, sizeof(OPENFILENAMEW));
        openFileNamePtr_->lStructSize = sizeof(OPENFILENAMEW);

        // �I�����ꂽ�t�@�C�����̕ۑ�����m��
        openFileNamePtr_->lpstrFile    = selectFileNamePath_;
        openFileNamePtr_->lpstrFile[0] = L'\0';
        openFileNamePtr_->nMaxFile     = MAX_PATH;

        // �g���q�̕ۑ��������
        openFileNamePtr_->lpstrDefExt    = selectExtentionName_;
        openFileNamePtr_->nFileExtension = EXTENSION_SIZE;

        // �I�v�V�����ݒ�
        openFileNamePtr_->Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    }


    /**
     * OpenFileName �\����
     */
    OPENFILENAMEW *openFileNamePtr_;


    /**
     * �t�B���^������
     */
    wchar_t *safetyFilter_;


    /**
     * �I�������t�@�C���̊g���q
     */
    wchar_t selectExtentionName_[EXTENSION_SIZE];


    /**
     * �I�������t�@�C����
     */
    wchar_t selectFileNamePath_[MAX_PATH];


    ///////////////////////////////////////////////////////////////////////////////////////////////
    //
    // �R�s�[�R���X�g���N�^�C������Z�q�̋֎~
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