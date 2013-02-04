//
//  BackgroundWorker.h
//  Chattar
//
//  Created by kirill on 2/4/13.
//
//

#import <Foundation/Foundation.h>
#import "ChatViewController.h"
#import "MapViewController.h"
#import "AugmentedRealityController.h"
#import "QBChatMessageModel.h"
#import "QBCheckinModel.h"
#import "FBCheckinModel.h"
#import "PhotoWithLocationModel.h"
#import "JSON.h"

@protocol FBCheckinsDelegate <NSObject>
@optional
-(void)didReceiveFBCheckins:(NSArray*)fbCheckins;

@end

@protocol  QBGeodatasDelegate<NSObject>
@optional
-(void)didReceiveQBGeodatas:(NSArray*)qbGeodatas ;

@end

@protocol PhotosWithLocationsDelegate <NSObject>
@optional
-(void)didReceiveNewPhotosWithlocations:(NSArray*)photosWithLocations;
-(void)didReceiveCachedPhotosWithLocations:(NSArray*)photosWithLocations;
@end

@protocol QBChatMessagesDelegate <NSObject>
@optional

-(void)didReceiveCachedChatPoints:(NSArray*)cachedChatPoints;
-(void)didReceiveCachedChatMessagesIDs:(NSArray*)cachedChatMessagesIDs;
-(void)didReceiveQBChatMessages:(NSArray*)qbChatMessages;
-(void)willUpdate;

@end

@protocol MapControllerDelegate <NSObject>

@optional
-(void) didReceiveCachedMapPoints:(NSArray*)cachedMapPoints;
-(void) didReceiveCachedMapPointsIDs:(NSArray*)cachedMapIDs;
-(void) willAddNewPoint:(UserAnnotation*)point isFBCheckin:(BOOL)isFBCheckin;
-(void) willAddFBCheckin:(UserAnnotation*)checkin;
-(void) willShowMap;
@end

@protocol ChatControllerDelegate <NSObject>

@optional
-(void)willAddNewMessageToChat:(UserAnnotation*)annotation addToTop:(BOOL)toTop isFBCheckin:(BOOL)isFBCheckin;
-(void)willAddNewMessageToChat:(UserAnnotation*)annotation addToTop:(BOOL)toTop withReloadTable:(BOOL)reloadTable isFBCheckin:(BOOL)isFBCheckin;
@end

@protocol DataDelegate <NSObject>

@optional
-(void)didReceiveError;
-(void)endRetrievingData;

@end


@interface BackgroundWorker : NSObject<QBActionStatusDelegate,FBRequestDelegate,FBServiceResultDelegate>{
    NSTimer* updateTimer;
    short numberOfCheckinsRetrieved;
    short initState; // 2 if all data(map/chat) was retrieved
    
    dispatch_queue_t processCheckinsQueue;
    
    dispatch_queue_t processPhotosWithLocationsQueue;
}

@property (nonatomic, assign) id<PhotosWithLocationsDelegate,FBCheckinsDelegate,MapControllerDelegate,DataDelegate> mapDelegate;
@property (nonatomic, assign) id<QBGeodatasDelegate,QBChatMessagesDelegate,DataDelegate,ChatControllerDelegate> chatDelegate;

+(BackgroundWorker*)instance;
@end