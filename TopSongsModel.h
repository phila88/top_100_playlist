#ifndef TOPSONGSMODEL_H
#define TOPSONGSMODEL_H

#include <QAbstractListModel>

#include "TopSongsInfoDownloader.h"

class TopSongsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles
    {
        TitleRole = Qt::UserRole,
        ArtistRole,
        ImageRole,
        SampleRole
    };
    Q_ENUMS(Roles)

    explicit TopSongsModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    static QHash<int, QByteArray> ROLE_NAMES;
    QList<TopSongsInfoDownloader::SongData> m_songs;
    TopSongsInfoDownloader* m_songDownloader;
};

#endif // TOPSONGSMODEL_H
