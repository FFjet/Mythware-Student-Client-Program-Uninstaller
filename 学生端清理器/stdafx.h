// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <tchar.h>
#include <fstream>
using namespace std;


// TODO: 在此处引用程序需要的其他头文件
#include <Windows.h>
#include <NTSecAPI.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib,"psapi.lib")
#pragma warning(disable:4267)