#ifndef WINDOW_H
#define WINDOW_H
#include <wx/wx.h>


class Window : public wxApp
{
public:
    bool OnInit() override;
    int OnExit() override;
};

#endif //WINDOW_H