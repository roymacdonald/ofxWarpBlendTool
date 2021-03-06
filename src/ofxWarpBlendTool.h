#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGlWarper.h"
#include "ofxModifierKeys.h"

#define OFX_WARP_BLEND_TOOL_MAX_HISTORY 100
namespace ofxWarpBlendTool {
	class SelectablePoint: public ofPoint {
	public:
		SelectablePoint(){
			selected = false;
		}
		bool selected;
	};	
	class BaseQuad{
	public:
		int index;
		SelectablePoint TL;
		SelectablePoint TR;
		SelectablePoint BL;
		SelectablePoint BR;
	};
	class InternalQuad : public BaseQuad{
	public:
		int x;
		int y;
	};	
	class ControlQuad : public BaseQuad{
	public:
		vector<InternalQuad*> internalQuads;
	};
	
	class HistoryEntry{
	public:
		float * verticesData;
		ofxXmlSettings guiData;
		ofxXmlSettings perspectiveData;	
	};

	
	class Controller{
		
	public:
		void setup(ofTexture * texture, string name = "Warp/Blend", float guiWidth = 400, ofPoint initialOffset = ofPoint(0,0));
		void draw();
		void drawGui();
		
		void keyPressed(ofKeyEventArgs & args);
		void keyReleased(ofKeyEventArgs & args);
		void mouseMoved(ofMouseEventArgs & args);
		void mouseDragged(ofMouseEventArgs & args);
		void mousePressed(ofMouseEventArgs & args);
		void mouseReleased(ofMouseEventArgs & args);
		
	protected:
		void onSave(bool & value);
		void onLoad(bool & value);
        void onResetPerspective(bool &value);
        void onResetMesh(bool &value);
		void onBlendChange(float & value);
		void onGridChange(int & value);
		void onCoordinatesChange(float & value);
		void onEnablePerpective(bool & value);
        void onGuiLinesThicknessChange(int & value);
        void onPerspectiveChange(ofxGLWarper::CornerLocation & cornerLocation);
		
		void selectVertex(float mouseX, float mouseY);
		ofPoint getInteractionOffset(float mouseX, float mouseY);
		void updateVertices();
		
        void resetVertices(bool saveInHistory = true);
		void saveVertices(float * handler);
		void loadVertices(float * handler);
		
        void resetPerspective(bool saveInHistory = true);
		void savePerspective(ofxXmlSettings & handler);
		void loadPerspective(ofxXmlSettings & handler);
        bool perspectiveHasChanged;
		
		void saveGUI(ofxXmlSettings & handler);
		void loadGUI(ofxXmlSettings & handler);
		bool guiHasChanged;
		
		void saveHistoryEntry();
		void loadHistoryEntry(int index);
		int historyIndex;
		
		vector<HistoryEntry* > history;
		
		void drawEvent(ofEventArgs& args);
		bool drawing, drawn;		

		ofTexture * texture;
        ofPoint initialOffset;
		ofxPanel gui;		
		ofxGLWarper perspective;
				
		ofVboMesh controlMesh;
		ofVboMesh internalMesh;
		
		vector<ControlQuad*> controlQuads;
		
		ofVec2f gridSize;
		ofVec2f resolution;
        		
		ofVec2f coordinatesStart;
		ofVec2f coordinatesEnd;
        
        float blendL, blendR, blendT, blendB;
        int guiLineThickness;
	
		string name, safename;
		string guiFile, perspectiveFile, meshFile;
		int lastClickTime;
		bool isMovingVertex;
		ofPoint interactionOffset, tempInteractionOffset;
		ofVec2f mouse;
				
		ofFbo guiHelperFbo;
        
    
		
		static string safe_string(string str) {
			string safe = str;
			for (int i = 0; i < strlen(str.c_str()); i++) {
				if (isalpha(str[i]))
					safe[i] = str[i];
				else
					safe[i] = '_';
			}
			return safe;
		}
	};
}