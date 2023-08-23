#include <iostream>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
}

static double fraction2double(AVRational r)
{
    return r.den == 0 ? 0 : (double)r.num / r.den;
}

int main(int argc, char const *argv[])
{
    std::cout << "Hello, World!" << std::endl;
    AVFormatContext *fmt_ctx = nullptr;
    int videoStream = 0;
    int audioStream = 0;
    int totalMilliseconds = 0;

    const char *url = "C:\\Users\\icuxika\\Desktop\\test.mp4";
    int result;
    // 参数设置
    AVDictionary *options = nullptr;
    // 设置rtsp流以tcp协议打开
    av_dict_set(&options, "rtsp_transport", "tcp", 0);
    // 设置网络延时
    av_dict_set(&options, "max_delay", "500", 0);
    result = avformat_open_input(&fmt_ctx, url, nullptr, &options);
    if (result != 0)
    {
        char errbuf[64] = {0};
        std::cout << av_make_error_string(errbuf, 64, result) << std::endl;
        return 1;
    }
    // 获取流信息
    result = avformat_find_stream_info(fmt_ctx, nullptr);
    // 获取总时长（毫秒）
    totalMilliseconds = fmt_ctx->duration / (AV_TIME_BASE / 1000);
    // 获取总时长（秒）
    int totalSeconds = fmt_ctx->duration / AV_TIME_BASE;
    std::cout << "获取媒体总时长（秒）" << totalSeconds << std::endl;
    // 打印视频流信息
    av_dump_format(fmt_ctx, 0, url, 0);
    // 获取音视频流信息
    videoStream = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    AVStream *vStream = fmt_ctx->streams[videoStream];
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "视频信息（videoStream）" << videoStream << std::endl;
    std::cout << "视频宽度" << vStream->codecpar->width << std::endl;
    std::cout << "视频高度" << vStream->codecpar->height << std::endl;
    std::cout << "视频帧率FPS" << fraction2double(vStream->avg_frame_rate) << std::endl;
    std::cout << "视频像素格式" << vStream->codecpar->format << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;
    audioStream = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    AVStream *aStream = fmt_ctx->streams[audioStream];
    std::cout << "音频信息（audioStream）" << audioStream << std::endl;
    std::cout << "样本率" << aStream->codecpar->sample_rate << std::endl;
    std::cout << "音频采样格式" << aStream->codecpar->format << std::endl;
    std::cout << "声道数" << aStream->codecpar->channels << std::endl;
    std::cout << "编码格式" << aStream->codecpar->codec_id << std::endl;
    std::cout << "音频FPS" << fraction2double(aStream->avg_frame_rate) << std::endl;
    std::cout << "一帧音频的大小" << aStream->codecpar->frame_size << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    // 获取视频参数
    AVCodecParameters *codec_param = avcodec_parameters_alloc();
    avcodec_parameters_copy(codec_param, fmt_ctx->streams[videoStream]->codecpar);
    // 找到解码器
    const AVCodec *codec = avcodec_find_decoder(codec_param->codec_id);
    // 创建解码器上下文
    AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
    result = avcodec_parameters_to_context(codec_ctx, codec_param);
    std::cout << "avcodec_parameters_to_context result: " << result << std::endl;
    // 打开解码器
    result = avcodec_open2(codec_ctx, nullptr, nullptr);
    std::cout << "avcodec_open2 result: " << result << codec_ctx->codec_id << std::endl;

    AVPacket *packet = nullptr;
    while (packet == nullptr)
    {
        AVPacket *pkt = av_packet_alloc();
        result = av_read_frame(fmt_ctx, pkt);
        if (pkt->stream_index == videoStream)
        {
            packet = pkt;
        }
    }

    result = avcodec_send_packet(codec_ctx, packet);
    std::cout << "avcodec_send_packet result: " << result << std::endl;

    AVFrame *frame = av_frame_alloc();
    result = avcodec_receive_frame(codec_ctx, frame);

    std::cout << frame->width << std::endl;
    std::cout << frame->height << std::endl;

    int width = frame->width;
    int height = frame->height;
    struct SwsContext *swsCtx = sws_getContext(width, height, (AVPixelFormat)frame->format,
                                               width, height, AV_PIX_FMT_RGBA,
                                               SWS_BILINEAR, NULL, NULL, NULL);
    uint8_t *rgbaData[4];
    int rgbaLinesize[4];
    av_image_alloc(rgbaData, rgbaLinesize, width, height, AV_PIX_FMT_RGBA, 1);

    sws_scale(swsCtx, (const uint8_t * const*)frame->data, frame->linesize,
              0, height, rgbaData, rgbaLinesize);
    return 0;
}
