#ifndef _GEOC_UPDATE_REQUESTS_H
#define _GEOC_UPDATE_REQUESTS_H

/** \ingroup App */
enum GEOC_APP_REQUEST_CODE
{
    GEOC_APP_NO_REQUEST,		// No action.
    GEOC_APP_REDISPLAY,			// Redraw the screen.
    GEOC_APP_STATUS_BAR_UPDATE 	// Redraw the status bar.
};

#endif //_GEOC_UPDATE_REQUESTS_H
