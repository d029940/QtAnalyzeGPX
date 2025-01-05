#include <QDir>

#include "garminfiles.h"


namespace fs = std::filesystem;
using namespace std;

GarminFiles::GarminFiles(const QString &volRootPath)
    : m_volRootPath(volRootPath),
      m_gpxPath{ m_volRootPath + "/" + kGarminPath + "/" + kGpxPath },
      m_coursesPath{ m_volRootPath + "/" + kGarminPath + "/" + kCoursesPath }
{
}

void GarminFiles::find()
{
    // reading gpx files
    QDir path = QDir(m_gpxPath);
    if (path.exists()) {
        findFilesInDir(m_gpxPath, m_gpxFiles, kGpxExt);
    }

    // reading fit files
    path = QDir(m_coursesPath);
    if (path.exists()) {
        findFilesInDir(m_coursesPath, m_courseFiles, kCoursesExt);
    }
}

std::vector<QString> GarminFiles::gpxFiles() const
{
    return m_gpxFiles;
}

std::vector<QString> GarminFiles::courseFiles() const
{
    return m_courseFiles;
}

void GarminFiles::print() const
{
    qDebug() << "GPX files on: " << m_volRootPath;
    for (const QString &file : m_gpxFiles) {
        qDebug() << "  " << file;
    }
    qDebug() << "Course files on: " << m_volRootPath;
    for (const QString &file : m_courseFiles) {
        qDebug() << "  " << file;
    }
    qDebug() << Qt::endl;
}

void GarminFiles::findFilesInDir(const QString &path, std::vector<QString> &fileCollection,
                                 const QString &ext)
{
    fileCollection.clear();

    QDir pathDir = QDir(path);
    pathDir.setFilter(QDir::Files | QDir::QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QFileInfoList fileList = pathDir.entryInfoList();

    for (const QFileInfo &file : std::as_const(fileList)) {
        if (file.suffix().toLower() == ext.toLower()) {
            fileCollection.push_back(file.absoluteFilePath());
        }
    }
}

QString GarminFiles::volRootPath() const
{
    return m_volRootPath;
}

QString GarminFiles::gpxPath() const
{
    return m_gpxPath;
}

QString GarminFiles::coursesPath() const
{
    return m_coursesPath;
}
