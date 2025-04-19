#include "playerwindow.h"
#include "ui_playerwindow.h"
#include <string>
#include <QFileDialog>


using std::to_string;
using std::string;

PlayerWindow::PlayerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerWindow), player(parent, QMediaPlayer::VideoSurface)
{
    ui->setupUi(this);

    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    layout = new QVBoxLayout();

    layout->addWidget(videoWidget);
    ui->groupBox_2->setLayout(layout);
    mediaPlayer->setVideoOutput(videoWidget);
    ui->directory->setIcon(QIcon(":/Resources/ui_icons/Add File.png"));

    connect(mediaPlayer, &QMediaPlayer::durationChanged, ui->hSliderVideo, &QSlider::setMaximum);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, ui->hSliderVideo, &QSlider::setValue);


    this->on_vSliderSound_valueChanged(50);

    pFrame = new PlayerFrame();
    player.setVideoOutput(pFrame);
}

PlayerWindow::~PlayerWindow()
{
    delete pFrame;
    delete mediaPlayer;
    delete layout;
    delete videoWidget;
    delete ui;
}

void PlayerWindow::on_BtnPlay_clicked()
{
    mediaPlayer->play();
    if(!filename.isEmpty()){
        videoWidget->resize(videoWidget->width()+1, videoWidget->height());
        videoWidget->resize(videoWidget->width()-1, videoWidget->height());

    }
    this->SetTimeLabel();

}

void PlayerWindow::on_BtnPause_clicked()
{
    mediaPlayer->pause();
    this->SetTimeLabel();
}

void PlayerWindow::on_BtnStop_clicked()
{
    mediaPlayer->stop();
    this->SetTimeLabel();
}

void PlayerWindow::on_comboBox_activated(int rate)
{
    qreal nowrate = 0;
    switch (rate) {
        case 0:
        {
            nowrate = 1;
            break;
        }
    case 1:
        {
            nowrate = 0.5;
            break;
        }
    case 2:
        {
            nowrate = 2;
            break;
        }
    }
        mediaPlayer->setPlaybackRate(nowrate);
}

void PlayerWindow::on_directory_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose videofile..","","*.mp4;*.mp3");
    QFile f(path);
    QFileInfo fileInfo(f.fileName());
    QString filename = fileInfo.fileName();

    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    ui->LblNowPlaying->setText(""+filename);

    player.setMedia(QUrl::fromLocalFile(path));

    connect(pFrame, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(GetFrame(QPixmap)),Qt::QueuedConnection);

    connect(this, SIGNAL(fnClearPixmap()),
            pFrame, SLOT(fnClearPixmap()),Qt::QueuedConnection);

}

void PlayerWindow::GetFrame(QPixmap pix)
{
    player.pause();
    pixmap = pix;
}

void PlayerWindow::SetTimeLabel()
{
    int seconds = static_cast<int>(mediaPlayer->duration()/1000);
    int minutes = 0, hours = 0;
    string stringData;

    if (hours > 9){
        stringData = to_string(hours) + ":";
    }else{
        stringData = to_string(hours) + "0:";
    }

    if((minutes = seconds / 60) > 0){
        seconds -= minutes * 60;
        if((hours = minutes / 60) > 0){
            minutes -= hours * 60;
        }
    }
    if(minutes > 9){
         stringData += to_string(minutes) + ":";
    }else{
        stringData += "0" + to_string(minutes) + ":";
    }
    if(seconds > 9){
         stringData += to_string(seconds);
    }else{
        stringData += "0" + to_string(seconds);
    }
    ui->endTime->setText(QString::fromStdString(stringData));

}

void PlayerWindow::on_vSliderSound_valueChanged(int value)
{
    mediaPlayer->setVolume(value);
    if(value == 0){
        ui->BtnMute->setIcon(QIcon(":/Resources/ui_icons/Mute_48px.png"));
    }else{
        ui->BtnMute->setIcon(QIcon(":/Resources/ui_icons/Voice_48px.png"));
    }
    ui->vSliderSound->setSliderPosition(value);
}

void PlayerWindow::on_hSliderVideo_sliderMoved(int position)
{
    qInfo() << "position is " << position ;
    mediaPlayer->setPosition(position);
}

void PlayerWindow::on_actionAdd_triggered()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose your file.","","*.mp4;*.mp3");
    mediaPlayer->setMedia(QUrl::fromLocalFile(path));

    ui->LblNowPlaying->setText(""+path);

    player.setMedia(QUrl::fromLocalFile(path));

    connect(pFrame, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(GetFrame(QPixmap)),Qt::QueuedConnection);

    connect(this, SIGNAL(fnClearPixmap()),
            pFrame, SLOT(fnClearPixmap()),Qt::QueuedConnection);
}

void PlayerWindow::on_actionPlay_triggered()
{
    mediaPlayer->play();
    videoWidget->resize(videoWidget->width()+1, videoWidget->height());
    videoWidget->resize(videoWidget->width()-1, videoWidget->height());
    this->SetTimeLabel();
}

void PlayerWindow::on_actionPause_triggered()
{
    mediaPlayer->pause();
}

void PlayerWindow::on_actionStop_triggered()
{
    mediaPlayer->stop();
    this->SetTimeLabel();
}

void PlayerWindow::on_actionExit_triggered()
{
    exit(0);
}

void PlayerWindow::on_actionInfo_triggered()
{
    QMessageBox mssInfo;
    mssInfo.setIcon(QMessageBox::Information);
    mssInfo.setText("This media player is developed by Harsha Madhushan Jayasinghe."
                    "This media player is support MP4 video files & mp3 audio files only."
                    "To work with the media player it is required to install codec software.");
    mssInfo.exec();
}

void PlayerWindow::on_BtnMute_clicked()
{
    mediaPlayer->setVolume(0);
    ui->vSliderSound->setSliderPosition(0);
}




