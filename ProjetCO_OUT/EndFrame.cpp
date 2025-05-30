//
// Created by matthias on 21/05/25.
//

#include "EndFrame.hpp"
#include <filesystem>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <bits/fs_fwd.h>

EndFrame::EndFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    wxInitAllImageHandlers();

    // Met la fenêtre en plein écran avec la barre de titre visible
    Maximize(true);

    wxPanel* panel = new wxPanel(this, -1);

    wxImage image;
    std::string folder = "/home/matthias/Bureau/ProjetCO_OUT/";
    std::string randomImage = GetRandomJpegFromFolder(folder);
    if (image.LoadFile(randomImage, wxBITMAP_TYPE_ANY)) {
        wxBitmap bitmap(image);
        new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(0, 0));
    } else {
        new wxStaticText(panel, wxID_ANY, "Erreur de chargement de l'image", wxPoint(50, 50));
    }
}

std::string EndFrame::GetRandomJpegFromFolder(const std::string& folderPath) {
    namespace fs = std::filesystem;
    std::vector<std::string> Images;

    // Parcours des fichiers dans le dossier
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            auto path = entry.path();
            if (path.extension() == ".jpeg" || path.extension() == ".jpg" || path.extension() == ".png") {
                Images.push_back(path.string());
                std::cout << path.string() << std::endl;
            }
        }
    }

    // Aucun fichier trouvé
    if (Images.empty()) {
        return "";
    }

    // Tirage aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, Images.size() - 1);

    return Images[distr(gen)];
}
