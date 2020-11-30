#include "audiointerface.h"

#include <QDebug>

AudioInterface::AudioInterface():
    m_audio_input(0), m_audio_output(0), m_input(0)
{

}

AudioInterface::~AudioInterface()
{
    m_audio_output->stop();
    m_output = nullptr;

    delete m_audio_input;
    delete m_audio_output;
}

void AudioInterface::audio_init(QAudioDeviceInfo in, QAudioDeviceInfo out)
{
    m_format.setSampleRate(8000);                       //set frequency to 8000
    m_format.setChannelCount(1);                        //set channels to mono
    m_format.setSampleSize(8);//m_format.setSampleSize(16);                         //set sample size to 16 bit
    m_format.setSampleType(QAudioFormat::UnSignedInt);//m_format.setSampleType(QAudioFormat::UnSignedInt);  //Sample type as usigned integer sample
    m_format.setByteOrder(QAudioFormat::LittleEndian);  //Byte order
    m_format.setCodec("audio/pcm");                     //set codec as simple audio/pcm


    QAudioDeviceInfo infoIn = in;
    QAudioDeviceInfo infoOut = out;
    /*
    if (!infoIn.isFormatSupported(m_format))
    {
        //Default format not supported - trying to use nearest
        m_format = infoIn.nearestFormat(m_format);
    }

    if (!infoOut.isFormatSupported(m_format))
    {
       //Default format not supported - trying to use nearest
        m_format = infoOut.nearestFormat(m_format);
    }
*/
    qDebug() << "codec: " << m_format.codec();
    qDebug() << "sampleRate: " << m_format.sampleRate();
    qDebug() << "sampleSize: " << m_format.sampleSize();
    qDebug() << "sampleType: " << m_format.sampleType();
    qDebug() << "byteOrder: " << m_format.byteOrder();
    qDebug() << "bytePerFrame: " << m_format.bytesPerFrame();

    m_audio_input = new QAudioInput(infoIn, m_format);
    m_audio_output = new QAudioOutput(infoOut, m_format);

    m_output = m_audio_output->start();
}

void AudioInterface::audio_input_start()
{
    m_input = m_audio_input->start();

    //call data_ready_to_read when audio samples fill in inputbuffer
    connect(m_input, SIGNAL(readyRead()), this, SLOT(data_ready_to_read()));

    qDebug() << "start reading audio";
}

void AudioInterface::audio_input_stop()
{
    disconnect(m_input, SIGNAL(readyRead()), nullptr, nullptr);
    m_audio_input->stop();
    m_input = nullptr;

    qDebug() << "stop reading audio";
}

void AudioInterface::data_ready_to_read()
{
    //Return if audio input is null
    if(!m_audio_input)
        return;

    //Check the number of samples in input buffer
    qint64 sample_buffer_size = m_audio_input->bytesReady();

    //Limit sample size
    if(sample_buffer_size > 4096)
        sample_buffer_size = 4096;

    //char* temp_data = new char[sample_buffer_size];
    //Read sound samples from input device to buffer
    //int64 read_sample_buffer_size = m_input->read(temp_data, sample_buffer_size);

    // low_pass_filter(temp_data, sample_buffer_size);

    if(sample_buffer_size > 0)
    {
        //qDebug() <<  " sample ready: " << read_sample_buffer_size;
        //QByteArray data = QByteArray(temp_data);

        QByteArray data = m_input->read(sample_buffer_size);


        //this signal will be cathced in the Multicast class by the slot Multicast::data_audio_ready(QByteArray& i_data_audio)
        emit data_ready(data);
    }

    //delete[] temp_data;
}

void AudioInterface::audio_reproduce_audio(QByteArray& i_audio_data)
{
    m_output->write(i_audio_data, i_audio_data.size());
}

void AudioInterface::low_pass_filter(char *i_samples, int i_n_sample)
{
//    char* y = new char[i_n_sample];
//    *y = *i_samples;

}

void AudioInterface::check_sample_len_timeout()
{
    if(m_prev_samples_len == m_samples.size())
        //emit
}
