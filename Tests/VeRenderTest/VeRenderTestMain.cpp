////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Source File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  Module:      VeRenderTest
//  File name:   VeRenderTestMain.cpp
//  Created:     2015/08/04 by Napoleon
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#include "VeRenderTest.h"

VeInt32 VeEntry(const VeChar8* pcCmdLine) noexcept
{
	VeRenderTest app;
	app.Go();
	return 0;
}
