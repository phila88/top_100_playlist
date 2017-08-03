#ifndef TOPSONGS_H
#define TOPSONGS_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

class TopSongsInfoDownloader : public QObject
{
    Q_OBJECT

public:
    explicit TopSongsInfoDownloader(QObject *parent = nullptr);

    struct SongData {
        QString m_title;
        QString m_artist;
        QString m_imageUrl;
        QString m_sampleUrl;

        SongData(QString title, QString name, QString imageUrl, QString sampleUrl)
            : m_title(title), m_artist(name), m_imageUrl(imageUrl), m_sampleUrl(sampleUrl)
        {}
    };

    void downloadAllSongsInfo();

public slots:
    void onReceive(QNetworkReply *response);

signals:
    void downloadComplete(QList<SongData>& songData);

private:
    QList<SongData> m_songs;
};

#endif // TOPSONGS_H
