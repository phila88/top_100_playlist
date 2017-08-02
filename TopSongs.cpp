#include "TopSongs.h"

#include <QXmlStreamReader>

TopSongs::TopSongs(QObject *parent) : QObject(parent)
{

}

void TopSongs::downloadSongInfo()
{
    QNetworkAccessManager * mgr = new QNetworkAccessManager;
    connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(onfinish(QNetworkReply*)));
    connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));

    mgr->get(QNetworkRequest(QUrl("https://itunes.apple.com/us/rss/topsongs/limit=100/xml")));
}

QList<TopSongs::SongData> TopSongs::getSongs()
{
    return m_songs;
}

void TopSongs::onfinish(QNetworkReply* rep)
{
    QByteArray bts = rep->readAll();
    QString str(bts);

    QXmlStreamReader xml(bts);
    int count = 0;
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
        ++count;
    }
    if (xml.hasError()) {
        qDebug() << "HAD ERROR !!!!!!!!!!";
    }
    qDebug() << "DONE !!!!!!!!";
    //for(auto song : m_songs)
        //qDebug() << "T:" << song.m_title << "A:" << song.m_artist << "U:" << song.m_imageUrl;

    emit downloadComplete(m_songs);
}
