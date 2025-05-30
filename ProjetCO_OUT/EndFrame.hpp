#ifndef ENDFRAME_H
#define ENDFRAME_H

#include <wx/wx.h>

class EndFrame : public wxFrame
{
public:
    EndFrame(const wxString& title);
private:
    std::string GetRandomJpegFromFolder(const std::string& folderPath);
};

#endif
