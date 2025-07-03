//
// Created by matthias on 21/05/25.
//

#include "EndFrame.hpp"
#include <wx/wx.h>
#include <wx/image.h>
#include <filesystem>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <cstdlib>    // pour getenv

EndFrame::EndFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    wxInitAllImageHandlers();

    Maximize(true);
    wxPanel* panel = new wxPanel(this, -1);

    wxImage image;

    // Récupération du répertoire Images depuis HOME
    const char* homeDir = std::getenv("HOME");
    if (homeDir == nullptr) {
        std::cerr << "Erreur : la variable d'environnement HOME n'est pas définie." << std::endl;
        new wxStaticText(panel, wxID_ANY, "Erreur : répertoire personnel introuvable", wxPoint(50, 50));
        return;
    }
    std::string folder = std::string(homeDir) + "/Images";

    std::string randomImage = GetRandomJpegFromFolder(folder);
    if (!randomImage.empty() && image.LoadFile(randomImage, wxBITMAP_TYPE_ANY)) {
        wxBitmap bitmap(image);
        new wxStaticBitmap(panel, wxID_ANY, bitmap, wxPoint(0, 0));
    } else {
        new wxStaticText(panel, wxID_ANY, "Erreur de chargement de l'image", wxPoint(50, 50));
    }
}

std::string EndFrame::GetRandomJpegFromFolder(const std::string& folderPath) {
    namespace fs = std::filesystem;
    std::vector<std::string> images;

    // Parcours des fichiers dans le dossier
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_regular_file())
            continue;

        auto ext = entry.path().extension().string();
        if (ext == ".jpeg" || ext == ".jpg" || ext == ".png") {
            images.push_back(entry.path().string());
            std::cout << "Trouvé : " << entry.path().string() << std::endl;
        }
    }

    // Aucun fichier trouvé
    if (images.empty()) {
        return "";
    }

    // Tirage aléatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> distr(0, images.size() - 1);

    return images[distr(gen)];
}
