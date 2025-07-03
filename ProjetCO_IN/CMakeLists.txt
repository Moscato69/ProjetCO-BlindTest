cmake_minimum_required(VERSION 3.16)
project(ProjetCO_IN)

# Utilise le standard C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recherche wxWidgets statique installé avec make install
# Tu n'as pas besoin de set(wxWidgets_ROOT_DIR ...) si tu as fait sudo make install
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Inclut les réglages wxWidgets dans le projet
include(${wxWidgets_USE_FILE})

# Définir les fichiers sources
set(SOURCE_FILES
        main.cpp
        TeamsData.cpp TeamsData.hpp
        Frame.cpp Frame.hpp
        Window.cpp Window.h
)

# Crée l'exécutable
add_executable(ProjetCO_IN ${SOURCE_FILES})

# Lien avec wxWidgets (librairies statiques trouvées par find_package)
target_link_libraries(ProjetCO_IN ${wxWidgets_LIBRARIES})


