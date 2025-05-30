

#ifndef TEAMSDATA_HPP
#define TEAMSDATA_HPP

#include <cstdint>
#include <string>
#include <cstring>  // Pour memcpy

class TeamsData {
private:
    std::string Nom{};
    uint32_t Numéro{};
    uint32_t Score{};
    uint32_t IsUsed{};

public:
    std::string GetNom()  { return Nom; }
    std::string setNom(const std::string& nom) {
        Nom = nom;
        return Nom;  // Renvoie le nom après modification
    }

    uint32_t GetNuméro()  { return Numéro; }
    uint32_t setNuméro(uint8_t numéro) {
        Numéro = numéro;
        return Numéro;  // Renvoie le numéro après modification
    }

    uint32_t GetScore()  { return Score; }
    uint32_t setScore(uint32_t score) {
        Score = score;
        return Score;  // Renvoie le score après modification
    }

    uint32_t GetIsUsed()  { return IsUsed; }
    uint32_t SetIsUsed() {
        IsUsed = 1;
        return Score;  // Renvoie le score après modification
    }
    uint32_t ResetIsUsed()
    {
        IsUsed = 0;
        return Score;
    }

    // Fonction pour sérialiser l'objet
    void serialize(char* buffer) const {
        // Sérialisation du Nom (chaine de caractères)
        memcpy(buffer, Nom.c_str(), Nom.size());
        buffer[Nom.size()] = '\0';  // Assurez-vous de terminer la chaîne correctement

        // Sérialisation du Numéro
        memcpy(buffer + Nom.size() + 1, &Numéro, sizeof(Numéro));

        // Sérialisation du Score
        memcpy(buffer + Nom.size() + 1 + sizeof(Numéro), &Score, sizeof(Score));
    }
};

#endif // TEAMSDATA_HPP
