#include "Frame.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <iostream>
#include <cstdint>
#include <algorithm>

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_BUTTON(TEAM1ADD, Frame::onTeam1_AddClick)
    EVT_BUTTON(TEAM1DEL, Frame::onTeam1_DelClick)
    EVT_BUTTON(TEAM1INC, Frame::onTeam1_IncClick)
    EVT_BUTTON(TEAM1DEC, Frame::onTeam1_DecClick)
    EVT_BUTTON(TEAM2ADD, Frame::onTeam2_AddClick)
    EVT_BUTTON(TEAM2DEL, Frame::onTeam2_DelClick)
    EVT_BUTTON(TEAM2INC, Frame::onTeam2_IncClick)
    EVT_BUTTON(TEAM2DEC, Frame::onTeam2_DecClick)
    EVT_BUTTON(TEAM3ADD, Frame::onTeam3_AddClick)
    EVT_BUTTON(TEAM3DEL, Frame::onTeam3_DelClick)
    EVT_BUTTON(TEAM3INC, Frame::onTeam3_IncClick)
    EVT_BUTTON(TEAM3DEC, Frame::onTeam3_DecClick)
    EVT_BUTTON(TEAM4ADD, Frame::onTeam4_AddClick)
    EVT_BUTTON(TEAM4DEL, Frame::onTeam4_DelClick)
    EVT_BUTTON(TEAM4INC, Frame::onTeam4_IncClick)
    EVT_BUTTON(TEAM4DEC, Frame::onTeam4_DecClick)
    EVT_BUTTON(TEAM5ADD, Frame::onTeam5_AddClick)
    EVT_BUTTON(TEAM5DEL, Frame::onTeam5_DelClick)
    EVT_BUTTON(TEAM5INC, Frame::onTeam5_IncClick)
    EVT_BUTTON(TEAM5DEC, Frame::onTeam5_DecClick)
    EVT_BUTTON(TEAM6ADD, Frame::onTeam6_AddClick)
    EVT_BUTTON(TEAM6DEL, Frame::onTeam6_DelClick)
    EVT_BUTTON(TEAM6INC, Frame::onTeam6_IncClick)
    EVT_BUTTON(TEAM6DEC, Frame::onTeam6_DecClick)
    EVT_BUTTON(TEAM7ADD, Frame::onTeam7_AddClick)
    EVT_BUTTON(TEAM7DEL, Frame::onTeam7_DelClick)
    EVT_BUTTON(TEAM7INC, Frame::onTeam7_IncClick)
    EVT_BUTTON(TEAM7DEC, Frame::onTeam7_DecClick)
    EVT_BUTTON(TEAM8ADD, Frame::onTeam8_AddClick)
    EVT_BUTTON(TEAM8DEL, Frame::onTeam8_DelClick)
    EVT_BUTTON(TEAM8INC, Frame::onTeam8_IncClick)
    EVT_BUTTON(TEAM8DEC, Frame::onTeam8_DecClick)
    EVT_SIZE(Frame::OnResize)
wxEND_EVENT_TABLE()
Frame::Frame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(VIEWPORTWIDTH, VIEWPORTHEIGHT))
{
    panel = new wxPanel(this, wxID_ANY);

    wxSize size = GetClientSize();

    const int maxElementWidth = 280;
    const int maxElementHeight = 100;
    const int minElementWidth = maxElementWidth / 2;
    const int minElementHeight = maxElementHeight / 2;

    // Calculer en fonction de la fenêtre, puis limiter avec clamp
    elementWidth = std::clamp(size.GetWidth() / 4 - 25, minElementWidth, maxElementWidth);
    elementHeight = std::clamp(size.GetHeight() / 10, minElementHeight, maxElementHeight);

    Bind(wxEVT_SIZE, &Frame::OnResize, this);

    int offsetX = 50; // Décalage horizontal
    int offsetY = 100; // Décalage vertical
    int spacingY = 50; // Espacement vertical entre nom et score


    // Créer une police personnalisée avec une taille de 20 points
    wxFont customFont(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    // Première ligne (Noms des équipes 1 à 4)
    Team1_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX, offsetY), wxSize(elementWidth, elementHeight));
    Team2_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + elementWidth, offsetY), wxSize(elementWidth, elementHeight));
    Team3_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 2 * elementWidth, offsetY), wxSize(elementWidth, elementHeight));
    Team4_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 3 * elementWidth, offsetY), wxSize(elementWidth, elementHeight));

    Team1_Name->SetFont(customFont);
    Team2_Name->SetFont(customFont);
    Team3_Name->SetFont(customFont);
    Team4_Name->SetFont(customFont);

    // Première ligne (Scores des équipes 1 à 4)
    Team1_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX, offsetY + elementHeight + spacingY), wxSize(elementWidth, elementHeight));
    Team2_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + elementWidth, offsetY + elementHeight + spacingY), wxSize(elementWidth, elementHeight));
    Team3_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 2 * elementWidth, offsetY + elementHeight + spacingY), wxSize(elementWidth, elementHeight));
    Team4_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 3 * elementWidth, offsetY + elementHeight + spacingY), wxSize(elementWidth, elementHeight));

    Team1_Score->SetFont(customFont);
    Team2_Score->SetFont(customFont);
    Team3_Score->SetFont(customFont);
    Team4_Score->SetFont(customFont);

    // Deuxième ligne (Noms des équipes 5 à 8) - avec offset de +50 sur Y
    Team5_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX, offsetY + 2 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));
    Team6_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + elementWidth, offsetY + 2 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));
    Team7_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 2 * elementWidth, offsetY + 2 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));
    Team8_Name = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 3 * elementWidth, offsetY + 2 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));

    Team5_Name->SetFont(customFont);
    Team6_Name->SetFont(customFont);
    Team7_Name->SetFont(customFont);
    Team8_Name->SetFont(customFont);

    // Deuxième ligne (Scores des équipes 5 à 8) - avec offset de +50 sur Y
    Team5_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX, offsetY + 3 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));
    Team6_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + elementWidth, offsetY + 3 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));
    Team7_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 2 * elementWidth, offsetY + 3 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));
    Team8_Score = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(offsetX + 3 * elementWidth, offsetY + 3 * (elementHeight + spacingY) + 50), wxSize(elementWidth, elementHeight));

    Team5_Score->SetFont(customFont);
    Team6_Score->SetFont(customFont);
    Team7_Score->SetFont(customFont);
    Team8_Score->SetFont(customFont);

    // Ajustement des boutons pour Teams 1 à 4
    Team1_Add = new wxButton(panel, TEAM1ADD, "Ajouter", wxPoint(offsetX, offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team1_Del = new wxButton(panel, TEAM1DEL, "Supprimer", wxPoint(offsetX + (elementWidth / 2), offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team1_Inc = new wxButton(panel, TEAM1INC, "+", wxPoint(offsetX, offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));
    Team1_Dec = new wxButton(panel, TEAM1DEC, "-", wxPoint(offsetX + (elementWidth / 2), offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));

    Team2_Add = new wxButton(panel, TEAM2ADD, "Ajouter", wxPoint(offsetX + elementWidth, offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team2_Del = new wxButton(panel, TEAM2DEL, "Supprimer", wxPoint(offsetX + (elementWidth + (elementWidth / 2)), offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team2_Inc = new wxButton(panel, TEAM2INC, "+", wxPoint(offsetX + elementWidth, offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));
    Team2_Dec = new wxButton(panel, TEAM2DEC, "-", wxPoint(offsetX + (elementWidth + (elementWidth / 2)), offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));

    Team3_Add = new wxButton(panel, TEAM3ADD, "Ajouter", wxPoint(offsetX + 2 * elementWidth, offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team3_Del = new wxButton(panel, TEAM3DEL, "Supprimer", wxPoint(offsetX + (2 * elementWidth + (elementWidth / 2)), offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team3_Inc = new wxButton(panel, TEAM3INC, "+", wxPoint(offsetX + 2 * elementWidth, offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));
    Team3_Dec = new wxButton(panel, TEAM3DEC, "-", wxPoint(offsetX + (2 * elementWidth + (elementWidth / 2)), offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));

    Team4_Add = new wxButton(panel, TEAM4ADD, "Ajouter", wxPoint(offsetX + 3 * elementWidth, offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team4_Del = new wxButton(panel, TEAM4DEL, "Supprimer", wxPoint(offsetX + (3 * elementWidth + (elementWidth / 2)), offsetY - (elementHeight / 2)), wxSize(elementWidth / 2, elementHeight / 2));
    Team4_Inc = new wxButton(panel, TEAM4INC, "+", wxPoint(offsetX + 3 * elementWidth, offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));
    Team4_Dec = new wxButton(panel, TEAM4DEC, "-", wxPoint(offsetX + (3 * elementWidth + (elementWidth / 2)), offsetY + (elementHeight)), wxSize(elementWidth / 2, elementHeight / 2));

    // Ajustement des boutons pour Teams 5 à 8 - avec offset de +50 sur Y
    Team5_Add = new wxButton(panel, TEAM5ADD, "Ajouter", wxPoint(offsetX, offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team5_Del = new wxButton(panel, TEAM5DEL, "Supprimer", wxPoint(offsetX + elementWidth / 2, offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team5_Inc = new wxButton(panel, TEAM5INC, "+", wxPoint(offsetX, offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team5_Dec = new wxButton(panel, TEAM5DEC, "-", wxPoint(offsetX + elementWidth / 2, offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));

    Team6_Add = new wxButton(panel, TEAM6ADD, "Ajouter", wxPoint(offsetX + elementWidth, offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team6_Del = new wxButton(panel, TEAM6DEL, "Supprimer", wxPoint(offsetX + elementWidth + (elementWidth / 2), offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team6_Inc = new wxButton(panel, TEAM6INC, "+", wxPoint(offsetX + elementWidth, offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team6_Dec = new wxButton(panel, TEAM6DEC, "-", wxPoint(offsetX + elementWidth + (elementWidth / 2), offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));

    Team7_Add = new wxButton(panel, TEAM7ADD, "Ajouter", wxPoint(offsetX + 2 * elementWidth, offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team7_Del = new wxButton(panel, TEAM7DEL, "Supprimer", wxPoint(offsetX + 2 * elementWidth + (elementWidth / 2), offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team7_Inc = new wxButton(panel, TEAM7INC, "+", wxPoint(offsetX + 2 * elementWidth, offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team7_Dec = new wxButton(panel, TEAM7DEC, "-", wxPoint(offsetX + 2 * elementWidth + (elementWidth / 2), offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));

    Team8_Add = new wxButton(panel, TEAM8ADD, "Ajouter", wxPoint(offsetX + 3 * elementWidth, offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team8_Del = new wxButton(panel, TEAM8DEL, "Supprimer", wxPoint(offsetX + 3 * elementWidth + (elementWidth / 2), offsetY + 2 * (elementHeight + spacingY / 2) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team8_Inc = new wxButton(panel, TEAM8INC, "+", wxPoint(offsetX + 3 * elementWidth, offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));
    Team8_Dec = new wxButton(panel, TEAM8DEC, "-", wxPoint(offsetX + 3 * elementWidth + (elementWidth / 2), offsetY + 2 * (elementHeight + 2 * spacingY) + 50), wxSize(elementWidth / 2, elementHeight / 2));

    Frame::init();
}

Frame::~Frame() = default;

void Frame::onTeam1_AddClick(wxCommandEvent &event){
    if (Team1_Name->GetValue() != "")
    {
        wxString team1Name = Team1_Name->GetValue();
        std::string team1NameStd = team1Name.ToStdString();
        const char* team1NameCStr = team1NameStd.c_str();
        std::cout << team1NameCStr << std::endl;
        SendUDP("add", team1NameCStr);
        Team1_Del->Show();Team1_Dec->Show();Team1_Inc->Show();Team1_Add->Hide();
        Team2_Name->Show();Team2_Add->Show();
        Team1_Name->SetEditable(false);
        NbTeams = 1;
    }
}

void Frame::onTeam1_DelClick(wxCommandEvent &event){
    if (NbTeams >= 1)
    {
        SendUDP("del", Team1_Name->GetValue());
        ShiftTeamsLeft(1);
    }
}

void Frame::onTeam1_IncClick(wxCommandEvent& event)
{
    wxString team1Score = Team1_Score->GetValue();
    std::string team1ScoreStd = team1Score.ToStdString();
    const char* team1ScoreCStr = team1Score.c_str();
    std::cout << team1ScoreCStr << std::endl;

    wxString team1Name = Team1_Name->GetValue();
    std::string team1NameStd = team1Name.ToStdString();
    const char* team1NameCStr = team1NameStd.c_str();
    std::cout << team1NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team1NameCStr);
    Team1_Score->Clear();
}

void Frame::onTeam1_DecClick(wxCommandEvent &event)
{
    wxString team1Score = Team1_Score->GetValue();
    std::string team1ScoreStd = team1Score.ToStdString();
    const char* team1ScoreCStr = team1Score.c_str();
    std::cout << team1ScoreCStr << std::endl;

    wxString team1Name = Team1_Name->GetValue();
    std::string team1NameStd = team1Name.ToStdString();
    const char* team1NameCStr = team1NameStd.c_str();
    std::cout << team1NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team1NameCStr);
    Team1_Score->Clear();
}

void Frame::onTeam2_AddClick(wxCommandEvent &event){
    if (Team2_Name->GetValue() != "")
    {
        wxString team2Name = Team2_Name->GetValue();
        std::string team2NameStd = team2Name.ToStdString();
        const char* team2NameCStr = team2NameStd.c_str();
        std::cout << team2NameCStr << std::endl;
        SendUDP("add", team2NameCStr);
        Team2_Del->Show();Team2_Dec->Show();Team2_Inc->Show();Team2_Add->Hide();
        Team3_Name->Show();Team3_Add->Show();
        Team2_Name->SetEditable(false);
        NbTeams = 2;
    }
}

void Frame::onTeam2_DelClick(wxCommandEvent &event){
    if (NbTeams >= 2)
    {
        SendUDP("del", Team2_Name->GetValue());
        ShiftTeamsLeft(2);
    }
}

void Frame::onTeam2_IncClick(wxCommandEvent& event)
{
    wxString team2Score = Team2_Score->GetValue();
    std::string team2ScoreStd = team2Score.ToStdString();
    const char* team2ScoreCStr = team2Score.c_str();
    std::cout << team2ScoreCStr << std::endl;

    wxString team2Name = Team2_Name->GetValue();
    std::string team2NameStd = team2Name.ToStdString();
    const char* team2NameCStr = team2NameStd.c_str();
    std::cout << team2NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team2NameCStr);
    Team2_Score->Clear();
}

void Frame::onTeam2_DecClick(wxCommandEvent &event)
{
    wxString team2Score = Team2_Score->GetValue();
    std::string team2ScoreStd = team2Score.ToStdString();
    const char* team2ScoreCStr = team2Score.c_str();
    std::cout << team2ScoreCStr << std::endl;

    wxString team2Name = Team2_Name->GetValue();
    std::string team2NameStd = team2Name.ToStdString();
    const char* team2NameCStr = team2NameStd.c_str();
    std::cout << team2NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team2NameCStr);
    Team2_Score->Clear();
}

void Frame::onTeam3_AddClick(wxCommandEvent &event){
    if (Team3_Name->GetValue() != "")
    {
        wxString team3Name = Team3_Name->GetValue();
        std::string team3NameStd = team3Name.ToStdString();
        const char* team3NameCStr = team3NameStd.c_str();
        std::cout << team3NameCStr << std::endl;
        SendUDP("add", team3NameCStr);
        Team3_Del->Show();Team3_Dec->Show();Team3_Inc->Show();Team3_Add->Hide();
        Team4_Name->Show();Team4_Add->Show();
        Team3_Name->SetEditable(false);
        NbTeams = 3;
    }
}

void Frame::onTeam3_DelClick(wxCommandEvent &event)
{
    if (NbTeams >= 3)
    {
        SendUDP("del", Team3_Name->GetValue());
        ShiftTeamsLeft(3);
    }
}

void Frame::onTeam3_IncClick(wxCommandEvent& event)
{
    wxString team3Score = Team3_Score->GetValue();
    std::string team3ScoreStd = team3Score.ToStdString();
    const char* team3ScoreCStr = team3Score.c_str();
    std::cout << team3ScoreCStr << std::endl;

    wxString team3Name = Team3_Name->GetValue();
    std::string team3NameStd = team3Name.ToStdString();
    const char* team3NameCStr = team3NameStd.c_str();
    std::cout << team3NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team3NameCStr);
    Team3_Score->Clear();
}

void Frame::onTeam3_DecClick(wxCommandEvent &event)
{
    wxString team3Score = Team3_Score->GetValue();
    std::string team3ScoreStd = team3Score.ToStdString();
    const char* team3ScoreCStr = team3Score.c_str();
    std::cout << team3ScoreCStr << std::endl;

    wxString team3Name = Team3_Name->GetValue();
    std::string team3NameStd = team3Name.ToStdString();
    const char* team3NameCStr = team3NameStd.c_str();
    std::cout << team3NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("lsteams", ""/*team3NameCStr*/);
    Team3_Score->Clear();
}

void Frame::onTeam4_AddClick(wxCommandEvent &event){
    if (Team4_Name->GetValue() != "")
    {
        wxString team4Name = Team4_Name->GetValue();
        std::string team4NameStd = team4Name.ToStdString();
        const char* team4NameCStr = team4NameStd.c_str();
        std::cout << team4NameCStr << std::endl;
        SendUDP("add", team4NameCStr);
        Team4_Del->Show();Team4_Dec->Show();Team4_Inc->Show();Team4_Add->Hide();
        Team5_Name->Show();Team5_Add->Show();
        Team4_Name->SetEditable(false);
        NbTeams = 4;
    }
}

void Frame::onTeam4_DelClick(wxCommandEvent &event){
    if (NbTeams >= 4)
    {
        SendUDP("del", Team4_Name->GetValue());
        ShiftTeamsLeft(4);
    }
}

void Frame::onTeam4_IncClick(wxCommandEvent& event)
{
    wxString team4Score = Team4_Score->GetValue();
    std::string team4ScoreStd = team4Score.ToStdString();
    const char* team4ScoreCStr = team4Score.c_str();
    std::cout << team4ScoreCStr << std::endl;

    wxString team4Name = Team4_Name->GetValue();
    std::string team4NameStd = team4Name.ToStdString();
    const char* team4NameCStr = team4NameStd.c_str();
    std::cout << team4NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team4NameCStr);
    Team4_Score->Clear();
}

void Frame::onTeam4_DecClick(wxCommandEvent &event)
{
    wxString team4Score = Team4_Score->GetValue();
    std::string team4ScoreStd = team4Score.ToStdString();
    const char* team4ScoreCStr = team4Score.c_str();
    std::cout << team4ScoreCStr << std::endl;

    wxString team4Name = Team4_Name->GetValue();
    std::string team4NameStd = team4Name.ToStdString();
    const char* team4NameCStr = team4NameStd.c_str();
    std::cout << team4NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team4NameCStr);
    Team4_Score->Clear();
}

void Frame::onTeam5_AddClick(wxCommandEvent &event){
    if (Team5_Name->GetValue() != "")
    {
        wxString team5Name = Team5_Name->GetValue();
        std::string team5NameStd = team5Name.ToStdString();
        const char* team5NameCStr = team5NameStd.c_str();
        std::cout << team5NameCStr << std::endl;
        SendUDP("add", team5NameCStr);
        Team5_Del->Show();Team5_Dec->Show();Team5_Inc->Show();Team5_Add->Hide();
        Team6_Name->Show();Team6_Add->Show();
        Team5_Name->SetEditable(false);
        NbTeams = 5;
    }
}

void Frame::onTeam5_DelClick(wxCommandEvent &event){
    if (NbTeams >= 5)
    {
        SendUDP("del", Team5_Name->GetValue());
        ShiftTeamsLeft(5);
    }
}

void Frame::onTeam5_IncClick(wxCommandEvent& event)
{
    wxString team5Score = Team5_Score->GetValue();
    std::string team5ScoreStd = team5Score.ToStdString();
    const char* team5ScoreCStr = team5Score.c_str();
    std::cout << team5ScoreCStr << std::endl;

    wxString team5Name = Team5_Name->GetValue();
    std::string team5NameStd = team5Name.ToStdString();
    const char* team5NameCStr = team5NameStd.c_str();
    std::cout << team5NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team5NameCStr);
    Team5_Score->Clear();
}

void Frame::onTeam5_DecClick(wxCommandEvent &event)
{
    wxString team5Score = Team5_Score->GetValue();
    std::string team5ScoreStd = team5Score.ToStdString();
    const char* team5ScoreCStr = team5Score.c_str();
    std::cout << team5ScoreCStr << std::endl;

    wxString team5Name = Team5_Name->GetValue();
    std::string team5NameStd = team5Name.ToStdString();
    const char* team5NameCStr = team5NameStd.c_str();
    std::cout << team5NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team5NameCStr);
    Team5_Score->Clear();
}

void Frame::onTeam6_AddClick(wxCommandEvent &event){
    if (Team6_Name->GetValue() != "")
    {
        wxString team6Name = Team6_Name->GetValue();
        std::string team6NameStd = team6Name.ToStdString();
        const char* team6NameCStr = team6NameStd.c_str();
        std::cout << team6NameCStr << std::endl;
        SendUDP("add", team6NameCStr);
        Team6_Del->Show();Team6_Dec->Show();Team6_Inc->Show();Team6_Add->Hide();
        Team7_Name->Show();Team7_Add->Show();
        Team6_Name->SetEditable(false);
        NbTeams = 6;
    }

}

void Frame::onTeam6_DelClick(wxCommandEvent &event){
    if (NbTeams >= 6)
    {
        SendUDP("del", Team6_Name->GetValue());
        ShiftTeamsLeft(6);
    }
}

void Frame::onTeam6_IncClick(wxCommandEvent& event)
{
    wxString team6Score = Team6_Score->GetValue();
    std::string team6ScoreStd = team6Score.ToStdString();
    const char* team6ScoreCStr = team6Score.c_str();
    std::cout << team6ScoreCStr << std::endl;

    wxString team6Name = Team6_Name->GetValue();
    std::string team6NameStd = team6Name.ToStdString();
    const char* team6NameCStr = team6NameStd.c_str();
    std::cout << team6NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team6NameCStr);
    Team6_Score->Clear();
}

void Frame::onTeam6_DecClick(wxCommandEvent &event)
{
    wxString team6Score = Team6_Score->GetValue();
    std::string team6ScoreStd = team6Score.ToStdString();
    const char* team6ScoreCStr = team6Score.c_str();
    std::cout << team6ScoreCStr << std::endl;

    wxString team6Name = Team6_Name->GetValue();
    std::string team6NameStd = team6Name.ToStdString();
    const char* team6NameCStr = team6NameStd.c_str();
    std::cout << team6NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team6NameCStr);
    Team6_Score->Clear();
}

void Frame::onTeam7_AddClick(wxCommandEvent &event){
    if (Team7_Name->GetValue() != "")
    {
        wxString team7Name = Team7_Name->GetValue();
        std::string team7NameStd = team7Name.ToStdString();
        const char* team7NameCStr = team7NameStd.c_str();
        std::cout << team7NameCStr << std::endl;
        SendUDP("add", team7NameCStr);
        Team7_Del->Show();Team7_Dec->Show();Team7_Inc->Show();Team7_Add->Hide();
        Team8_Name->Show();Team8_Add->Show();
        Team7_Name->SetEditable(false);
        NbTeams = 7;
    }
}

void Frame::onTeam7_DelClick(wxCommandEvent &event){
    if (NbTeams >= 7)
    {
        SendUDP("del", Team7_Name->GetValue());
        ShiftTeamsLeft(7);
    }
}

void Frame::onTeam7_IncClick(wxCommandEvent& event)
{
    wxString team7Score = Team7_Score->GetValue();
    std::string team7ScoreStd = team7Score.ToStdString();
    const char* team7ScoreCStr = team7Score.c_str();
    std::cout << team7ScoreCStr << std::endl;

    wxString team7Name = Team7_Name->GetValue();
    std::string team7NameStd = team7Name.ToStdString();
    const char* team7NameCStr = team7NameStd.c_str();
    std::cout << team7NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team7NameCStr);
    Team7_Score->Clear();
}

void Frame::onTeam7_DecClick(wxCommandEvent &event)
{
    wxString team7Score = Team7_Score->GetValue();
    std::string team7ScoreStd = team7Score.ToStdString();
    const char* team7ScoreCStr = team7Score.c_str();
    std::cout << team7ScoreCStr << std::endl;

    wxString team7Name = Team7_Name->GetValue();
    std::string team7NameStd = team7Name.ToStdString();
    const char* team7NameCStr = team7NameStd.c_str();
    std::cout << team7NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team7NameCStr);
    Team7_Score->Clear();
}

void Frame::onTeam8_AddClick(wxCommandEvent &event){
    if (Team8_Name->GetValue() != "")
    {
        wxString team8Name = Team8_Name->GetValue();
        std::string team8NameStd = team8Name.ToStdString();
        const char* team8NameCStr = team8NameStd.c_str();
        std::cout << team8NameCStr << std::endl;
        SendUDP("add", team8NameCStr);
        Team8_Del->Show();Team8_Dec->Show();Team8_Inc->Show();Team8_Add->Hide();
        Team8_Name->SetEditable(false);
        NbTeams = 8;
    }
}

void Frame::onTeam8_DelClick(wxCommandEvent &event){
    if (NbTeams == 8)
    {
        wxString team8Name = Team8_Name->GetValue();
        std::string team8NameStd = team8Name.ToStdString();
        const char* team8NameCStr = team8NameStd.c_str();
        std::cout << team8NameCStr << std::endl;
        SendUDP("del", team8NameCStr);
        Team8_Name->Clear();
        Team8_Del->Hide();Team8_Dec->Hide();Team8_Inc->Hide();Team8_Score->Hide();Team8_Add->Show();
        NbTeams = 7;
        Team8_Name->SetEditable(true);
    }
}

void Frame::onTeam8_IncClick(wxCommandEvent& event)
{
    wxString team8Score = Team8_Score->GetValue();
    std::string team8ScoreStd = team8Score.ToStdString();
    const char* team8ScoreCStr = team8Score.c_str();
    std::cout << team8ScoreCStr << std::endl;

    wxString team8Name = Team8_Name->GetValue();
    std::string team8NameStd = team8Name.ToStdString();
    const char* team8NameCStr = team8NameStd.c_str();
    std::cout << team8NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("inc", team8NameCStr);
    Team8_Score->Clear();
}

void Frame::onTeam8_DecClick(wxCommandEvent &event)
{
    wxString team8Score = Team8_Score->GetValue();
    std::string team8ScoreStd = team8Score.ToStdString();
    const char* team8ScoreCStr = team8Score.c_str();
    std::cout << team8ScoreCStr << std::endl;

    wxString team8Name = Team8_Name->GetValue();
    std::string team8NameStd = team8Name.ToStdString();
    const char* team8NameCStr = team8NameStd.c_str();
    std::cout << team8NameCStr << std::endl;

    //on envoi pas le nombre pour le moment car pas implémenté
    SendUDP("dec", team8NameCStr);
    Team8_Score->Clear();
}

void Frame::SendUDP(const char* Cmd, const char* Data)
{
    // Créer le socket UDP
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Erreur lors de la création du socket." << std::endl;
    }
    // Configurer l'adresse du serveur
    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    std::string adresseServeur = "127.0.0.1";
    if (inet_aton(adresseServeur.c_str(), &servaddr.sin_addr) == 0) {
        std::cerr << "Adresse IP du serveur invalide." << std::endl;
        close(sockfd);
    }
    // Préparer le message à envoyer
    std::string message = std::string(Cmd) + ";" + std::string(Data);
    // Envoyer le message au serveur
    ssize_t bytesSent = sendto(sockfd, message.c_str(), message.size(), 0,
                               reinterpret_cast<sockaddr*>(&servaddr), sizeof(servaddr));
    if (bytesSent < 0) {
        std::cerr << "Erreur lors de l'envoi du message." << std::endl;
    } else
    {
        std::cout << "Commande envoyée : " << message << std::endl;
        // Fermer le socket
        close(sockfd);
    }
}

void Frame::ShiftTeamsLeft(uint8_t StartIndex) {
    wxTextCtrl* nameFields[8] = {
        Team1_Name, Team2_Name, Team3_Name, Team4_Name,
        Team5_Name, Team6_Name, Team7_Name, Team8_Name
    };

    wxTextCtrl* scoreFields[8] = {
        Team1_Score, Team2_Score, Team3_Score, Team4_Score,
        Team5_Score, Team6_Score, Team7_Score, Team8_Score
    };

    wxButton* delButtons[8] = {
        Team1_Del, Team2_Del, Team3_Del, Team4_Del,
        Team5_Del, Team6_Del, Team7_Del, Team8_Del
    };

    wxButton* incButtons[8] = {
        Team1_Inc, Team2_Inc, Team3_Inc, Team4_Inc,
        Team5_Inc, Team6_Inc, Team7_Inc, Team8_Inc
    };

    wxButton* decButtons[8] = {
        Team1_Dec, Team2_Dec, Team3_Dec, Team4_Dec,
        Team5_Dec, Team6_Dec, Team7_Dec, Team8_Dec
    };

    wxButton* addButtons[8] = {
        Team1_Add, Team2_Add, Team3_Add, Team4_Add,
        Team5_Add, Team6_Add, Team7_Add, Team8_Add
    };

    for (int i = StartIndex; i < NbTeams; i++)
    {
        nameFields[i-1]->SetValue(nameFields[i]->GetValue());
        scoreFields[i-1]->SetValue(scoreFields[i]->GetValue());
    }


    // Nettoyer le dernier slot
    nameFields[NbTeams-1]->Clear();
    scoreFields[NbTeams-1]->Clear();
    delButtons[NbTeams-1]->Hide();
    incButtons[NbTeams-1]->Hide();
    decButtons[NbTeams-1]->Hide();
    scoreFields[NbTeams-1]->Hide();
    addButtons[NbTeams-1]->Show();
    nameFields[NbTeams-1]->SetEditable(true);
    if (NbTeams < 8)
    {
        addButtons[NbTeams]->Hide();
        nameFields[NbTeams]->Hide();
    }
    NbTeams--;
}

void Frame::OnResize(wxSizeEvent& event)
{
    wxSize size = GetClientSize();

    const int maxElementWidth = 280;
    const int maxElementHeight = 100;
    const int minElementWidth = maxElementWidth / 2;
    const int minElementHeight = maxElementHeight / 2;

    elementWidth = std::clamp(size.GetWidth() / 4 - 25, minElementWidth, maxElementWidth);
    elementHeight = std::clamp(size.GetHeight() / 6, minElementHeight, maxElementHeight);
    std::cout << elementWidth << " " << elementHeight << std::endl;
    std::cout << elementWidth << " " << elementHeight << std::endl;

    int offsetX = 50;
    int offsetY = 100;
    int spacingY = 50;

    // Ligne 1 - Noms
    Team1_Name->SetSize(wxRect(offsetX, offsetY, elementWidth, elementHeight));
    Team2_Name->SetSize(wxRect(offsetX + elementWidth, offsetY, elementWidth, elementHeight));
    Team3_Name->SetSize(wxRect(offsetX + 2 * elementWidth, offsetY, elementWidth, elementHeight));
    Team4_Name->SetSize(wxRect(offsetX + 3 * elementWidth, offsetY, elementWidth, elementHeight));
    
    // Ligne 3 - Noms 5 à 8
    int offsetY2 = offsetY + 2 * (elementHeight + spacingY) + 50;
    std::cout << offsetY2 << std::endl;
    Team5_Name->SetSize(wxRect(offsetX, offsetY2, elementWidth, elementHeight));
    Team6_Name->SetSize(wxRect(offsetX + elementWidth, offsetY2, elementWidth, elementHeight));
    Team7_Name->SetSize(wxRect(offsetX + 2 * elementWidth, offsetY2, elementWidth, elementHeight));
    Team8_Name->SetSize(wxRect(offsetX + 3 * elementWidth, offsetY2, elementWidth, elementHeight));
    

    // Boutons Teams 1 à 4
    Team1_Add->SetSize(wxRect(offsetX, offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team1_Del->SetSize(wxRect(offsetX + (elementWidth / 2), offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team1_Inc->SetSize(wxRect(offsetX + (elementWidth / 2), offsetY + elementHeight, elementWidth / 2, elementHeight / 2));
    Team1_Dec->SetSize(wxRect(offsetX, offsetY + elementHeight, elementWidth / 2, elementHeight / 2));

    Team2_Add->SetSize(wxRect(offsetX + elementWidth, offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team2_Del->SetSize(wxRect(offsetX + elementWidth + (elementWidth / 2), offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team2_Inc->SetSize(wxRect(offsetX + elementWidth + (elementWidth / 2), offsetY + elementHeight, elementWidth / 2, elementHeight / 2));
    Team2_Dec->SetSize(wxRect(offsetX + elementWidth, offsetY + elementHeight, elementWidth / 2, elementHeight / 2));

    Team3_Add->SetSize(wxRect(offsetX + 2 * elementWidth, offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team3_Del->SetSize(wxRect(offsetX + 2 * elementWidth + (elementWidth / 2), offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team3_Inc->SetSize(wxRect(offsetX + 2 * elementWidth + (elementWidth / 2), offsetY + elementHeight, elementWidth / 2, elementHeight / 2));
    Team3_Dec->SetSize(wxRect(offsetX + 2 * elementWidth, offsetY + elementHeight, elementWidth / 2, elementHeight / 2));

    Team4_Add->SetSize(wxRect(offsetX + 3 * elementWidth, offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team4_Del->SetSize(wxRect(offsetX + 3 * elementWidth + (elementWidth / 2), offsetY - (elementHeight / 2), elementWidth / 2, elementHeight / 2));
    Team4_Inc->SetSize(wxRect(offsetX + 3 * elementWidth + (elementWidth / 2), offsetY + elementHeight, elementWidth / 2, elementHeight / 2));
    Team4_Dec->SetSize(wxRect(offsetX + 3 * elementWidth, offsetY + elementHeight, elementWidth / 2, elementHeight / 2));

    // Boutons Teams 5 à 8
    int by1 = offsetY + 2 * (elementHeight + spacingY / 2) + 50;
    std::cout << by1 << std::endl;
    int by2 = offsetY + 2 * (elementHeight + 2 * spacingY) + 50;
    std::cout << by2 << std::endl;

    Team5_Add->SetSize(wxRect(offsetX, by1, elementWidth / 2, elementHeight / 2));
    Team5_Del->SetSize(wxRect(offsetX + elementWidth / 2, by1, elementWidth / 2, elementHeight / 2));
    Team5_Inc->SetSize(wxRect(offsetX + elementWidth / 2, by2, elementWidth / 2, elementHeight / 2));
    Team5_Dec->SetSize(wxRect(offsetX, by2, elementWidth / 2, elementHeight / 2));

    Team6_Add->SetSize(wxRect(offsetX + elementWidth, by1, elementWidth / 2, elementHeight / 2));
    Team6_Del->SetSize(wxRect(offsetX + elementWidth + elementWidth / 2, by1, elementWidth / 2, elementHeight / 2));
    Team6_Inc->SetSize(wxRect(offsetX + elementWidth + elementWidth / 2, by2, elementWidth / 2, elementHeight / 2));
    Team6_Dec->SetSize(wxRect(offsetX + elementWidth, by2, elementWidth / 2, elementHeight / 2));

    Team7_Add->SetSize(wxRect(offsetX + 2 * elementWidth, by1, elementWidth / 2, elementHeight / 2));
    Team7_Del->SetSize(wxRect(offsetX + 2 * elementWidth + elementWidth / 2, by1, elementWidth / 2, elementHeight / 2));
    Team7_Inc->SetSize(wxRect(offsetX + 2 * elementWidth + elementWidth / 2, by2, elementWidth / 2, elementHeight / 2));
    Team7_Dec->SetSize(wxRect(offsetX + 2 * elementWidth, by2, elementWidth / 2, elementHeight / 2));

    Team8_Add->SetSize(wxRect(offsetX + 3 * elementWidth, by1, elementWidth / 2, elementHeight / 2));
    Team8_Del->SetSize(wxRect(offsetX + 3 * elementWidth + elementWidth / 2, by1, elementWidth / 2, elementHeight / 2));
    Team8_Inc->SetSize(wxRect(offsetX + 3 * elementWidth + elementWidth / 2, by2, elementWidth / 2, elementHeight / 2));
    Team8_Dec->SetSize(wxRect(offsetX + 3 * elementWidth, by2, elementWidth / 2, elementHeight / 2));


    event.Skip();
}


void Frame::init()
{
    Team1_Del->Hide();
    Team1_Inc->Hide();
    Team1_Dec->Hide();
    Team1_Score->Hide();

    Team2_Add->Hide();
    Team2_Del->Hide();
    Team2_Inc->Hide();
    Team2_Dec->Hide();
    Team2_Score->Hide();
    Team2_Name->Hide();

    Team3_Add->Hide();
    Team3_Del->Hide();
    Team3_Inc->Hide();
    Team3_Dec->Hide();
    Team3_Score->Hide();
    Team3_Name->Hide();

    Team4_Add->Hide();
    Team4_Del->Hide();
    Team4_Inc->Hide();
    Team4_Dec->Hide();
    Team4_Score->Hide();
    Team4_Name->Hide();

    Team5_Add->Hide();
    Team5_Del->Hide();
    Team5_Inc->Hide();
    Team5_Dec->Hide();
    Team5_Score->Hide();
    Team5_Name->Hide();

    Team6_Add->Hide();
    Team6_Del->Hide();
    Team6_Inc->Hide();
    Team6_Dec->Hide();
    Team6_Score->Hide();
    Team6_Name->Hide();

    Team7_Add->Hide();
    Team7_Del->Hide();
    Team7_Inc->Hide();
    Team7_Dec->Hide();
    Team7_Score->Hide();
    Team7_Name->Hide();

    Team8_Add->Hide();
    Team8_Del->Hide();
    Team8_Inc->Hide();
    Team8_Dec->Hide();
    Team8_Score->Hide();
    Team8_Name->Hide();

    Team1_Inc->SetBackgroundColour(*wxGREEN);
    Team1_Dec->SetBackgroundColour(*wxRED);

    Team2_Inc->SetBackgroundColour(*wxGREEN);
    Team2_Dec->SetBackgroundColour(*wxRED);

    Team3_Inc->SetBackgroundColour(*wxGREEN);
    Team3_Dec->SetBackgroundColour(*wxRED);

    Team4_Inc->SetBackgroundColour(*wxGREEN);
    Team4_Dec->SetBackgroundColour(*wxRED);

    Team5_Inc->SetBackgroundColour(*wxGREEN);
    Team5_Dec->SetBackgroundColour(*wxRED);

    Team6_Inc->SetBackgroundColour(*wxGREEN);
    Team6_Dec->SetBackgroundColour(*wxRED);

    Team7_Inc->SetBackgroundColour(*wxGREEN);
    Team7_Dec->SetBackgroundColour(*wxRED);

    Team8_Inc->SetBackgroundColour(*wxGREEN);
    Team8_Dec->SetBackgroundColour(*wxRED);
}
