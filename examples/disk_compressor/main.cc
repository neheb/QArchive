#include <QCoreApplication>
#include <QDebug>
#include <QMetaMethod>
#include <QMetaObject>
#include <qarchivediskcompressor_p.hpp>
#include <qarchive_enums.hpp>

using QArchive::DiskCompressorPrivate;
static QMetaMethod getMethod(DiskCompressorPrivate *object , const char *function)
{
    auto metaObject = object->metaObject();
    return metaObject->method(metaObject->indexOfMethod(QMetaObject::normalizedSignature(function)));
}


int main(int ac, char **av)
{
    if(ac < 2) {
        qDebug() << "Usage: " << av[0] << " [ARCHIVE PATH] [FILE(S)]";
        return 0;
    }
    
    QCoreApplication app(ac, av);
    QString ArchivePath = QString(av[1]);
    QStringList Files;
    
    for(auto i = 2; i < ac ; ++i){
	    QString file = QString(av[i]);
	    Files.append(file);
    }

    /* Construct DiskCompressor Object. */
    DiskCompressorPrivate Compressor;
    Compressor.setFileName(ArchivePath);
    Compressor.addFiles(Files);
    
    /* Connect Signals with Slots (in this case lambda functions). */
    QObject::connect(&Compressor , &DiskCompressorPrivate::started , [&](){
        qInfo() << "[+] Starting Compressor... ";
    });
    QObject::connect(&Compressor , &DiskCompressorPrivate::finished , [&](){
        qInfo() << "[+] Compressed File(s) Successfully!";
        app.quit();
        return;
    });
    QObject::connect(&Compressor , &DiskCompressorPrivate::error , [&](short code , QString file){
        qInfo() << "[-] An error has occured :: " << code << " :: " << file;
        app.quit();
        return;
    });

    /* Start the Compressor. 
     * Note:
     *    You don't really have to worry about the event loop since all method calls 
     *    to the extractor object is queued and only gets executed when the event
     *    loop starts , most likely.
    */
    getMethod(&Compressor , "start()").invoke(&Compressor ,Qt::QueuedConnection);
    return app.exec();
}
