#ifndef DECODE_H
#define DECODE_H

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/avutil.h>
}
#include <QObject>

#define INBUF_SIZE 4096

class QImage;
class Decode : public QObject
{
    Q_OBJECT
public:
    explicit Decode(QObject *parent = nullptr);
    ~Decode();
    void parse(char *_data, int _size);
    bool init();

private:
    void decode(AVCodecContext *dec_ctx, AVFrame *frame, AVPacket *pkt);

    QImage getQImageFromFrame(const AVFrame* pFrame) const;

signals:
    void dataAvaliable(const QImage &image);

private:
    const char *outfilename;
    const AVCodec *codec;
    AVCodecParserContext *parser;
    AVCodecContext *c= NULL;
    AVFrame *frame;
    uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    uint8_t *data;
    size_t   data_size;
    int ret;
    int eof;
    AVPacket *pkt;
};

#endif // DECODE_H
