#pragma once
#include <QList>
#include <QStorageInfo>

class VolumeInfo
{
public:
    VolumeInfo();

    QStringList getVolumeNameList() const;

private:
    const QList<QStorageInfo> volumesList;
};
