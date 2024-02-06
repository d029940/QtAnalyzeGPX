#include <QDir>

#include "garminfiles.h"


namespace fs = std::filesystem;
using namespace std;

GarminFiles::GarminFiles(const QString &volRootPath) : m_volRootPath(volRootPath) { }

void GarminFiles::find()
{
    // reading gpx files
    QString gpx_path{ m_volRootPath + "/" + kGarminPath + "/" + kGpxPath };
    findFilesInDir(gpx_path, m_gpxFiles, kGpxExt);

    // reading fit files
    QString courses_path{ m_volRootPath + "/" + kGarminPath + "/" + kCoursesPath };
    findFilesInDir(courses_path, m_courseFiles, kCoursesExt);
}

std::vector<QString> GarminFiles::gpxFiles() const
{
    return m_gpxFiles;
}

std::vector<QString> GarminFiles::courseFiles() const
{
    return m_courseFiles;
}

void GarminFiles::findFilesInDir(const QString &path, std::vector<QString> &fileCollection,
                                 const QString &ext)
{
    fileCollection.clear();

    QDir pathDir = QDir(path);
    pathDir.setFilter(QDir::Files | QDir::QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QFileInfoList fileList = pathDir.entryInfoList();

    for (const QFileInfo &file : fileList) {
        if (file.suffix().toLower() == ext.toLower()) {
            fileCollection.push_back(file.absoluteFilePath());
        }
    }
}
