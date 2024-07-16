#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class LevelMeterAudioProcessor  : public juce::AudioProcessor,
    public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    LevelMeterAudioProcessor();
    ~LevelMeterAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged(const String& parameterID, float newValue) override;
    AudioProcessorValueTreeState& getApvts() { return parameters; }
    std::vector<float> getRmsLevels();
    float getRmsLevel(const int channel) const;
private:
    LinearSmoothedValue<float> rmsLevelLeft, rmsLevelRight;
    AudioProcessorValueTreeState parameters;
    LinearSmoothedValue<float> gainLeft, gainRight;
    
    int rmsWindowSize = 50;
    double sampleRate = 44'100.0;
    bool isSmoothed = true;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeterAudioProcessor)
};
