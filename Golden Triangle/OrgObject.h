/* Abstract class encasing all objects drawn in the organization
 *
 */

#import <Cocoa/Cocoa.h>
#import "OrgPoint.h"
#import "BoundingPolygon.h"
#import "OrgMath.h"

@interface OrgObject : NSObject {
	NSMutableArray * polygonList;
}

-(OrgObject *) init;
-(OrgObject *) initWithPolygons:(NSArray *)poly;
-(NSArray *) polygons;
-(void) addPolygon:(BoundingPolygon *)polygon;
-(void) dealloc;

@end
