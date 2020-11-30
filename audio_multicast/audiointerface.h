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

    void low_pass_filter(char* i_samples, int i_n_sample);

    //QAudioDeviceInfo m_input_device;
    //QAudioDeviceInfo m_output_device;
    QAudioFormat m_format;
    QAudioInput *m_audio_input;
    QAudioOutput *m_audio_output;
    QIODevice *m_input;
    QIODevice *m_output;

    QTimer m_timer_check_samples_len;

    QByteArray m_samples;
    int m_prev_samples_len;

signals:
    void data_ready(QByteArray&);

private slots:
    void data_ready_to_read();
    void check_sample_len_timeout();
};

#endif // AUDIOINTERFACE_H
