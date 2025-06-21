#pragma once

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>

class MusicManager : public QObject {
    Q_OBJECT

private:
    QString findMusicFile(const QString& fileName);
    void setupMediaPlayer();

    QMediaPlayer* mediaPlayer;
    QAudioOutput* audioOutput;

public:
    explicit MusicManager(QObject* parent = nullptr);
    ~MusicManager();

    bool loadBackgroundMusic(const QString& fileName, float volume = 0.3f);
    void play();
    void pause();
    void stop();
    void setVolume(float volume);
    bool isPlaying() const;


};