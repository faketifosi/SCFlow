// stdafx.h : 可在此標頭檔中包含標準的系統 Include 檔，
// 或是經常使用卻很少變更的
// 專案專用 Include 檔案
#pragma once

// TODO: 在此參考您的程式所需要的其他標頭
#pragma comment(lib,"cv210.lib")
#pragma comment(lib,"cxcore210.lib")
#pragma comment(lib,"highgui210.lib")

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <fstream> 
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <windows.h>


#include <msclr/marshal.h>        // .NET string to C-style string
#include <msclr/marshal_cppstd.h> // .NET string to STL string

using namespace std;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;