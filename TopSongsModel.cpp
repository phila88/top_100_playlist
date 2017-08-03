#include "TopSongsModel.h"

QHash<int, QByteArray> TopSongsModel::ROLE_NAMES({{TitleRole, "titleRole"},
                                                  {ArtistRole, "artistRole"},
                                                  {ImageRole, "imageRole"}});

TopSongsModel::TopSongsModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_songDownloader(new TopSongsInfoDownloader(this))
{
    m_songDownloader->downloadSongInfo();

    connect(m_songDownloader, &TopSongsInfoDownloader::downloadComplete, this, [this](QList<TopSongsInfoDownloader::SongData>& songData){
        m_songs = songData;
        qDebug() << "Reset model" << rowCount();
        beginResetModel();
        endResetModel();
    });
}

QHash<int, QByteArray> TopSongsModel::roleNames() const
{
    return ROLE_NAMES;
}

int TopSongsModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return m_songs.size();
}

QVariant TopSongsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    switch(role)
    {
    case TitleRole:
        return m_songs.at(index.row()).m_title;
    case ArtistRole:
        return m_songs.at(index.row()).m_artist;
    case ImageRole:
        return m_songs.at(index.row()).m_imageUrl;
    default:
        qWarning() << "Invalid role";
    }

    return QVariant();
}

bool TopSongsModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endInsertRows();

    return true;
}

bool TopSongsModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    // FIXME: Implement me!
    endRemoveRows();

    return false;
}
