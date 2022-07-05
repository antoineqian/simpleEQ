//
//  LookAndFeel.hpp
//  Simple EQ - VST3
//
//  Created by Antoine Qian on 7/5/22.
//  Copyright © 2022 Hsian. All rights reserved.
//

#ifndef LookAndFeel_hpp
#define LookAndFeel_hpp

struct PowerButton : juce::ToggleButton {
    
};

struct AnalyzerButton : juce::ToggleButton {
    void resized() override{
        auto bounds = getLocalBounds();
        auto insetRect = bounds.reduced(4);
        randomPath.clear();
        juce::Random r;
        randomPath.startNewSubPath(insetRect.getX(), insetRect.getY() + insetRect.getHeight() * r.nextFloat());
        for (auto x  = insetRect.getX() + 1; x<insetRect.getRight(); x+=2){
            randomPath.lineTo(x, insetRect.getY() + insetRect.getHeight() * r.nextFloat());
        }
    };
    juce::Path randomPath;
};

struct LookAndFeel: juce::LookAndFeel_V4{
    
    void drawRotarySlider (juce::Graphics&,
                                   int x, int y, int width, int height,
                                   float sliderPosProportional,
                                   float rotaryStartAngle,
                                   float rotaryEndAngle,
                           juce::Slider&) override;
    void drawToggleButton (juce::Graphics& g, juce::ToggleButton& toggleButton, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
};
#endif /* LookAndFeel_hpp */
