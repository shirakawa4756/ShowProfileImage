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
//
// �ǂݍ��񂾉摜�̏c���v���t�@�C����\�����܂��D
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <image/image_profilter.hpp>
#include <utility/open_file_dialog_winapi.hpp>


namespace {
/*******************************************************************************************/// ***
/**
 * Windows �̃p�X��؂���`���܂�
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = '\\';



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
void fittingDisplayImageSize(const cv::Mat &src, int profileHeight, cv::Mat &dst)
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



/*******************************************************************************************/// ***
/**
 * ���f�B�A���t�B���^���{���֐��I�u�W�F�N�g���`���܂�
 *
 * �v���t�@�C���\�����Ă���Ƃ��C����̃L�[�������ƃ��f�B�A���t�B���^���{���悤��
 * ImageProcessingCommand ���p���������f�B�A���t�B���^�̊֐��I�u�W�F�N�g���`���܂��D
 *
 *************************************************************************************************/
class MedianFilter : public show_profile_image::ImageProcessingCommand
{
public:
    MedianFilter()
      : kernelSize_(show_profile_image::DEFAULT_KERNEL_SIZE)
    {
    }


    virtual ~MedianFilter()
    {
    }


    virtual void operator()(const cv::Mat &src, cv::Mat &dst) const
    {
        cv::medianBlur(src, dst, kernelSize_);
    }


    virtual int kernelSize() const
    {
        return kernelSize_;
    }


    virtual void setKernelSize(int kernel)
    {
        kernelSize_ = kernel;
    }


private:
    int kernelSize_;
};



} // namespace



int _tmain(int argc, _TCHAR* argv[])
{
    using namespace show_profile_image;
    _tsetlocale(LC_ALL, _T(""));

    std::wstring filename;
    if (argc < 2) {
        filename = openFileDialog(L"�摜�t�@�C�� (*.jpg;*tif;*png)|*.jpg;*tif;*png");
    } else {
        filename = std::wstring(argv[1]);
    }



    ImageProfiler imageProfiler;
    imageProfiler.setCaption(toString(createCaption(filename)));

    // m �L�[���������Ƃ��C���f�B�A���t�B���^���{��
    imageProfiler.addImageProcessingCommand('m', std::make_shared<MedianFilter>());

    cv::Mat im = cv::imread(toString(filename));
    fittingDisplayImageSize(im, imageProfiler.profileHeight(), im);

    imageProfiler.setImage(im);
    imageProfiler.show();
    return 0;
}

