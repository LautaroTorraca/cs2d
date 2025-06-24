#include "MusicManager.h"
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QUrl>

MusicManager::MusicManager(QObject* parent)
        : QObject(parent), mediaPlayer(nullptr), audioOutput(nullptr) {
}

MusicManager::~MusicManager() {
    if (mediaPlayer) {
        mediaPlayer->stop();
    }
}

bool MusicManager::loadBackgroundMusic(const QString& fileName, float volume) {
    QString musicPath = findMusicFile(fileName);
    if (musicPath.isEmpty()) {
        return false;
    }

    setupMediaPlayer();
    
    QUrl musicUrl;
    if (musicPath.startsWith(":/")) {
        musicUrl = QUrl("qrc" + musicPath);
    } else {
        musicUrl = QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath());
    }

    mediaPlayer->setSource(musicUrl);
    mediaPlayer->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(volume);

    connect(mediaPlayer, &QMediaPlayer::mediaStatusChanged, this,
            [this](QMediaPlayer::MediaStatus status) {
                if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia) {
                    mediaPlayer->play();
                }
            });

    return true;
}

void MusicManager::play() {
    if (mediaPlayer) {
        mediaPlayer->play();
    }
}

void MusicManager::pause() {
    if (mediaPlayer) {
        mediaPlayer->pause();
    }
}

void MusicManager::stop() {
    if (mediaPlayer) {
        mediaPlayer->stop();
    }
}

void MusicManager::setVolume(float volume) {
    if (audioOutput) {
        audioOutput->setVolume(volume);
    }
}

bool MusicManager::isPlaying() const {
    return mediaPlayer && mediaPlayer->playbackState() == QMediaPlayer::PlayingState;
}

QString MusicManager::findMusicFile(const QString& fileName) {
    QString resourcePath = ":/Music/" + fileName;
    QFile resourceFile(resourcePath);
    if (resourceFile.exists()) {
        return resourcePath;
    }

    QString appDir = QCoreApplication::applicationDirPath();
    QStringList fallbackPaths = {
            appDir + "/../client/Login/Assets/Music/" + fileName,
            appDir + "/../Login/Assets/Music/" + fileName,
            appDir + "/client/Login/Assets/Music/" + fileName,
            appDir + "/Login/Assets/Music/" + fileName,
            "client/Login/Assets/Music/" + fileName,
            "Login/Assets/Music/" + fileName,
            "Assets/Music/" + fileName,
            "Music/" + fileName,
            fileName
    };

    for (const QString& path : fallbackPaths) {
        QFile file(path);
        if (file.exists()) {
            return path;
        }
    }

    return QString();
}

void MusicManager::setupMediaPlayer() {
    if (!mediaPlayer) {
        audioOutput = new QAudioOutput(this);
        mediaPlayer = new QMediaPlayer(this);
        mediaPlayer->setAudioOutput(audioOutput);
    }
}
