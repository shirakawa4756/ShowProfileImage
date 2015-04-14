///////////////////////////////////////////////////////////////////////////////////////////////////
//
// �ǂݍ��񂾉摜�̏c���v���t�@�C����\�����܂��D
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <image/image_profilter.hpp>

namespace {
#ifdef _WIN32
/*******************************************************************************************/// ***
/**
 * Windows �̃p�X��؂���`���܂�
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = '\\';
#else
/*******************************************************************************************/// ***
/**
 * UNIX�n �̃p�X��؂���`���܂�
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = L'/';
#endif



/*******************************************************************************************/// ***
/**
 * �t���p�X����t�@�C�����𒊏o���܂��D
 *
 * �Ⴆ�΁CC:\dir\image\abc.png �Ƃ��������񂪓��͂��ꂽ�ꍇ�C
 * abc.png �Ƃ����������Ԃ��܂��D
 *
 * ex.
 *    C:\dir\image\abc.png  -> abc.png
 *
 * @param path �t���p�X��
 * @return �t�@�C����
 *
 *************************************************************************************************/
std::wstring getFilename(const std::wstring &path)
{
    std::wstring::size_type  pos = path.find_last_of(PATH_SEPARATOR);

    if (pos == std::wstring::npos) {
        return path;
    }

    return path.substr(pos, path.size());
}



/*******************************************************************************************/// ***
/**
 * �v���t�@�C������\������E�C���h�E�̕\����쐬���܂��D
 *
 * �\��Ƃ��āCProfile Of `<filename>' �Ƃ�����������쐬���܂��D
 * ���͂���t�@�C�����́C�t���p�X�ł��悭�C���̏ꍇ�́C�t�@�C���������𒊏o����
 * Profile Of `<filename>' �Ƃ�����������쐬���܂��D
 *
 * @param path �t���p�X
 * @return �\��
 *
 *************************************************************************************************/
std::wstring createCaption(const std::wstring &path)
{
    std::wstringstream wss;
    wss << L"Profile of "
        << "`"
        << path.c_str()
        << "'";
    return wss.str();
}

} // namespace



int _tmain(int argc, _TCHAR* argv[])
{
    _tsetlocale(LC_ALL, _T(""));

    std::wstring filename;
    if (argc < 2) {
        filename = L"t.png";
    } else {
        filename = std::wstring(argv[1]);
    }

    cv::Mat im = cv::imread(cv::fromUtf16(filename));

    show_profile_image::ImageProfiler imageProfiler;
    imageProfiler.setImage(im);
    imageProfiler.setCaption(createCaption(filename));
    imageProfiler.show();

    return 0;
}

