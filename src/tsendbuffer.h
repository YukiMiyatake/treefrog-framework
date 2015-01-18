#ifndef THTTPBUFFER_H
#define THTTPBUFFER_H

#include <QByteArray>
#include <TGlobal>
#include <TAccessLog>

class QFile;
class QFileInfo;
class QHostAddress;
class THttpHeader;


class T_CORE_EXPORT TSendBuffer
{
public:
    ~TSendBuffer();

    bool atEnd() const;
    void *getData(int &size);
    bool seekData(int pos);
    int prepend(const char *data, int maxSize);
    TAccessLogger &accessLogger() { return accesslogger; }
    const TAccessLogger &accessLogger() const { return accesslogger; }
    void release();

private:
    QByteArray arrayBuffer;
    QFile* bodyFile;
    bool fileRemove;
    TAccessLogger accesslogger;
    int startPos;

    TSendBuffer(const QByteArray &header, const QFileInfo &file, bool autoRemove, const TAccessLogger &logger);
    TSendBuffer(const QByteArray &header);
    TSendBuffer(int statusCode, const QHostAddress &address, const QByteArray &method);
    TSendBuffer();

    friend class TEpollSocket;
    Q_DISABLE_COPY(TSendBuffer)
};

#endif // THTTPBUFFER_H
