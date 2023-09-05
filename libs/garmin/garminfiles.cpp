#include <algorithm>
#include "garminfiles.h"

const std::string GarminFiles::kGarminPath = "Garmin";
const std::string GarminFiles::kGpxPath = "GPX";
const std::string GarminFiles::kCoursesPath = "Courses";
const std::string GarminFiles::kGpxExt = ".gpx";
const std::string GarminFiles::kCoursesExt = ".fit";

namespace fs = std::filesystem;
using namespace std;

GarminFiles::GarminFiles(const std::string &volRootPath) : m_volRootPath(volRootPath) { }

void GarminFiles::find()
{
    // reading gpx files
    std::string gpx_path{ m_volRootPath + "/" + kGarminPath + "/" + kGpxPath };
    findFilesInDir(gpx_path, m_gpxFiles, kGpxExt);

    // reading fit files
    std::string courses_path{ m_volRootPath + "/" + kGarminPath + "/" + kCoursesPath };
    findFilesInDir(courses_path, m_courseFiles, kCoursesExt);
}

std::vector<std::string> GarminFiles::gpxFiles() const
{
    return m_gpxFiles;
}

std::vector<std::string> GarminFiles::courseFiles() const
{
    return m_courseFiles;
}

void GarminFiles::findFilesInDir(const std::string &path, std::vector<std::string> &fileCollection,
                                 const string &ext)
{
    fileCollection.clear();
    fs::directory_entry dir = fs::directory_entry{ path };
    if (dir.is_directory()) {
        for (auto const &dir_entry : fs::directory_iterator(path)) {
            if (dir_entry.is_regular_file()) {
                auto s = dir_entry.path().extension().string();
                transform(s.begin(), s.end(), s.begin(), ::tolower);
                if (s == ext) {
                    fileCollection.push_back(dir_entry.path().string());
                }
            }
        }
    }
}
