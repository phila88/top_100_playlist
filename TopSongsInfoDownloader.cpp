#include "TopSongsInfoDownloader.h"

#include <QXmlStreamReader>

namespace
{
const QUrl ITUNES_LIST("https://itunes.apple.com/us/rss/topsongs/limit=100/xml");
}

// TODO: need a refresh function to make a new list if there are changes on the website. Should be done with QtConcurrent::run or thread
TopSongsInfoDownloader::TopSongsInfoDownloader(QObject *parent) : QObject(parent)
{

}

void TopSongsInfoDownloader::downloadAllSongsInfo()
{
    QNetworkAccessManager *accessManager = new QNetworkAccessManager;
    connect(accessManager, static_cast<void (QNetworkAccessManager::*)(QNetworkReply*)>(&QNetworkAccessManager::finished),
            this, &TopSongsInfoDownloader::onReceive);
    connect(accessManager, static_cast<void (QNetworkAccessManager::*)(QNetworkReply*)>(&QNetworkAccessManager::finished),
            accessManager, &QNetworkAccessManager::deleteLater);

    accessManager->get(QNetworkRequest(QUrl(ITUNES_LIST)));
}

// TODO: There may be a better way to parse the xml. I don't have much experience parsing XML.
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

        if(xml.name() == "title") // song title
        {
            title = xml.readElementText();
        }
        else if(xml.name() == "artist") // artist name
        {
            artist = xml.readElementText();
        }
        else if(xml.name() == "link" // audio sample url
                && xml.attributes().hasAttribute("title")
                && xml.attributes().value("title") == "Preview")
        {
            sampleUrl = xml.attributes().value("href").toString();
        }
        else if(xml.name() == "image" // artist/album/single image
                && xml.attributes().value("height") == "60")
        {
            imageUrl = xml.readElementText();
            title.remove(" - " + artist);
            SongData data(title, artist, imageUrl, sampleUrl);
            m_songs.append(data);
        }
    }

    // TODO: need to let UI know parsing failed
    if (xml.hasError())
    {
        qDebug() << "Parsing ERROR !!!!!!!!!!";
        return;
    }
    qDebug() << "Download complete";

    emit downloadComplete(m_songs);
}
