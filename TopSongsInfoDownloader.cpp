#include "TopSongsInfoDownloader.h"

#include <QXmlStreamReader>

namespace
{
const QUrl ITUNES_LIST("https://itunes.apple.com/us/rss/topsongs/limit=100/xml");
}

TopSongsInfoDownloader::TopSongsInfoDownloader(QObject *parent) : QObject(parent)
{

}

void TopSongsInfoDownloader::downloadSongInfo()
{
    QNetworkAccessManager *accessManager = new QNetworkAccessManager;
    connect(accessManager, static_cast<void (QNetworkAccessManager::*)(QNetworkReply*)>(&QNetworkAccessManager::finished),
            this, &TopSongsInfoDownloader::onReceive);
    connect(accessManager, static_cast<void (QNetworkAccessManager::*)(QNetworkReply*)>(&QNetworkAccessManager::finished),
            accessManager, &QNetworkAccessManager::deleteLater);

    accessManager->get(QNetworkRequest(QUrl(ITUNES_LIST)));
}

void TopSongsInfoDownloader::onReceive(QNetworkReply* response)
{
    QByteArray bytes = response->readAll();

    QXmlStreamReader xml(bytes);
    QString title;
    QString artist;
    QString imageUrl;

    while(!xml.atEnd()) {
        xml.readNext();
        if(xml.name() == "title")
        {
            //qDebug() << count << "NAME:" << xml.name() << "TITLE:" << xml.readElementText();
            title = xml.readElementText();
        }
        if(xml.name() == "artist")
        {
            //qDebug() << count << "NAME:" << xml.name() << "ARTIST:" << xml.readElementText();
            artist = xml.readElementText();
        }
        if(xml.name() == "image")
        {
            auto url = xml.readElementText();
            if(url.contains("55x55"))
            {
                //qDebug() << count << "NAME:" << xml.name() << "IMAGE:" << imageUrl;
                imageUrl = url;
                SongData data(title, artist, imageUrl);
                m_songs.append(data);
            }
        }
    }
    if (xml.hasError()) {
        qDebug() << "HAD ERROR !!!!!!!!!!";
    }
    qDebug() << "DONE !!!!!!!!";
    //for(auto song : m_songs)
        //qDebug() << "T:" << song.m_title << "A:" << song.m_artist << "U:" << song.m_imageUrl;

    emit downloadComplete(m_songs);
}
