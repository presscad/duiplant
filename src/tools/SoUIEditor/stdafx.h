// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#include <dui/duistd.h>
#include <dui/duihostwnd.h>
#include <dui/duictrls.h>
#include <dui/duiwndnotify.h>
#include <dui/DuiCSS.h>

#include "resource.h"	//win32 id

#include "FileHelper.h"

using namespace DuiEngine;
using namespace pugi;

#include "SoUIHelper.h"
#include "SkinView.h"
#include "colorpicker/DuiColorPicker.h"


#ifdef _DEBUG

	#if defined(DLL_DUI)
	# pragma comment(lib, "duiengine-win32-debug-shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-debug-static.lib")
	#endif


#else


	#if defined(DLL_DUI)
	# pragma comment(lib, "duiengine-win32-release-shared.lib")
	#else
	# pragma comment(lib, "duiengine-win32-release-static.lib")
	#endif



#endif


