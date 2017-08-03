#ifndef TOPSONGS_H
#define TOPSONGS_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class TopSongs : public QObject
{
    Q_OBJECT

public:
    explicit TopSongs(QObject *parent = nullptr);

    struct SongData {
        QString m_title;
        QString m_artist;
        QString m_imageUrl;

        SongData(QString title, QString name, QString imageUrl)
            : m_title(title), m_artist(name), m_imageUrl(imageUrl)
        {}
    };

    void downloadSongInfo();

public slots:
    void onReceive(QNetworkReply *response);

signals:
    void downloadComplete(QList<SongData>& songData);

private:
    QList<SongData> m_songs;
};

#endif // TOPSONGS_H
