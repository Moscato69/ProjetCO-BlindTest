#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/sizer.h>
#include "InputDeviceUDP.hpp"

#define VIEWPORTWIDTH 1920
#define VIEWPORTHEIGHT 1080

class FrameGrid : public wxFrame
{
public:
    FrameGrid(const wxString& title);
    void SetNumberOfTeams(int numTeams);
    void UpdateSizer();

private:
    static constexpr int ID_F12_CAPTURED = wxID_HIGHEST + 1;
    wxGridSizer* m_sizer;
    int m_numTeams;
    InputDeviceUDP client;
    wxTimer m_timer;  // Timer pour mise à jour automatique

    void OnTimer(wxTimerEvent& event);  // Méthode déclenchée par le timer
    void OnGlobalKey(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);


    wxDECLARE_EVENT_TABLE();
};
