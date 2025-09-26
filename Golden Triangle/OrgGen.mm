//
//  OrgGen.m
//  Golden Triangle
//
//  Created by Alex Bullard on 1/6/11.
//  Copyright 2011 Middlebury College. All rights reserved.
//

#import "OrgGen.h"
#import "BoundingPolygon.h"

@implementation OrgGen

//TODO change to instance of CityGLView
+ (void) masterGenerate:(NSView *)glView vertices:(vector<OrgVertex> &)vertices faces:(vector<OrgPolygon> &)faces pregenObjs:(OrgPregen &)pregenList{
	//NSMutableArray * polygons3D = [[NSMutableArray alloc] initWithObjects:nil];
	//vector<CityPolyObject> polygons3D = vector<CityPolyObject>(500);
	//OrgPregen pregenList = OrgPregen();
	[glView addLoadingMessage:@"building organization..."];
	[glView addLoadingMessage:@"generating voronoi diagrams..."];
	[OrgGen addPlane:vertices f:faces];
	pair<list<list<JPoint> >, pair<list<Segment>,list<Segment> > > city = GenerateVoronoi(RANDSEED, NUMCONTROL, MINX, MAXX, MINZ, MAXZ);
	[glView addLoadingMessage:@"creating departments..."];
	double cx = MINX + (MAXX-MINX)/2;
	double cz = MINZ + (MAXZ-MINZ)/2;
	
	double maxDist = MAXX-cx + MAXZ - cz;
	
	[OrgGen addOrgDepartments:vertices f:faces diagram:city.first centerX:cx z:cz maxDist:maxDist];
	[glView addLoadingMessage:@"establishing connections..."];

	//list<pair<JPoint, double> > stoplightPos;
	for(list<Segment>::iterator sit = city.second.first.begin(); sit != city.second.first.end(); ++sit){
		ConnectionObject * tmp = [[ConnectionObject alloc] initWithEndPoints:6.0 x1:(*sit).p.x y1:-.9 z1:(*sit).p.y x2:(*sit).q.x y2:-0.9 z2:(*sit).q.y];
		vector<OrgCoordinate> tmpV = [tmp intersections];
		if ([tmp connectionLength] > 5.0) {
			pregenList.coordinates[STOPLIGHT_INDEX].insert(pregenList.coordinates[STOPLIGHT_INDEX].end(), tmpV.begin(), tmpV.end());
		}
		[tmp connectionPoly:vertices f:faces];

	}
	for(list<Segment>::iterator sit = city.second.second.begin(); sit != city.second.second.end(); ++sit){
		ConnectionObject * tmp =[[ConnectionObject alloc] initWithEndPoints:3.0 x1:(*sit).p.x y1:-.9 z1:(*sit).p.y x2:(*sit).q.x y2:-0.9 z2:(*sit).q.y];
		vector<OrgCoordinate> tmpV = [tmp intersections];
		if ([tmp connectionLength] > 5.0) {
			pregenList.coordinates[STOPSIGN_INDEX].insert(pregenList.coordinates[STOPSIGN_INDEX].end(), tmpV.begin(), tmpV.end());
		}
		[tmp connectionPoly:vertices f:faces];
	}
}

+ (void) addPlane:(vector<OrgVertex> &)vertices f:(vector<OrgPolygon> &)faces {
	int startIndex = vertices.size();
	vertices.push_back(OrgVertex(-500.0, -1.0, -500.0));
	vertices.push_back(OrgVertex(-500.0, -1.0, 500.0));
	vertices.push_back(OrgVertex(500.0, -1.0, 500.0));
	vertices.push_back(OrgVertex(500.0, -1.0, -500.0));
	GLfloat dl[4] = {.1289,.3,.125,1.0};
	GLfloat sl[4] = {0.0,0.0,0.0,1.0};
	GLfloat el[4] = {0.0,0.0,0.0,1.0};
	int planeVerts[4] = {startIndex,startIndex+1,startIndex+2,startIndex+3};
	vector<int> vpv = vector<int>(planeVerts, planeVerts+sizeof(planeVerts)/sizeof(planeVerts[0]));
	faces.push_back(OrgPolygon(vpv,dl,sl,el));
}

+ (void) addOrgDepartments:(vector<OrgVertex> &)vertices f:(vector<OrgPolygon> &)faces diagram:(std::list<std::list<JPoint> >)polys centerX:(double)cx z:(double)cz maxDist:(double)mD{
	
	for(std::list<std::list<JPoint> >::iterator p = polys.begin(); p != polys.end(); ++p){
		int startIndex = vertices.size();
		for(std::list<JPoint>::iterator pit = (*p).begin(); pit != (*p).end(); ++pit){
			vertices.push_back(OrgVertex((*pit).x,-0.9,(*pit).y));
		}
		double x = (*p).front().x;
		double z = (*p).front().y;

		double dist = abs(cz-z) + abs(cx-x);
		double avgH = 2+30*[CityMath bell:dist/40 sigma:.7 mu:0];
		[DepartmentObject initWithBounds:vertices faces:faces startIndex:startIndex avgHeight:avgH];
	}
}

@end
