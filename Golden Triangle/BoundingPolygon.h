//
//  BoundingPolygon.h
//  Golden Triangle
//
//  Created by Alex Bullard on 1/6/11.
//  Copyright 2011 Middlebury College. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <vector>
#import "OrgMath.h"

using namespace std;

struct OrgNormal{
	float x,y,z;
	OrgNormal(){
		
	};
	OrgNormal(double _x, double _y, double _z){
		x = _x; y=_y; z=_z;
	}
};

struct OrgVertex{
	float x,y,z;
	vector<int> faces;
	OrgNormal vertexNormal;
	OrgVertex(double _x, double _y, double _z){
		x = _x; y =_y; z = _z;
		faces = vector<int>();
	}
	OrgVertex(){}
};

// Stores a location and a rotation
struct OrgCoordinate {
	float x,y,z,r;
	OrgCoordinate(double _x, double _y, double _z, double _r){
		x = _x; y =_y; z = _z; r=_r;
	}
	OrgCoordinate(){}	
};

struct OrgPolygon {
	vector<int> vertexList;
	OrgNormal faceNormal;
	GLfloat diffuseLight[4];
	GLfloat specularLight[4];
	GLfloat emissiveLight[4];

	OrgPolygon() {
		vertexList = vector<int>();
	}
	OrgPolygon(vector <int> &vl, GLfloat dl[], GLfloat sl[], GLfloat el[]) {
		vertexList = vector<int>(vl);
		for(int i=0; i<4; i++){
			diffuseLight[i] = dl[i];
			specularLight[i] = sl[i];
			emissiveLight[i] = el[i];
		}
	}
	/* create and calulate normal */
	OrgPolygon(vector <int> &vl, GLfloat dl[], GLfloat sl[], GLfloat el[], vector<OrgVertex> &vertices) {
		vertexList = vector<int>(vl);
		for(int i=0; i<4; i++){
			diffuseLight[i] = dl[i];
			specularLight[i] = sl[i];
			emissiveLight[i] = el[i];
		}
		calculateNormal(vertices);
	}
	
	/* create and calulate normal */
	OrgPolygon(vector <int> &vl, GLfloat dl[], GLfloat sl[], GLfloat el[], OrgNormal &fnormal) {
		vertexList = vector<int>(vl);
		for(int i=0; i<4; i++){
			diffuseLight[i] = dl[i];
			specularLight[i] = sl[i];
			emissiveLight[i] = el[i];
		}
		faceNormal = fnormal;
	}
	
	
	void calculateNormal(vector<OrgVertex> &vertices){
		OrgVertex a = vertices[vertexList[0]]; 
		OrgVertex b = vertices[vertexList[1]]; 
		OrgVertex c = vertices[vertexList[2]];
		double normx = (a.z-b.z)*(c.y-b.y)-(a.y-b.y)*(c.z-b.z);
		double normy = (a.x-b.x)*(c.z-b.z)-(a.z-b.z)*(c.x-b.x);
		double normz = (a.y-b.y)*(c.x-b.x)-(a.x-b.x)*(c.y-b.y);
		double normlength = sqrt(normx*normx+normy*normy+normz*normz);
		faceNormal = OrgNormal(normx /= normlength,normy /= normlength,normz /= normlength);
	}
};

struct OrgPolyObject {
	vector<OrgVertex> * vp;
	vector<OrgPolygon> * pp;
	vector<OrgVertex>  vertices;
	vector<OrgPolygon>  polygons;
	
	OrgPolyObject(vector<OrgVertex> &cv,vector<OrgPolygon> &cp) {
		vp = &cv;
		pp = &cp;
		vertices = *vp;
		polygons = *pp;
//		vertices = vector<OrgVertex>(cv);
//		polygons = vector<OrgPolygon>(cp);
	//	generateNormals();
	}
	OrgPolyObject(){
		
	}
	void generateNormals () {
		// Add faces to vertex definitions
		for (int i=0; i<polygons.size(); i++) {
			for (int j=0; j<polygons[i].vertexList.size(); j++) {
				vertices[polygons[i].vertexList[j]].faces.push_back(i);
			}
		}/*
		// Generate vertex normals NOT NORMALIZED!
		for (int i=0; i<vertices.size(); i++){
			double tx=0.0, ty=0.0,tz=0.0;
			for (int j=0; j<vertices[i].faces.size(); j++) {
				tx += polygons[vertices[i].faces[j]].faceNormal.x;
				ty += polygons[vertices[i].faces[j]].faceNormal.y;
				tz += polygons[vertices[i].faces[j]].faceNormal.z;
			}
			vertices[i].vertexNormal = OrgNormal(tx/vertices[i].faces.size(),ty/vertices[i].faces.size(),tz/vertices[i].faces.size());
		}*/
	}
};

struct OrgPregen {
	vector< vector<OrgCoordinate> > coordinates;
	
	OrgPregen(){
		coordinates = vector< vector<OrgCoordinate> >(2); //YOU SHOULD BE A CONSTANT
	}
};


@interface BoundingPolygon : NSObject {
	NSArray * coordinates;
	GLfloat emissive[4];
	float red;
	float green;
	float blue;
	bool border;
}

-(BoundingPolygon *) initWithCoord:(NSArray *)coord andColorRed:(float)r green:(float)g blue:(float)b border:(bool)bor;
-(BoundingPolygon *) initWithCoord:(NSArray *)coord andColorRed:(float)r green:(float)g blue:(float)b;
-(NSArray *) coordinates;
-(float) red;
-(float) green;
-(float) blue;
-(bool) border;
-(void) dealloc;

@end
