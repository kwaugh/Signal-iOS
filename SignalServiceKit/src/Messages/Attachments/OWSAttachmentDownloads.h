//
//  Copyright (c) 2018 Open Whisper Systems. All rights reserved.
//

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kAttachmentDownloadProgressNotification;
extern NSString *const kAttachmentDownloadProgressKey;
extern NSString *const kAttachmentDownloadAttachmentIDKey;

@class SSKProtoAttachmentPointer;
@class TSAttachment;
@class TSAttachmentPointer;
@class TSAttachmentStream;
@class TSMessage;
@class YapDatabaseReadTransaction;
@class YapDatabaseReadWriteTransaction;

#pragma mark -

/**
 * Given incoming attachment protos, determines which we support.
 * It can download those that we support and notifies threads when it receives unsupported attachments.
 */
@interface OWSAttachmentDownloads : NSObject

- (NSArray<NSString *> *)attachmentsIdsForAttachments:(NSArray<TSAttachment *> *)attachments;

- (NSArray<TSAttachmentPointer *> *)
    saveAttachmentPointersForAttachmentProtos:(NSArray<SSKProtoAttachmentPointer *> *)attachmentProtos
                                  transaction:(YapDatabaseReadWriteTransaction *)transaction;

- (void)downloadAttachmentsForMessage:(TSMessage *)message
                          transaction:(YapDatabaseReadTransaction *)transaction
                              success:(void (^)(NSArray<TSAttachmentStream *> *attachmentStreams))success
                              failure:(void (^)(NSError *error))failure;

- (void)downloadAttachmentPointer:(TSAttachmentPointer *)attachmentPointer
                          success:(void (^)(NSArray<TSAttachmentStream *> *attachmentStreams))success
                          failure:(void (^)(NSError *error))failure;

@end

NS_ASSUME_NONNULL_END
