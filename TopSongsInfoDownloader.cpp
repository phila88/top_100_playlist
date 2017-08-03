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
    QString sampleUrl;

    while(!xml.atEnd())
    {
        // Traverse over startelements
        if(xml.readNext() != QXmlStreamReader::StartElement)
        {
            continue;
        }

        if(xml.name() == "title")
        {
            title = xml.readElementText();
        }
        else if(xml.name() == "artist")
        {
            artist = xml.readElementText();
        }
        else if(xml.name() == "link"
                && xml.attributes().hasAttribute("title")
                && xml.attributes().value("title") == "Preview")
        {
            //qDebug() << xml.attributes().value("href");
            sampleUrl = xml.attributes().value("href").toString();
        }
        else if(xml.name() == "image"
                && xml.attributes().value("height") == "60")
        {
            imageUrl = xml.readElementText();
            title.remove(" - " + artist);
            SongData data(title, artist, imageUrl, sampleUrl);
            m_songs.append(data);
        }
    }
    if (xml.hasError()) {
        qDebug() << "HAD ERROR !!!!!!!!!!";
    }
    qDebug() << "Download complete";

    emit downloadComplete(m_songs);
}
