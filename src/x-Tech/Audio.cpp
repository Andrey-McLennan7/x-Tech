#include "Audio.h"
#include <stb_vorbis.c>

#include <stdexcept>

namespace xTech
{
    void Audio::load_ogg(const std::string& path, std::vector<unsigned char>& buffer, ALenum& format, ALsizei& frequency)
    {
        int channels = 0;
        int sampleRate = 0;
        short* output = NULL;

        unsigned int samples = stb_vorbis_decode_filename(path.c_str(),
            &channels, &sampleRate, &output);

        if (samples == -1)
        {
            throw std::runtime_error("Failed to open file '" + path + "' for decoding");
        }

        // Record the format required by OpenAL
        if (channels < 2)
        {
            format = AL_FORMAT_MONO16;
        }
        else
        {
            format = AL_FORMAT_STEREO16;
        }

        // Copy (# samples) * (1 or 2 channels) * (16 bits == 2 bytes == short)
        buffer.resize(samples * channels * sizeof(short));
        memcpy(&buffer.at(0), output, buffer.size());

        // Record the sample rate required by OpenAL
        frequency = sampleRate;

        // Clean up the read data
        free(output);
    }

    void Audio::on_load()
    {
        ALenum format = 0;
        ALsizei freq = 0;

        std::vector<unsigned char> bufferData;

        load_ogg(this->get_path() + ".ogg", bufferData, format, freq);

        alGenBuffers(1, &this->m_id);

        alBufferData(this->m_id, format, &bufferData.at(0),
            static_cast<ALsizei>(bufferData.size()), freq);
    }
}