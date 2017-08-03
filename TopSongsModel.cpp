#include "TopSongsModel.h"

QHash<int, QByteArray> TopSongsModel::ROLE_NAMES({{TitleRole, "titleRole"},
                                                  {ArtistRole, "artistRole"},
                                                  {ImageRole, "imageRole"},
                                                  {SampleRole, "sampleRole"}});

TopSongsModel::TopSongsModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_songDownloader(new TopSongsInfoDownloader(this))
{
    m_songDownloader->downloadSongInfo();

    connect(m_songDownloader, &TopSongsInfoDownloader::downloadComplete, this, [this](QList<TopSongsInfoDownloader::SongData>& songData){
        m_songs = songData;
        qDebug() << "Reset model. Row count:" << rowCount();
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
    case SampleRole:
        return m_songs.at(index.row()).m_sampleUrl;
    default:
        qWarning() << "Invalid role:" << role;
    }

    return QVariant();
}
