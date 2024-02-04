#include "volumeinfo.h"

VolumeInfo::VolumeInfo() : volumesList{ QStorageInfo::mountedVolumes() } { }

QStringList VolumeInfo::getVolumeNameList() const
{
    QStringList volumeNames;
    for (const QStorageInfo &storage : volumesList) {
        if (storage.isValid() && storage.isReady()) {
            volumeNames.append(storage.name());
        }
    }
    return volumeNames;
}
