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
#ifndef SHOW_PROFILE_IMAGE_IMAGE_PROCESSING_COMMAND
#define SHOW_PROFILE_IMAGE_IMAGE_PROCESSING_COMMAND

#include <algorithm>
#include <map>
#include <string>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

namespace show_profile_image {
/*******************************************************************************************/// ***
/**
 * ����̃J�[�l���T�C�Y
 *
 *************************************************************************************************/
const int DEFAULT_KERNEL_SIZE = 3;

class ImageProcessingCommand
{
public:
    /**
     *
     */
    virtual ~ImageProcessingCommand() {}


    /**
     *
     */
    virtual void operator()(const cv::Mat &src, cv::Mat &dst) const = 0;


    /**
     *
     */
    virtual int kernelSize() const = 0;


    /**
     *
     */
    virtual void setKernelSize(int kernel) = 0;
};


typedef std::shared_ptr<ImageProcessingCommand> ImageProcessingCommandPtr;




/*******************************************************************************************/// ***
/**
 * �{�b�N�X�t�B���^���{���܂�
 *
 *************************************************************************************************/
class BoxFilter : public ImageProcessingCommand
{
public:
    /**
     * �R���X�g���N�^
     */
    BoxFilter() : kernelSize_(DEFAULT_KERNEL_SIZE, DEFAULT_KERNEL_SIZE) {}


    /**
     * �f�X�g���N�^
     */
    virtual ~BoxFilter() {}


    /**
     * �{�b�N�X�t�B���^���{���܂�
     */
    void operator()(const cv::Mat &src, cv::Mat &dst) const
    {
        cv::blur(src, dst, kernelSize_);
    }


    /**
     * �J�[�l���T�C�Y���擾���܂�
     */
    virtual int kernelSize() const
    {
        return kernelSize_.width;
    }


    /**
     * �J�[�l���T�C�Y��ݒ肵�܂�
     */
    virtual void setKernelSize(int kernel)
    {
        kernelSize_.width  = kernel;
        kernelSize_.height = kernel;
    }


private:
    /**
     * �J�[�l���T�C�Y
     */
    cv::Size kernelSize_;
};







/*******************************************************************************************/// ***
/**
* �{�b�N�X�t�B���^���{���܂�
*
*************************************************************************************************/
class LaplacianFilter : public ImageProcessingCommand
{
public:
    /**
    * �R���X�g���N�^
    */
    LaplacianFilter() : kernelSize_(DEFAULT_KERNEL_SIZE) {}


    /**
    * �f�X�g���N�^
    */
    virtual ~LaplacianFilter() {}


    /**
    * �{�b�N�X�t�B���^���{���܂�
    */
    void operator()(const cv::Mat &src, cv::Mat &dst) const
    {
        cv::Mat tmp;
        cv::Laplacian(src, tmp, CV_32F, kernelSize_);

        double min = 0.0;
        double max = 0.0;
        cv::minMaxLoc(tmp, &min, &max);

        const double scale = std::max(std::abs(min), std::abs(max));
        cv::convertScaleAbs(tmp, dst, 255.0 / scale);
    }


    /**
    * �J�[�l���T�C�Y���擾���܂�
    */
    virtual int kernelSize() const
    {
        return kernelSize_;
    }


    /**
    * �J�[�l���T�C�Y��ݒ肵�܂�
    */
    virtual void setKernelSize(int kernel)
    {
        kernelSize_ = kernel;
    }


private:
    /**
    * �J�[�l���T�C�Y
    */
    int kernelSize_;
};


} // namespace show_profile_image
#endif // #ifndef SHOW_PROFILE_IMAGE_IMAGE_PROCESSING_COMMAND