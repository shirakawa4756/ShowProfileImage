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
// WinAPI32 �̃I�[�v���_�C�A���O���Ăяo���܂�
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
 * OpenFileDialog ���Ăяo���܂�.
 *
 * Windows �� OpenFileDialog �ɂ���ăt�@�C����1�I�����܂��D
 * �t�@�C����I������ۂ̑I���t�B���^����͂���ƊȈՓI�� OpenFileDialog ���Ăяo����܂��D
 *
 *
 * @param filters �t�B���^(��؂蕶����'|')
 * @return �I�������t�@�C���p�X�D�I�������ɏI�������Ƃ��͋󕶎��D
 *
 *
 * �g�p��
 * @code
 * // ����t�@�C���Ɖ摜�t�@�C����I���ł��� OpenFileDialog ���Ăяo���܂�
 * std::wstring selectedPath = openFileDialog(L"����t�@�C��(*.avi)|*.avi|"
 *                                            L"�摜�t�@�C��(*.png)|*.png|"
 *                                            L"���ׂẴt�@�C��|*.*");
 *
 * std::wcout << L"�I���t�@�C��: " << selectedPath << std::endl;
 * @endcode
 *
 *************************************************************************************************/
std::wstring openFileDialog(const std::wstring &filter);



/*******************************************************************************************/// ***
/**
* OpenFileDialog ���Ăяo���܂�.
*
* Windows �� OpenFileDialog �ɂ���ăt�@�C����1�I�����܂��D
* �t�@�C����I������ۂ̑I���t�B���^����͂���ƊȈՓI�� OpenFileDialog ���Ăяo����܂��D
*
*
* @param filters �t�B���^(��؂蕶����'|')
* @return �I�������t�@�C���p�X�D�I�������ɏI�������Ƃ��͋󕶎��D
*
*
* �g�p��
* @code
* // ����t�@�C���Ɖ摜�t�@�C����I���ł��� OpenFileDialog ���Ăяo���܂�
* std::string selectedPath = openFileDialog("����t�@�C��(*.avi)|*.avi|"
*                                           "�摜�t�@�C��(*.png)|*.png|"
*                                           "���ׂẴt�@�C��|*.*");
*
* std::cout << "�I���t�@�C��: " << selectedPath << std::endl;
* @endcode
*
*************************************************************************************************/
inline std::string openFileDialog(const std::string &filter)
{
    return toString(openFileDialog(toWString(filter)));
}


/*******************************************************************************************/// ***
/**
* SaveFileDialog ���Ăяo���܂�.
*
* Windows �� SaveFileDialog �ɂ���ăt�@�C���̕ۑ�������肵�܂�.
*
* @param filters �t�B���^(��؂蕶����'|')
* @return �I�������t�@�C���p�X�D�m�肹���ɏI�������Ƃ��͋󕶎��D
*
*************************************************************************************************/
std::wstring saveFileDialog(const std::wstring &filter);


/*******************************************************************************************/// ***
/**
 * SaveFileDialog ���Ăяo���܂�.
 *
 * Windows �� SaveFileDialog �ɂ���ăt�@�C���̕ۑ�������肵�܂�.
 *
 * @param filters �t�B���^(��؂蕶����'|')
 * @return �I�������t�@�C���p�X�D�m�肹���ɏI�������Ƃ��͋󕶎��D
 *
 *************************************************************************************************/
inline std::string saveFileDialog(const std::string &filter)
{
    return toString(saveFileDialog(toWString(filter)));
}
} // namespace show_profile_image
#endif // #ifndef SHOW_PROFILE_IMAGE_UTILITY_OPEN_FILE_DIALOG_WINAPI_HPP
#endif // #if (defined WIN32 || defined _WIN32 || defined _WIN64 || defined WINCE) 