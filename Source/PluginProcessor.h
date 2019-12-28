/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioFeatureExtractor.hpp"
#include <fdeep/fdeep.hpp>
#include "BTrack/BTrack.h"

#include "essentia/algorithmfactory.h"
#include "essentia/essentiamath.h"
#include "essentia/pool.h"

#include "beat_detection/Source/Core/OnsetClassification.h"
#include "AudioLiveScrollingDisplay.h"

using namespace essentia;
using namespace essentia::standard;


//==============================================================================
/**
*/
class DeepboxAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DeepboxAudioProcessor();
    ~DeepboxAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void recordMidi (bool isRecording);
    void setOnsetSlider (Slider onsetSlider);
    void initialiseSynth();
    vector<MidiMessage> triggerKickDrum(MidiBuffer& midiMessages, double msPerTick) const;
    vector<MidiMessage> triggerSnareDrum(MidiBuffer& midiMessages, double msPerTick) const;
    vector<MidiMessage> triggerHihatDrum(MidiBuffer& midiMessages, double msPerTick) const;
    //==============================================================================
    bool hitkick = false;
    bool hitsnare = false;
    bool hithihat = false;
    LiveScrollingAudioDisplay liveAudioScroller;
    Slider onset_threshold_slider;
    ImageButton mykickButton{"kick"};
    ImageButton mysnareButton{"snare"};
    ImageButton myhihatButton{"hihat"};
    ImageButton deepbox_text{"deepbox"};
    Image deepbox_text_img = ImageCache::getFromFile(File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile).getChildFile("Contents/Resources/deepbox_text.png").getFullPathName());
    Image draglips_text_img = ImageCache::getFromFile(File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile).getChildFile("Contents/Resources/draglips_text.png").getFullPathName());

private:
    
    const int kickNoteNumber = 36;
    const int snareNoteNumber = 38;
    const int hihatNoteNumber = 40;
    MidiOutput *midiOut;
    MidiOutput *midiIn;
    Synthesiser drumSynth;
    StringArray mididevices;
    OnsetClassification my_onset_detector;
    MidiMessageSequence mms;
    int tempo;
    int microsecondsPerQuarter;
    double msPerTick;
    double startTime;
    AudioPlayHead* playHead;
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    double sample_Rate;
    int samples_Per_Block;
    float floor_onset_threshold = -25;
    bool onset_below_floor_threshold = true;
    fdeep::model mymodel{fdeep::load_model(File::getSpecialLocation(File::SpecialLocationType::currentApplicationFile).getChildFile("Contents/Resources/my_deepbox_model_v2.json").getFullPathName().toStdString())};

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeepboxAudioProcessor)
};
