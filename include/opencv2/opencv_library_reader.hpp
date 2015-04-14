///////////////////////////////////////////////////////////////////////////////////////////////////
//
// OpenCV �̃��C�u�������o�[�W�����ɉ����ēǂݍ���
//
// OpenCV �̐ÓI���C�u�����������I�ɓǂݍ��ރw���p�[�w�b�_�[�ł��D
// Visual Studio �� pragma comment(lib, ~) �𗘗p���ăC���X�g�[������
// Debug�CRelease ���[�h��OpenCV �ɉ����Ăقڎ����I�ɂ��ׂẴ��C�u������ǂݍ��݂܂��D
//
// �܂��C���̃w�b�_�t�@�C���ɂ��Ă̓p�u���b�v�h���C����錾���܂�.
//
//
// Public Domain
//
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef OPENCV_LIBRARY_READER_HPP
#define OPENCV_LIBRARY_READER_HPP

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
#include <opencv2/core/version.hpp>

#define OPENCV_VERSION CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
#ifdef _DEBUG
#define OPENCV_LIBRARY_NAME(str) str OPENCV_VERSION "d.lib"
#else
#define OPENCV_LIBRARY_NAME(str) str OPENCV_VERSION ".lib"
#endif
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_calib3d"))      // opencv_contrib
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_contrib"))      // opencv_contrib
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_core"))         // opencv_core
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_features2d"))   // opencv_features2d
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_flann"))        // opencv_flann
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_gpu"))          // opencv_gpu
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_highgui"))      // opencv_highgui
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_imgproc"))      // opencv_imgproc
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_legacy"))       // opencv_legacy
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_ml"))           // opencv_ml
#pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_objdetect"))    // opencv_objdetect

#if CV_MINOR_VERSION > 3
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_nonfree"))      // opencv_nonfree
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_photo"))        // opencv_photo
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_stitching"))    // opencv_stitching
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_superres"))     // opencv_superres
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_ts"))           // opencv_ts
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_video"))        // opencv_video
#   pragma comment(lib,OPENCV_LIBRARY_NAME("opencv_videostab"))    // opencv_videostab
#endif

#undef OPENCV_LIBRARY_NAME
#endif // #if defined(_WIN32) || defined(_WIN64)
#endif // #ifndef __CV_WAPPER_HPP__