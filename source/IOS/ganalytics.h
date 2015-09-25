#ifndef GANALYTICS_H
#define GANALYTICS_H

#include <gglobal.h>

#ifdef __cplusplus
extern "C" {
#endif

void ganalytics_StartAnalytics(const char *apiKey,bool crash);
void ganalytics_SendScreen(const char *screenName);
void ganalytics_SendEvent(const char *eventCategory, const char *action, const char *label, int eventValue);
    
#ifdef __cplusplus
}
#endif

#endif
