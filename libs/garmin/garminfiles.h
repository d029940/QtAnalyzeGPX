#pragma once

#include <string>
#include <vector>

class GarminFiles
{
public:
    GarminFiles(const std::string &volRootPath);
    void find();

    std::vector<std::string> gpxFiles() const;

    std::vector<std::string> courseFiles() const;

private:
    void findFilesInDir(const std::string &path, std::vector<std::string> &fileCollection,
                        const std::string &ext);

    static const std::string kGarminPath;
    static const std::string kGpxPath;
    static const std::string kCoursesPath;
    static const std::string kGpxExt;
    static const std::string kCoursesExt;
    const std::string m_volRootPath;
    std::vector<std::string> m_gpxFiles;
    std::vector<std::string> m_courseFiles;
};
