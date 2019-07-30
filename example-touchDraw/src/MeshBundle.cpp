#include "MeshBundle.h";

MeshBundle::MeshBundle(int id_in) {
	id = id_in;

	ofMesh *newMesh = new ofMesh;
	mesh = *newMesh;

	mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
	mesh.enableColors();

	clr = ofColor::fromHsb(ofRandom(0, 255), 200, 255);
}