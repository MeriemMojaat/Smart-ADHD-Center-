#include "playerframe.h"
#include <QtWidgets>
#include <qvideosurfaceformat.h>

PlayerFrame::PlayerFrame(QObject *parent)
    : QAbstractVideoSurface(parent)
    , imgFormat(QImage::Format_Invalid)
{

}

bool PlayerFrame::Videostart(const QVideoSurfaceFormat &format)
{
     // Extract the image format and size from the given video surface format.
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize size = format.frameSize();

    // Check that the image format is not invalid and that the frame size is not empty.

    if (imageFormat != QImage::Format_Invalid && !size.isEmpty())
    {
        this->imgFormat = imageFormat;
        QAbstractVideoSurface::start(format);
        return true;

    }
    else return false;
}

void PlayerFrame::fnClearPixmap()
{
    CapImage = QPixmap();
}

void PlayerFrame::stopVideo()
{
    QAbstractVideoSurface::stop();
    // Set the `CapImage` member variable to an empty QPixmap,
}

QList<QVideoFrame::PixelFormat> PlayerFrame::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    if (handleType == QAbstractVideoBuffer::NoHandle) {// If the handle type is "NoHandle", the video player can handle the following pixel formats.
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32
                << QVideoFrame::Format_ARGB32
                << QVideoFrame::Format_ARGB32_Premultiplied
                << QVideoFrame::Format_RGB565
                << QVideoFrame::Format_RGB555;
    }
    else
    {
        return QList<QVideoFrame::PixelFormat>();
    }
}

bool PlayerFrame::isFormatSupported(const QVideoSurfaceFormat &format) const
{
    QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(format.pixelFormat());
    QSize size = format.frameSize();

    return imageFormat != QImage::Format_Invalid && !size.isEmpty() && format.handleType() == QAbstractVideoBuffer::NoHandle;
}

bool PlayerFrame::present(const QVideoFrame &frame)
{
    // Check if the surface format and size matches the format and size of the input frame.
    if (surfaceFormat().pixelFormat() != frame.pixelFormat() || surfaceFormat().frameSize() != frame.size())
    {
        // If the formats do not match, set an error and stop the video playback.
        setError(IncorrectFormatError);
        stop();
        return false;
    }
    else
    {
        if (!CapImage.isNull())
        {
             fnSurfaceStopped(CapImage);
             //fnSurfaceStopped signal is emitted. This signal is used to notify the
             //application that the video surface has stopped, and that the last captured frame can be processed or displayed.
        }

        curFrame = frame;
        if (curFrame.map(QAbstractVideoBuffer::ReadOnly))
        {
            // Convert the current frame to a QImage.
            QImage image(
                    curFrame.bits(),
                    curFrame.width(),
                    curFrame.height(),
                    curFrame.bytesPerLine(),
                    imgFormat);
            // If `CapImage` is empty, initialize it with a copy of the converted image.
            if (CapImage.isNull())
            {
                    CapImage = QPixmap::fromImage(image.copy(image.rect()));
            }
            curFrame.unmap();
        }
        return true;
    }
}
