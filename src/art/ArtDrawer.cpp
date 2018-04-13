#include "ArtDrawer.h"
#include "frames/Art1.h"
#include "frames/Art2.h"
#include "frames/Art3.h"

using namespace iFish;

ArtDrawer::ArtDrawer()
{
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Art Drawer init");

	arts.push_back(BaseArtPtr(new Art1()));
	//arts.push_back(BaseArtPtr(new Art2()));
	arts.push_back(BaseArtPtr(new Art3()));

	currentArtIndex = 0;
	currentArt = arts[currentArtIndex];

	holst.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	endTime = 1 * 5;
	startTime = ofGetElapsedTimef();

}

void ArtDrawer::init(ConfigPtr config)
{

}

void ArtDrawer::update()
{
	if (ofGetElapsedTimef() - startTime >= endTime)
	{
		startTime = ofGetElapsedTimef();
		updateFBO();
	}
	currentArt->update();
}

void ArtDrawer::draw()
{
	currentArt->showBackground();
	//holst.draw(0, 0);
	currentArt->draw();
}

void ArtDrawer::changeArt()
{
	currentArtIndex = (currentArtIndex + 1) % arts.size();
	currentArt = arts[currentArtIndex];
	clearArt();

	ofLog(ofLogLevel::OF_LOG_NOTICE, "Change Art...");
}

void ArtDrawer::changeColor()
{
	currentArt->changeColor();

	ofLog(ofLogLevel::OF_LOG_NOTICE, "Change Color...");
}

void ArtDrawer::addPointToArt(ofVec3f point)
{
	currentArt->addPoint(point);
}

void ArtDrawer::clearArt()
{
	currentArt->clear();
}

ofImage ArtDrawer::getArt() const {
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Get Art...");
	ofImage img;
	holst.readToPixels(img.getPixelsRef());
	img.update();
	return img;
}


void ArtDrawer::updateFBO()
{
	holst.begin();
	holst.draw(0, 0);
	currentArt->draw();
	holst.end();
	//currentArt->clear();
	ofLog(ofLogLevel::OF_LOG_NOTICE, "Save To FBO...");
}


ArtDrawer::~ArtDrawer()
{

}
