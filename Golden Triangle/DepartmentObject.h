//
//  DepartmentObject.h
//  Golden Triangle
//
//  Created by Alex Bullard on 1/7/11.
//  Copyright 2011 Middlebury College. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "OrgObject.h"
#import <cmath>
#import "BoundingPolygon.h"


#define MINHEIGHT 2

@interface DepartmentObject : OrgObject {
	// Department Vars
	//int numberOfTiers;
	//float * tierHeights;
	/*float departmentHeight;
	float windowSizeX;
	float windowSizeY;
	float windowSeperationX; 
	float windowSeperationY;*/
	//BoundingPolygon * basePolygon;
	//vector<OrgVertex> vertices;
	//vector<OrgPolygon> faces;
	//OrgPolyObject department;
}

+ (void) initWithBounds:(vector<OrgVertex> &)vertices faces:(vector<OrgPolygon> &)faces startIndex:(int)si avgHeight:(float)height;
+ (void) addWindowsToFace:(int)faceIndex v:(vector<OrgVertex> &)vertices f:(vector<OrgPolygon> &)faces wx:(double)windowSizeX wy:(double) windowSizeY sx:(double)windowSeparationX sy:(double)windowSeparationY;
//- (void) buildRectangularDepartment;
//- (void) buildCircularDepartment;
//- (OrgPolyObject) orgPoly;
//- (OrgPolyObject) addWindowsToFace:(OrgPolygon)face;
//- (NSArray *) polygons;

@end
