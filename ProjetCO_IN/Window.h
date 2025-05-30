#ifndef WINDOW_H
#define WINDOW_H
#include <wx/wx.h>

class Window : public wxApp
{
public:
    bool OnInit() override;
};

#endif //WINDOW_H