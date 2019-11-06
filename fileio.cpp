#include "fileio.h"

void saveSettings()
{
    std::ofstream file;
    file.open(SETTINGS_FILE_NAME);
    file << p1 << std::endl
         << p2 << std::endl
         << minRadius << std::endl
         << maxRadius << std::endl
         << MINY << std::endl
         << MAXY << std::endl
         << ENDLINE << std::endl
         << WORKING_DELTA << std::endl
         << GATE_DELTA << std::endl
         << kx << std::endl
         << winWidth << std::endl
         << winHeight << std::endl;
    file.close();
    std::cout << "Settings saved!" << std::endl;
}

void loadSettings()
{
    std::ifstream file;
    file.open(SETTINGS_FILE_NAME);
    if (!file.is_open())
    {
        std::cout << "Error opening settings file" << std::endl;
        setupTrackbars();
        return;
    }

    file >> p1 >> p2 >> minRadius >> maxRadius >> MINY >> MAXY >> ENDLINE
            >> WORKING_DELTA >> GATE_DELTA >> kx >> winWidth >> winHeight;
    file.close();
    cv::destroyWindow(TRACKBARS_NAME);
    setupTrackbars();
    std::cout << "Settings loaded!" << std::endl;

}
