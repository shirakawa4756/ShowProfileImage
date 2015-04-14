///////////////////////////////////////////////////////////////////////////////////////////////////
//
// 読み込んだ画像の縦横プロファイルを表示します．
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
 * Windows のパス区切りを定義します
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = '\\';
#else
/*******************************************************************************************/// ***
/**
 * UNIX系 のパス区切りを定義します
 *
 *************************************************************************************************/
const wchar_t PATH_SEPARATOR = L'/';
#endif



/*******************************************************************************************/// ***
/**
 * フルパスからファイル名を抽出します．
 *
 * 例えば，C:\dir\image\abc.png という文字列が入力された場合，
 * abc.png という文字列を返します．
 *
 * ex.
 *    C:\dir\image\abc.png  -> abc.png
 *
 * @param path フルパス名
 * @return ファイル名
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
 * プロファイル情報を表示するウインドウの表題を作成します．
 *
 * 表題として，Profile Of `<filename>' という文字列を作成します．
 * 入力するファイル名は，フルパスでもよく，その場合は，ファイル名部分を抽出して
 * Profile Of `<filename>' という文字列を作成します．
 *
 * @param path フルパス
 * @return 表題
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

