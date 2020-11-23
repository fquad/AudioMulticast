#include "audiointerface.h"

#include <QDebug>

AudioInterface::AudioInterface():
    m_input_device(QAudioDeviceInfo::defaultInputDevice()),
    m_output_device(QAudioDeviceInfo::defaultOutputDevice()),
    m_audio_input(0), m_audio_output(0), m_input(0)
{
    audio_init();

    m_output = m_audio_output->start();
}

AudioInterface::~AudioInterface()
{
    delete m_audio_input;
    delete m_audio_output;

    m_audio_output->stop();
    m_output = nullptr;
}

void AudioInterface::audio_init()
{
    m_format.setSampleRate(8000); //set frequency to 8000
    m_format.setChannelCount(1); //set channels to mono
    m_format.setSampleSize(16); //set sample size to 16 bit
    m_format.setSampleType(QAudioFormat::UnSignedInt); //Sample type as usigned integer sample
    m_format.setByteOrder(QAudioFormat::LittleEndian); //Byte order
    m_format.setCodec("audio/pcm"); //set codec as simple audio/pcm

    QAudioDeviceInfo infoIn(QAudioDeviceInfo::defaultInputDevice());
    if (!infoIn.isFormatSupported(m_format))
    {
        //Default format not supported - trying to use nearest
        m_format = infoIn.nearestFormat(m_format);
    }

    QAudioDeviceInfo infoOut(QAudioDeviceInfo::defaultOutputDevice());

    if (!infoOut.isFormatSupported(m_format))
    {
       //Default format not supported - trying to use nearest
        m_format = infoOut.nearestFormat(m_format);
    }

    m_audio_input = new QAudioInput(m_input_device, m_format);
    m_audio_output = new QAudioOutput(m_output_device, m_format);
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
    if(sample_buffer_size > 512) //4096
        sample_buffer_size = 512  ;

    char* temp_data = new char[sample_buffer_size];
    //Read sound samples from input device to buffer
    qint64 read_sample_buffer_size = m_input->read(temp_data, sample_buffer_size);

    // low_pass_filter(temp_data, sample_buffer_size);

    if(read_sample_buffer_size > 0)
    {
        QByteArray data = QByteArray(temp_data);

        //this signal will be cathced in the Mulicast class by the slot Multicast::data_audio_ready(QByteArray& i_data_audio)
        emit data_ready(data);
    }

    delete[] temp_data;
}

void AudioInterface::audio_reproduce_audio(QByteArray& i_audio_data)
{
    m_output->write(i_audio_data, i_audio_data.size());
}

void AudioInterface::low_pass_filter(char *i_samples, int i_n_sample)
{
//    char* y = new char[i_n_sample];
//    *y = *i_samples;
    char* _y = i_samples;
    int y[600];

    for(int i = 0; i<i_n_sample; ++i)
        y[i]=int(_y[i]);


    
    for(int i = 6; i < i_n_sample-6; ++i)
        _y[i] = char ( ( y[i] + y[i-1] + y[i+1] + y[i-2] + y[i+2] + y[i-3] + y[i+3] +
                 y[i-4] + y[i+4] + y[i-5] + y[i+5] + y[i-6] + y[i+6] )  * 1/13);
}
