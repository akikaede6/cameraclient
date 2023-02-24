#include "decode.h"

#include <QDebug>
#include <QImage>

Decode::Decode(QObject *parent) : QObject(parent)
{
}

Decode::~Decode()
{
    decode(c, frame, NULL);
    av_parser_close(parser);
    avcodec_free_context(&c);
    av_frame_free(&frame);
    av_packet_free(&pkt);
}

void Decode::parse(char *_data, int _size)
{
    /* use the parser to split the data into frames */
    data_size = _size;
    data = (uint8_t*)(_data);
    while (data_size > 0) {
        ret = av_parser_parse2(parser, c, &pkt->data, &pkt->size,
                               data, data_size, AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0);
        if (ret < 0) {
            fprintf(stderr, "Error while parsing\n");
            return;
        }
        data      += ret;
        data_size -= ret;

        if (pkt->size)
            decode(c, frame, pkt);
    }
}

bool Decode::init()
{
    pkt = av_packet_alloc();
    if (!pkt) {
        fprintf(stderr, "packet alloc failed\n");
        return false;
    }

    /* set end of buffer to 0 (this ensures that no overreading happens for damaged MPEG streams) */
    memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    /* find the MPEG-1 video decoder */
    codec = avcodec_find_decoder(AV_CODEC_ID_H264);
    if (!codec) {
        fprintf(stderr, "Codec not found\n");
        return false;
    }

    parser = av_parser_init(codec->id);
    if (!parser) {
        fprintf(stderr, "parser not found\n");
        return false;
    }

    c = avcodec_alloc_context3(codec);
    if (!c) {
        fprintf(stderr, "Could not allocate video codec context\n");
        return false;
    }

    /* For some codecs, such as msmpeg4 and mpeg4, width and height
       MUST be initialized there because this information is not
       available in the bitstream. */

    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        return false;
    }

    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Could not allocate video frame\n");
        return false;
    }
    return true;
}

void Decode::decode(AVCodecContext *dec_ctx, AVFrame *frame, AVPacket *pkt)
{
    char buf[1024];
    int ret;

    ret = avcodec_send_packet(dec_ctx, pkt);
    if (ret < 0) {
        fprintf(stderr, "Error sending a packet for decoding\n");
        return;
    }

    while (ret >= 0) {
        ret = avcodec_receive_frame(dec_ctx, frame);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error during decoding\n");
            return;
        }

        printf("saving frame %3d\n", dec_ctx->frame_number);
        fflush(stdout);

        /* the picture is allocated by the decoder. no need to
           free it */
        QImage img = getQImageFromFrame(frame);
        emit dataAvaliable(img);
    }
}

QImage Decode::getQImageFromFrame(const AVFrame *pFrame) const
{
    // first convert the input AVFrame to the desired format

        SwsContext* img_convert_ctx = sws_getContext(
                                         pFrame->width,
                                         pFrame->height,
                                         (AVPixelFormat)pFrame->format,
                                         pFrame->width,
                                         pFrame->height,
                                         AV_PIX_FMT_RGB24,
                                         SWS_BICUBIC, NULL, NULL, NULL);
        if(!img_convert_ctx){
            qDebug() << "Failed to create sws context";
            return QImage();
        }

        // prepare line sizes structure as sws_scale expects
        int rgb_linesizes[8] = {0};
        rgb_linesizes[0] = 3*pFrame->width;

        // prepare char buffer in array, as sws_scale expects
        unsigned char* rgbData[8];
        int imgBytesSyze = 3*pFrame->height*pFrame->width;
        // as explained above, we need to alloc extra 64 bytes
        rgbData[0] = (unsigned char *)malloc(imgBytesSyze+64);
        if(!rgbData[0]){
            qDebug() << "Error allocating buffer for frame conversion";
            free(rgbData[0]);
            sws_freeContext(img_convert_ctx);
            return QImage();
        }
        if(sws_scale(img_convert_ctx,
                    pFrame->data,
                    pFrame->linesize, 0,
                    pFrame->height,
                    rgbData,
                    rgb_linesizes)
                != pFrame->height){
            qDebug() << "Error changing frame color range";
            free(rgbData[0]);
            sws_freeContext(img_convert_ctx);
            return QImage();
        }

        // then create QImage and copy converted frame data into it

        QImage image(pFrame->width,
                     pFrame->height,
                     QImage::Format_RGB888);

        for(int y=0; y<pFrame->height; y++){
            memcpy(image.scanLine(y), rgbData[0]+y*3*pFrame->width, 3*pFrame->width);
        }

        free(rgbData[0]);
        sws_freeContext(img_convert_ctx);
        image = image.scaled(pFrame->width / 2, pFrame->height / 2, Qt::KeepAspectRatio);
        return image;
}

