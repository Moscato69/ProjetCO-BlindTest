//
// Created by matthias on 16/01/25.
//

#ifndef FRAME_HPP
#define FRAME_HPP
#include <wx/wx.h>
#include <wx/richtext/richtextctrl.h>


#define VIEWPORTWIDTH 1920
#define VIEWPORTHEIGHT 1280

#define BUTTONWIDTH 200
#define BUTTONHEIGHT 35
#define TEXTCTRLWIDTH 850
#define TEXTCTRLHEIGHT 25
#define INFOTEXTCTRLHEIGHT 275
#define CHOICEWIDTH 200
#define CHOICEHEIGHT 35
#define GAUGEHEIGTH 27

#define PARAMNUMBER 12

enum {
    TEAM1ADD = wxID_HIGHEST + 1,
    TEAM1DEL,
    TEAM1INC,
    TEAM1DEC,
    TEAM2ADD,
    TEAM2DEL,
    TEAM2INC,
    TEAM2DEC,
    TEAM3ADD,
    TEAM3DEL,
    TEAM3INC,
    TEAM3DEC,
    TEAM4ADD,
    TEAM4DEL,
    TEAM4INC,
    TEAM4DEC,
    TEAM5ADD,
    TEAM5DEL,
    TEAM5INC,
    TEAM5DEC,
    TEAM6ADD,
    TEAM6DEL,
    TEAM6INC,
    TEAM6DEC,
    TEAM7ADD,
    TEAM7DEL,
    TEAM7INC,
    TEAM7DEC,
    TEAM8ADD,
    TEAM8DEL,
    TEAM8INC,
    TEAM8DEC
};

class Frame : public wxFrame{
private:
    wxPanel *panel;

    int elementWidth = 280;
    int elementHeight = 100;

    uint8_t NbTeams = 0;

    wxTextCtrl *Team1_Name;
    wxTextCtrl *Team2_Name;
    wxTextCtrl *Team3_Name;
    wxTextCtrl *Team4_Name;
    wxTextCtrl *Team5_Name;
    wxTextCtrl *Team6_Name;
    wxTextCtrl *Team7_Name;
    wxTextCtrl *Team8_Name;

    wxTextCtrl *Team1_Score;
    wxTextCtrl *Team2_Score;
    wxTextCtrl *Team3_Score;
    wxTextCtrl *Team4_Score;
    wxTextCtrl *Team5_Score;
    wxTextCtrl *Team6_Score;
    wxTextCtrl *Team7_Score;
    wxTextCtrl *Team8_Score;

    wxButton *Team1_Add;
    wxButton *Team1_Del;
    wxButton *Team1_Inc;
    wxButton *Team1_Dec;

    wxButton *Team2_Add;
    wxButton *Team2_Del;
    wxButton *Team2_Inc;
    wxButton *Team2_Dec;

    wxButton *Team3_Add;
    wxButton *Team3_Del;
    wxButton *Team3_Inc;
    wxButton *Team3_Dec;

    wxButton *Team4_Add;
    wxButton *Team4_Del;
    wxButton *Team4_Inc;
    wxButton *Team4_Dec;

    wxButton *Team5_Add;
    wxButton *Team5_Del;
    wxButton *Team5_Inc;
    wxButton *Team5_Dec;

    wxButton *Team6_Add;
    wxButton *Team6_Del;
    wxButton *Team6_Inc;
    wxButton *Team6_Dec;

    wxButton *Team7_Add;
    wxButton *Team7_Del;
    wxButton *Team7_Inc;
    wxButton *Team7_Dec;

    wxButton *Team8_Add;
    wxButton *Team8_Del;
    wxButton *Team8_Inc;
    wxButton *Team8_Dec;

public:
    explicit Frame(const wxString& title);
    ~Frame() override;

    void onTeam1_AddClick(wxCommandEvent &event);
    void onTeam1_DelClick(wxCommandEvent &event);
    void onTeam1_IncClick(wxCommandEvent &event);
    void onTeam1_DecClick(wxCommandEvent &event);

    void onTeam2_AddClick(wxCommandEvent &event);
    void onTeam2_DelClick(wxCommandEvent &event);
    void onTeam2_IncClick(wxCommandEvent &event);
    void onTeam2_DecClick(wxCommandEvent &event);

    void onTeam3_AddClick(wxCommandEvent &event);
    void onTeam3_DelClick(wxCommandEvent &event);
    void onTeam3_IncClick(wxCommandEvent &event);
    void onTeam3_DecClick(wxCommandEvent &event);

    void onTeam4_AddClick(wxCommandEvent &event);
    void onTeam4_DelClick(wxCommandEvent &event);
    void onTeam4_IncClick(wxCommandEvent &event);
    void onTeam4_DecClick(wxCommandEvent &event);

    void onTeam5_AddClick(wxCommandEvent &event);
    void onTeam5_DelClick(wxCommandEvent &event);
    void onTeam5_IncClick(wxCommandEvent &event);
    void onTeam5_DecClick(wxCommandEvent &event);

    void onTeam6_AddClick(wxCommandEvent &event);
    void onTeam6_DelClick(wxCommandEvent &event);
    void onTeam6_IncClick(wxCommandEvent &event);
    void onTeam6_DecClick(wxCommandEvent &event);

    void onTeam7_AddClick(wxCommandEvent &event);
    void onTeam7_DelClick(wxCommandEvent &event);
    void onTeam7_IncClick(wxCommandEvent &event);
    void onTeam7_DecClick(wxCommandEvent &event);

    void onTeam8_AddClick(wxCommandEvent &event);
    void onTeam8_DelClick(wxCommandEvent &event);
    void onTeam8_IncClick(wxCommandEvent &event);
    void onTeam8_DecClick(wxCommandEvent &event);

    void ShiftTeamsLeft(uint8_t StartIndex);
    void OnResize(wxSizeEvent& event);
    void init();
    void SendUDP(const char* Cmd,const char* Data);
    wxDECLARE_EVENT_TABLE();
};



#endif //FRAME_HPP
