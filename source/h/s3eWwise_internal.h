/*
 * Internal header for the s3eWwise extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#ifndef S3EWWISE_INTERNAL_H
#define S3EWWISE_INTERNAL_H

#include "s3eTypes.h"
#include "s3eWwise.h"
#include "s3eWwise_autodefs.h"

/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult s3eWwiseInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult s3eWwiseInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void s3eWwiseTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void s3eWwiseTerminate_platform();

s3eWwiseResult s3eWwiseSoundEngineInit_platform(s3eWwiseInitSettings* in_pSettings, s3eWwisePlatformInitSettings* in_pPlatformSettings);

void s3eWwiseSoundEngineGetDefaultPlatformInitSettings_platform(s3eWwisePlatformInitSettings* out_settings);

#endif /* !S3EWWISE_INTERNAL_H */