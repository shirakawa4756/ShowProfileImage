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



#ifdef _WIN32
/*******************************************************************************************/// ***
/**
 * �f�B�X�v���C�̉�ʃT�C�Y���擾���܂�
 *
 * �����̃f�B�X�v���C���ڑ�����Ă����ꍇ�͂ǂ��Ȃ邩������܂���D
 *
 * @param[out] width ���̉𑜓x
 * @param[out] height �c�̉𑜓x
 *
 *************************************************************************************************/
cv::Size getDisplaySize()
{
    const int width  = GetSystemMetrics(SM_CXSCREEN);
    const int height = GetSystemMetrics(SM_CYSCREEN);
    return cv::Size(width, height);
}
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

    return path.substr(pos + 1, path.size());
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
        << getFilename(path.c_str())
        << "'";
    return wss.str();
}



/*******************************************************************************************/// ***
/**
 * �v���t�@�C������\������ہC�f�B�X�v���C�𑜓x���傫���Ȃ�Ȃ��悤�Ɍ��摜���k�����܂�
 *
 *************************************************************************************************/
void fittingDisplaySize(const cv::Mat &src, int profileHeight, cv::Mat &dst)
{
    // �E�C���h�E�̃^�C�g���o�[�̍���
    const int WINDOW_TITLE_HEIGHT = 80;

    // �f�B�X�v���C����͂ݏo�Ȃ��摜�T�C�Y���v�Z����
    const cv::Size displaySize = getDisplaySize();
    const cv::Size fittingSize(displaySize.width - profileHeight,
                               displaySize.height - profileHeight - WINDOW_TITLE_HEIGHT);
    const cv::Point2d reduction(fittingSize.width / static_cast<double>(src.size().width),
                                fittingSize.height / static_cast<double>(src.size().height));
    const double reductionParcent = std::min(reduction.x, reduction.y);


    // �k������K�v�������Ƃ��͂��̂܂܏I������
    if (reductionParcent >= 1.0) {
        dst = src.clone();
        return;
    }

    // ���摜���k�����ăf�B�X�v���C����͂ݏo�Ȃ��悤�ɂ���
    cv::resize(src, dst, cv::Size(), reductionParcent, reductionParcent, cv::INTER_LANCZOS4);
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


    show_profile_image::ImageProfiler imageProfiler;
    imageProfiler.setCaption(createCaption(filename));

    cv::Mat im = cv::imread(cv::fromUtf16(filename));
    fittingDisplaySize(im, imageProfiler.profileHeight(), im);

    imageProfiler.setImage(im);
    imageProfiler.show();

    return 0;
}

