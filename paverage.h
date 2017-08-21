// The master file: interface
#ifndef PAV_BASE_H
#define PAV_BASE_H

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif

#include "FileDetails.h"

// Main application
class PaverageApp: public wxApp {
    public:
        virtual bool OnInit();
};

#endif //PAV_BASE_H
