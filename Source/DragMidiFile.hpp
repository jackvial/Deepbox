//
//  DragMidiFile.hpp
//  DrumPad - VST3
//
//  Created by eugene upston on 7/14/19.
//

#ifndef DragMidiFile_hpp
#define DragMidiFile_hpp

#include "../JuceLibraryCode/JuceHeader.h"

class DragMidiFile  :   public ImageButton,
                        public DragAndDropContainer

{
public:
    
    DragMidiFile(){};    
    void mouseDrag(const MouseEvent& e) override;
    
    ImageButton* imgBtnChangeOnDrag;
    Image* imgChangeOnDrag;

private:
    
};

#endif /* DragMidiFile_hpp */

