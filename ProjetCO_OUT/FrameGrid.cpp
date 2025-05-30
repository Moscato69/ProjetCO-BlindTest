#include "FrameGrid.hpp"
#include "InputDeviceUDP.hpp"
#include "EndFrame.hpp"

// Associer l'événement du timer à la méthode OnTimer
wxBEGIN_EVENT_TABLE(FrameGrid, wxFrame)
    EVT_TIMER(wxID_ANY, FrameGrid::OnTimer)
    EVT_CHAR_HOOK(FrameGrid::OnKeyDown)
    EVT_COMMAND(wxID_ANY, wxEVT_MENU, FrameGrid::OnGlobalKey)

wxEND_EVENT_TABLE()

FrameGrid::FrameGrid(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(VIEWPORTWIDTH, VIEWPORTHEIGHT)),
      m_sizer(nullptr), m_numTeams(0), m_timer(this)  // Initialisation du timer
{
    wxSize screenSize = wxGetDisplaySize();
    UpdateSizer();
    SetSize(screenSize);
    Centre();

    // Démarrer le timer avec un intervalle de 1000 ms (1 seconde)
    m_timer.Start(1000);
}

void FrameGrid::SetNumberOfTeams(int numTeams)
{
    m_numTeams = numTeams;
}

void FrameGrid::UpdateSizer() {
    // Récupérer les équipes du client
    const auto& teams = client.getTeams();
    m_numTeams = client.getNumTeams();
    std::cout << m_numTeams << std::endl;
    if (m_numTeams >0)
    {
        // Réinitialiser le sizer
        if (m_sizer) {
            m_sizer->Clear(true);
        }

        int numColumns = std::ceil(static_cast<float>(m_numTeams) / 2);
        int numRows = std::ceil(static_cast<float>(m_numTeams) / numColumns);
        m_sizer = new wxGridSizer(numRows, numColumns, 0, 10); // Espacement horizontal seulement

        wxFont font(30, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

        // Créer les panels pour chaque équipe
        for (int i = 0; i < m_numTeams; i++) {
            if (i >= teams.size()) {
                std::cerr << "Erreur : tentative d'accès hors limite dans UpdateSizer" << std::endl;
                continue;
            }

            wxPanel* panel = new wxPanel(this);
            panel->SetBackgroundColour(*wxLIGHT_GREY);
            wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);

            // Nom de l'équipe (jusqu'à 25 caractères max)
            std::string fullName = teams[i].name;
            std::string line1, line2;
            if (fullName.size() > 13) {
                line1 = fullName.substr(0, 13);  // Première partie (12 caractères max)
                line2 = fullName.substr(13);      // Le reste du nom après 12 caractères
            } else {
                line1 = fullName;
                line2 = "";  // Pas besoin de ligne 2 si le nom est plus court
            }

            // Première ligne du nom
            wxStaticText* nameText1 = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8(line1.c_str()));
            nameText1->SetFont(font);
            panelSizer->Add(nameText1, wxSizerFlags().Center().Border(wxALL, 2));

            // Afficher la deuxième partie seulement si elle n'est pas vide
            if (!line2.empty()) {
                wxStaticText* nameText2 = new wxStaticText(panel, wxID_ANY, wxString::FromUTF8(line2.c_str()));
                nameText2->SetFont(font);
                panelSizer->Add(nameText2, wxSizerFlags().Center().Border(wxALL, 2));
            }

            // Score de l'équipe
            wxStaticText* scoreText = new wxStaticText(panel, wxID_ANY, wxString::Format("Score: %d", teams[i].score));
            scoreText->SetFont(font);
            panelSizer->Add(scoreText, wxSizerFlags().Center().Border(wxALL, 5));

            // Appliquer le sizer et ajouter le panel à m_sizer
            panel->SetSizer(panelSizer);
            m_sizer->Add(panel, wxSizerFlags().Expand().Border(wxALL, 5));
        }

        // Mettre à jour l'affichage avec le nouveau sizer
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->AddStretchSpacer(1); // Espace vide avant
        mainSizer->Add(m_sizer, wxSizerFlags().Center().Expand());
        mainSizer->AddStretchSpacer(1); // Espace vide après
        SetSizerAndFit(mainSizer);
        Layout();
    }
}


// Méthode déclenchée par le timer chaque seconde
void FrameGrid::OnTimer(wxTimerEvent& event)
{
    client.sendAndReceiveData();  // Appeler la méthode d'envoi et de réception
    UpdateSizer();  // Mettre à jour l'affichage après réception des données
}

void FrameGrid::OnKeyDown(wxKeyEvent& event)
{
    // Si la touche f12 (WXK_F12) est pressée
    if (event.GetKeyCode() == WXK_F12)
    {
        this->Close(); // Ferme la fenêtre principale

        // Ouvre la fenêtre de fin
        EndFrame* endFrame = new EndFrame("Fin de l'application");
        endFrame->Show(true);
    }
    else
    {
        event.Skip(); // Laisse les autres touches passer à d'autres handlers
    }
}
void FrameGrid::OnGlobalKey(wxCommandEvent& event)
{
    this->Close(); // Ferme la fenêtre principale
    EndFrame* endFrame = new EndFrame("Fin de l'application");
    endFrame->Show(true);
}