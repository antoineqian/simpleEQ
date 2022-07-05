//
//  RotarySliderWithLabels.hpp
//  Simple EQ - VST3
//
//  Created by Antoine Qian on 7/5/22.
//  Copyright © 2022 Hsian. All rights reserved.
//

#ifndef RotarySliderWithLabels_hpp
#define RotarySliderWithLabels_hpp
#include <JuceHeader.h>
#include "LookAndFeel.hpp"

struct RotarySliderWithLabels : juce::Slider {
    RotarySliderWithLabels(juce::RangedAudioParameter& rap, const juce::String& unitSuffix) : juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        juce::Slider::TextEntryBoxPosition::NoTextBox), param(&rap), suffix(unitSuffix){
        setLookAndFeel(&lnf);
    }
    ~RotarySliderWithLabels(){
        setLookAndFeel(nullptr);
    }
    struct LabelPos{
        float pos;
        juce::String label;
    };
    juce::Array<LabelPos> labels;
    void paint(juce::Graphics& g) override;
    juce::Rectangle<int> getSliderBounds() const;
    int getTextHeight() const {return 14;}
    juce::String getDisplayString() const;
private:
    LookAndFeel lnf;
    juce::RangedAudioParameter* param;
    juce::String suffix;
};
#endif /* RotarySliderWithLabels_hpp */
