//
//  OrgGen.h
//  Golden Triangle
//
//  Created by Alex Bullard on 1/6/11.
//  Copyright 2011 Middlebury College. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "DepartmentObject.h"
#import "PlaneObject.h"
#import "ConnectionObject.h"
#import "voronoi.h"
#import "OrgGLView.h"
#import "FileIO.h"
#import <vector>

using namespace std;

#define MINX -100
#define MAXX 100
#define MINZ -200
#define MAXZ 0
#define RANDSEED 32
#define NUMCONTROL 10
@interface OrgGen : NSObject {

}

+ (void) masterGenerate:(NSView *)glView vertices:(vector<OrgVertex> &)vertices faces:(vector<OrgPolygon> &)faces pregenObjs:(OrgPregen &)pregenList;
+ (void) addPlane:(vector<OrgVertex> &)vertices f:(vector<OrgPolygon> &)faces;
+ (void) addOrgDepartments:(vector<OrgVertex> &)vertices f:(vector<OrgPolygon> &)faces diagram:(std::list<std::list<JPoint> >)polys centerX:(double)cx z:(double)cz maxDist:(double)mD;
@end
