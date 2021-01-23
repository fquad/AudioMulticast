#ifndef AUDIOINTERFACE_H
#define AUDIOINTERFACE_H

#include <qaudioinput.h>
#include <qaudiooutput.h>
#include <QTimer>

class AudioInterface: public QObject
{
    Q_OBJECT
public:
    AudioInterface();
    ~AudioInterface();

    void audio_input_start();
    void audio_input_stop();
    void audio_init(QAudioDeviceInfo in, QAudioDeviceInfo out);
    void audio_reproduce_audio(QByteArray& i_audio_data);

private:

    void digital_processing(QByteArray& i_samples);

    //QAudioDeviceInfo m_input_device;
    //QAudioDeviceInfo m_output_device;
    QAudioFormat m_format;
    QAudioInput *m_audio_input;
    QAudioOutput *m_audio_output;
    QIODevice *m_input;
    QIODevice *m_output;

    QByteArray m_samples;

signals:
    void data_ready(QByteArray&);

private slots:
    void data_ready_to_read();
};

#endif // AUDIOINTERFACE_H
