#pragma once

#include <vector>
#include <QString>
class GarminFiles
{
public:
    GarminFiles(const QString &volRootPath);

    // Constants for file paths
    inline static const QString kGarminPath{ "Garmin" };
    inline static const QString kGpxPath{ "GPX" };
    inline static const QString kCoursesPath{ "Courses" };
    inline static const QString kGpxExt{ "gpx" };
    inline static const QString kCoursesExt{ "fit" };

    void find();

    std::vector<QString> gpxFiles() const;
    std::vector<QString> courseFiles() const;

    void print() const;

    QString coursesPath() const;

    QString volRootPath() const;

    QString gpxPath() const;

private:
    void findFilesInDir(const QString &path, std::vector<QString> &fileCollection,
                        const QString &ext);

    const QString m_volRootPath;
    const QString m_gpxPath;
    const QString m_coursesPath;
    std::vector<QString> m_gpxFiles;
    std::vector<QString> m_courseFiles;
};
