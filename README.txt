Top 100 songs
by: Phillip Arthur

My goal was to try to make a desktop playlist that looked/acted like a phone app.
Currently it's just a simple listview showing the information for each song. When you click on a song
the intent was to play a sample. I couldn't get that to work because of this error:

defaultServiceProvider::requestService(): no service found for - "org.qt-project.qt.mediaplayer"

I also had trouble parsing the XML and that took alot of my time unfortunately.
I don't have any prior experience parsing XML.
I built it with Qt Creator 4.3.0 (Based on Qt 5.8.0 (GCC 5.3.1 20160406 (Red Hat 5.3.1-6), 64 bit) on Ubuntu 14.04
and not from the command line. I including everything except the pro.user file.

Please let the recruiter know if you have any questions so I can address them.

References:
  http://doc.qt.io/qt-5/qxmlstreamreader.html
  https://stackoverflow.com/questions/13302236/qt-simple-post-request
  view-source:https://itunes.apple.com/us/rss/topsongs/limit=100/xml
  https://wiki.qt.io/Download_Data_from_URL

