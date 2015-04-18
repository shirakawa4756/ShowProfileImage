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
// * �����BSD���C�Z���X�@�a��
//
// Copyright (c) 2015, shirakawa4756@github.com
// All rights reserved.
//
// �\�[�X�R�[�h�`�����o�C�i���`�����A�ύX���邩���Ȃ������킸�A
// �ȉ��̏����𖞂����ꍇ�Ɍ���A�ĔЕz����юg�p��������܂��B
//
// 1. �\�[�X�R�[�h���ĔЕz����ꍇ�A��L�̒��쌠�\���A�{�����ꗗ�A
//    ����щ��L�Ɛӏ������܂߂邱�ƁB
//
// 2. �o�C�i���`���ōĔЕz����ꍇ�A�Еz���ɕt���̃h�L�������g����
//    �����ɁA��L�̒��쌠�\���A�{�����ꗗ�A����щ��L�Ɛӏ�������
//    �߂邱�ƁB
//
// �{�\�t�g�E�F�A�́A���쌠�҂���уR���g���r���[�^�[�ɂ���āu����̂܂܁v�񋟂���Ă���A
// �����َ����킸�A���ƓI�Ȏg�p�\���A����ѓ���̖ړI�ɑ΂���K�����Ɋւ���Öق̕ۏ�
// ���܂߁A�܂�����Ɍ��肳��Ȃ��A�����Ȃ�ۏ؂�����܂���B
// ���쌠�҂��R���g���r���[�^�[���A���R�̂�������킸�A���Q�����̌�����������킸�A
// ���ӔC�̍������_��ł��邩���i�ӔC�ł��邩�i�ߎ����̑��́j�s�@�s�ׂł��邩���킸�A
// ���ɂ��̂悤�ȑ��Q����������\����m�炳��Ă����Ƃ��Ă��A�{�\�t�g�E�F�A�̎g�p��
// ����Ĕ��������i��֕i�܂��͑�p�T�[�r�X�̒��B�A�g�p�̑r���A�f�[�^�̑r���A���v�̑r���A
// �Ɩ��̒��f���܂߁A�܂�����Ɍ��肳��Ȃ��j���ڑ��Q�A�Ԑڑ��Q�A�����I�ȑ��Q�A���ʑ��Q�A
// �����I���Q�A�܂��͌��ʑ��Q�ɂ��āA��ؐӔC�𕉂�Ȃ����̂Ƃ��܂��B
//
// ��� Windows �� Unicode ���g�p���邽�߂Ɏg�p����
// �}���`�o�C�g�������烏�C�h�����ւ̕ϊ��Ƌt�ϊ����`���܂��D
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
 * wstring(���C�h����)�ւ̕ϊ����܂�
 *
 * ���͂� wstring �ł� string �̂ǂ���ɂ��Ή����邽�߂�
 * ������ wstring �ł���`���܂��D
 *
 * @param wstr ���C�h������
 * @return ���̕�����
 *
 *************************************************************************************************/
inline std::wstring toWString(const std::wstring &wstr)
{
    return wstr;
}


/*******************************************************************************************/// ***
/**
 * wstring(���C�h����)�ւ̕ϊ�
 *
 * �}���`�o�C�g�����񂩂烏�C�h������֕ϊ����܂�
 *
 * @param str �}���`�o�C�g������
 * @return ���C�h������
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
 * string(�}���`�o�C�g����)�ւ̕ϊ�
 *
 * ���͂� wstring �ł� string �̂ǂ���ɂ��Ή����邽�߂�
 * ������ string �ł���`���܂��D
 *
 * @param str �}���`�o�C�g������
 * @return ���̕�����
 *
 *************************************************************************************************/
inline std::string toString(const std::string &str)
{
    return str;
}



/*******************************************************************************************/// ***
/**
 * string(�}���`�o�C�g����)�ւ̕ϊ�
 *
 * ���C�h�����񂩂�}���`�o�C�g������֕ϊ����܂�
 *
 * @param wstr ���C�h������
 * @return �}���`�o�C�g������
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