#include "AudioFile.h"
#include <math.h>
#include <vector>

using std::vector;

void writeSineWaveToAudioFile( const vector<float> frequenciesInHz = {440.f}, const float length=1.0, const float sampleRate = 44100.f);

int main()
{
    AudioFile<double> audioFile;

    // audioFile.load ("C:/Users/flori/Documents/MusicFinderFiles/file_example_1.wav");
    // audioFile.printSummary();

    vector<float> frequs = {300.f, 440.f, 410.f, 430.f, 550.f};

    writeSineWaveToAudioFile(frequs, 3.0);
}

void writeSineWaveToAudioFile(const vector<float> frequenciesInHz, const float length, const float sampleRate)
{
    //---------------------------------------------------------------
    std::cout << "**********************" << std::endl;
    std::cout << "Writing Sine Wave To Audio File" << std::endl;
    std::cout << "**********************" << std::endl << std::endl;
    
    //---------------------------------------------------------------
    // 1. Let's setup our AudioFile instance
    
    AudioFile<float> a;
    a.setNumChannels (2);
    a.setNumSamplesPerChannel (length*sampleRate);

    //---------------------------------------------------------------
    // 3. Write the samples to the AudioFile sample buffer
    
    vector<float>::const_iterator thisFrequ;

    for (int i = 0; i < a.getNumSamplesPerChannel(); i++)
    {
        for (int channel = 0; channel < a.getNumChannels(); channel++)
        {
            for(thisFrequ=frequenciesInHz.begin();thisFrequ!=frequenciesInHz.end();thisFrequ++)
            {
                a.samples[channel][i] += sin ((static_cast<float> (i) / sampleRate) * *thisFrequ * 2.f * M_PI);
            }
        }
    }
    
    //---------------------------------------------------------------
    // 4. Save the AudioFile
    
    std::string filePath = "sine-wave.wav"; // change this to somewhere useful for you
    a.save ("sine-wave.wav", AudioFileFormat::Wave);
}